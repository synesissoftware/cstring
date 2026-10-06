/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring/common.h
 *
 * Purpose: Common definitions for the cstring headers.
 *
 * Created: 5th October 2026
 * Updated: 6th October 2026
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


/** \file cstring/common.h Common definitions for the cstring headers
 */

#ifndef CSTRING_INCL_CSTRING_H_COMMON
#define CSTRING_INCL_CSTRING_H_COMMON


/* /////////////////////////////////////////////////////////////////////////
 * version
 */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
# define CSTRING_VER_CSTRING_H_COMMON_MAJOR     1
# define CSTRING_VER_CSTRING_H_COMMON_MINOR     0
# define CSTRING_VER_CSTRING_H_COMMON_REVISION  1
# define CSTRING_VER_CSTRING_H_COMMON_EDIT      1
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stddef.h>


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

/* Shared detection of <stdint.h>, used by cstring/hash.h when selecting the
 * type of cstring_hash_t.
 */

#if 0
#elif defined(__STDC_VERSION__) &&\
      __STDC_VERSION__ >= 199901L

# define CSTRING_HAS_h_stdint_
#elif defined(__cplusplus) &&\
      defined(__has_include) &&\
      __has_include(<stdint.h>)

# define CSTRING_HAS_h_stdint_
#elif defined(__cplusplus) &&\
      __cplusplus >= 201103L

# define CSTRING_HAS_h_stdint_
#elif 0 ||\
      (   defined(_MSC_VER) &&\
          _MSC_VER >= 1310) ||\
      0

# define CSTRING_HAS_h_stdint_
#else

#endif


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifdef CSTRING_HAS_h_stdint_
# include <stdint.h>
#endif /* CSTRING_HAS_h_stdint_ */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* CSTRING_INCL_CSTRING_H_COMMON */

/* ///////////////////////////// end of file //////////////////////////// */

