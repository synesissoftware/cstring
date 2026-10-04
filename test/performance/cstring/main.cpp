/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/test.performance.cstring/main.cpp
 *
 * Purpose: Competitive performance tests for cstring vs std::string and a
 *          hand-rolled realloc/memcpy floor. On Windows, the same scenarios
 *          also time the Global, process-heap, and COM task arenas. When
 *          p99 is available, also report per-iteration percentiles.
 *
 * Created: 23rd September 2026
 * Updated: 4th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>

#include "perf_harness.hpp"

#include <stlsoft/memory/auto_buffer.hpp>

#include <string>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

char const* const IMPL_CSTRING  = "cstring";
char const* const IMPL_STD      = "std::string";
char const* const IMPL_RAW      = "raw_realloc";
char const* const IMPL_BORROWED = "cstring_borrowed";
char const* const IMPL_FIXEDBUF = "fixed_char_buf";
#ifdef _WIN32

/* Realloc row is the ratio baseline. These arenas follow unit-test order
 * (global, process heap, COM task), which is also flag-value order.
 */
struct cstring_arena
{
    char const*     impl;
    cstring_flags_t flags;
};

cstring_arena const WINDOWS_CSTRING_ARENAS[] =
{
    { "cstring_win_global", CSTRING_F_USE_WINDOWS_GLOBAL_MEMORY },
    { "cstring_win_processheap", CSTRING_F_USE_WINDOWS_PROCESSHEAP_MEMORY },
    { "cstring_win_comtask", CSTRING_F_USE_WINDOWS_COM_TASK_MEMORY },
};
#endif /* _WIN32 */

size_t const SIZES[] =
{
    16u,
    64u,
    256u,
    4096u,
    65536u,
};

const size_t NUM_STACK_ELEMENTS = 512;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

namespace {

using namespace cstring_perf;

void
emit_row(
    char const*         scenario
,   size_t              size
,   char const*         impl
,   size_t              num_iterations
,   size_t              num_actions
,   run_result const&   r
,   interval_t          cstring_tm_ns
)
{
    char const* const baselines[] =
    {
        IMPL_CSTRING,
        IMPL_BORROWED,
    };

    cstring_perf::emit_row(
        scenario
    ,   size
    ,   impl
    ,   num_iterations
    ,   num_actions
    ,   r
    ,   cstring_tm_ns
    ,   baselines
    ,   STLSOFT_NUM_ELEMENTS(baselines)
    );
}

/* Windows rows share the scenario's realloc cstring total as the ratio
 * baseline. createEx / createLenEx selects the arena. Flags on a live
 * instance must not be written by the caller.
 */
template <typename F>
void
emit_windows_cstring_arenas(
    char const* scenario
,   size_t      size
,   size_t      num_iterations
,   size_t      num_warm_loops
,   size_t      num_actions
,   interval_t  baseline_ns
,   F           body
)
{
#ifdef _WIN32

    for (size_t i = 0; STLSOFT_NUM_ELEMENTS(WINDOWS_CSTRING_ARENAS) != i; ++i)
    {
        cstring_flags_t const flags = WINDOWS_CSTRING_ARENAS[i].flags;

        run_result const r = time_iterations(
            num_iterations
        ,   num_warm_loops
        ,   [&body, flags]() -> std::uint64_t
            {
                return body(flags);
            }
        );

        emit_row(
            scenario
        ,   size
        ,   WINDOWS_CSTRING_ARENAS[i].impl
        ,   num_iterations
        ,   num_actions
        ,   r
        ,   baseline_ns
        );
    }
#else /* ? _WIN32 */

    ((void)scenario);
    ((void)size);
    ((void)num_iterations);
    ((void)num_warm_loops);
    ((void)num_actions);
    ((void)baseline_ns);
    ((void)body);
#endif /* _WIN32 */
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * scenarios
 */

namespace {

void
scenario_create_destroy_empty(
    size_t num_iterations
,   size_t num_warm_loops
)
{
    run_result const cs = time_iterations(num_iterations, num_warm_loops, []() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        std::uint64_t const a = s.len;
        cstring_destroy(&s);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, []() -> std::uint64_t {
        std::string s;
        return s.size();
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, []() -> std::uint64_t {
        raw_string s;
        raw_init(&s);
        raw_assign_len(&s, "", 0);
        std::uint64_t const a = s.len;
        raw_destroy(&s);
        return a;
    });

    emit_row("create_destroy_empty", 0, IMPL_CSTRING, num_iterations, 1, cs, cs.tm_ns);
    emit_windows_cstring_arenas(
        "create_destroy_empty"
    ,   0
    ,   num_iterations
    ,   num_warm_loops
    ,   1
    ,   cs.tm_ns
    ,   [](cstring_flags_t flags) -> std::uint64_t
        {
            cstring_t s = cstring_t_DEFAULT;

            cstring_createEx(&s, "", flags, NULL, 0);

            std::uint64_t const a = s.len;

            cstring_destroy(&s);

            return a;
        }
    );
    emit_row("create_destroy_empty", 0, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("create_destroy_empty", 0, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_create_destroy_len(
    size_t n
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    std::string const payload = make_payload(n);
    char const* const p = payload.data();

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        cstring_createLen(&s, p, n);
        std::uint64_t const a = s.len + (NULL != s.ptr ? static_cast<unsigned char>(s.ptr[0]) : 0u);
        cstring_destroy(&s);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        std::string s(p, n);
        return s.size() + static_cast<unsigned char>(s[0]);
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        raw_string s;
        raw_init(&s);
        raw_assign_len(&s, p, n);
        std::uint64_t const a = s.len + static_cast<unsigned char>(s.ptr[0]);
        raw_destroy(&s);
        return a;
    });

    emit_row("create_destroy_len", n, IMPL_CSTRING, num_iterations, 1, cs, cs.tm_ns);
    emit_windows_cstring_arenas(
        "create_destroy_len"
    ,   n
    ,   num_iterations
    ,   num_warm_loops
    ,   1
    ,   cs.tm_ns
    ,   [p, n](cstring_flags_t flags) -> std::uint64_t
        {
            cstring_t s = cstring_t_DEFAULT;

            cstring_createLenEx(&s, p, n, flags, NULL, 0);

            std::uint64_t const a =
                s.len + (NULL != s.ptr ? static_cast<unsigned char>(s.ptr[0]) : 0u)
                ;

            cstring_destroy(&s);

            return a;
        }
    );
    emit_row("create_destroy_len", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("create_destroy_len", n, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_assign_len_grow(
    size_t n
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    std::string const payload = make_payload(n);
    char const* const p = payload.data();

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        cstring_assignLen(&s, p, n);
        std::uint64_t const a = s.len;
        cstring_destroy(&s);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        std::string s;
        s.assign(p, n);
        return s.size();
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        raw_string s;
        raw_init(&s);
        raw_assign_len(&s, p, n);
        std::uint64_t const a = s.len;
        raw_destroy(&s);
        return a;
    });

    emit_row("assign_len_grow", n, IMPL_CSTRING, num_iterations, 1, cs, cs.tm_ns);
    emit_windows_cstring_arenas(
        "assign_len_grow"
    ,   n
    ,   num_iterations
    ,   num_warm_loops
    ,   1
    ,   cs.tm_ns
    ,   [p, n](cstring_flags_t flags) -> std::uint64_t
        {
            cstring_t s = cstring_t_DEFAULT;

            cstring_createEx(&s, "", flags, NULL, 0);
            cstring_assignLen(&s, p, n);

            std::uint64_t const a = s.len;

            cstring_destroy(&s);

            return a;
        }
    );
    emit_row("assign_len_grow", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("assign_len_grow", n, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_append_len_growth(
    size_t chunk
,   size_t num_appends
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    std::string const payload = make_payload(chunk);
    char const* const p = payload.data();

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, chunk, num_appends]() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        cstring_create(&s, "");
        for (size_t i = 0; num_appends != i; ++i)
        {
            cstring_appendLen(&s, p, chunk);
        }
        std::uint64_t const a = s.len;
        cstring_destroy(&s);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [p, chunk, num_appends]() -> std::uint64_t {
        std::string s;
        for (size_t i = 0; num_appends != i; ++i)
        {
            s.append(p, chunk);
        }
        return s.size();
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [p, chunk, num_appends]() -> std::uint64_t {
        raw_string s;
        raw_init(&s);
        for (size_t i = 0; num_appends != i; ++i)
        {
            raw_append_len(&s, p, chunk);
        }
        std::uint64_t const a = s.len;
        raw_destroy(&s);
        return a;
    });

    char scenario[64];
    std::snprintf(scenario, sizeof(scenario), "append_len_growth_x%zu", num_appends);

    emit_row(scenario, chunk, IMPL_CSTRING, num_iterations, num_appends, cs, cs.tm_ns);
    emit_windows_cstring_arenas(
        scenario
    ,   chunk
    ,   num_iterations
    ,   num_warm_loops
    ,   num_appends
    ,   cs.tm_ns
    ,   [p, chunk, num_appends](cstring_flags_t flags) -> std::uint64_t
        {
            cstring_t s = cstring_t_DEFAULT;

            cstring_createEx(&s, "", flags, NULL, 0);

            for (size_t i = 0; num_appends != i; ++i)
            {
                cstring_appendLen(&s, p, chunk);
            }

            std::uint64_t const a = s.len;

            cstring_destroy(&s);

            return a;
        }
    );
    emit_row(scenario, chunk, IMPL_STD, num_iterations, num_appends, st, cs.tm_ns);
    emit_row(scenario, chunk, IMPL_RAW, num_iterations, num_appends, raw, cs.tm_ns);
}

void
scenario_append_len_reserved(
    size_t n
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    std::string const payload = make_payload(n);
    char const* const p = payload.data();
    size_t const chunk = (n < 16u) ? n : 16u;
    size_t const num_appends = (0 == chunk) ? 0u : (n / chunk);

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, chunk, n, num_appends]() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        cstring_create(&s, "");
        cstring_setCapacity(&s, n);
        for (size_t i = 0; num_appends != i; ++i)
        {
            cstring_appendLen(&s, p, chunk);
        }
        std::uint64_t const a = s.len;
        cstring_destroy(&s);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [p, chunk, n, num_appends]() -> std::uint64_t {
        std::string s;
        s.reserve(n);
        for (size_t i = 0; num_appends != i; ++i)
        {
            s.append(p, chunk);
        }
        return s.size();
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [p, chunk, n, num_appends]() -> std::uint64_t {
        raw_string s;
        raw_init(&s);
        raw_reserve(&s, n);
        for (size_t i = 0; num_appends != i; ++i)
        {
            raw_append_len(&s, p, chunk);
        }
        std::uint64_t const a = s.len;
        raw_destroy(&s);
        return a;
    });

    emit_row("append_len_reserved", n, IMPL_CSTRING, num_iterations, num_appends, cs, cs.tm_ns);
    emit_windows_cstring_arenas(
        "append_len_reserved"
    ,   n
    ,   num_iterations
    ,   num_warm_loops
    ,   num_appends
    ,   cs.tm_ns
    ,   [p, chunk, n, num_appends](cstring_flags_t flags) -> std::uint64_t
        {
            cstring_t s = cstring_t_DEFAULT;

            cstring_createEx(&s, "", flags, NULL, 0);
            cstring_setCapacity(&s, n);

            for (size_t i = 0; num_appends != i; ++i)
            {
                cstring_appendLen(&s, p, chunk);
            }

            std::uint64_t const a = s.len;

            cstring_destroy(&s);

            return a;
        }
    );
    emit_row("append_len_reserved", n, IMPL_STD, num_iterations, num_appends, st, cs.tm_ns);
    emit_row("append_len_reserved", n, IMPL_RAW, num_iterations, num_appends, raw, cs.tm_ns);
}

void
scenario_insert_len_mid(
    size_t n
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    std::string const base = make_payload(n);
    std::string const ins = make_payload(n / 4u == 0 ? 1u : n / 4u);
    char const* const bp = base.data();
    char const* const ip = ins.data();
    size_t const in = ins.size();
    int const pos = static_cast<int>(n / 2u);

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [bp, n, ip, in, pos]() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        cstring_createLen(&s, bp, n);
        cstring_insertLen(&s, pos, ip, in);
        std::uint64_t const a = s.len;
        cstring_destroy(&s);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [bp, n, ip, in, pos]() -> std::uint64_t {
        std::string s(bp, n);
        s.insert(pos, ip, in);
        return s.size();
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [bp, n, ip, in, pos]() -> std::uint64_t {
        raw_string s;
        raw_init(&s);
        raw_assign_len(&s, bp, n);
        raw_insert_len(&s, pos, ip, in);
        std::uint64_t const a = s.len;
        raw_destroy(&s);
        return a;
    });

    emit_row("insert_len_mid", n, IMPL_CSTRING, num_iterations, 1, cs, cs.tm_ns);
    emit_windows_cstring_arenas(
        "insert_len_mid"
    ,   n
    ,   num_iterations
    ,   num_warm_loops
    ,   1
    ,   cs.tm_ns
    ,   [bp, n, ip, in, pos](cstring_flags_t flags) -> std::uint64_t
        {
            cstring_t s = cstring_t_DEFAULT;

            cstring_createLenEx(&s, bp, n, flags, NULL, 0);
            cstring_insertLen(&s, pos, ip, in);

            std::uint64_t const a = s.len;

            cstring_destroy(&s);

            return a;
        }
    );
    emit_row("insert_len_mid", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("insert_len_mid", n, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_copy(
    size_t n
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    std::string const payload = make_payload(n);
    char const* const p = payload.data();

    cstring_t src_cs = cstring_t_DEFAULT;
    cstring_createLen(&src_cs, p, n);

    std::string const src_st(p, n);

    raw_string src_raw;
    raw_init(&src_raw);
    raw_assign_len(&src_raw, p, n);

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [&src_cs]() -> std::uint64_t {
        cstring_t d = cstring_t_DEFAULT;
        cstring_copy(&d, &src_cs);
        std::uint64_t const a = d.len;
        cstring_destroy(&d);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [&src_st]() -> std::uint64_t {
        std::string d(src_st);
        return d.size();
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [&src_raw]() -> std::uint64_t {
        raw_string d;
        raw_init(&d);
        raw_copy(&d, &src_raw);
        std::uint64_t const a = d.len;
        raw_destroy(&d);
        return a;
    });

    raw_destroy(&src_raw);

    emit_row("copy", n, IMPL_CSTRING, num_iterations, 1, cs, cs.tm_ns);
    /* cstring_copy allocates with the destination's existing flags, so a
     * default instance stays on realloc. createLenEx is the supported way
     * to duplicate a payload in a selected arena.
     */
    emit_windows_cstring_arenas(
        "copy"
    ,   n
    ,   num_iterations
    ,   num_warm_loops
    ,   1
    ,   cs.tm_ns
    ,   [&src_cs, n](cstring_flags_t flags) -> std::uint64_t
        {
            cstring_t d = cstring_t_DEFAULT;

            cstring_createLenEx(&d, src_cs.ptr, n, flags, NULL, 0);

            std::uint64_t const a = d.len;

            cstring_destroy(&d);

            return a;
        }
    );
    cstring_destroy(&src_cs);
    emit_row("copy", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("copy", n, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_borrowed_fixed_construct(
    size_t n
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    std::string const payload = make_payload(n);
    char const* const p = payload.data();

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        stlsoft::auto_buffer<char, NUM_STACK_ELEMENTS> buf(n + 1);
        cstring_t s = cstring_t_DEFAULT;
        cstring_createLenEx(
            &s
        ,   p
        ,   n
        ,   CSTRING_F_MEMORY_IS_BORROWED | CSTRING_F_MEMORY_IS_FIXED
        ,   &buf[0]
        ,   n + 1u
        );

        std::uint64_t const r = s.len + (s.len == 0 ? 0 : size_t(s.ptr[s.len - 1]));
        cstring_destroy(&s);

        return r;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        std::string s(p, n);

        return s.size() + (s.empty() ? 0 : size_t(s.back()));
    });

    run_result const fx = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        stlsoft::auto_buffer<char, NUM_STACK_ELEMENTS> buf(n + 1);
        ::memcpy(&buf[0], p, n);
        buf[n] = '\0';

        return n + (n == 0 ? 0 : size_t(buf[n - 1]));
    });

    emit_row("borrowed_fixed_construct", n, IMPL_BORROWED, num_iterations, 1, cs, cs.tm_ns);
    emit_row("borrowed_fixed_construct", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("borrowed_fixed_construct", n, IMPL_FIXEDBUF, num_iterations, 1, fx, cs.tm_ns);
}

void
scenario_borrowed_fixed_assign(
    size_t n
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    std::string const payload = make_payload(n);
    char const* const p = payload.data();

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        stlsoft::auto_buffer<char, NUM_STACK_ELEMENTS> buf(n + 1);
        cstring_t s = cstring_t_DEFAULT;
        cstring_createEx(
            &s
        ,   ""
        ,   CSTRING_F_MEMORY_IS_BORROWED | CSTRING_F_MEMORY_IS_FIXED
        ,   &buf[0]
        ,   n + 1u
        );
        cstring_assignLen(&s, p, n);
        std::uint64_t const r = s.len + (s.len == 0 ? 0 : size_t(s.ptr[s.len - 1]));
        cstring_destroy(&s);

        return r;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        std::string s;
        s.assign(p, n);

        return s.size() + (s.empty() ? 0 : size_t(s.back()));
    });

    run_result const fx = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        stlsoft::auto_buffer<char, NUM_STACK_ELEMENTS> buf(n + 1);
        ::memcpy(&buf[0], p, n);
        buf[n] = '\0';

        return n + (n == 0 ? 0 : size_t(buf[n - 1]));
    });

    emit_row("borrowed_fixed_assign", n, IMPL_BORROWED, num_iterations, 1, cs, cs.tm_ns);
    emit_row("borrowed_fixed_assign", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("borrowed_fixed_assign", n, IMPL_FIXEDBUF, num_iterations, 1, fx, cs.tm_ns);
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /*argc*/, char* /*argv*/[])
{
    size_t const num_iterations = cstring_perf::default_iterations();
    size_t const num_warm_loops = cstring_perf::default_warmups();

    // Fewer outer iters for heavy growth / large sizes
    size_t const heavy_iters =
        (num_iterations > 10000u) ? (num_iterations / 10u) : num_iterations
        ;

    cstring_perf::display_banner("test.performance.cstring");
#ifdef _WIN32

    std::cout
        << "  Windows arenas (ratio vs realloc cstring): cstring_win_global,"
        << std::endl
        << "  cstring_win_processheap, cstring_win_comtask."
        << std::endl
        << "  cstring_win_comtask loads and unloads OLE32 when no COM-task"
        << std::endl
        << "  allocation stays live across the call."
        << std::endl
        ;
#endif /* _WIN32 */
    cstring_perf::display_results_title();

    scenario_create_destroy_empty(num_iterations, num_warm_loops);

    for (size_t i = 0; STLSOFT_NUM_ELEMENTS(SIZES) != i; ++i)
    {
        size_t const n      =   SIZES[i];
        size_t const iters  =   (n >= 4096u) ? heavy_iters : num_iterations;

        scenario_create_destroy_len(n, iters, num_warm_loops);
        scenario_assign_len_grow(n, iters, num_warm_loops);
        scenario_append_len_reserved(n, iters, num_warm_loops);
        scenario_copy(n, iters, num_warm_loops);
        scenario_borrowed_fixed_construct(n, iters, num_warm_loops);
        scenario_borrowed_fixed_assign(n, iters, num_warm_loops);

        if (n <= 4096u)
        {
            scenario_insert_len_mid(n, iters, num_warm_loops);
            scenario_append_len_growth(16u, n / 16u == 0 ? 1u : n / 16u, heavy_iters, num_warm_loops);
        }
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */
