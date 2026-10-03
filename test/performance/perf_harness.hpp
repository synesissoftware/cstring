/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/perf_harness.hpp
 *
 * Purpose: Shared helpers for cstring performance programs.
 *
 * Created: 23rd September 2026
 * Updated: 3rd October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#ifndef CSTRING_TEST_PERFORMANCE_PERF_HARNESS_HPP_INCLUDED
#define CSTRING_TEST_PERFORMANCE_PERF_HARNESS_HPP_INCLUDED


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <platformstl/system/console_functions.h>
#include <stlsoft/conversion/number/grouping_functions.hpp>
#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#include <stlsoft/std/cstdlib.hpp>
#include <stlsoft/stlsoft.h>

#ifdef HAS_P99
# include <p99/p99.hpp>
#endif

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

typedef stlsoft::std_chrono_hrc_stopwatch                   stopwatch_t;
typedef stopwatch_t::interval_type                          interval_t;


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

namespace cstring_perf
{


/* /////////////////////////////////////////////////////////////////////////
 * configuration
 */

inline
size_t
env_size_t(
    char const* name
,   size_t      default_value
)
{
    char const* const env = ::getenv(name);

    if (NULL == env ||
        '\0' == env[0])
    {
        return default_value;
    }

    char*               end =   NULL;
    unsigned long const v   =   stlsoft::strtoul(env, &end, 10);

    if (end == env ||
        NULL == end ||
        '\0' != end[0] ||
        0 == v)
    {
        return default_value;
    }

    return static_cast<size_t>(v);
}

inline
size_t
default_iterations()
{
#ifdef NDEBUG

    return env_size_t("CSTRING_PERF_ITERATIONS", 100000u);
#else

    return env_size_t("CSTRING_PERF_ITERATIONS", 1000u);
#endif
}

inline
size_t
default_warmups()
{
    return env_size_t("CSTRING_PERF_WARMUPS", 2u);
}

inline
size_t
default_file_trials()
{
#ifdef NDEBUG

    return env_size_t("CSTRING_PERF_FILE_TRIALS", 200u);
#else

    return env_size_t("CSTRING_PERF_FILE_TRIALS", 40u);
#endif
}


/* /////////////////////////////////////////////////////////////////////////
 * payloads
 */

inline
std::string
make_payload(
    size_t n
)
{
    if (0 == n)
    {
        return std::string();
    }

    std::string s(n, 'x');

    for (size_t i = 0; n != i; ++i)
    {
        s[i] = static_cast<char>('a' + static_cast<int>(i % 26));
    }

    return s;
}


/* /////////////////////////////////////////////////////////////////////////
 * filesystem fixtures
 */

enum line_ending_t
{
    LINE_ENDING_LF = 0,
    LINE_ENDING_CRLF,
    LINE_ENDING_NONE,
};

inline
bool
write_lines_file(
    char const*     path
,   size_t          num_lines
,   size_t          line_len
,   line_ending_t   ending
)
{
    std::ofstream out(path, std::ios::binary | std::ios::trunc);

    if (!out)
    {
        return false;
    }

    std::string const line = make_payload(line_len);

    for (size_t i = 0; num_lines != i; ++i)
    {
        out.write(line.data(), static_cast<std::streamsize>(line.size()));

        if (LINE_ENDING_CRLF == ending)
        {
            out.write("\r\n", 2);
        }
        else if (LINE_ENDING_LF == ending)
        {
            out.put('\n');
        }
    }

    return static_cast<bool>(out);
}


/* /////////////////////////////////////////////////////////////////////////
 * timing
 */

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
    size_t  num_iterations
,   size_t  num_warm_loops
,   F       fn
)
{
    run_result result = {};
    stopwatch_t sw;

    for (size_t w = num_warm_loops; 0 != w; --w)
    {
        result.anchor = 0;
#ifdef HAS_P99

        result.hist.clear();
#endif /* HAS_P99 */
        interval_t tm_ns = 0;
#ifdef HAS_P99

        for (size_t i = 0; num_iterations != i; ++i)
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
        for (size_t i = 0; num_iterations != i; ++i)
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


/* /////////////////////////////////////////////////////////////////////////
 * display
 */

template <ss_typename_param_k T_integer>
inline
std::string
thousands(
    T_integer const& v
)
{
    char    dest[41];
    size_t  n = stlsoft::format_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;0", v);

    return std::string(dest, n > 0 ? n - 1 : 0);
}

inline
void
display_banner(
    char const* program_name
)
{
    std::cout
        << program_name
        << ": competitive performance timings (human attention; not a CI gate)."
        << std::endl
        << "  Note: std::string typically has SSO; cstring is heap-oriented —"
        << std::endl
        << "  small sizes favour std::string. Prefer Release builds."
        << std::endl
#ifdef HAS_P99
        << "  p99: available — per-op percentiles reported where timed."
        << std::endl
        << "  Env: CSTRING_PERF_ITERATIONS, CSTRING_PERF_WARMUPS"
        << ", CSTRING_PERF_FILE_TRIALS"
        << ", SIS_PERFTESTS_GROUPGAPS."
#else /* ? HAS_P99 */
        << "  p99: not linked — mean ns/op only; filesystem suites skipped."
        << std::endl
        << "  Env: CSTRING_PERF_ITERATIONS, CSTRING_PERF_WARMUPS"
        << ", SIS_PERFTESTS_GROUPGAPS."
#endif /* HAS_P99 */
        << std::endl
        ;
}
#ifdef HAS_P99

inline
void
append_percentile_columns(
    p99::histogram const*   h
)
{
    uint64_t p50 = 0;
    uint64_t p90 = 0;
    uint64_t p99v = 0;
    uint64_t maxv = 0;

    if (NULL != h && !h->empty())
    {
        (void)h->try_get_value_at_p50(&p50);
        (void)h->try_get_value_at_percentile(90.0, &p90);
        (void)h->try_get_value_at_p99(&p99v);
        (void)h->try_get_max_event_time(&maxv);
    }

    std::cout
        << '\t' << std::setw(10) << std::right << thousands(p50)
        << '\t' << std::setw(10) << std::right << thousands(p90)
        << '\t' << std::setw(10) << std::right << thousands(p99v)
        << '\t' << std::setw(10) << std::right << thousands(maxv)
        ;
}
#endif /* HAS_P99 */

inline
bool
env_is_truey(
    char const* name
)
{
    char const* const env = ::getenv(name);

    if (NULL == env ||
        '\0' == env[0])
    {
        return false;
    }

    if (0 == ::strcmp(env, "1") ||
        0 == ::strcmp(env, "ok") ||
        0 == ::strcmp(env, "on") ||
        0 == ::strcmp(env, "true") ||
        0 == ::strcmp(env, "yes") ||
        0 == ::strcmp(env, "y") ||
        0 == ::strcmp(env, "OK") ||
        0 == ::strcmp(env, "ON") ||
        0 == ::strcmp(env, "TRUE") ||
        0 == ::strcmp(env, "YES") ||
        0 == ::strcmp(env, "Y"))
    {
        return true;
    }

    return false;
}

inline
bool
group_gaps_enabled()
{
    return env_is_truey("SIS_PERFTESTS_GROUPGAPS");
}

inline
void
maybe_emit_group_gap(
    char const* scenario
,   size_t      size
)
{
    if (!group_gaps_enabled())
    {
        return;
    }

    static bool         have_prev = false;
    static std::string  prev_scenario;
    static size_t  prev_size = 0;

    if (have_prev &&
        (   prev_scenario != scenario ||
            prev_size != size))
    {
        // Bare blank lines are stripped by GitHub Actions log UI; use a
        // visible rule when stdout is not a TTY (CI / redirected logs).
        if (platformstl::isatty(stdout))
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\t----------" << std::endl;
        }
    }

    prev_scenario   =   scenario;
    prev_size       =   size;
    have_prev       =   true;
}

inline
void
display_results_title()
{
    std::cout
        << '\t'
        << std::setw(40) << std::left << "scenario"
        << '\t'
        << std::setw(12) << std::right << "size"
        << '\t'
        << std::setw(24) << std::left << "impl"
        << '\t'
        << std::setw(12) << std::right << "#iters"
        << '\t'
        << std::setw(10) << std::right << "#acts"
        << '\t'
        << std::setw(14) << std::right << "tm (ns)"
        << '\t'
        << std::setw(12) << std::right << "ns/op"
        << '\t'
        << std::setw(10) << std::right << "vs cstr"
#ifdef HAS_P99
        << '\t'
        << std::setw(10) << std::right << "p50"
        << '\t'
        << std::setw(10) << std::right << "p90"
        << '\t'
        << std::setw(10) << std::right << "p99"
        << '\t'
        << std::setw(10) << std::right << "max"
#endif /* HAS_P99 */
        << '\t'
        << std::setw(14) << std::right << "anchor"
        << std::endl
        ;
}

inline
void
display_results(
    char const*             scenario
,   size_t                  size
,   char const*             impl
,   size_t                  num_iterations
,   size_t                  num_actions
,   interval_t              tm_ns
,   double                  ratio_vs_cstring
,   ::uint64_t              anchor_value
#ifdef HAS_P99
,   p99::histogram const*   hist = NULL
#endif /* HAS_P99 */
)
{
    maybe_emit_group_gap(scenario, size);

    size_t const denom =
        (0 == num_iterations || 0 == num_actions)
            ? 1u
            : (num_iterations * num_actions)
            ;

    std::cout
        << '\t'
        << std::setw(40) << std::left << scenario
        << '\t'
        << std::setw(12) << std::right << size
        << '\t'
        << std::setw(24) << std::left << impl
        << '\t'
        << std::setw(12) << std::right << num_iterations
        << '\t'
        << std::setw(10) << std::right << num_actions
        << '\t'
        << std::setw(14) << std::right << thousands(tm_ns)
        << '\t'
        << std::setw(12) << std::right << thousands(tm_ns / denom)
        << '\t'
        ;

    if (ratio_vs_cstring < 0.0)
    {
        std::cout << std::setw(10) << std::right << "-";
    }
    else
    {
        std::cout
            << std::setw(10) << std::right
            << std::fixed << std::setprecision(2) << ratio_vs_cstring
            ;
    }
#ifdef HAS_P99

    append_percentile_columns(hist);
#endif /* HAS_P99 */

    std::cout
        << '\t'
        << std::setw(14) << std::right << anchor_value
        << std::endl
        ;
}

inline
double
ratio_or_dash(
    interval_t subject_ns
,   interval_t baseline_ns
)
{
    if (0 == baseline_ns)
    {
        return -1.0;
    }

    return static_cast<double>(subject_ns) / static_cast<double>(baseline_ns);
}

inline
bool
impl_is_baseline(
    char const*         impl
,   char const* const*  baseline_impls
,   size_t              num_baselines
)
{
    for (size_t i = 0; num_baselines != i; ++i)
    {
        if (0 == ::strcmp(impl, baseline_impls[i]))
        {
            return true;
        }
    }

    return false;
}

/* Baseline impl names are ratio 1.0. Every other impl is timed against
 * baseline_ns.
 */
inline
void
emit_row(
    char const*         scenario
,   size_t              size
,   char const*         impl
,   size_t              num_iterations
,   size_t              num_actions
,   run_result const&   r
,   interval_t          baseline_ns
,   char const* const*  baseline_impls
,   size_t              num_baselines
)
{
    double const ratio =
        impl_is_baseline(impl, baseline_impls, num_baselines)
            ? 1.0
            : ratio_or_dash(r.tm_ns, baseline_ns)
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


/* /////////////////////////////////////////////////////////////////////////
 * hand-rolled string (competitive floor)
 */

struct raw_string
{
    char*   ptr;
    size_t  len;
    size_t  capacity;
};

inline
void
raw_init(
    raw_string* s
)
{
    s->ptr = NULL;
    s->len = 0;
    s->capacity = 0;
}

inline
void
raw_destroy(
    raw_string* s
)
{
    ::free(s->ptr);
    raw_init(s);
}

inline
int
raw_reserve(
    raw_string* s
,   size_t      capacity
)
{
    if (capacity <= s->capacity && NULL != s->ptr)
    {
        return 0;
    }

    char* const p = static_cast<char*>(::realloc(s->ptr, capacity + 1u));

    if (NULL == p)
    {
        return -1;
    }

    s->ptr = p;
    s->capacity = capacity;
    s->ptr[s->len] = '\0';

    return 0;
}

inline
int
raw_assign_len(
    raw_string* s
,   char const* src
,   size_t      n
)
{
    if (0 != raw_reserve(s, n))
    {
        return -1;
    }

    if (0 != n)
    {
        ::memcpy(s->ptr, src, n);
    }

    s->len = n;
    s->ptr[n] = '\0';

    return 0;
}

inline
int
raw_append_len(
    raw_string* s
,   char const* src
,   size_t      n
)
{
    size_t const need = s->len + n;

    if (0 != raw_reserve(s, need))
    {
        return -1;
    }

    if (0 != n)
    {
        ::memcpy(s->ptr + s->len, src, n);
    }

    s->len = need;
    s->ptr[need] = '\0';

    return 0;
}

inline
int
raw_insert_len(
    raw_string* s
,   size_t      pos
,   char const* src
,   size_t      n
)
{
    if (pos > s->len)
    {
        pos = s->len;
    }

    size_t const need = s->len + n;

    if (0 != raw_reserve(s, need))
    {
        return -1;
    }

    if (0 != n)
    {
        ::memmove(s->ptr + pos + n, s->ptr + pos, s->len - pos);
        ::memcpy(s->ptr + pos, src, n);
    }

    s->len = need;
    s->ptr[need] = '\0';

    return 0;
}

inline
int
raw_copy(
    raw_string*         dest
,   raw_string const*   src
)
{
    return raw_assign_len(dest, src->ptr, src->len);
}


/* /////////////////////////////////////////////////////////////////////////
 * hand-rolled string vector (competitive floor)
 */

struct raw_string_vector
{
    char**  ptr;
    size_t  len;
    size_t  capacity;
};

inline
void
raw_vec_init(
    raw_string_vector* v
)
{
    v->ptr = NULL;
    v->len = 0;
    v->capacity = 0;
}

inline
void
raw_vec_destroy(
    raw_string_vector* v
)
{
    if (NULL != v->ptr)
    {
        for (size_t i = 0; v->len != i; ++i)
        {
            ::free(v->ptr[i]);
        }

        ::free(v->ptr);
    }

    raw_vec_init(v);
}

inline
int
raw_vec_reserve(
    raw_string_vector*  v
,   size_t              capacity
)
{
    if (capacity <= v->capacity)
    {
        return 0;
    }

    char** const p = static_cast<char**>(
        ::realloc(v->ptr, capacity * sizeof(char*))
    );

    if (NULL == p)
    {
        return -1;
    }

    v->ptr = p;
    v->capacity = capacity;

    return 0;
}

inline
int
raw_vec_append_cstr(
    raw_string_vector*  v
,   char const*         s
,   size_t              n
)
{
    if (v->len == v->capacity)
    {
        size_t const nc =
            (0 == v->capacity) ? 8u : (v->capacity * 2u)
            ;

        if (0 != raw_vec_reserve(v, nc))
        {
            return -1;
        }
    }

    char* const copy = static_cast<char*>(::malloc(n + 1u));

    if (NULL == copy)
    {
        return -1;
    }

    if (0 != n)
    {
        ::memcpy(copy, s, n);
    }

    copy[n] = '\0';
    v->ptr[v->len++] = copy;

    return 0;
}

inline
int
raw_vec_prepend_cstr(
    raw_string_vector*  v
,   char const*         s
,   size_t              n
)
{
    if (v->len == v->capacity)
    {
        size_t const nc =
            (0 == v->capacity)
                ? 8u
                : (v->capacity * 2u)
            ;

        if (0 != raw_vec_reserve(v, nc))
        {
            return -1;
        }
    }

    char* const copy = static_cast<char*>(::malloc(n + 1u));

    if (NULL == copy)
    {
        return -1;
    }

    if (0 != n)
    {
        ::memcpy(copy, s, n);
    }

    copy[n] = '\0';

    if (0 != v->len)
    {
        ::memmove(v->ptr + 1, v->ptr, v->len * sizeof(char*));
    }

    v->ptr[0] = copy;
    ++v->len;

    return 0;
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

} // namespace cstring_perf


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* !CSTRING_TEST_PERFORMANCE_PERF_HARNESS_HPP_INCLUDED */

/* ///////////////////////////// end of file //////////////////////////// */
