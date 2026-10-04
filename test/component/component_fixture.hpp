/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/component_fixture.hpp
 *
 * Purpose: Shared file fixtures and setup/teardown for cstring component
 *          tests.
 *
 * Created: 3rd October 2026
 * Updated: 3rd October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#ifndef CSTRING_TEST_COMPONENT_COMPONENT_FIXTURE_HPP_INCLUDED
#define CSTRING_TEST_COMPONENT_COMPONENT_FIXTURE_HPP_INCLUDED


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/internal/safestr.h>

#include <platformstl/exception/platformstl_exception.hpp>
#include <platformstl/system/system_traits.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>

#include <string>

#include <stddef.h>
#include <stdio.h>


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

namespace cstring_component
{


/* /////////////////////////////////////////////////////////////////////////
 * file fixtures
 */

inline
FILE*
fopen_or_throw(
    char const* fileName
,   char const* mode
)
{
#ifdef CSTRING_USING_SAFE_STR_FUNCTIONS
    FILE*   f;

    if (0 != ::fopen_s(&f, fileName, mode))
#else /* ? CSTRING_USING_SAFE_STR_FUNCTIONS */
    FILE*   f = ::fopen(fileName, mode);

    if (NULL == f)
#endif /* CSTRING_USING_SAFE_STR_FUNCTIONS */
    {
        throw platformstl::platform_exception((std::string("Could not open file '") + fileName + "'").c_str(), platformstl::system_traits<char>::get_last_error());
    }

    return f;
}

inline
void
write_bytes(
    char const* fileName
,   void const* bytes
,   size_t      cb
)
{
    FILE* f = fopen_or_throw(fileName, "wb");

    stlsoft::scoped_handle<FILE*> scoper(f, ::fclose);

    if (cb != ::fwrite(bytes, 1, cb, f))
    {
        throw platformstl::platform_exception("Could not write test file", platformstl::system_traits<char>::get_last_error());
    }
}

inline
void
write_string_bytes(
    char const*         fileName
,   std::string const&  bytes
)
{
    write_bytes(fileName, bytes.data(), bytes.size());
}

inline
std::string
make_filled(
    size_t  n
,   char    ch
)
{
    return std::string(n, ch);
}


/* /////////////////////////////////////////////////////////////////////////
 * xTests runner
 */

inline
int
setup(void*)
{
    return 0;
}

inline
int
teardown(void* arg)
{
    char const* path = static_cast<char const*>(arg);

    if (NULL != path &&
        '\0' != path[0])
    {
        ::remove(path);
    }

    return 0;
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

} // namespace cstring_component


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* !CSTRING_TEST_COMPONENT_COMPONENT_FIXTURE_HPP_INCLUDED */

/* ///////////////////////////// end of file //////////////////////////// */

