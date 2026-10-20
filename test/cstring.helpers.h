/* /////////////////////////////////////////////////////////////////////////
 * File:    test/cstring.helpers.h
 *
 * Purpose: Literals and comparisons for examples and tests that compile
 *          when cstring_char_t is either char or wchar_t. This is not
 *          part of the library contract.
 *
 * Created: 5th October 2026
 * Updated: 5th October 2026
 *
 * Home:    http://synesis.com.au/software/
 *
 * Copyright (c) 2026, Matthew Wilson and Synesis Information Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the names of Matthew Wilson and Synesis Information Systems nor
 *   the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file test/cstring.helpers.h Literals and comparisons for examples and tests
 */

#ifndef CSTRING_INCL_TEST_H_CSTRING_HELPERS
#define CSTRING_INCL_TEST_H_CSTRING_HELPERS

/* /////////////////////////////////////////////////////////////////////////
 * version
 */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
# define CSTRING_VER_TEST_H_CSTRING_HELPERS_MAJOR       1
# define CSTRING_VER_TEST_H_CSTRING_HELPERS_MINOR       0
# define CSTRING_VER_TEST_H_CSTRING_HELPERS_REVISION    1
# define CSTRING_VER_TEST_H_CSTRING_HELPERS_EDIT        2
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>

#include <string.h>
#ifdef CSTRING_USE_WIDE_STRINGS
# include <wchar.h>
#endif /* CSTRING_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * literals and comparisons
 *
 * printf conversions are intentionally absent. `%ls` and `%.*ls` do not
 * mean the same thing on every compiler this library still supports, and
 * a precision may count bytes or characters. Print a cstring_t with
 * cstring_write() / cstring_writeline().
 */

#ifdef CSTRING_USE_WIDE_STRINGS

# define CSTRING_T_(x)                                      L ## x
# define CSTRING_STRCMP_(a, b)                              wcscmp((a), (b))
# define CSTRING_STRNCMP_(a, b, n)                          wcsncmp((a), (b), (n))
#else /* ? CSTRING_USE_WIDE_STRINGS */

# define CSTRING_T_(x)                                      x
# define CSTRING_STRCMP_(a, b)                              strcmp((a), (b))
# define CSTRING_STRNCMP_(a, b, n)                          strncmp((a), (b), (n))
#endif /* CSTRING_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* CSTRING_INCL_TEST_H_CSTRING_HELPERS */

/* ///////////////////////////// end of file //////////////////////////// */
