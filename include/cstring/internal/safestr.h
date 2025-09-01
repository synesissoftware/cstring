/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring/internal/safestr.h
 *
 * Purpose: Internal utility header for the cstring API.
 *
 * Created: 13th May 2008
 * Updated: 23rd March 2025
 *
 * Home:    http://synesis.com.au/software/
 *
 * Copyright (c) 2019-2025, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2008-2019, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the names of Matthew Wilson and Synesis Information Systems nor
 *   the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file cstring/internal/safestr.h Internal utility header for the cstring API
 */

#ifndef CSTRING_INCL_CSTRING_INTERNAL_H_SAFESTR
#define CSTRING_INCL_CSTRING_INTERNAL_H_SAFESTR

/* /////////////////////////////////////////////////////////////////////////
 * version
 */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
# define CSTRING_VER_CSTRING_INTERNAL_H_SAFESTR_MAJOR       1
# define CSTRING_VER_CSTRING_INTERNAL_H_SAFESTR_MINOR       0
# define CSTRING_VER_CSTRING_INTERNAL_H_SAFESTR_REVISION    1
# define CSTRING_VER_CSTRING_INTERNAL_H_SAFESTR_EDIT        4
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>

#ifdef CSTRING_SAFE_STR_USE_crtdefs_h_
# undef CSTRING_SAFE_STR_USE_crtdefs_h_
#endif /* CSTRING_SAFE_STR_USE_crtdefs_h_ */

#if 0
#elif defined(__BORLANDC__)
#elif defined(__DMC__)
#elif defined(__GNUC__)
#elif defined(__INTEL_COMPILER)

# if defined(_MSC_VER) && \
     _MSC_VER >= 1400

#  define CSTRING_SAFE_STR_USE_crtdefs_h_
# endif /* _MSC_VER >= 1400 */
#elif defined(__MWERKS__)
#elif defined(__WATCOMC__)
#elif defined(_MSC_VER)

# if _MSC_VER >= 1400

#  define CSTRING_SAFE_STR_USE_crtdefs_h_
# endif /* _MSC_VER >= 1400 */
#elif defined(__COMO__)
#else
#endif /* compiler */

#ifdef CSTRING_SAFE_STR_USE_crtdefs_h_
# include <crtdefs.h>
#endif /* CSTRING_SAFE_STR_USE_crtdefs_h_ */

/* /////////////////////////////////////////////////////////////////////////
 * feature detection
 */

#ifdef __STDC_SECURE_LIB__

# if defined(__STDC_WANT_SECURE_LIB__) && \
     __STDC_WANT_SECURE_LIB__ == 1

#  define CSTRING_USING_SAFE_STR_FUNCTIONS
# endif /* __STDC_WANT_SECURE_LIB__ == 1 */
#endif /* __STDC_SECURE_LIB__ */

/* ////////////////////////////////////////////////////////////////////// */

#endif /* CSTRING_INCL_CSTRING_INTERNAL_H_SAFESTR */

/* ///////////////////////////// end of file //////////////////////////// */

