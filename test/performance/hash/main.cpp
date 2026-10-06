/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/hash/main.cpp
 *
 * Purpose: Times djb2, FNV-1a, and SDBM against a degenerate lose-lose
 *          sum. Each group is one input and length: lose-lose, djb2,
 *          FNV-1a, then SDBM. The "vs cstr" column is the ratio against
 *          lose-lose. --gap-groups separates those groups.
 *
 * Created: 6th October 2026
 * Updated: 6th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>

#include "lose_lose.h"
#include "perf_harness.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * character encoding
 */

#ifdef CSTRING_USE_WIDE_STRINGS
# define CSTRING_T_(x)                                      L ## x
#else /* ? CSTRING_USE_WIDE_STRINGS */
# define CSTRING_T_(x)                                      x
#endif /* CSTRING_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

using namespace cstring_perf;

char const* const IMPL_LOSE_LOSE = "lose-lose";

char const* const BASELINES[] =
{
    IMPL_LOSE_LOSE,
};

size_t const SIZES[] =
{
    1u,
    16u,
    64u,
    256u,
    4096u,
    65536u,
};

/* C linkage, so these match lose_lose_* and cstring_hash_*. lose-lose stays
 * the first row of every table: a gapped group opens with the baseline.
 * Append a row to every table when adding an algorithm.
 */

extern "C"
{

typedef cstring_hash_t (cstring_fn_t)(struct cstring_t const*);
typedef cstring_hash_t (mbs_fn_t)(char const*);
typedef cstring_hash_t (mbuf_fn_t)(char const*, size_t);
typedef cstring_hash_t (wcs_fn_t)(wchar_t const*);
typedef cstring_hash_t (wbuf_fn_t)(wchar_t const*, size_t);

} /* extern "C" */

struct cstring_algo
{
    char const*     name;
    cstring_fn_t*   fn;
};

struct mbs_algo
{
    char const* name;
    mbs_fn_t*   fn;
};

struct mbuf_algo
{
    char const* name;
    mbuf_fn_t*  fn;
};

struct wcs_algo
{
    char const* name;
    wcs_fn_t*   fn;
};

struct wbuf_algo
{
    char const* name;
    wbuf_fn_t*  fn;
};

cstring_algo const CSTRING_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_cstring, },
    { "djb2", cstring_hash_djb2, },
    { "fnv1a", cstring_hash_fnv1a, },
    { "sdbm", cstring_hash_sdbm, },
};

cstring_algo const CSTRING_CASE_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_cstring_case, },
    { "djb2", cstring_hash_djb2_case, },
    { "fnv1a", cstring_hash_fnv1a_case, },
    { "sdbm", cstring_hash_sdbm_case, },
};

mbs_algo const MBS_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_mbs, },
    { "djb2", cstring_hash_djb2_mbs, },
    { "fnv1a", cstring_hash_fnv1a_mbs, },
    { "sdbm", cstring_hash_sdbm_mbs, },
};

mbs_algo const MBS_CASE_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_mbs_case, },
    { "djb2", cstring_hash_djb2_mbs_case, },
    { "fnv1a", cstring_hash_fnv1a_mbs_case, },
    { "sdbm", cstring_hash_sdbm_mbs_case, },
};

mbuf_algo const MBUF_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_mbuf, },
    { "djb2", cstring_hash_djb2_mbuf, },
    { "fnv1a", cstring_hash_fnv1a_mbuf, },
    { "sdbm", cstring_hash_sdbm_mbuf, },
};

mbuf_algo const MBUF_CASE_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_mbuf_case, },
    { "djb2", cstring_hash_djb2_mbuf_case, },
    { "fnv1a", cstring_hash_fnv1a_mbuf_case, },
    { "sdbm", cstring_hash_sdbm_mbuf_case, },
};

wcs_algo const WCS_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_wcs, },
    { "djb2", cstring_hash_djb2_wcs, },
    { "fnv1a", cstring_hash_fnv1a_wcs, },
    { "sdbm", cstring_hash_sdbm_wcs, },
};

wcs_algo const WCS_CASE_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_wcs_case, },
    { "djb2", cstring_hash_djb2_wcs_case, },
    { "fnv1a", cstring_hash_fnv1a_wcs_case, },
    { "sdbm", cstring_hash_sdbm_wcs_case, },
};

wbuf_algo const WBUF_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_wbuf, },
    { "djb2", cstring_hash_djb2_wbuf, },
    { "fnv1a", cstring_hash_fnv1a_wbuf, },
    { "sdbm", cstring_hash_sdbm_wbuf, },
};

wbuf_algo const WBUF_CASE_ALGOS[] =
{
    { IMPL_LOSE_LOSE, lose_lose_wbuf_case, },
    { "djb2", cstring_hash_djb2_wbuf_case, },
    { "fnv1a", cstring_hash_fnv1a_wbuf_case, },
    { "sdbm", cstring_hash_sdbm_wbuf_case, },
};


/* /////////////////////////////////////////////////////////////////////////
 * payloads
 */

std::string
make_mixed(size_t n)
{
    std::string s(n, '\0');

    for (size_t i = 0; n != i; ++i)
    {
        char const upper = static_cast<char>('A' + static_cast<int>(i % 26));

        s[i] = (0 == (i % 2)) ? upper : static_cast<char>(upper - 'A' + 'a');
    }

    return s;
}

std::string
make_high(size_t n)
{
    std::string s(n, '\0');

    for (size_t i = 0; n != i; ++i)
    {
        s[i] = static_cast<char>(static_cast<unsigned char>(0x80u + (i % 0x80u)));
    }

    return s;
}

/* Even code units are letters. Odd code units are NUL. Length 1 is the
 * single letter at index 0.
 */

std::string
make_embedded(size_t n)
{
    std::string s(n, '\0');

    for (size_t i = 0; n > i; i += 2)
    {
        s[i] = static_cast<char>('a' + static_cast<int>(i % 26));
    }

    return s;
}

std::vector<cstring_char_t>
ambient_from(std::string const& bytes)
{
    std::vector<cstring_char_t> s(bytes.size());

    for (size_t i = 0; bytes.size() != i; ++i)
    {
        unsigned char const octet = static_cast<unsigned char>(bytes[i]);

        s[i] = static_cast<cstring_char_t>(octet);
    }

    return s;
}

std::vector<wchar_t>
terminated_wide(std::string const& bytes)
{
    std::vector<wchar_t> s(bytes.size() + 1u, L'\0');

    for (size_t i = 0; bytes.size() != i; ++i)
    {
        s[i] = static_cast<wchar_t>(static_cast<unsigned char>(bytes[i]));
    }

    return s;
}

std::vector<wchar_t>
wide_high(size_t n)
{
    std::vector<wchar_t> s(n + 1u, L'\0');

    for (size_t i = 0; n != i; ++i)
    {
        s[i] = static_cast<wchar_t>(0x180u + (i % 0x80u));
    }

    return s;
}

std::vector<wchar_t>
wide_embedded(size_t n)
{
    std::vector<wchar_t> s(n, L'\0');

    for (size_t i = 0; n > i; i += 2)
    {
        s[i] = static_cast<wchar_t>(L'a' + static_cast<int>(i % 26));
    }

    return s;
}


/* /////////////////////////////////////////////////////////////////////////
 * timing
 */

/* Lengths up to 64 octets use base_iterations. Longer inputs use fewer
 * iterations so the timed loop visits about the same number of octets. The
 * floor is 4.
 */

size_t
iterations_for_length(
    size_t length
,   size_t base_iterations
)
{
    size_t const unit   =   (length < 64u) ? 64u : length;
    size_t       iters  =   (base_iterations * 64u) / unit;

    if (iters < 4u)
    {
        iters = 4u;
    }

    return iters;
}

template <typename Algo, typename Invoke>
void
run_group(
    char const* scenario
,   size_t      size
,   size_t      num_iterations
,   size_t      num_warm_loops
,   Algo const* algos
,   size_t      num_algos
,   Invoke      invoke
)
{
    if (0 == num_algos)
    {
        return;
    }

    std::vector<run_result> results;

    results.reserve(num_algos);

    for (size_t i = 0; num_algos != i; ++i)
    {
        results.push_back(time_iterations(
            num_iterations
        ,   num_warm_loops
        ,   [&invoke, i]() -> uint64_t
            {
                return invoke(i);
            }
        ));
    }

    interval_t baseline_ns = results[0].tm_ns;

    for (size_t i = 0; num_algos != i; ++i)
    {
        if (0 == ::strcmp(algos[i].name, IMPL_LOSE_LOSE))
        {
            baseline_ns = results[i].tm_ns;

            break;
        }
    }

    for (size_t i = 0; num_algos != i; ++i)
    {
        emit_row(
            scenario
        ,   size
        ,   algos[i].name
        ,   num_iterations
        ,   1u
        ,   results[i]
        ,   baseline_ns
        ,   BASELINES
        ,   STLSOFT_NUM_ELEMENTS(BASELINES)
        );
    }
}

void
run_cstring(
    char const*             scenario
,   size_t                  n
,   size_t                  iters
,   size_t                  warm
,   cstring_algo const*     algos
,   size_t                  num_algos
,   struct cstring_t const* pcs
)
{
    run_group(
        scenario
    ,   n
    ,   iters
    ,   warm
    ,   algos
    ,   num_algos
    ,   [algos, pcs](size_t algo) -> uint64_t
        {
            return algos[algo].fn(pcs);
        }
    );
}

void
run_mbs(
    char const*     scenario
,   char const*     data
,   size_t          n
,   size_t          iters
,   size_t          warm
,   mbs_algo const* algos
,   size_t          num_algos
)
{
    run_group(
        scenario
    ,   n
    ,   iters
    ,   warm
    ,   algos
    ,   num_algos
    ,   [algos, data](size_t algo) -> uint64_t
        {
            return algos[algo].fn(data);
        }
    );
}

void
run_mbuf(
    char const*         scenario
,   char const*         data
,   size_t              n
,   size_t              iters
,   size_t              warm
,   mbuf_algo const*    algos
,   size_t              num_algos
)
{
    run_group(
        scenario
    ,   n
    ,   iters
    ,   warm
    ,   algos
    ,   num_algos
    ,   [algos, data, n](size_t algo) -> uint64_t
        {
            return algos[algo].fn(data, n);
        }
    );
}

void
run_wcs(
    char const*         scenario
,   wchar_t const*      data
,   size_t              n
,   size_t              iters
,   size_t              warm
,   wcs_algo const*     algos
,   size_t              num_algos
)
{
    run_group(
        scenario
    ,   n
    ,   iters
    ,   warm
    ,   algos
    ,   num_algos
    ,   [algos, data](size_t algo) -> uint64_t
        {
            return algos[algo].fn(data);
        }
    );
}

void
run_wbuf(
    char const*         scenario
,   wchar_t const*      data
,   size_t              n
,   size_t              iters
,   size_t              warm
,   wbuf_algo const*    algos
,   size_t              num_algos
)
{
    run_group(
        scenario
    ,   n
    ,   iters
    ,   warm
    ,   algos
    ,   num_algos
    ,   [algos, data, n](size_t algo) -> uint64_t
        {
            return algos[algo].fn(data, n);
        }
    );
}

template <typename F>
bool
with_cstring(
    char const*             scenario
,   cstring_char_t const*   chars
,   size_t                  n
,   F                       fn
)
{
    cstring_t           cs = cstring_t_DEFAULT;
    CSTRING_RC const    rc = cstring_createLen(&cs, chars, n);

    if (CSTRING_RC_SUCCESS != rc)
    {
        std::cerr
            << scenario
            << ": cstring_createLen failed ("
            << static_cast<int>(rc)
            << ")"
            << std::endl
            ;

        return false;
    }

    fn(static_cast<cstring_t const*>(&cs));
    cstring_destroy(&cs);

    return true;
}


/* /////////////////////////////////////////////////////////////////////////
 * scenarios
 */

bool
run_null_and_empty(
    size_t iters
,   size_t warm
)
{
    run_cstring("null_cstring", 0, iters, warm, CSTRING_ALGOS, STLSOFT_NUM_ELEMENTS(CSTRING_ALGOS), NULL);
    run_mbs("null_mbs", NULL, 0, iters, warm, MBS_ALGOS, STLSOFT_NUM_ELEMENTS(MBS_ALGOS));
    run_mbuf("null_mbuf", NULL, 0, iters, warm, MBUF_ALGOS, STLSOFT_NUM_ELEMENTS(MBUF_ALGOS));
    run_wcs("null_wcs", NULL, 0, iters, warm, WCS_ALGOS, STLSOFT_NUM_ELEMENTS(WCS_ALGOS));
    run_wbuf("null_wbuf", NULL, 0, iters, warm, WBUF_ALGOS, STLSOFT_NUM_ELEMENTS(WBUF_ALGOS));

    cstring_t           cs = cstring_t_DEFAULT;
    CSTRING_RC const    rc = cstring_create(&cs, CSTRING_T_(""));

    if (CSTRING_RC_SUCCESS != rc)
    {
        std::cerr
            << "empty_cstring: cstring_create failed ("
            << static_cast<int>(rc)
            << ")"
            << std::endl
            ;

        return false;
    }

    run_cstring("empty_cstring", 0, iters, warm, CSTRING_ALGOS, STLSOFT_NUM_ELEMENTS(CSTRING_ALGOS), &cs);
    cstring_destroy(&cs);

    run_mbs("empty_mbs", "", 0, iters, warm, MBS_ALGOS, STLSOFT_NUM_ELEMENTS(MBS_ALGOS));
    run_mbuf("empty_mbuf", "", 0, iters, warm, MBUF_ALGOS, STLSOFT_NUM_ELEMENTS(MBUF_ALGOS));
    run_wcs("empty_wcs", L"", 0, iters, warm, WCS_ALGOS, STLSOFT_NUM_ELEMENTS(WCS_ALGOS));
    run_wbuf("empty_wbuf", L"", 0, iters, warm, WBUF_ALGOS, STLSOFT_NUM_ELEMENTS(WBUF_ALGOS));

    return true;
}

bool
run_length(
    size_t n
,   size_t iters
,   size_t warm
)
{
    std::string const alpha = make_payload(n);
    std::string const mixed = make_mixed(n);
    std::string const high = make_high(n);
    std::string const embedded = make_embedded(n);

    std::vector<cstring_char_t> const a_alpha = ambient_from(alpha);
    std::vector<cstring_char_t> const a_mixed = ambient_from(mixed);

    std::vector<wchar_t> const walpha = terminated_wide(alpha);
    std::vector<wchar_t> const wmixed = terminated_wide(mixed);
    std::vector<wchar_t> const whigh = wide_high(n);
    std::vector<wchar_t> const wembedded = wide_embedded(n);

    if (!with_cstring(
            "cstring_alpha"
        ,   a_alpha.data()
        ,   n
        ,   [&](cstring_t const* pcs)
            {
                run_cstring(
                    "cstring_alpha"
                ,   n
                ,   iters
                ,   warm
                ,   CSTRING_ALGOS
                ,   STLSOFT_NUM_ELEMENTS(CSTRING_ALGOS)
                ,   pcs
                );
            }
        ))
    {
        return false;
    }

    if (!with_cstring(
            "cstring_case"
        ,   a_mixed.data()
        ,   n
        ,   [&](cstring_t const* pcs)
            {
                run_cstring(
                    "cstring_case"
                ,   n
                ,   iters
                ,   warm
                ,   CSTRING_CASE_ALGOS
                ,   STLSOFT_NUM_ELEMENTS(CSTRING_CASE_ALGOS)
                ,   pcs
                );
            }
        ))
    {
        return false;
    }

    run_mbs("mbs_alpha", alpha.c_str(), n, iters, warm, MBS_ALGOS, STLSOFT_NUM_ELEMENTS(MBS_ALGOS));
    run_mbs("mbs_case", mixed.c_str(), n, iters, warm, MBS_CASE_ALGOS, STLSOFT_NUM_ELEMENTS(MBS_CASE_ALGOS));

    run_mbuf("mbuf_alpha", alpha.data(), n, iters, warm, MBUF_ALGOS, STLSOFT_NUM_ELEMENTS(MBUF_ALGOS));
    run_mbuf("mbuf_case", mixed.data(), n, iters, warm, MBUF_CASE_ALGOS, STLSOFT_NUM_ELEMENTS(MBUF_CASE_ALGOS));
    run_mbuf("mbuf_embedded_nul", embedded.data(), n, iters, warm, MBUF_ALGOS, STLSOFT_NUM_ELEMENTS(MBUF_ALGOS));
    run_mbuf("mbuf_high_case", high.data(), n, iters, warm, MBUF_CASE_ALGOS, STLSOFT_NUM_ELEMENTS(MBUF_CASE_ALGOS));

    run_wcs("wcs_alpha", walpha.data(), n, iters, warm, WCS_ALGOS, STLSOFT_NUM_ELEMENTS(WCS_ALGOS));
    run_wcs("wcs_case", wmixed.data(), n, iters, warm, WCS_CASE_ALGOS, STLSOFT_NUM_ELEMENTS(WCS_CASE_ALGOS));

    run_wbuf("wbuf_alpha", walpha.data(), n, iters, warm, WBUF_ALGOS, STLSOFT_NUM_ELEMENTS(WBUF_ALGOS));
    run_wbuf("wbuf_case", wmixed.data(), n, iters, warm, WBUF_CASE_ALGOS, STLSOFT_NUM_ELEMENTS(WBUF_CASE_ALGOS));
    run_wbuf("wbuf_embedded_nul", wembedded.data(), n, iters, warm, WBUF_ALGOS, STLSOFT_NUM_ELEMENTS(WBUF_ALGOS));
    run_wbuf("wbuf_high_case", whigh.data(), n, iters, warm, WBUF_CASE_ALGOS, STLSOFT_NUM_ELEMENTS(WBUF_CASE_ALGOS));

    return true;
}


/* /////////////////////////////////////////////////////////////////////////
 * banner
 */

void
display_banner()
{
    std::cout
        << "test.performance.hash: djb2, FNV-1a, and SDBM against lose-lose."
        << std::endl
        << "  Human attention only; not a CI gate. Prefer a Release build."
        << std::endl
        << "  lose-lose adds each low octet. \"vs cstr\" is the ratio"
        << std::endl
        << "  against that baseline (lose-lose prints 1.00)."
        << std::endl
        << "  A group is one scenario and length: lose-lose, djb2, fnv1a, sdbm."
        << std::endl
        << "  SIS_PERFTESTS_GROUPGAPS=1 separates groups"
        << std::endl
        << "  (run_all_performance_tests.sh --gap-groups)."
        << std::endl
        << "  *_case rows fold case. mbuf_high_case folds octets >= 0x80."
        << std::endl
        << "  wbuf_high_case folds code units above 0xFF (low 8 bits)."
        << std::endl
        << "  *_embedded_nul hashes interior NULs (odd units are NUL)."
        << std::endl
        << "  Payloads are built outside the timed loop. Iterations fall"
        << std::endl
        << "  as length grows so each row visits a similar octet count."
        << std::endl
#ifdef HAS_P99
        << "  p99: p50/p90/p99/max are one iteration, not divided by #acts."
        << std::endl
        << "  vs cstr is \"-\" when p50 is 0 and ns/op does not grow."
        << std::endl
#endif /* HAS_P99 */
        << "  Env: CSTRING_PERF_ITERATIONS, CSTRING_PERF_WARMUPS,"
        << std::endl
        << "  SIS_PERFTESTS_GROUPGAPS."
        << std::endl
        ;
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /*argc*/, char* /*argv*/[])
{
    size_t const base = cstring_perf::default_iterations();
    size_t const warm = cstring_perf::default_warmups();

    display_banner();
    cstring_perf::display_results_title();

    if (!run_null_and_empty(base, warm))
    {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; STLSOFT_NUM_ELEMENTS(SIZES) != i; ++i)
    {
        size_t const n = SIZES[i];

        if (!run_length(n, iterations_for_length(n, base), warm))
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

