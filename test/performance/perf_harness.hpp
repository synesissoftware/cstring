/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/perf_harness.hpp
 *
 * Purpose: Shared helpers for cstring performance programs.
 *
 * Created: 23rd September 2026
 * Updated: 23rd September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#ifndef CSTRING_TEST_PERFORMANCE_PERF_HARNESS_HPP_INCLUDED
#define CSTRING_TEST_PERFORMANCE_PERF_HARNESS_HPP_INCLUDED


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/conversion/number/grouping_functions.hpp>
#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#include <stlsoft/stlsoft.h>

#ifdef HAS_P99
# include <p99/p99.hpp>
#endif

#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

typedef stlsoft::std_chrono_hrc_stopwatch                   stopwatch_t;
typedef stopwatch_t::interval_type                          interval_t;


/* /////////////////////////////////////////////////////////////////////////
 * configuration
 */

namespace cstring_perf {

inline
std::size_t
env_size_t(
    char const*     name
,   std::size_t     default_value
)
{
    char const* const env = std::getenv(name);

    if (NULL == env || '\0' == *env)
    {
        return default_value;
    }

    char* end = NULL;
    unsigned long const v = std::strtoul(env, &end, 10);

    if (end == env || NULL == end || '\0' != *end || 0 == v)
    {
        return default_value;
    }

    return static_cast<std::size_t>(v);
}

inline
std::size_t
default_iterations()
{
#ifdef NDEBUG

    return env_size_t("CSTRING_PERF_ITERATIONS", 100000u);
#else

return env_size_t("CSTRING_PERF_ITERATIONS", 1000u);
#endif
}

inline
std::size_t
default_warmups()
{
    return env_size_t("CSTRING_PERF_WARMUPS", 2u);
}

inline
std::size_t
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
    std::size_t n
)
{
    if (0 == n)
    {
        return std::string();
    }

    std::string s(n, 'x');

    for (std::size_t i = 0; n != i; ++i)
    {
        s[i] = static_cast<char>('a' + static_cast<int>(i % 26));
    }

    return s;
}


/* /////////////////////////////////////////////////////////////////////////
 * display
 */

template <typename T_integer>
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
        << "  p99: not linked — mean ns/op only; file_lines suite skipped."
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
    char const* const env = std::getenv(name);

    if (NULL == env || '\0' == *env)
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
,   std::size_t size
)
{
    if (!group_gaps_enabled())
    {
        return;
    }

    static bool         have_prev = false;
    static std::string  prev_scenario;
    static std::size_t  prev_size = 0;

    if (have_prev &&
        (prev_scenario != scenario || prev_size != size))
    {
        std::cout << std::endl;
    }

    prev_scenario = scenario;
    prev_size = size;
    have_prev = true;
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
    char const*     scenario
,   std::size_t     size
,   char const*     impl
,   std::size_t     num_iterations
,   std::size_t     num_actions
,   interval_t      tm_ns
,   double          ratio_vs_cstring
,   std::uint64_t   anchor_value
#ifdef HAS_P99
,   p99::histogram const* hist = NULL
#endif /* HAS_P99 */
)
{
    maybe_emit_group_gap(scenario, size);

    std::size_t const denom =
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


/* /////////////////////////////////////////////////////////////////////////
 * hand-rolled string (competitive floor)
 */

struct raw_string
{
    char*       ptr;
    std::size_t len;
    std::size_t capacity;
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
    std::free(s->ptr);
    raw_init(s);
}

inline
int
raw_reserve(
    raw_string* s
,   std::size_t capacity
)
{
    if (capacity <= s->capacity && NULL != s->ptr)
    {
        return 0;
    }

    char* const p = static_cast<char*>(std::realloc(s->ptr, capacity + 1u));

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
    raw_string*     s
,   char const*     src
,   std::size_t     n
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
    raw_string*     s
,   char const*     src
,   std::size_t     n
)
{
    std::size_t const need = s->len + n;

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
    raw_string*     s
,   std::size_t     pos
,   char const*     src
,   std::size_t     n
)
{
    if (pos > s->len)
    {
        pos = s->len;
    }

    std::size_t const need = s->len + n;

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
    char**      ptr;
    std::size_t len;
    std::size_t capacity;
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
        for (std::size_t i = 0; v->len != i; ++i)
        {
            std::free(v->ptr[i]);
        }

        std::free(v->ptr);
    }

    raw_vec_init(v);
}

inline
int
raw_vec_reserve(
    raw_string_vector*  v
,   std::size_t         capacity
)
{
    if (capacity <= v->capacity)
    {
        return 0;
    }

    char** const p = static_cast<char**>(
        std::realloc(v->ptr, capacity * sizeof(char*))
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
,   std::size_t         n
)
{
    if (v->len == v->capacity)
    {
        std::size_t const nc =
            (0 == v->capacity) ? 8u : (v->capacity * 2u)
            ;

        if (0 != raw_vec_reserve(v, nc))
        {
            return -1;
        }
    }

    char* const copy = static_cast<char*>(std::malloc(n + 1u));

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
,   std::size_t         n
)
{
    if (v->len == v->capacity)
    {
        std::size_t const nc =
            (0 == v->capacity) ? 8u : (v->capacity * 2u)
            ;

        if (0 != raw_vec_reserve(v, nc))
        {
            return -1;
        }
    }

    char* const copy = static_cast<char*>(std::malloc(n + 1u));

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
} /* namespace cstring_perf */


/* ////////////////////////////////////////////////////////////////////// */

#endif /* !CSTRING_TEST_PERFORMANCE_PERF_HARNESS_HPP_INCLUDED */

/* ///////////////////////////// end of file //////////////////////////// */
