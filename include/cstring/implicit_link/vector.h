/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring/implicit_link/vector.h
 *
 * Purpose: Implicit linking for the cstring.vector library.
 *
 * Created: 27th January 2012
 * Updated: 20th February 2021
 *
 * Home:    http://synesis.com.au/software/
 *
 * Copyright (c) 2019-2021, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2012-2019, Matthew Wilson and Synesis Software
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


/** \file cstring/implicit_link/vector.h Implicit linking for the 
 *    cstring.vector library
 *
 * Inclusion of this file causes the appropriate library file to be
 * automatically linked for compilers that support implicit linking:
 *  - Borland
 *  - Metrowerks
 *  - CodeWarrior
 *  - Intel
 *  - Visual C++
 *
 * \note For compilers that do not support implicit linking, inclusion of
 *   the file has no effect.
 */

#ifndef CSTRING_INCL_CSTRING_IMPLICIT_LINK_H_VECTOR
#define CSTRING_INCL_CSTRING_IMPLICIT_LINK_H_VECTOR

/* /////////////////////////////////////////////////////////////////////////
 * version
 */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
# define CSTRING_VER_CSTRING_IMPLICIT_LINK_H_VECTOR_MAJOR       1
# define CSTRING_VER_CSTRING_IMPLICIT_LINK_H_VECTOR_MINOR       0
# define CSTRING_VER_CSTRING_IMPLICIT_LINK_H_VECTOR_REVISION    1
# define CSTRING_VER_CSTRING_IMPLICIT_LINK_H_VECTOR_EDIT        3
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/internal/implicit_link/base_.h>

/* /////////////////////////////////////////////////////////////////////////
 * implicit linking
 */

#ifdef CSTRING_IMPLICIT_LINK_SUPPORT

# define CSTRING_IMPL_LINK_VECTOR_NAME CSTRING_IMPL_LINK_LIBRARY_NAME(".vector")

# pragma message("lib: " CSTRING_IMPL_LINK_VECTOR_NAME)

# pragma comment(lib, CSTRING_IMPL_LINK_VECTOR_NAME)

#endif /* CSTRING_IMPLICIT_LINK_SUPPORT */

/* ////////////////////////////////////////////////////////////////////// */

#endif /* CSTRING_INCL_CSTRING_IMPLICIT_LINK_H_VECTOR */

/* ///////////////////////////// end of file //////////////////////////// */

