/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring/vector.h
 *
 * Purpose: Definition of the cstring.vector API.
 *
 * Created: 21st January 2012
 * Updated: 1st September 2025
 *
 * Home:    http://synesis.com.au/software/
 *
 * Copyright (c) 2019-2025, Matthew Wilson and Synesis Information Systems
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


/** \file cstring/vector.h Definition of the cstring.vector API
 */

#ifndef CSTRING_INCL_CSTRING_H_VECTOR
#define CSTRING_INCL_CSTRING_H_VECTOR

/* /////////////////////////////////////////////////////////////////////////
 * version
 */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
# define CSTRING_VER_CSTRING_H_VECTOR_MAJOR     1
# define CSTRING_VER_CSTRING_H_VECTOR_MINOR     0
# define CSTRING_VER_CSTRING_H_VECTOR_REVISION  2
# define CSTRING_VER_CSTRING_H_VECTOR_EDIT      7
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <cstring/cstring.h>


/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */

/** \brief The cstring-vector structure
 *
 * Represents a cstring-vector as a slice - length + pointer - along with
 * the allocated capacity, and flags controlling the allocation arena and
 * other characteristics.
 */
struct cstring_vector_t
{
    size_t          len;        /*!< Number of strings.                                 */
    cstring_t*      ptr;        /*!< Pointer to the first string. If \link cstring_vector_t::capacity capacity\endlink is 0, the
                                     value of this member is undetermined.              */
    size_t          capacity;   /*!< Number of instances available.                     */
    cstring_flags_t flags;      /*!< Flags. This field belongs to the implementation,
                                     and must not be modified by any application code.  */
};
#ifndef __cplusplus
typedef struct cstring_vector_t                             cstring_vector_t;
#endif /*!__cplusplus*/

/** \def cstring_vector_t_DEFAULT
 * \brief Default initialised value for a cstring_vector_t instance
 */
#define cstring_vector_t_DEFAULT                            { 0, NULL, 0, 0 }

/** \def cstring_vector_DEFAULT_CAPACITY
 *
 * Sentinel value to be passed to creator functions to indicate that the
 * implementation should select the default capacity.
 */
#define cstring_vector_DEFAULT_CAPACITY                     (~(size_t)(0))


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** \brief Initialises a cstring-vector instance to a default form
 *
 * \note This must only be called on an uninitialised cstring-vector
 *  instance;
 *
 * \pre (NULL != pcsv)
 */
CSTRING_RC
cstring_vector_init(
    cstring_vector_t*   pcsv
,   size_t              minCapacity
);

/** \brief Releases resources and resets the attributes of the
 *  cstring-vector instance
 *
 * \param pcsv The cstring instance to be destroyed;
 *
 * \note This must only be called on an initialised cstring-vector instance,
 *   which is then rendered in the uninitialised state.
 *
 * \retval CSTRING_RC_SUCCESS the capacity was destroyed
 *
 * \pre (NULL != pcsv)
 */
CSTRING_RC
cstring_vector_destroy(
    cstring_vector_t* pcsv
);

/** \brief Truncates the cstring-vector instance
 *
 * \param pcsv The cstring instance to be truncated;
 * \param len The required length. Ignored if not less than the current
 *   length;
 *
 * \note The cstring instance must not be readonly
 *
 * \retval CSTRING_RC_SUCCESS cstring-vector instance contents were
 *   truncated (or the truncation length was out of bounds);
 * \retval CSTRING_RC_READONLY the cstring-vector instance is marked
 *   readonly (CSTRING_F_MEMORY_IS_READONLY);
 *
 * \pre (NULL != pcsv)
 */
CSTRING_RC
cstring_vector_truncate(
    cstring_vector_t*   pcsv
,   size_t              len
);

/** \brief Creates a cstring-vector instance of the given size;
 *
 * \pre (NULL != pcsv)
 */
CSTRING_RC
cstring_vector_create(
    cstring_vector_t*   pcsv
,   size_t              initialSize
);

/**
 *
 * \param pcsv Pointer to the c-string vector instance
 * \param position Position within the vector at which to insert the given item(s)
 * \param strings Pointer to an array of cstring_t instances with at least
 *   as many elements as \c numStrings. May be NULL, in which case the
 *   function will behave as if \c strings points to an array containing
 *   \c numStrings blank cstring_t instances.
 * \param numStrings The number of cstring_t instances to be inserted at the
 *   given position.
 *
 * \pre (NULL != pcsv)
 * \pre (position <= pcsv->len)
 */
CSTRING_RC
cstring_vector_insertAt(
    cstring_vector_t*   pcsv
,   size_t              position
,   cstring_t const*    strings
,   size_t              numStrings
);

#define cstring_vector_append(pscv, strings, numStrings)    cstring_vector_insertAt((pscv), (pscv)->len, (strings), (numStrings))

#define cstring_vector_prepend(pscv, strings, numStrings)   cstring_vector_insertAt((pscv), 0, (strings), (numStrings))

/**
 *
 *
 * \pre (NULL != pcsv)
 */
CSTRING_RC
cstring_vector_readLines(
    FILE*               stm
,   cstring_vector_t*   pcsv
,   size_t*             numLinesRead /* = NULL */
);


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* CSTRING_INCL_CSTRING_H_VECTOR */

/* ///////////////////////////// end of file //////////////////////////// */

