/* /////////////////////////////////////////////////////////////////////////
 * File:    test/scratch/hash/main.cpp
 *
 * Purpose: Reports how lose-lose, djb2, FNV-1a, and SDBM spread 10000
 *          pseudo-random strings: distinct 64-bit values, distinct values
 *          in each hash octet, and distinct residues for likely hashtable
 *          divisors.
 *
 * Created: 6th October 2026
 * Updated: 6th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/hash.h>

#include "lose_lose.h"

#include <stlsoft/stlsoft.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_set>
#include <vector>


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

size_t const NUM_STRINGS    =   10000u;
size_t const MIN_LENGTH     =   1u;
size_t const MAX_LENGTH     =   64u;

/* splitmix64. Printed with the report so a run can be repeated. */

uint64_t const GENERATOR_SEED = 0x0000000c5711a601ull;

/* Powers of two, and a prime just below each. A power of two uses the low
 * bits. The prime mixes the whole hash.
 */

uint64_t const DIVISORS[] =
{
    251ull,
    256ull,
    1021ull,
    1024ull,
    4093ull,
    4096ull,
    8191ull,
    8192ull,
    16381ull,
    16384ull,
    32749ull,
    32768ull,
    65521ull,
    65536ull,
};

extern "C"
{

typedef cstring_hash_t (mbuf_fn_t)(char const*, size_t);

} /* extern "C" */

struct algo_t
{
    char const* name;
    mbuf_fn_t*  fn;
};

/* lose-lose stays first: it is the sum the other rows are read against.
 * Same order as test.performance.hash.
 */

algo_t const ALGOS[] =
{
    { "lose-lose", lose_lose_mbuf, },
    { "djb2", cstring_hash_djb2_mbuf, },
    { "fnv1a", cstring_hash_fnv1a_mbuf, },
    { "sdbm", cstring_hash_sdbm_mbuf, },
};


/* /////////////////////////////////////////////////////////////////////////
 * generation
 */

uint64_t
splitmix64(uint64_t* state)
{
    uint64_t z = (*state += 0x9E3779B97F4A7C15ull);

    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;

    return z ^ (z >> 31);
}

bool
generate_strings(
    std::vector<std::string>&   strings
,   size_t&                     len_min
,   size_t&                     len_max
,   double&                     len_mean
)
{
    std::unordered_set<std::string> seen;
    uint64_t                        state = GENERATOR_SEED;
    size_t                          len_sum = 0u;
    size_t                          attempts = 0u;

    seen.reserve(NUM_STRINGS);
    strings.clear();
    strings.reserve(NUM_STRINGS);

    len_min = MAX_LENGTH;
    len_max = MIN_LENGTH;

    while (NUM_STRINGS != strings.size())
    {
        uint64_t const span = static_cast<uint64_t>(MAX_LENGTH - MIN_LENGTH) + 1ull;
        size_t const   len  = MIN_LENGTH + static_cast<size_t>(splitmix64(&state) % span);
        std::string    s(len, '\0');

        ++attempts;

        if (attempts > (NUM_STRINGS * 100u))
        {
            ::fprintf(stderr, "test.scratch.hash: stopped while building unique strings\n");

            return false;
        }

        for (size_t i = 0; len != i; ++i)
        {
            unsigned const octet = 1u + static_cast<unsigned>(splitmix64(&state) % 255ull);

            s[i] = static_cast<char>(octet);
        }

        if (!seen.insert(s).second)
        {
            continue;
        }

        len_sum += len;

        if (len < len_min)
        {
            len_min = len;
        }

        if (len > len_max)
        {
            len_max = len;
        }

        strings.push_back(s);
    }

    len_mean = static_cast<double>(len_sum) / static_cast<double>(strings.size());

    return true;
}


/* /////////////////////////////////////////////////////////////////////////
 * spread
 */

void
report_absolute(
    std::vector<uint64_t> const& hashes
)
{
    std::vector<uint64_t> sorted(hashes);
    size_t                distinct = 0u;
    size_t                run = 0u;
    size_t                max_mult = 0u;
    uint64_t              previous = 0u;

    std::sort(sorted.begin(), sorted.end());

    for (size_t i = 0; sorted.size() != i; ++i)
    {
        if ((0u == i) || (sorted[i] != previous))
        {
            ++distinct;
            run = 1u;
            previous = sorted[i];
        }
        else
        {
            ++run;
        }

        if (run > max_mult)
        {
            max_mult = run;
        }
    }

    ::printf(
        "  absolute   inputs %zu   distinct %zu   collisions %zu   max multiplicity %zu\n"
    ,   hashes.size()
    ,   distinct
    ,   hashes.size() - distinct
    ,   max_mult
    );
}

void
report_octets(
    std::vector<uint64_t> const& hashes
)
{
    uint32_t lane[8][256] = {};
    double const mean = static_cast<double>(hashes.size()) / 256.0;

    for (size_t i = 0; hashes.size() != i; ++i)
    {
        uint64_t const hash = hashes[i];

        for (unsigned b = 0u; 8u != b; ++b)
        {
            unsigned const octet = static_cast<unsigned>((hash >> (8u * b)) & 0xffu);

            lane[b][octet] += 1u;
        }
    }

    ::printf("  octet lanes (lane 0 is the low 8 bits; mean %.2f):\n", mean);
    ::printf("    %-6s %6s %10s %8s %8s\n", "lane", "bits", "distinct", "min", "max");

    for (unsigned b = 0u; 8u != b; ++b)
    {
        uint32_t min_count = lane[b][0];
        uint32_t max_count = lane[b][0];
        size_t   distinct = 0u;

        for (unsigned octet = 0u; 256u != octet; ++octet)
        {
            uint32_t const count = lane[b][octet];

            if (0u != count)
            {
                ++distinct;
            }

            if (count < min_count)
            {
                min_count = count;
            }

            if (count > max_count)
            {
                max_count = count;
            }
        }

        ::printf(
            "    %6u %3u-%-2u %10zu %8u %8u\n"
        ,   b
        ,   8u * b
        ,   (8u * b) + 7u
        ,   distinct
        ,   min_count
        ,   max_count
        );
    }
}

void
report_moduli(
    std::vector<uint64_t> const& hashes
)
{
    ::printf("  hashtable moduli (uniform is the distinct count of a uniform hash):\n");
    ::printf(
        "    %8s %10s %10s %8s %8s %8s\n"
    ,   "divisor"
    ,   "distinct"
    ,   "uniform"
    ,   "empty"
    ,   "max"
    ,   "mean"
    );

    for (size_t d = 0; STLSOFT_NUM_ELEMENTS(DIVISORS) != d; ++d)
    {
        uint64_t const           divisor = DIVISORS[d];
        std::vector<uint32_t>    bins(static_cast<size_t>(divisor), 0u);
        size_t                   distinct = 0u;
        size_t                   empty = 0u;
        uint32_t                 max_count = 0u;
        double const             load = static_cast<double>(hashes.size()) / static_cast<double>(divisor);
        double const             uniform = static_cast<double>(divisor) * (1.0 - std::exp(-load));

        for (size_t i = 0; hashes.size() != i; ++i)
        {
            uint64_t const residue = hashes[i] % divisor;

            bins[static_cast<size_t>(residue)] += 1u;
        }

        for (size_t i = 0; bins.size() != i; ++i)
        {
            uint32_t const count = bins[i];

            if (0u == count)
            {
                ++empty;
            }
            else
            {
                ++distinct;
            }

            if (count > max_count)
            {
                max_count = count;
            }
        }

        ::printf(
            "    %8llu %10zu %10.1f %8zu %8u %8.2f\n"
        ,   static_cast<unsigned long long>(divisor)
        ,   distinct
        ,   uniform
        ,   empty
        ,   max_count
        ,   load
        );
    }
}

void
assess(
    char const*                     name
,   mbuf_fn_t*                      fn
,   std::vector<std::string> const& strings
)
{
    std::vector<uint64_t> hashes;

    hashes.reserve(strings.size());

    for (size_t i = 0; strings.size() != i; ++i)
    {
        hashes.push_back(fn(strings[i].data(), strings[i].size()));
    }

    ::printf("\n%s\n", name);
    report_absolute(hashes);
    ::printf("\n");
    report_octets(hashes);
    ::printf("\n");
    report_moduli(hashes);
}

void
display_banner()
{
    ::printf("test.scratch.hash: spread of lose-lose, djb2, FNV-1a, and SDBM.\n");
    ::printf("  Human attention only; not a CI gate.\n");
    ::printf("  %zu distinct strings. Lengths %zu..%zu. Octets 0x01..0xFF.\n", NUM_STRINGS, MIN_LENGTH, MAX_LENGTH);
    ::printf("  Generator seed 0x%016llx (splitmix64). Duplicate strings are\n", static_cast<unsigned long long>(GENERATOR_SEED));
    ::printf("  discarded, so an absolute collision is a hash collision.\n");
    ::printf("  lose-lose adds each octet (lose_lose_mbuf). djb2, FNV-1a,\n");
    ::printf("  and SDBM use the counted multibyte mix (cstring_hash_*_mbuf).\n");
    ::printf("  absolute: distinct full 64-bit values.\n");
    ::printf("  octet: each of the 8 hash bytes. A mixed lane uses all 256\n");
    ::printf("  values, with min near the mean.\n");
    ::printf("  modulo: residue = hash %% divisor. Compare distinct with\n");
    ::printf("  uniform. empty and max are bucket occupancy.\n");
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /*argc*/, char* /*argv*/[])
{
    std::vector<std::string>    strings;
    size_t                      len_min = 0u;
    size_t                      len_max = 0u;
    double                      len_mean = 0.0;

    display_banner();

    if (!generate_strings(strings, len_min, len_max, len_mean))
    {
        return EXIT_FAILURE;
    }

    ::printf(
        "  realised lengths min %zu  max %zu  mean %.2f\n"
    ,   len_min
    ,   len_max
    ,   len_mean
    );

    for (size_t i = 0; STLSOFT_NUM_ELEMENTS(ALGOS) != i; ++i)
    {
        assess(ALGOS[i].name, ALGOS[i].fn, strings);
    }

    ::printf("\n");

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

