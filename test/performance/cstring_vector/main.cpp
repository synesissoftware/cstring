/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/test.performance.cstring_vector/main.cpp
 *
 * Purpose: Competitive performance tests for cstring_vector vs
 *          std::vector<std::string> and a hand-rolled floor. When p99 is
 *          available, report per-iteration percentiles throughout, and run
 *          the filesystem suite (cstring_vector_readLines, ifstream +
 *          getline, platformstl::file_lines).
 *
 * Created: 23rd September 2026
 * Updated: 4th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.vector.h>

#include "perf_harness.hpp"

#ifdef HAS_P99
# include <platformstl/filesystem/file_lines.hpp>
# include <fstream>
# include <utility>
#endif /* HAS_P99 */

#include <string>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

char const* const IMPL_CSTRING_VECTOR = "cstring_vector";
char const* const IMPL_STD_VECTOR     = "vector<string>";
char const* const IMPL_RAW_VECTOR     = "raw_char_star_vec";
char const* const IMPL_READLINES      = "cstring_vector_readLines";
#ifdef HAS_P99
char const* const IMPL_GETLINE        = "ifstream+getline";
char const* const IMPL_FILE_LINES     = "platformstl::file_lines";

char const TEST_FILE_NAME[] = "test.performance.cstring_vector.lines.txt";
#endif /* HAS_P99 */
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
,   bool                comparable = true
)
{
    char const* const baselines[] =
    {
        IMPL_CSTRING_VECTOR,
        IMPL_READLINES,
    };

    cstring_perf::emit_row(
        scenario
    ,   size
    ,   impl
    ,   num_iterations
    ,   num_actions
    ,   r
    ,   comparable ? cstring_tm_ns : interval_t(0)
    ,   baselines
    ,   STLSOFT_NUM_ELEMENTS(baselines)
    );
}

cstring_t
make_cstring_payload(
    size_t n
)
{
    std::string const s = make_payload(n);
    cstring_t cs = cstring_t_DEFAULT;

    cstring_createLen(&cs, s.data(), n);

    return cs;
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * scenarios
 */

namespace {

void
scenario_create_destroy(
    size_t n
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    run_result const cs = time_iterations(num_iterations, num_warm_loops, [n]() -> uint64_t {
        cstring_vector_t v = cstring_vector_t_DEFAULT;
        cstring_vector_create(&v, n);
        uint64_t const a = v.len + v.capacity;
        cstring_vector_destroy(&v);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [n]() -> uint64_t {
        std::vector<std::string> v(n);
        return v.size() + v.capacity();
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [n]() -> uint64_t {
        raw_string_vector v;
        raw_vec_init(&v);
        raw_vec_reserve(&v, n);
        v.len = n;
        for (size_t i = 0; n != i; ++i)
        {
            v.ptr[i] = NULL;
        }
        uint64_t const a = v.len + v.capacity;
        raw_vec_destroy(&v);
        return a;
    });

    emit_row("create_destroy", n, IMPL_CSTRING_VECTOR, num_iterations, 1, cs, cs.tm_ns);
    emit_row("create_destroy", n, IMPL_STD_VECTOR, num_iterations, 1, st, cs.tm_ns);
    emit_row("create_destroy", n, IMPL_RAW_VECTOR, num_iterations, 1, raw, cs.tm_ns);
}

void
scenario_append_one_by_one(
    size_t payload_len
,   size_t k
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    cstring_t payload = make_cstring_payload(payload_len);
    std::string const payload_s = make_payload(payload_len);

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [&payload, k]() -> uint64_t {
        cstring_vector_t v = cstring_vector_t_DEFAULT;
        cstring_vector_init(&v, 0);
        for (size_t i = 0; k != i; ++i)
        {
            cstring_vector_append(&v, &payload, 1);
        }
        char const* volatile head =
            (0 != v.len && NULL != v.ptr && NULL != v.ptr[0].ptr)
                ? v.ptr[0].ptr
                : NULL
                ;
        char const* volatile tail =
            (0 != v.len && NULL != v.ptr && NULL != v.ptr[v.len - 1u].ptr)
                ? v.ptr[v.len - 1u].ptr
                : NULL
                ;
        uint64_t const a =
            v.len
            + (NULL != head ? static_cast<unsigned char>(head[0]) : 0u)
            + (NULL != tail ? static_cast<unsigned char>(tail[0]) : 0u)
            ;
        cstring_vector_destroy(&v);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [&payload_s, k]() -> uint64_t {
        std::vector<std::string> v;
        for (size_t i = 0; k != i; ++i)
        {
            v.push_back(payload_s);
        }
        char const* volatile head = v.empty() ? NULL : v.front().data();
        char const* volatile tail = v.empty() ? NULL : v.back().data();
        return v.size()
            + (NULL != head ? static_cast<unsigned char>(head[0]) : 0u)
            + (NULL != tail ? static_cast<unsigned char>(tail[0]) : 0u)
            ;
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [&payload_s, payload_len, k]() -> uint64_t {
        raw_string_vector v;
        raw_vec_init(&v);
        for (size_t i = 0; k != i; ++i)
        {
            raw_vec_append_cstr(&v, payload_s.data(), payload_len);
        }
        char const* volatile head =
            (0 != v.len && NULL != v.ptr) ? v.ptr[0] : NULL
            ;
        char const* volatile tail =
            (0 != v.len && NULL != v.ptr) ? v.ptr[v.len - 1u] : NULL
            ;
        uint64_t const a =
            v.len
            + (NULL != head ? static_cast<unsigned char>(head[0]) : 0u)
            + (NULL != tail ? static_cast<unsigned char>(tail[0]) : 0u)
            ;
        raw_vec_destroy(&v);
        return a;
    });

    cstring_destroy(&payload);

    emit_row("append_one_by_one", payload_len, IMPL_CSTRING_VECTOR, num_iterations, k, cs, cs.tm_ns);
    emit_row("append_one_by_one", payload_len, IMPL_STD_VECTOR, num_iterations, k, st, cs.tm_ns);
    emit_row("append_one_by_one", payload_len, IMPL_RAW_VECTOR, num_iterations, k, raw, cs.tm_ns);
}

void
scenario_append_batch(
    size_t payload_len
,   size_t k
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    std::vector<cstring_t> payloads(k);
    std::vector<std::string> payloads_s(k);
    std::string const proto = make_payload(payload_len);

    for (size_t i = 0; k != i; ++i)
    {
        payloads[i] = cstring_t_DEFAULT;
        cstring_createLen(&payloads[i], proto.data(), payload_len);
        payloads_s[i] = proto;
    }

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [&payloads, k]() -> uint64_t {
        cstring_vector_t v = cstring_vector_t_DEFAULT;
        cstring_vector_init(&v, 0);
        cstring_vector_append(&v, &payloads[0], k);
        char const* volatile head =
            (0 != v.len && NULL != v.ptr && NULL != v.ptr[0].ptr)
                ? v.ptr[0].ptr
                : NULL
                ;
        char const* volatile tail =
            (0 != v.len && NULL != v.ptr && NULL != v.ptr[v.len - 1u].ptr)
                ? v.ptr[v.len - 1u].ptr
                : NULL
                ;
        uint64_t const a =
            v.len
            + (NULL != head ? static_cast<unsigned char>(head[0]) : 0u)
            + (NULL != tail ? static_cast<unsigned char>(tail[0]) : 0u)
            ;
        cstring_vector_destroy(&v);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [&payloads_s]() -> uint64_t {
        std::vector<std::string> v;
        v.insert(v.end(), payloads_s.begin(), payloads_s.end());
        char const* volatile head = v.empty() ? NULL : v.front().data();
        char const* volatile tail = v.empty() ? NULL : v.back().data();
        return v.size()
            + (NULL != head ? static_cast<unsigned char>(head[0]) : 0u)
            + (NULL != tail ? static_cast<unsigned char>(tail[0]) : 0u)
            ;
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [&payloads_s, payload_len, k]() -> uint64_t {
        raw_string_vector v;
        raw_vec_init(&v);
        raw_vec_reserve(&v, k);
        for (size_t i = 0; k != i; ++i)
        {
            raw_vec_append_cstr(&v, payloads_s[i].data(), payload_len);
        }
        char const* volatile head =
            (0 != v.len && NULL != v.ptr) ? v.ptr[0] : NULL
            ;
        char const* volatile tail =
            (0 != v.len && NULL != v.ptr) ? v.ptr[v.len - 1u] : NULL
            ;
        uint64_t const a =
            v.len
            + (NULL != head ? static_cast<unsigned char>(head[0]) : 0u)
            + (NULL != tail ? static_cast<unsigned char>(tail[0]) : 0u)
            ;
        raw_vec_destroy(&v);
        return a;
    });

    for (size_t i = 0; k != i; ++i)
    {
        cstring_destroy(&payloads[i]);
    }

    emit_row("append_batch", payload_len, IMPL_CSTRING_VECTOR, num_iterations, k, cs, cs.tm_ns);
    emit_row("append_batch", payload_len, IMPL_STD_VECTOR, num_iterations, k, st, cs.tm_ns);
    emit_row("append_batch", payload_len, IMPL_RAW_VECTOR, num_iterations, k, raw, cs.tm_ns);
}

void
scenario_prepend_one_by_one(
    size_t payload_len
,   size_t k
,   size_t num_iterations
,   size_t num_warm_loops
)
{
    cstring_t payload = make_cstring_payload(payload_len);
    std::string const payload_s = make_payload(payload_len);

    run_result const cs = time_iterations(num_iterations, num_warm_loops, [&payload, k]() -> uint64_t {
        cstring_vector_t v = cstring_vector_t_DEFAULT;
        cstring_vector_init(&v, 0);
        for (size_t i = 0; k != i; ++i)
        {
            cstring_vector_prepend(&v, &payload, 1);
        }
        char const* volatile head =
            (0 != v.len && NULL != v.ptr && NULL != v.ptr[0].ptr)
                ? v.ptr[0].ptr
                : NULL
                ;
        char const* volatile tail =
            (0 != v.len && NULL != v.ptr && NULL != v.ptr[v.len - 1u].ptr)
                ? v.ptr[v.len - 1u].ptr
                : NULL
                ;
        uint64_t const a =
            v.len
            + (NULL != head ? static_cast<unsigned char>(head[0]) : 0u)
            + (NULL != tail ? static_cast<unsigned char>(tail[0]) : 0u)
            ;
        cstring_vector_destroy(&v);
        return a;
    });

    run_result const st = time_iterations(num_iterations, num_warm_loops, [&payload_s, k]() -> uint64_t {
        std::vector<std::string> v;
        for (size_t i = 0; k != i; ++i)
        {
            v.insert(v.begin(), payload_s);
        }
        char const* volatile head = v.empty() ? NULL : v.front().data();
        char const* volatile tail = v.empty() ? NULL : v.back().data();
        return v.size()
            + (NULL != head ? static_cast<unsigned char>(head[0]) : 0u)
            + (NULL != tail ? static_cast<unsigned char>(tail[0]) : 0u)
            ;
    });

    run_result const raw = time_iterations(num_iterations, num_warm_loops, [&payload_s, payload_len, k]() -> uint64_t {
        raw_string_vector v;
        raw_vec_init(&v);
        for (size_t i = 0; k != i; ++i)
        {
            raw_vec_prepend_cstr(&v, payload_s.data(), payload_len);
        }
        char const* volatile head =
            (0 != v.len && NULL != v.ptr) ? v.ptr[0] : NULL
            ;
        char const* volatile tail =
            (0 != v.len && NULL != v.ptr) ? v.ptr[v.len - 1u] : NULL
            ;
        uint64_t const a =
            v.len
            + (NULL != head ? static_cast<unsigned char>(head[0]) : 0u)
            + (NULL != tail ? static_cast<unsigned char>(tail[0]) : 0u)
            ;
        raw_vec_destroy(&v);
        return a;
    });

    cstring_destroy(&payload);

    emit_row("prepend_one_by_one", payload_len, IMPL_CSTRING_VECTOR, num_iterations, k, cs, cs.tm_ns);
    emit_row("prepend_one_by_one", payload_len, IMPL_STD_VECTOR, num_iterations, k, st, cs.tm_ns);
    emit_row("prepend_one_by_one", payload_len, IMPL_RAW_VECTOR, num_iterations, k, raw, cs.tm_ns);
}
#ifdef HAS_P99

template <typename F>
uint64_t
sum_line_lengths(
    size_t  count
,   F       length_at
)
{
    uint64_t a = count;

    for (size_t i = 0; count != i; ++i)
    {
        a += length_at(i);
    }

    return a;
}

bool
file_anchors_agree(
    size_t              num_lines
,   run_result const&   cs
,   run_result const&   gl
,   run_result const&   fl
)
{
    if (0 != cs.anchor &&
        cs.anchor == gl.anchor &&
        cs.anchor == fl.anchor)
    {
        return true;
    }

    std::cerr
        << "anchor mismatch in file_read_all_lines"
        << " lines " << num_lines
        << ": cstring_vector_readLines=" << cs.anchor
        << " ifstream+getline=" << gl.anchor
        << " platformstl::file_lines=" << fl.anchor
        << std::endl
        ;

    return false;
}

bool
scenario_file_lines_vs_readlines(
    size_t num_lines
,   size_t line_len
,   size_t num_trials
,   size_t num_warm_loops
)
{
    if (!write_lines_file(TEST_FILE_NAME, num_lines, line_len, LINE_ENDING_LF))
    {
        std::cerr
            << "failed to write " << TEST_FILE_NAME << "; skipping file_lines suite"
            << std::endl
            ;
        return true;
    }

    std::cout
        << "\nfile_lines suite (" << num_lines << " lines x " << line_len
        << " chars; " << num_trials
        << " trials; filesystem-sensitive — use p99 percentiles):"
        << std::endl
        << "  Owning peer is ifstream+getline. platformstl::file_lines is"
        << std::endl
        << "  timed, and its vs cstr column is \"-\"."
        << std::endl
        << "  Anchor is line count plus the sum of line lengths."
        << std::endl
        ;

    run_result const cs = time_iterations(num_trials, num_warm_loops, []() -> uint64_t {
        FILE* f = std::fopen(TEST_FILE_NAME, "rb");
        if (NULL == f)
        {
            return 0;
        }

        cstring_vector_t v = cstring_vector_t_DEFAULT;
        cstring_vector_init(&v, 0);
        cstring_vector_readLines(f, &v, NULL);
        uint64_t const a = sum_line_lengths(
            v.len
        ,   [&v](size_t i) -> size_t
            {
                return (NULL != v.ptr) ? v.ptr[i].len : 0u;
            }
        );
        cstring_vector_destroy(&v);
        std::fclose(f);
        return a;
    });

    run_result const gl = time_iterations(num_trials, num_warm_loops, []() -> uint64_t {
        std::ifstream in(TEST_FILE_NAME, std::ios::in | std::ios::binary);

        if (!in)
        {
            return 0;
        }

        std::vector<std::string> lines;
        std::string line;

        while (std::getline(in, line))
        {
            lines.push_back(line);
            line.clear();
        }

        return sum_line_lengths(
            lines.size()
        ,   [&lines](size_t i) -> size_t
            {
                return lines[i].size();
            }
        );
    });

    run_result const fl = time_iterations(num_trials, num_warm_loops, []() -> uint64_t {
        platformstl::file_lines_a lines(TEST_FILE_NAME);
        return sum_line_lengths(
            lines.size()
        ,   [&lines](size_t i) -> size_t
            {
                return lines[i].size();
            }
        );
    });

    bool const ok = file_anchors_agree(num_lines, cs, gl, fl);

    if (ok)
    {
        emit_row("file_read_all_lines", num_lines, IMPL_READLINES, num_trials, 1, cs, cs.tm_ns);
        emit_row("file_read_all_lines", num_lines, IMPL_GETLINE, num_trials, 1, gl, cs.tm_ns);
        emit_row("file_read_all_lines", num_lines, IMPL_FILE_LINES, num_trials, 1, fl, cs.tm_ns, false);
    }

    std::remove(TEST_FILE_NAME);

    return ok;
}
#endif /* HAS_P99 */
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /*argc*/, char* /*argv*/[])
{
    size_t const num_iterations = cstring_perf::default_iterations();
    size_t const num_warm_loops = cstring_perf::default_warmups();
    size_t const heavy_iters =
        (num_iterations > 10000u) ? (num_iterations / 10u) : num_iterations
        ;

    cstring_perf::display_banner("test.performance.cstring_vector");
    cstring_perf::display_results_title();

    scenario_create_destroy(16u, num_iterations, num_warm_loops);
    scenario_create_destroy(256u, heavy_iters, num_warm_loops);

    scenario_append_one_by_one(16u, 64u, heavy_iters, num_warm_loops);
    scenario_append_one_by_one(256u, 64u, heavy_iters, num_warm_loops);

    scenario_append_batch(16u, 64u, heavy_iters, num_warm_loops);
    scenario_append_batch(256u, 64u, heavy_iters, num_warm_loops);

    scenario_prepend_one_by_one(16u, 32u, heavy_iters, num_warm_loops);
    scenario_prepend_one_by_one(256u, 32u, heavy_iters, num_warm_loops);
#ifdef HAS_P99

    size_t const file_trials = cstring_perf::default_file_trials();

    if (!scenario_file_lines_vs_readlines(1000u, 64u, file_trials, num_warm_loops) ||
        !scenario_file_lines_vs_readlines(5000u, 80u, file_trials, num_warm_loops))
    {
        return EXIT_FAILURE;
    }
#else /* ? HAS_P99 */

    std::cout
        << "\nfile_lines suite skipped (p99 not available)."
        << std::endl
        ;
#endif /* HAS_P99 */

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */
