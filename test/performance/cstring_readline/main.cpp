/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/test.performance.cstring_readline/main.cpp
 *
 * Purpose: Competitive performance tests for cstring_readline() against
 *          std::getline, fgets (bounded buffer), and a char-at-a-time fgetc
 *          floor. Scenarios cover reused capacity, CRLF stripping, a fresh
 *          instance per line, a pre-reserved buffer, empty lines, and an
 *          unterminated final line. Percentiles and this filesystem suite
 *          require p99.
 *
 * Created: 27th September 2026
 * Updated: 4th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>

#include "perf_harness.hpp"

#ifdef HAS_P99
# include <fstream>
# include <string>
# include <vector>

# include <stdio.h>
# include <string.h>
#endif /* HAS_P99 */

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

#ifdef HAS_P99
namespace {

char const* const IMPL_READLINE = "cstring_readline";
char const* const IMPL_GETLINE  = "std::getline";
char const* const IMPL_FGETS    = "fgets";
char const* const IMPL_RAW      = "raw_fgetc";

char const TEST_FILE_NAME[] = "test.performance.cstring_readline.lines.txt";

using namespace cstring_perf;

enum instance_mode_t
{
    INSTANCE_REUSE = 0,
    INSTANCE_FRESH,
    INSTANCE_PRERESERVED,
};

struct readline_case
{
    char const*     scenario;
    size_t          num_lines;
    size_t          line_len;
    line_ending_t   ending;
    instance_mode_t mode;
};

readline_case const CASES[] =
{
    { "readline_empty_lines",      2000u,     0u, LINE_ENDING_LF,   INSTANCE_REUSE, },
    { "readline_fresh_each_line",   200u,    80u, LINE_ENDING_LF,   INSTANCE_FRESH, },
    { "readline_prereserved",       100u,  1024u, LINE_ENDING_LF,   INSTANCE_PRERESERVED, },
    { "readline_reuse_crlf",       1000u,    80u, LINE_ENDING_CRLF, INSTANCE_REUSE, },
    { "readline_reuse_lf",         1000u,    16u, LINE_ENDING_LF,   INSTANCE_REUSE, },
    { "readline_reuse_lf",         1000u,    80u, LINE_ENDING_LF,   INSTANCE_REUSE, },
    { "readline_reuse_lf",          100u,  1024u, LINE_ENDING_LF,   INSTANCE_REUSE, },
    { "readline_unterminated_eof",    1u, 16384u, LINE_ENDING_NONE, INSTANCE_REUSE, },
};
} // anonymous namespace
#endif /* HAS_P99 */


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

#ifdef HAS_P99
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
        IMPL_READLINE,
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

std::uint64_t
line_anchor(
    size_t          len
,   unsigned char   head
)
{
    return static_cast<std::uint64_t>(len) + 1u + static_cast<std::uint64_t>(head);
}

unsigned char
content_head(
    char const* p
,   size_t      n
)
{
    if (0 == n || NULL == p)
    {
        return 0;
    }

    return static_cast<unsigned char>(p[0]);
}

std::uint64_t
read_all_cstring(
    char const*     path
,   size_t          line_len
,   instance_mode_t mode
)
{
    FILE* const f = std::fopen(path, "rb");

    if (NULL == f)
    {
        return 0;
    }

    cstring_t cs = cstring_t_DEFAULT;
    std::uint64_t anchor = 0;

    if (INSTANCE_PRERESERVED == mode && 0 != line_len)
    {
        if (CSTRING_RC_SUCCESS != cstring_setCapacity(&cs, line_len))
        {
            cstring_destroy(&cs);
            std::fclose(f);

            return 0;
        }
    }

    for (;;)
    {
        if (INSTANCE_FRESH == mode && NULL != cs.ptr)
        {
            cstring_destroy(&cs);
            cs = cstring_t_DEFAULT;
        }

        CSTRING_RC const rc = cstring_readline(f, &cs, NULL);

        if (CSTRING_RC_SUCCESS != rc && CSTRING_RC_EOF != rc)
        {
            anchor = 0;
            break;
        }

        if (0 != cs.len || CSTRING_RC_EOF != rc)
        {
            anchor += line_anchor(cs.len, content_head(cs.ptr, cs.len));
        }

        if (CSTRING_RC_EOF == rc)
        {
            break;
        }
    }

    cstring_destroy(&cs);
    std::fclose(f);

    return anchor;
}

std::uint64_t
read_all_getline(
    char const*     path
,   size_t          line_len
,   instance_mode_t mode
)
{
    std::ifstream in(path, std::ios::in | std::ios::binary);

    if (!in)
    {
        return 0;
    }

    std::string line;
    std::uint64_t anchor = 0;

    if (INSTANCE_PRERESERVED == mode && 0 != line_len)
    {
        line.reserve(line_len);
    }

    while (std::getline(in, line))
    {
        if (!line.empty() && '\r' == line[line.size() - 1u])
        {
            line.pop_back();
        }

        anchor += line_anchor(line.size(), content_head(line.data(), line.size()));

        if (INSTANCE_FRESH == mode)
        {
            std::string empty;

            line.swap(empty);
        }
    }

    return anchor;
}

/* Pre-reserved keeps one buffer of line_len + 4 (content, CR, LF, NUL).
 * Fresh allocates that size again for each line. Reuse keeps one 4096-byte
 * buffer and stitches a read that does not end in a newline, holding a CR
 * that falls on a chunk boundary until the next read.
 */
size_t const FGETS_REUSE_BUF = 4096u;

std::uint64_t
read_all_fgets(
    char const*     path
,   size_t          line_len
,   instance_mode_t mode
)
{
    FILE* const f = std::fopen(path, "rb");

    if (NULL == f)
    {
        return 0;
    }

    size_t const buf_n =
        (INSTANCE_REUSE == mode) ? FGETS_REUSE_BUF : (line_len + 4u)
        ;

    std::vector<char>   buf;
    std::uint64_t       anchor      =   0;
    size_t              content_len =   0;
    unsigned char       head        =   0;
    bool                pending_cr  =   false;

    if (INSTANCE_FRESH != mode)
    {
        buf.resize(buf_n);
    }

    for (;;)
    {
        if (INSTANCE_FRESH == mode)
        {
            buf.resize(buf_n);
        }

        if (NULL == std::fgets(&buf[0], static_cast<int>(buf.size()), f))
        {
            if (pending_cr)
            {
                if (0 == content_len)
                {
                    head = static_cast<unsigned char>('\r');
                }

                ++content_len;
                pending_cr = false;
            }

            if (0 != content_len)
            {
                anchor += line_anchor(content_len, head);
            }

            break;
        }

        size_t const    n           =   std::strlen(&buf[0]);
        bool            line_done   =   false;

        for (size_t i = 0; n != i; ++i)
        {
            unsigned char const ch = static_cast<unsigned char>(buf[i]);

            if (pending_cr)
            {
                pending_cr = false;

                if ('\n' == ch)
                {
                    line_done = true;

                    break;
                }

                if (0 == content_len)
                {
                    head = static_cast<unsigned char>('\r');
                }

                ++content_len;
            }

            if ('\n' == ch)
            {
                line_done = true;

                break;
            }

            if ('\r' == ch)
            {
                pending_cr = true;

                continue;
            }

            if (0 == content_len)
            {
                head = ch;
            }

            ++content_len;
        }

        if (!line_done)
        {
            continue;
        }

        anchor += line_anchor(content_len, (0 == content_len) ? 0u : head);
        content_len = 0;
        head = 0;
        pending_cr = false;

        if (INSTANCE_FRESH == mode)
        {
            std::vector<char> empty;

            buf.swap(empty);
        }
    }

    std::fclose(f);

    return anchor;
}

std::uint64_t
read_all_raw_fgetc(
    char const*     path
,   size_t          line_len
,   instance_mode_t mode
)
{
    FILE* const f = std::fopen(path, "rb");

    if (NULL == f)
    {
        return 0;
    }

    raw_string s;
    raw_init(&s);

    if (INSTANCE_PRERESERVED == mode && 0 != line_len)
    {
        if (0 != raw_reserve(&s, line_len))
        {
            raw_destroy(&s);
            std::fclose(f);

            return 0;
        }
    }

    std::uint64_t anchor = 0;
    int previous = '\0';

    for (;;)
    {
        int const ch = std::fgetc(f);

        if (EOF == ch)
        {
            if (0 != s.len)
            {
                anchor += line_anchor(s.len, content_head(s.ptr, s.len));
            }

            break;
        }

        if ('\n' == ch)
        {
            if ('\r' == previous && 0 != s.len)
            {
                --s.len;
                s.ptr[s.len] = '\0';
            }

            anchor += line_anchor(s.len, content_head(s.ptr, s.len));
            s.len = 0;

            if (NULL != s.ptr)
            {
                s.ptr[0] = '\0';
            }

            previous = '\0';

            if (INSTANCE_FRESH == mode)
            {
                raw_destroy(&s);
                raw_init(&s);
            }

            continue;
        }

        char const c = static_cast<char>(ch);

        if (0 != raw_append_len(&s, &c, 1u))
        {
            anchor = 0;
            break;
        }

        previous = ch;
    }

    raw_destroy(&s);
    std::fclose(f);

    return anchor;
}

bool
anchors_agree(
    char const*         scenario
,   size_t              line_len
,   run_result const&   cs
,   run_result const&   gl
,   run_result const&   fg
,   run_result const&   raw
)
{
    if (0 != cs.anchor &&
        cs.anchor == gl.anchor &&
        cs.anchor == fg.anchor &&
        cs.anchor == raw.anchor)
    {
        return true;
    }

    std::cerr
        << "anchor mismatch in " << scenario
        << " size " << line_len
        << ": cstring_readline=" << cs.anchor
        << " std::getline=" << gl.anchor
        << " fgets=" << fg.anchor
        << " raw_fgetc=" << raw.anchor
        << std::endl
        ;

    return false;
}

bool
scenario_readline(
    readline_case const&    spec
,   size_t                  num_trials
,   size_t                  num_warm_loops
)
{
    if (LINE_ENDING_NONE == spec.ending && 1u != spec.num_lines)
    {
        std::cerr
            << spec.scenario
            << ": unterminated input must be a single line"
            << std::endl
            ;

        return false;
    }

    if (!write_lines_file(TEST_FILE_NAME, spec.num_lines, spec.line_len, spec.ending))
    {
        std::cerr
            << "failed to write " << TEST_FILE_NAME
            << "; skipping " << spec.scenario
            << std::endl
            ;
        std::remove(TEST_FILE_NAME);

        return true;
    }

    char const* const       path        =   TEST_FILE_NAME;
    size_t const            line_len    =   spec.line_len;
    instance_mode_t const   mode        =   spec.mode;

    run_result const cs = time_iterations(num_trials, num_warm_loops, [path, line_len, mode]() -> std::uint64_t {
        return read_all_cstring(path, line_len, mode);
    });

    run_result const gl = time_iterations(num_trials, num_warm_loops, [path, line_len, mode]() -> std::uint64_t {
        return read_all_getline(path, line_len, mode);
    });

    run_result const fg = time_iterations(num_trials, num_warm_loops, [path, line_len, mode]() -> std::uint64_t {
        return read_all_fgets(path, line_len, mode);
    });

    run_result const raw = time_iterations(num_trials, num_warm_loops, [path, line_len, mode]() -> std::uint64_t {
        return read_all_raw_fgetc(path, line_len, mode);
    });

    bool const ok = anchors_agree(spec.scenario, spec.line_len, cs, gl, fg, raw);

    if (ok)
    {
        emit_row(spec.scenario, spec.line_len, IMPL_READLINE, num_trials, spec.num_lines, cs, cs.tm_ns);
        emit_row(spec.scenario, spec.line_len, IMPL_GETLINE, num_trials, spec.num_lines, gl, cs.tm_ns);
        emit_row(spec.scenario, spec.line_len, IMPL_FGETS, num_trials, spec.num_lines, fg, cs.tm_ns);
        emit_row(spec.scenario, spec.line_len, IMPL_RAW, num_trials, spec.num_lines, raw, cs.tm_ns);
    }

    std::remove(TEST_FILE_NAME);

    return ok;
}
} // anonymous namespace
#endif /* HAS_P99 */


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /*argc*/, char* /*argv*/[])
{
#ifdef HAS_P99

    size_t const    num_trials      =   cstring_perf::default_file_trials();
    size_t const    num_warm_loops  =   cstring_perf::default_warmups();

    cstring_perf::display_banner("test.performance.cstring_readline");

    std::cout
        << "readline suite (#acts = lines, so ns/op is per line;"
        << std::endl
        << "  cstring_readline is fgetc + one-character append;"
        << std::endl
        << "  fgets: fresh allocates line_len+4 per line, pre-reserved"
        << std::endl
        << "  keeps that buffer, reuse keeps a 4 KB buffer and stitches):"
        << std::endl
        ;

    cstring_perf::display_results_title();

    for (size_t i = 0; STLSOFT_NUM_ELEMENTS(CASES) != i; ++i)
    {
        if (!scenario_readline(CASES[i], num_trials, num_warm_loops))
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
#else /* ? HAS_P99 */

    cstring_perf::display_banner("test.performance.cstring_readline");

    std::cout
        << "\nreadline suite skipped (p99 not available)."
        << std::endl
        ;

    return EXIT_SUCCESS;
#endif /* HAS_P99 */
}


/* ///////////////////////////// end of file //////////////////////////// */

