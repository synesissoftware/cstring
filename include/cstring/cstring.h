/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring/cstring.h
 *
 * Purpose: Definition of the cstring.core API.
 *
 * Created: 16th June 1994
 * Updated: 22nd March 2025
 *
 * Home:    http://synesis.com.au/software/
 *
 * Copyright (c) 2019-2025, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 1994-2019, Matthew Wilson and Synesis Software
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


/** \file cstring/cstring.h Definition of the cstring.core API
 */

#ifndef CSTRING_INCL_CSTRING_H_CSTRING
#define CSTRING_INCL_CSTRING_H_CSTRING


/* /////////////////////////////////////////////////////////////////////////
 * version
 */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
# define CSTRING_VER_CSTRING_H_CSTRING_MAJOR    3
# define CSTRING_VER_CSTRING_H_CSTRING_MINOR    11
# define CSTRING_VER_CSTRING_H_CSTRING_REVISION 8
# define CSTRING_VER_CSTRING_H_CSTRING_EDIT     79
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */

/** \def CSTRING_VER_MAJOR
 * The major version number of cstring
 */

/** \def CSTRING_VER_MINOR
 * The minor version number of cstring
 */

/** \def CSTRING_VER_REVISION
 * The revision version number of cstring
 */

/** \def CSTRING_VER
 * The current composite version number of cstring
 */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
# define CSTRING_VER_1_0_1      0x01000100
# define CSTRING_VER_1_0_2      0x01000200
# define CSTRING_VER_2_0_1      0x02000100
# define CSTRING_VER_2_1_1      0x02010100
# define CSTRING_VER_2_2_1      0x02020100
# define CSTRING_VER_3_0_1      0x03000100
# define CSTRING_VER_3_1_1      0x03010100
# define CSTRING_VER_3_1_2      0x03010200
# define CSTRING_VER_3_1_3      0x03010300
# define CSTRING_VER_3_2_1      0x03020100
# define CSTRING_VER_3_3_1      0x03030100
# define CSTRING_VER_3_3_2      0x03030200
# define CSTRING_VER_3_4_1      0x03040100
# define CSTRING_VER_3_4_2      0x03040200
# define CSTRING_VER_3_4_3      0x03040300
# define CSTRING_VER_3_4_4      0x03040400
# define CSTRING_VER_3_5_1      0x03050100
# define CSTRING_VER_3_5_2      0x03050200
# define CSTRING_VER_3_5_3      0x03050300
# define CSTRING_VER_3_5_4      0x03050400
# define CSTRING_VER_3_6_1      0x03060100
# define CSTRING_VER_3_6_2      0x030602ff
# define CSTRING_VER_3_7_1      0x03070100
# define CSTRING_VER_4_0_1      0x04000100
# define CSTRING_VER_4_0_2      0x04000200
# define CSTRING_VER_4_0_3      0x04000300
# define CSTRING_VER_4_0_4      0x04000400
# define CSTRING_VER_4_0_5      0x04000500
# define CSTRING_VER_4_0_6      0x04000600
# define CSTRING_VER_4_0_7      0x04000700
# define CSTRING_VER_4_0_8      0x04000881
# define CSTRING_VER_4_0_9      0x04000981
# define CSTRING_VER_4_0_10     0x04000aff
# define CSTRING_VER_4_0_11     0x04000bff
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */

#define CSTRING_VER             CSTRING_VER_4_0_11

#define CSTRING_VER_MAJOR       4
#define CSTRING_VER_MINOR       0
#define CSTRING_VER_REVISION    11


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stddef.h>
#include <stdio.h>


/* /////////////////////////////////////////////////////////////////////////
 * documentation
 */

/** \defgroup group__cstring_api cstring API
 * \brief The cstring Public API
 *
 * The types, constants and functions that constitute the cstring API.
 */


/* /////////////////////////////////////////////////////////////////////////
 * storage class
 */

#ifdef __cplusplus

# define CSTRING_EXTERN_C                                   extern "C"
#else /* ? __cplusplus */

# define CSTRING_EXTERN_C                                   extern
#endif /* ? __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * constants & definitions
 */

/** \brief The return code type of the cstring API
 * \ingroup group__cstring_api
 */
enum CSTRING_RC
{
        CSTRING_RC_SUCCESS               =   0  /*!< \brief operation completed successfully */
    ,   CSTRING_RC_OUTOFMEMORY                  /*!< \brief out of memory */
    ,   CSTRING_RC_FIXED                        /*!< \brief operation cannot procede because the cstring has fixed capacity */
    ,   CSTRING_RC_BORROWED                     /*!< \brief operation cannot procede because the cstring is borrowed */
    ,   CSTRING_RC_READONLY                     /*!< \brief operation cannot procede because the cstring is readonly */
    ,   CSTRING_RC_INVALIDARENA                 /*!< \brief invalid arena */
    ,   CSTRING_RC_CUSTOMARENANOTSUPPORTED      /*!< \brief custom arena functionality not currently supported */
    ,   CSTRING_RC_EXCEEDFIXEDCAPACITY          /*!< \brief operation cannot procede because the current capacity would be exceeded and the cstring has fixed capacity */
    ,   CSTRING_RC_EXCEEDBORROWEDCAPACITY       /*!< \brief operation cannot procede because the current capacity would be exceeded and the cstring is borrowed */
    ,   CSTRING_RC_CANNOTYIELDFROMSO            /*!< \brief yield operation from a dynamic-library version of cstring was not allowed. */
    ,   CSTRING_RC_ARENAOVERLOADED              /*!< \brief cannot use arena parameter for both borrowed memory and custom arena */
    /* cstring 3.5+ */
    ,   CSTRING_RC_INVALIDSTREAM                /*!< \brief the stream handle is invalid */
    ,   CSTRING_RC_EOF                          /*!< \brief reached the end of stream */
    ,   CSTRING_RC_INVALIDSECTION               /*!< \brief the given section is invalid */
    ,   CSTRING_RC_IOERROR                      /*!< \brief an I/O error occurred */
    /* cstring 3.6.2+ */
    ,   CSTRING_RC_SYSTEMSPECIFICFAILURE        /*!< \brief a system-specific failure occurred, the specifics of which will be indicated in a system-specific way by any function that returns this code */
    /* cstring 4.0+ */
    ,   CSTRING_RC_REQUESTTOOLARGE              /*!< \brief request exceeded inherent or runtime limit */

};
#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
typedef enum CSTRING_RC                                     CSTRING_RC;
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * character encoding
 */

#ifndef CSTRING_USE_WIDE_STRINGS
# if 0
# elif 1 &&\
       defined(_WIN32) &&\
       defined(UNICODE) &&\
       defined(_UNICODE) &&\
       1
#  define CSTRING_USE_WIDE_STRINGS
# endif /* _WIN32 && UNICODE && _UNICODE */
#endif /* !CSTRING_USE_WIDE_STRINGS */

#ifdef CSTRING_NO_USE_WIDE_STRINGS
# ifdef CSTRING_USE_WIDE_STRINGS
#  undef CSTRING_USE_WIDE_STRINGS
# endif /* CSTRING_USE_WIDE_STRINGS */
#endif /* CSTRING_NO_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */

/** \brief character type
 * \ingroup group__cstring_api
 */
#ifdef CSTRING_USE_WIDE_STRINGS

typedef wchar_t                                             cstring_char_t;
#else /* ? CSTRING_USE_WIDE_STRINGS */

typedef char                                                cstring_char_t;
#endif /* CSTRING_USE_WIDE_STRINGS */

/** \brief Flags type
 * \ingroup group__cstring_api
 */
typedef int                                                 cstring_flags_t;

/** \brief The cstring structure
 * \ingroup group__cstring_api
 *
 * Represents a cstring as a string slice - length + pointer - along with the
 * allocated capacity, and flags controlling the allocation arena and other
 * characteristics.
 */
struct cstring_t
{
    size_t          len;        /*!< Number of characters.                                                  */
    cstring_char_t* ptr;        /*!< Pointer to the string. If \link cstring_t::capacity capacity\endlink
                                     is 0, the value of this member is undetermined.                        */
    size_t          capacity;   /*!< Number of bytes available.                                             */
    cstring_flags_t flags;      /*!< Flags. This field belongs to the implementation, and must not be
                                     modified by any application code.                                      */
};
#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION
typedef struct cstring_t                                    cstring_t;
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */

/** \def cstring_t_DEFAULT
 * \ingroup group__cstring_api
 * \brief Default initialised value for a cstring_t instance
 */
#define cstring_t_DEFAULT                                   { 0, NULL, 0, 0 }


/* /////////////////////////////////////////////////////////////////////////
 * custom settings
 */

#ifndef CSTRING_NO_USE_SYNESIS_APIS
# if defined(_SYNSOFT_INCL_H_MLMEMORY)
#  define CSTRING_USE_SYNESIS_APIS
# endif /* _SYNSOFT_INCL_H_MLMEMORY */
#endif /* !CSTRING_NO_USE_SYNESIS_APIS */


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

/** \def CSTRING_FROM_END(x)
 *
 * \brief Defines a reverse offset for use with the insert and replace functions
 *
 * \sa cstring_insert()
 * \sa cstring_insertLen()
 * \sa cstring_replace()
 * \sa cstring_replaceLen()
 */

#define CSTRING_FROM_END(x)                                 (-1 - (int)(x))


/* /////////////////////////////////////////////////////////////////////////
 * flags
 */

/** \defgroup group__cstring_api__flags Function Control Flags
 * \ingroup group__cstring_api
 * \brief These flags control the behaviour of the various functions in the
 *   library.
 *
 * @{
 */

#define CSTRING_F_TYPE_MASK                                 (0x003f)
#define CSTRING_F_MEMORY_IS_INTERNAL_HEAP                   (0x0000)    /*!< Memory is allocated by the heap function, and is owned by the cstring instance */
#define CSTRING_F_MEMORY_IS_BORROWED                        (0x0001)    /*!< Memory is supplied external to the API, and may not be deallocated, moved or expanded. \note Implies CSTRING_F_MEMORY_IS_FIXED, unless CSTRING_F_MEMORY_CAN_GROW_TO_HEAP is also specified */
#define CSTRING_F_MEMORY_IS_FIXED                           (0x0002)    /*!< Memory is of fixed size, and any operation that requires expansion will fail */
#define CSTRING_F_MEMORY_IS_READONLY                        (0x0004)    /*!< cstring instance may not be modified */
#define CSTRING_F_MEMORY_IS_CONST                           CSTRING_F_MEMORY_IS_READONLY /*!< [DEPRECATED] Equivalent to CSTRING_F_MEMORY_IS_READONLY \deprecated Use CSTRING_F_MEMORY_IS_READONLY instead. */

#define CSTRING_F_MEMORY_IS_OFFSET                          (0x0040)    /*!< cstring instance may not be modified. This flag cannot be set by client code. */

#define CSTRING_F_MEMORY_CAN_GROW_TO_HEAP                   (0x0080)    /*!< Allows borrowed strings to move their contents to the heap and continue to grow when their borrowed capacity would be exceeded: note that they do not subsequently return to use the borrowed capacity if the size subsequently shrinks to within capacity. */

#define CSTRING_F_ARENA_MASK                                (0xff00)
#define CSTRING_F_USE_REALLOC                               (0x0000)    /*!< Uses C standard library function realloc() for all memory (de-)allocation */
#if 0
#elif 0 ||\
      defined(WIN32) ||\
      defined(WIN64) ||\
      0
# define CSTRING_F_USE_WINDOWS_GLOBAL_MEMORY                (0x0100)    /*!< Uses Win32 Global Memory API for all memory (de-)allocation (Windows only); arena parameter is ignored. */
# define CSTRING_F_USE_WINDOWS_PROCESSHEAP_MEMORY           (0x0200)  /*!< Uses Win32 Process Heap for all memory (de-)allocation (Windows only); arena parameter is ignored. */
# define CSTRING_F_USE_WINDOWS_COM_TASK_MEMORY              (0x0400)    /*!< Uses COM Task Allocator for all memory (de-)allocation (Windows only); arena parameter is ignored. */
#endif /* WIN32 || WIN64 */
#if defined(CSTRING_USE_SYNESIS_APIS)
# define CSTRING_F_USE_SYNESIS_HATOR                        (0x1000)    /*!< Assumes that the arena variable is a Synesis Software memory allocator */
#endif /* CSTRING_USE_SYNESIS_APIS */
#define CSTRING_F_USE_CUSTOMARENAFUNCTIONS                  (0x2000)    /*!< Uses an externally supplied allocator function for all memory (de-)allocation (NOT CURRENTLY SUPPORTED) */

#define CSTRING_F_CUSTOMARENA_CC_CDECL                      (0x0000)    /*!< Treats the externally supplied allocator function as having CDecl calling convention (de-)allocation (NOT CURRENTLY SUPPORTED) */
#define CSTRING_F_CUSTOMARENA_CC_STDCALL                    (0x0040)    /*!< Treats the externally supplied allocator function as having StdCall calling convention (de-)allocation (NOT CURRENTLY SUPPORTED) */
/** @} */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** \brief Returns a non-NULL nul-terminated character string describing the
 * given error code
 * \ingroup group__cstring_api
 *
 * \param rc The error code. Must be one of the CSTRING_RC enumeration
 *
 * \return A non-NULL nul-terminated string
 */
CSTRING_EXTERN_C
char const*
cstring_getStatusCodeString(
    CSTRING_RC  rc
);

/** \brief Returns the length of the string returned by
 * cstring_getStatusCodeString() for the given error code.
 *
 * \param rc The error code. Must be one of the CSTRING_RC enumeration
 *
 * \return The length of the string returned by
 *   cstring_getStatusCodeString() for the the given error code, or 0 if the
 *   code is not recognised.
 */
CSTRING_EXTERN_C
size_t
cstring_getStatusCodeStringLength(
    CSTRING_RC  rc
);

/** \brief [DEPRECATED] This function is deprecated, and may be removed in a
 * future version: instead use cstring_getStatusCodeString().
 *
 * \deprecated This function is deprecated, and may be removed in a
 * future version: instead use cstring_getStatusCodeString().
 *
 * \see cstring_getStatusCodeString
 */
#if 0
#elif defined(_MSC_VER) && \
      _MSC_VER >= 1400
__declspec(deprecated("cstring_error() is deprecated, and may be removed in a future version: instead use cstring_getStatusCodeString()"))
#endif /* compiler */
CSTRING_EXTERN_C
char const*
cstring_error(
    CSTRING_RC  rc
);

/** \brief Initialises a cstring instance to a default form
 * \ingroup group__cstring_api
 *
 * \note This must only be called on an uninitialised cstring instance
 *
 * \note This is equivalent to assigning an instance from cstring_t_DEFAULT.
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_init(
    struct cstring_t*       pcs
);

/** \brief Creates a cstring instance from a C-style string
 * \ingroup group__cstring_api
 *
 * \param pcs The uninitialised cstring instance to be created
 * \param s Pointer to the C-style string to copy. May be NULL
 *
 * \note This must only be called on an uninitialised cstring instance
 *
 * \retval CSTRING_RC_SUCCESS the capacity was adjusted
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_create(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
);

/** \brief Creates a cstring instance from a fixed number of characters
 * \ingroup group__cstring_api
 *
 * \param pcs The uninitialised cstring instance to be created
 * \param s Pointer to the first character in the array from which to copy.
 *   Must not be NULL, unless \c cch is 0
 * \param cch The number of characters to be copied into the cstring instance
 *
 * \note This must only be called on an uninitialised cstring instance
 *
 * \retval CSTRING_RC_SUCCESS the capacity was adjusted
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_createLen(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   size_t                  cch
);

/** \brief Creates a cstring instance consisting of a number of repetitions
 *    of a character
 * \ingroup group__cstring_api
 *
 * \param pcs The uninitialised cstring instance to be created
 * \param ch The character to be repeated
 * \param n The number of repetitions of character \c c
 *
 * \note This must only be called on an uninitialised cstring instance
 *
 * \retval CSTRING_RC_SUCCESS the capacity was adjusted
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_createN(
    struct cstring_t*       pcs
,   cstring_char_t          ch
,   size_t                  n
);


/** \brief Creates a cstring instance with special characteristics from a C-style string
 * \ingroup group__cstring_api
 *
 * \param pcs The uninitialised cstring instance to be created
 * \param s Pointer to the C-style string to copy. May be NULL
 * \param flags The flags defining the characteristics of the cstring instance
 * \param arena The memory buffer for borrowed (CSTRING_F_MEMORY_IS_BORROWED),
 *   or a pointer to a custom memory arena. Note that custom memory arenas are
 *   not currently supported, and this parameter must be NULL unless the flag
 *   CSTRING_F_MEMORY_IS_BORROWED is specified
 * \param capacity The capacity of the buffer specified in \c arena, or
 *   otherwise ignored
 *
 * \note This must only be called on an uninitialised cstring instance
 *
 * \retval CSTRING_RC_SUCCESS the capacity was adjusted
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 * \retval CSTRING_RC_INVALIDARENA an invalid arena specification was given in the \c flags parameter
 * \retval CSTRING_RC_CUSTOMARENANOTSUPPORTED A custom arena was specified, which is not yet supported
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_createEx(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   cstring_flags_t         flags
,   void*                   arena
,   size_t                  capacity
);

/** \brief Creates a cstring instance with special characteristics from a fixed number of characters
 * \ingroup group__cstring_api
 *
 * \param pcs The uninitialised cstring instance to be created
 * \param s Pointer to the first character in the array from which to copy.
 *   Must not be NULL, unless \c cch is 0
 * \param cch The number of characters to be copied into the cstring instance
 * \param flags The flags defining the characteristics of the cstring instance
 * \param arena The memory buffer for borrowed (CSTRING_F_MEMORY_IS_BORROWED),
 *   or a pointer to a custom memory arena. Note that custom memory arenas are
 *   not currently supported, and this parameter must be NULL unless the flag
 *   CSTRING_F_MEMORY_IS_BORROWED is specified
 * \param capacity The capacity of the buffer specified in \c arena, or
 *   otherwise ignored
 *
 * \note This must only be called on an uninitialised cstring instance
 *
 * \retval CSTRING_RC_SUCCESS the capacity was adjusted
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 * \retval CSTRING_RC_INVALIDARENA an invalid arena specification was given in the \c flags parameter
 * \retval CSTRING_RC_CUSTOMARENANOTSUPPORTED A custom arena was specified, which is not yet supported
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_createLenEx(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   size_t                  cch
,   cstring_flags_t         flags
,   void*                   arena
,   size_t                  capacity
);

/** \brief Releases resources and resets the attributes of the cstring instance
 * \ingroup group__cstring_api
 *
 * \param pcs The cstring instance to be destroyed
 *
 * \note This must only be called on an initialised cstring instance, which is
 *   then rendered in the uninitialised state.
 *
 * \retval CSTRING_RC_SUCCESS the capacity was destroyed
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_destroy(
    struct cstring_t*       pcs
);


/** \brief Removes the allocated buffer from the cstring instance into a caller supplied pointer
 * \ingroup group__cstring_api
 *
 * \param pcs the cstring instance whose buffer is to be retrieved. May not be NULL.
 * \param pRaw pointer to a buffer pointer which will receive the yielded raw memory. May not be NULL. May not be equal to pPayload.
 * \param pPayload pointer to a buffer pointer which will receive the yielded payload. May not be NULL. May not be equal to pRaw.
 *
 * \note The values of *pRaw and *pPayload may not be equal
 *
 * \retval CSTRING_RC_SUCCESS the buffer was yielded
 * \retval CSTRING_RC_READONLY the cstring instance is marked readonly (CSTRING_F_MEMORY_IS_READONLY)
 * \retval CSTRING_RC_BORROWED the cstring instance is marked fixed (CSTRING_F_MEMORY_IS_BORROWED)
 * \retval CSTRING_RC_CANNOTYIELDFROMSO the cstring instance uses realloc() in a Win32 dynamic library
 *
 * \note When linked to cstring as a Win32 dynamic library, this function will not
 *   work for strings allocated via realloc()
 */

CSTRING_EXTERN_C
CSTRING_RC
cstring_yield2(
    struct cstring_t*       pcs
,   cstring_char_t**        pPayload
,   void**                  pRaw
);

#ifdef CSTRING_OBSOLETE

CSTRING_EXTERN_C
CSTRING_RC
cstring_yield(
    struct cstring_t*       pcs
,   cstring_char_t**        ppBuff
);
#endif /* CSTRING_OBSOLETE */

/** Sets the capacity of the cstring instance
 * \ingroup group__cstring_api
 *
 * \param pcs The cstring instance to be adjusted
 * \param capacity The capacity to which the cstring instance should be adjusted
 *
 * \note If the specified capacity would cause the string contents to be
 *   truncated, the value is adjusted to the minimum possible without
 *   requiring truncation.
 *
 * \retval CSTRING_RC_SUCCESS the capacity was adjusted
 * \retval CSTRING_RC_READONLY the cstring instance is marked readonly (CSTRING_F_MEMORY_IS_READONLY)
 * \retval CSTRING_RC_EXCEEDFIXEDCAPACITY the cstring instance is marked fixed (CSTRING_F_MEMORY_IS_FIXED)
 * \retval CSTRING_RC_EXCEEDBORROWEDCAPACITY the cstring instance is marked borrowed (CSTRING_F_MEMORY_IS_BORROWED)
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_setCapacity(
    struct cstring_t*       pcs
,   size_t                  capacity
);


/** \brief Assigns a C-style string to the cstring instance
 * \ingroup group__cstring_api
 *
 * \param pcs The cstring to assign to
 * \param s Pointer to the C-style string to assign. May be NULL
 *
 * \retval CSTRING_RC_SUCCESS the requested number of bytes were assigned to the cstring
 * \retval CSTRING_RC_READONLY the cstring instance is marked readonly (CSTRING_F_MEMORY_IS_READONLY)
 * \retval CSTRING_RC_EXCEEDFIXEDCAPACITY the cstring instance is marked fixed (CSTRING_F_MEMORY_IS_FIXED)
 * \retval CSTRING_RC_EXCEEDBORROWEDCAPACITY the cstring instance is marked borrowed (CSTRING_F_MEMORY_IS_BORROWED)
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 *
 * \note The function is safe with respect to 'self-assignment', i.e, \c s can
 *   refer to (part of) the payload of \c pcs, and the function will still
 *   operate correctly to produce the logically desired result.
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_assign(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
);

/** \brief Assigns a fixed number of characters to the cstring instance
 * \ingroup group__cstring_api
 *
 * \param pcs The cstring to assign to
 * \param s Pointer to the first character in the array from which to assign.
 *   Must not be NULL, unless \c cch is 0
 * \param cch The number of characters to assign
 *
 * \note If the source has embedded nul characters, they will be incorporated
 *   into the cstring contents, which means that calling strlen() on the payload
 *   pointer may give inconsistent results
 *
 * \retval CSTRING_RC_SUCCESS the requested number of bytes were assigned to the cstring
 * \retval CSTRING_RC_READONLY the cstring instance is marked readonly (CSTRING_F_MEMORY_IS_READONLY)
 * \retval CSTRING_RC_EXCEEDFIXEDCAPACITY the cstring instance is marked fixed (CSTRING_F_MEMORY_IS_FIXED)
 * \retval CSTRING_RC_EXCEEDBORROWEDCAPACITY the cstring instance is marked borrowed (CSTRING_F_MEMORY_IS_BORROWED)
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_assignLen(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   size_t                  cch
);

/** \brief Copies the contents of one cstring instance to another
 * \ingroup group__cstring_api
 *
 * \param pcs The cstring to assign to
 * \param pcsSrc The cstring whose contents will be copied
 *
 * \retval CSTRING_RC_SUCCESS the requested number of bytes were copied to the cstring
 * \retval CSTRING_RC_READONLY the cstring instance is marked readonly (CSTRING_F_MEMORY_IS_READONLY)
 * \retval CSTRING_RC_EXCEEDFIXEDCAPACITY the cstring instance is marked fixed (CSTRING_F_MEMORY_IS_FIXED)
 * \retval CSTRING_RC_EXCEEDBORROWEDCAPACITY the cstring instance is marked borrowed (CSTRING_F_MEMORY_IS_BORROWED)
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_copy(
    struct cstring_t*       pcs
,   struct cstring_t const* pcsSrc
);

/** \brief Appends a C-style string to the cstring instance
 * \ingroup group__cstring_api
 *
 * \param pcs The cstring to append to
 * \param s Pointer to the C-style string to append. May be NULL
 *
 * \retval CSTRING_RC_SUCCESS the requested number of bytes were appended to the cstring
 * \retval CSTRING_RC_READONLY the cstring instance is marked readonly (CSTRING_F_MEMORY_IS_READONLY)
 * \retval CSTRING_RC_EXCEEDFIXEDCAPACITY the cstring instance is marked fixed (CSTRING_F_MEMORY_IS_FIXED)
 * \retval CSTRING_RC_EXCEEDBORROWEDCAPACITY the cstring instance is marked borrowed (CSTRING_F_MEMORY_IS_BORROWED)
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_append(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
);

/** \brief Appends a fixed number of characters to the cstring instance
 * \ingroup group__cstring_api
 *
 * \param pcs The cstring to append to
 * \param s Pointer to the first character in the array from which to append.
 *   Must not be NULL, unless \c cch is 0
 * \param cch The number of characters to append
 *
 * \note If the source has embedded nul characters, they will be incorporated
 *   into the cstring contents, which means that calling strlen() on the payload
 *   pointer may give inconsistent results
 *
 * \retval CSTRING_RC_SUCCESS the requested number of bytes were appended to the cstring
 * \retval CSTRING_RC_READONLY the cstring instance is marked readonly (CSTRING_F_MEMORY_IS_READONLY)
 * \retval CSTRING_RC_EXCEEDFIXEDCAPACITY the cstring instance is marked fixed (CSTRING_F_MEMORY_IS_FIXED)
 * \retval CSTRING_RC_EXCEEDBORROWEDCAPACITY the cstring instance is marked borrowed (CSTRING_F_MEMORY_IS_BORROWED)
 * \retval CSTRING_RC_OUTOFMEMORY insufficient memory to carry out the operation
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_appendLen(
    struct cstring_t*       pcs
,   cstring_char_t const*   s
,   size_t                  cch
);

/** \brief Truncates the cstring instance
 * \ingroup group__cstring_api
 *
 * \param pcs The cstring to truncate
 * \param len The required length. Ignored if not less than the current length
 *
 * \note The cstring instance must not be readonly
 *
 * \retval CSTRING_RC_SUCCESS cstring instance contents were truncated (or the truncation length was out of bounds)
 * \retval CSTRING_RC_READONLY the cstring instance is marked readonly (CSTRING_F_MEMORY_IS_READONLY)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_truncate(
    struct cstring_t*       pcs
,   size_t                  len
);

/** \brief Swaps the contents of the two cstring instances
 * \ingroup group__cstring_api
 *
 * \param pcs1 the cstring instance whose contents will be swapped with \c pcs2
 * \param pcs2 the cstring instance whose contents will be swapped with \c pcs1
 *
 * \note Neither instance can be either readonly or fixed-and-borrowed
 *
 * \retval CSTRING_RC_SUCCESS string instance contents were swapped
 * \retval CSTRING_RC_READONLY one or both instances are marked readonly (CSTRING_F_MEMORY_IS_READONLY)
 * \retval CSTRING_RC_BORROWED one or both instances are marked fixed (CSTRING_F_MEMORY_IS_BORROWED)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_swap(
    struct cstring_t*       pcs1
,   struct cstring_t*       pcs2
);


/** Reads in a line of text from the given text stream
 *
 * \param stm The stream from which the line will be read
 * \param pcs The initialised string instance into which the line will be
 *   stored.
 * \param numRead An optional pointer to a variable to receive the number
 *   of characters appended to the string. May be NULL
 *
 * \retval CSTRING_RC_INVALIDSTREAM The stream was not valid (as tested
 *   by <code>ferror()</code>)
 * \retval CSTRING_RC_SUCCESS A line terminated by a carriage return was
 *   read in
 * \retval CSTRING_RC_EOF A line terminted by the end-of-file was read in
 * \retval -other- any other value returned by cstring_appendLen()
 *
 * \pre (NULL != pcs)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_readline(
    FILE*               stm
,   struct cstring_t*   pcs
,   size_t*             numRead /* = NULL */
);

/** Writes a line of text to the given text stream
 *
 * \param stm The stream to which the line will be written
 * \param pcs The initialised string instance containing the string to be
 *   written, after which a carriage-return is appended.
 * \param numWritten An optional pointer to a variable to receive the number
 *   of characters written to the stream. May be NULL
 *
 * \retval CSTRING_RC_INVALIDSTREAM The stream was not valid (as tested
 *   by <code>ferror()</code>)
 * \retval CSTRING_RC_SUCCESS A line terminated by a carriage return was
 *   read in
 * \retval CSTRING_RC_IOERROR Could not write to the stream
 *
 * \pre (NULL != pcs)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_writeline(
    FILE*                   stm
,   struct cstring_t const* pcs
,   size_t*                 numWritten /* = NULL */
);

/** Writes a string to the given text stream
 *
 * \param stm The stream to which the string will be written
 * \param pcs The initialised string instance to be written
 * \param numWritten An optional pointer to a variable to receive the number
 *   of characters written to the stream. May be NULL
 *
 * \retval CSTRING_RC_INVALIDSTREAM The stream was not valid (as tested
 *   by <code>ferror()</code>)
 * \retval CSTRING_RC_SUCCESS The string was written
 * \retval CSTRING_RC_IOERROR Could not write to the stream
 *
 * \pre (NULL != pcs)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_write(
    FILE*                   stm
,   struct cstring_t const* pcs
,   size_t*                 numWritten /* = NULL */
);

/** Inserts the given string at the given index
 *
 * \pre (NULL != pcs)
 * \pre (NULL != s)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_insert(
    struct cstring_t*       pcs
,   int                     index
,   cstring_char_t const*   s
);

/** Inserts the given string at the given index
 *
 * \pre (NULL != pcs)
 * \pre (NULL != s || 0 == cch)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_insertLen(
    struct cstring_t*       pcs
,   int                     index
,   cstring_char_t const*   s
,   size_t                  cch
);

/** Replaces a specified section of the string with another
 *
 * \param pcs The cstring instance whose contents will be modified
 * \param index The position of the replaced section. May be negative, in
 *   which case it represents the position from the end of the string
 * \param len The length of the replaced section
 * \param s The replacing string
 *
 * \note If the identified section to be replaced is outside the bounds of
 *   the string,
 *
 * \pre (NULL != pcs)
 * \pre (NULL != s)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_replace(
    struct cstring_t*       pcs
,   int                     index
,   size_t                  len
,   cstring_char_t const*   s
);

/** Replaces a specified section of the string with another
 *
 * \param pcs The cstring instance whose contents will be modified
 * \param index The position of the replaced section. May be negative, in
 *   which case it represents the position from the end of the string
 * \param len The length of the replaced section
 * \param s The replacing string
 * \param cch The replacing string length
 *
 * \note If the identified section to be replaced is outside the bounds of
 *   the string,
 *
 * \pre (NULL != pcs)
 * \pre (NULL != s || 0 == cch)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_replaceLen(
    struct cstring_t*       pcs
,   int                     index
,   size_t                  len
,   cstring_char_t const*   s
,   size_t                  cch
);

/** Replaces all instances of one substring with another
 *
 * \param pcs The cstring instance whose contents will be modified
 * \param f The string to search for. If NULL or the empty string,
 *   the function returns immediately
 * \param t The string to replace with. If NULL or the empty string,
 *   all occurences of \c f will be removed
 * \param numReplaced An optional pointer to a variable to receive the
 *   number of replacements performed. May be NULL if caller does not
 *   require
 *
 * \pre (NULL != pcs)
 */
CSTRING_EXTERN_C
CSTRING_RC
cstring_replaceAll(
    struct cstring_t*       pcs
,   cstring_char_t const*   f
,   cstring_char_t const*   t
,   size_t*                 numReplaced /* = NULL */
);


/* ////////////////////////////////////////////////////////////////////// */

#ifndef CSTRING_DOCUMENTATION_SKIP_SECTION

typedef int (*cstring_allocFailHandler)(
    void*           pv
,   size_t          cb
,   cstring_flags_t flags
,   void*           param
);

/** This is an experimental feature */
CSTRING_EXTERN_C
CSTRING_RC
cstring_createLenFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   size_t                      cch
,   cstring_flags_t             flags
,   void*                       arena
,   size_t                      capacity
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
);

/** This is an experimental feature */
CSTRING_EXTERN_C
CSTRING_RC
cstring_setCapacityFn(
    struct cstring_t*           pcs
,   size_t                      capacity
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
);

/** This is an experimental feature */
CSTRING_EXTERN_C
CSTRING_RC
cstring_assignFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
);
/** This is an experimental feature */
CSTRING_EXTERN_C
CSTRING_RC
cstring_assignLenFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   size_t                      cch
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
);

/** This is an experimental feature */
CSTRING_EXTERN_C
CSTRING_RC
cstring_appendFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
);

/** This is an experimental feature */
CSTRING_EXTERN_C
CSTRING_RC
cstring_appendLenFn(
    struct cstring_t*           pcs
,   cstring_char_t const*       s
,   size_t                      cch
,   cstring_allocFailHandler    pfnAllocFailHandler
,   void*                       param
);
#endif /* !CSTRING_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * compiler warnings
 */

#if defined(_MSC_VER)
# if _MSC_VER >= 1200
#  pragma warning(push)
# endif /* compiler */
# pragma warning(disable : 4514) /* unreferenced inline function has been removed */
#endif /* compiler */


/* /////////////////////////////////////////////////////////////////////////
 * string access shims
 */

#ifdef __cplusplus

inline
cstring_char_t const*
c_str_data(
    struct cstring_t const* pcs
)
{
    static cstring_char_t const s_empty[] = { 0 };

    return (NULL == pcs || 0u == pcs->len) ? s_empty : pcs->ptr;
}
inline
cstring_char_t const*
c_str_data(
    struct cstring_t const& cs
)
{
    static cstring_char_t const s_empty[] = { 0 };

    return (0u == cs.len) ? s_empty : cs.ptr;
}

inline
cstring_char_t const*
# ifdef CSTRING_USE_WIDE_STRINGS
c_str_data_w(
# else /* ? CSTRING_USE_WIDE_STRINGS */
c_str_data_a(
# endif /* CSTRING_USE_WIDE_STRINGS */
    struct cstring_t const* pcs
)
{
    return c_str_data(pcs);
}
inline
cstring_char_t const*
# ifdef CSTRING_USE_WIDE_STRINGS
c_str_data_w(
# else /* ? CSTRING_USE_WIDE_STRINGS */
c_str_data_a(
# endif /* CSTRING_USE_WIDE_STRINGS */
    struct cstring_t const& cs
)
{
    return c_str_data(cs);
}


inline
size_t
c_str_len(
    struct cstring_t const* pcs
)
{
    return (NULL == pcs) ? 0u : pcs->len;
}
inline
size_t
c_str_len(
    struct cstring_t const& cs
)
{
    return cs.len;
}

inline
size_t
# ifdef CSTRING_USE_WIDE_STRINGS
c_str_len_w(
# else /* ? CSTRING_USE_WIDE_STRINGS */
c_str_len_a(
# endif /* CSTRING_USE_WIDE_STRINGS */
    struct cstring_t const* pcs
)
{
    return c_str_len(pcs);
}
inline
size_t
# ifdef CSTRING_USE_WIDE_STRINGS
c_str_len_w(
# else /* ? CSTRING_USE_WIDE_STRINGS */
c_str_len_a(
# endif /* CSTRING_USE_WIDE_STRINGS */
    struct cstring_t const& cs
)
{
    return c_str_len(cs);
}


inline
cstring_char_t const*
c_str_ptr(
    struct cstring_t const* pcs
)
{
    return c_str_data(pcs);
}
inline
cstring_char_t const*
c_str_ptr(
    struct cstring_t const& cs
)
{
    return c_str_data(cs);
}

inline
cstring_char_t const*
# ifdef CSTRING_USE_WIDE_STRINGS
c_str_ptr_w(
# else /* ? CSTRING_USE_WIDE_STRINGS */
c_str_ptr_a(
# endif /* CSTRING_USE_WIDE_STRINGS */
    struct cstring_t const* pcs
)
{
    return c_str_ptr(pcs);
}
inline
cstring_char_t const*
# ifdef CSTRING_USE_WIDE_STRINGS
c_str_ptr_w(
# else /* ? CSTRING_USE_WIDE_STRINGS */
c_str_ptr_a(
# endif /* CSTRING_USE_WIDE_STRINGS */
    struct cstring_t const& cs
)
{
    return c_str_ptr(cs);
}


inline
char const*
c_str_data_a(
    CSTRING_RC rc
)
{
    return cstring_getStatusCodeString(rc);
}
inline
char const*
c_str_data(
    CSTRING_RC rc
)
{
    return cstring_getStatusCodeString(rc);
}

inline
size_t
c_str_len_a(
    CSTRING_RC rc
)
{
    return cstring_getStatusCodeStringLength(rc);
}
inline
size_t
c_str_len(
    CSTRING_RC rc
)
{
    return cstring_getStatusCodeStringLength(rc);
}

inline
char const*
c_str_ptr_a(
    CSTRING_RC rc
)
{
    return cstring_getStatusCodeString(rc);
}
inline
char const*
c_str_ptr(
    CSTRING_RC rc
)
{
    return cstring_getStatusCodeString(rc);
}

# ifndef _STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#ifdef CSTRING_USE_WIDE_STRINGS
    using ::c_str_data_w;
    using ::c_str_len_w;
    using ::c_str_ptr_w;
#endif /* CSTRING_USE_WIDE_STRINGS */
    using ::c_str_data_a;
    using ::c_str_len_a;
    using ::c_str_ptr_a;
    using ::c_str_data;
    using ::c_str_len;
    using ::c_str_ptr;

} /* namespace stlsoft */
# endif /* !_STLSOFT_NO_NAMESPACE */
#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * compiler warnings
 */

#if defined(_MSC_VER)
# if _MSC_VER >= 1200
/* #  pragma warning(pop) */
# endif /* compiler */
#endif /* compiler */


/* /////////////////////////////////////////////////////////////////////////
 * obsolete
 */

#ifdef CSTRING_F_USE_WINDOWS_GLOBAL_MEMORY
# define CSTRING_F_USE_WIN32_GLOBAL_MEMORY                  CSTRING_F_USE_WINDOWS_GLOBAL_MEMORY
#endif

#ifdef CSTRING_F_USE_WINDOWS_PROCESSHEAP_MEMORY
# define CSTRING_F_USE_WIN32_PROCESSHEAP_MEMORY             CSTRING_F_USE_WINDOWS_PROCESSHEAP_MEMORY
#endif

#ifdef CSTRING_F_USE_WINDOWS_COM_TASK_MEMORY
# define CSTRING_F_USE_WIN32_COM_TASK_MEMORY                CSTRING_F_USE_WINDOWS_COM_TASK_MEMORY
#endif


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* CSTRING_INCL_CSTRING_H_CSTRING */

/* ///////////////////////////// end of file //////////////////////////// */

