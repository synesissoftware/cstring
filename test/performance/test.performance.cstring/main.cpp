/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/test.performance.cstring/main.cpp
 *
 * Purpose: Competitive performance tests for cstring vs std::string and a
 *          hand-rolled realloc/memcpy floor. When p99 is available, also
 *          report per-iteration percentiles.
 *
 * Created: 23rd September 2026
 * Updated: 23rd September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>

#include "perf_harness.hpp"

#include <string>
#include <vector>

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

std::size_t const SIZES[] =
{
    16u,
    64u,
    256u,
    4096u,
    65536u,
};

} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

namespace {

using namespace cstring_perf;

struct run_result
{
    interval_t      tm_ns;
    std::uint64_t   anchor;
#ifdef HAS_P99

    p99::histogram  hist;
#endif /* HAS_P99 */
};

template <typename F>
run_result
time_iterations(
    std::size_t num_iterations
,   std::size_t num_warm_loops
,   F           fn
)
{
    run_result result = {};
    stopwatch_t sw;

    for (std::size_t w = num_warm_loops; 0 != w; --w)
    {
        result.anchor = 0;
#ifdef HAS_P99

        result.hist.clear();
#endif /* HAS_P99 */
        interval_t tm_ns = 0;
#ifdef HAS_P99

        for (std::size_t i = 0; num_iterations != i; ++i)
        {
            sw.start();
            result.anchor += fn();
            sw.stop();

            interval_t const sample = sw.get_nanoseconds();

            tm_ns += sample;
            (void)result.hist.push_ns(static_cast<std::uint64_t>(sample));
        }
#else /* ? HAS_P99 */

        sw.start();
        for (std::size_t i = 0; num_iterations != i; ++i)
        {
            result.anchor += fn();
        }
        sw.stop();
        tm_ns = sw.get_nanoseconds();
#endif /* HAS_P99 */

        if (1 == w)
        {
            result.tm_ns = tm_ns;
        }
    }

    return result;
}

void
emit_row(
    char const*     scenario
,   std::size_t     size
,   char const*     impl
,   std::size_t     num_iterations
,   std::size_t     num_actions
,   run_result const& r
,   interval_t      cstring_tm_ns
)
{
    double const ratio =
        (0 == ::strcmp(impl, IMPL_CSTRING))
            ? 1.0
            : ratio_or_dash(r.tm_ns, cstring_tm_ns)
            ;

    display_results(
        scenario
    ,   size
    ,   impl
    ,   num_iterations
    ,   num_actions
    ,   r.tm_ns
    ,   ratio
    ,   r.anchor
#ifdef HAS_P99
    ,   &r.hist
#endif /* HAS_P99 */
    );
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * scenarios
 */

namespace {

void
scenario_create_destroy_empty(
    std::size_t num_iterations
,   std::size_t num_warm_loops
)
{
    run_result const cs = time_iterations(num_iterations, num_warm_loops, []() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        cstring_create(&s, "");
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
    emit_row("create_destroy_empty", 0, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("create_destroy_empty", 0, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_create_destroy_len(
    std::size_t n
,   std::size_t num_iterations
,   std::size_t num_warm_loops
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
    emit_row("create_destroy_len", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("create_destroy_len", n, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_assign_len_grow(
    std::size_t n
,   std::size_t num_iterations
,   std::size_t num_warm_loops
)
{
    std::string const payload = make_payload(n);
    char const* const p = payload.data();

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        cstring_create(&s, "");
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
    emit_row("assign_len_grow", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("assign_len_grow", n, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_append_len_growth(
    std::size_t chunk
,   std::size_t num_appends
,   std::size_t num_iterations
,   std::size_t num_warm_loops
)
{
    std::string const payload = make_payload(chunk);
    char const* const p = payload.data();

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, chunk, num_appends]() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        cstring_create(&s, "");
        for (std::size_t i = 0; num_appends != i; ++i)
        {
            cstring_appendLen(&s, p, chunk);
        }
        std::uint64_t const a = s.len;
        cstring_destroy(&s);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [p, chunk, num_appends]() -> std::uint64_t {
        std::string s;
        for (std::size_t i = 0; num_appends != i; ++i)
        {
            s.append(p, chunk);
        }
        return s.size();
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [p, chunk, num_appends]() -> std::uint64_t {
        raw_string s;
        raw_init(&s);
        for (std::size_t i = 0; num_appends != i; ++i)
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
    emit_row(scenario, chunk, IMPL_STD, num_iterations, num_appends, st, cs.tm_ns);
    emit_row(scenario, chunk, IMPL_RAW, num_iterations, num_appends, raw, cs.tm_ns);
}

void
scenario_append_len_reserved(
    std::size_t n
,   std::size_t num_iterations
,   std::size_t num_warm_loops
)
{
    std::string const payload = make_payload(n);
    char const* const p = payload.data();
    std::size_t const chunk = (n < 16u) ? n : 16u;
    std::size_t const num_appends = (0 == chunk) ? 0u : (n / chunk);

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, chunk, n, num_appends]() -> std::uint64_t {
        cstring_t s = cstring_t_DEFAULT;
        cstring_create(&s, "");
        cstring_setCapacity(&s, n);
        for (std::size_t i = 0; num_appends != i; ++i)
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
        for (std::size_t i = 0; num_appends != i; ++i)
        {
            s.append(p, chunk);
        }
        return s.size();
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [p, chunk, n, num_appends]() -> std::uint64_t {
        raw_string s;
        raw_init(&s);
        raw_reserve(&s, n);
        for (std::size_t i = 0; num_appends != i; ++i)
        {
            raw_append_len(&s, p, chunk);
        }
        std::uint64_t const a = s.len;
        raw_destroy(&s);
        return a;
    });

    emit_row("append_len_reserved", n, IMPL_CSTRING, num_iterations, num_appends, cs, cs.tm_ns);
    emit_row("append_len_reserved", n, IMPL_STD, num_iterations, num_appends, st, cs.tm_ns);
    emit_row("append_len_reserved", n, IMPL_RAW, num_iterations, num_appends, raw, cs.tm_ns);
}

void
scenario_insert_len_mid(
    std::size_t n
,   std::size_t num_iterations
,   std::size_t num_warm_loops
)
{
    std::string const base = make_payload(n);
    std::string const ins = make_payload(n / 4u == 0 ? 1u : n / 4u);
    char const* const bp = base.data();
    char const* const ip = ins.data();
    std::size_t const in = ins.size();
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
    emit_row("insert_len_mid", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("insert_len_mid", n, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_copy(
    std::size_t n
,   std::size_t num_iterations
,   std::size_t num_warm_loops
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

    cstring_destroy(&src_cs);
    raw_destroy(&src_raw);

    emit_row("copy", n, IMPL_CSTRING, num_iterations, 1, cs, cs.tm_ns);
    emit_row("copy", n, IMPL_STD, num_iterations, 1, st, cs.tm_ns);
    emit_row("copy", n, IMPL_RAW, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_borrowed_fixed(
    std::size_t n
,   std::size_t num_iterations
,   std::size_t num_warm_loops
)
{
    std::string const payload = make_payload(n);
    char const* const p = payload.data();

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        std::vector<char> buf(n + 1u, '\0');
        cstring_t s = cstring_t_DEFAULT;
        cstring_createEx(
            &s
        ,   ""
        ,   CSTRING_F_MEMORY_IS_BORROWED | CSTRING_F_MEMORY_IS_FIXED
        ,   &buf[0]
        ,   n
        );
        cstring_assignLen(&s, p, n);
        std::uint64_t const a = s.len;
        cstring_destroy(&s);
        return a;
    });

    run_result const fx = time_iterations(num_iterations, num_warm_loops, [p, n]() -> std::uint64_t {
        std::vector<char> buf(n + 1u, '\0');
        std::memcpy(&buf[0], p, n);
        buf[n] = '\0';
        return n + static_cast<unsigned char>(buf[0]);
    });

    emit_row("borrowed_fixed_assign", n, IMPL_BORROWED, num_iterations, 1, cs, cs.tm_ns);
    emit_row("borrowed_fixed_assign", n, IMPL_FIXEDBUF, num_iterations, 1, fx, cs.tm_ns);
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /*argc*/, char* /*argv*/[])
{
    std::size_t const num_iterations = cstring_perf::default_iterations();
    std::size_t const num_warm_loops = cstring_perf::default_warmups();

    // Fewer outer iters for heavy growth / large sizes
    std::size_t const heavy_iters =
        (num_iterations > 10000u) ? (num_iterations / 10u) : num_iterations
        ;

    cstring_perf::display_banner("test.performance.cstring");
    cstring_perf::display_results_title();

    scenario_create_destroy_empty(num_iterations, num_warm_loops);

    for (std::size_t i = 0; STLSOFT_NUM_ELEMENTS(SIZES) != i; ++i)
    {
        std::size_t const n = SIZES[i];
        std::size_t const iters = (n >= 4096u) ? heavy_iters : num_iterations;

        scenario_create_destroy_len(n, iters, num_warm_loops);
        scenario_assign_len_grow(n, iters, num_warm_loops);
        scenario_append_len_reserved(n, iters, num_warm_loops);
        scenario_copy(n, iters, num_warm_loops);
        scenario_borrowed_fixed(n, iters, num_warm_loops);

        if (n <= 4096u)
        {
            scenario_insert_len_mid(n, iters, num_warm_loops);
            scenario_append_len_growth(16u, n / 16u == 0 ? 1u : n / 16u, heavy_iters, num_warm_loops);
        }
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */
