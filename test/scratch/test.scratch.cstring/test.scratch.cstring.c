/* /////////////////////////////////////////////////////////////////////////////
 * File:        test.scratch.cstring.c
 *
 * Purpose:     Implementation file for the test.scratch.cstring project.
 *
 * Created:     7th July 2005
 * Updated:     20th February 2021
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright 1999-2021, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2005
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software. 
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage. 
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission. 
 *
 * ////////////////////////////////////////////////////////////////////////// */


/* cstring header files */
#include <cstring/cstring.h>

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* /////////////////////////////////////////////////////////////////////////////
 * compiler warnings
 */

#if defined(_MSC_VER) && \
    _MSC_VER >= 1310
# pragma warning(disable : 4054)
#endif /* compiler */

/* /////////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static int run_unittests(void);

#if defined(WIN32)
static int on_allocFail(void *pv, size_t cb, cstring_flags_t flags, void *param);
#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */

static void play_with_string(struct cstring_t *pcs);

int main(int argc, char *argv[])
{
#if 0
    { size_t i; for(i = 0; i < 0xFFFFFFFF; ++i){} }
#endif /* 0 */

#if !defined(__GNUC__)
    fprintf(stdout, "");
    fflush(stdout);
#endif /* !__GNUC__ */

    if( 2 == argc &&
        (   0 == strcmp(argv[1], "-unittest") ||
            0 == strcmp(argv[1], "--unittest")))
    {
        return run_unittests();
    }
    else
    {
        printf("\n========================================\n");
        printf("cstring_createLen():\n");
        {
            struct cstring_t    cs1;
            CSTRING_RC          rc  =   cstring_createLen(&cs1, "string-#1", 9);

            if(CSTRING_RC_SUCCESS == rc)
            {
                play_with_string(&cs1);

                cstring_destroy(&cs1);
            }
        }

#if defined(WIN32)
        printf("\n========================================\n");
        printf("cstring_createLenEx(CSTRING_F_USE_WIN32_PROCESSHEAP_MEMORY):\n");
        {
            struct cstring_t    cs1;
            CSTRING_RC          rc  =   cstring_createLenEx(&cs1, "string-#2", 9, CSTRING_F_USE_WIN32_PROCESSHEAP_MEMORY, NULL, 0);

            if(CSTRING_RC_SUCCESS == rc)
            {
                play_with_string(&cs1);

                cstring_destroy(&cs1);
            }
        }

        printf("\n========================================\n");
        printf("cstring_createLenFn(CSTRING_F_USE_WIN32_PROCESSHEAP_MEMORY):\n");
        {
            struct cstring_t    cs1;
            CSTRING_RC          rc  =   cstring_createLenFn(&cs1, "string-#2", 9, CSTRING_F_USE_WIN32_PROCESSHEAP_MEMORY, NULL, 0, on_allocFail, NULL);

            if(CSTRING_RC_SUCCESS == rc)
            {
                cstring_setCapacity(&cs1, 0x7fffffff);

                play_with_string(&cs1);

                cstring_destroy(&cs1);
            }
        }

        printf("\n========================================\n");
        printf("cstring_createLenEx(CSTRING_F_USE_WIN32_COM_TASK_MEMORY):\n");
        {
            struct cstring_t    cs1;
            CSTRING_RC          rc  =   cstring_createEx(&cs1, "string-#3", CSTRING_F_USE_WIN32_COM_TASK_MEMORY, NULL, 0);

            if(CSTRING_RC_SUCCESS == rc)
            {
                play_with_string(&cs1);

                cstring_destroy(&cs1);
            }
        }
#endif /* WIN32 */

        printf("\n========================================\n");
        printf("cstring_createLenEx(CSTRING_F_MEMORY_IS_FIXED | CSTRING_F_MEMORY_IS_BORROWED):\n");
        {
            char                sz[101];
            struct cstring_t    cs1;
            CSTRING_RC          rc  =   cstring_createLenEx(&cs1
                                                        ,   "string-#4"
                                                        ,   9
                                                        ,   CSTRING_F_MEMORY_IS_FIXED | CSTRING_F_MEMORY_IS_BORROWED
                                                        ,   &sz[0]
                                                        ,   sizeof(sz));

            if(CSTRING_RC_SUCCESS == rc)
            {
                play_with_string(&cs1);

                cstring_destroy(&cs1);
            }
        }
    }

    return EXIT_SUCCESS;
}

/* ////////////////////////////////////////////////////////////////////////// */

static void play_with_string(struct cstring_t *pcs)
{
    struct cstring_t    cs2 =   cstring_t_DEFAULT;
    struct cstring_t    cs3;
    CSTRING_RC          rc;

    fprintf(stdout, "  Initial contents: %.*s\n", (int)pcs->len, pcs->ptr);

    fprintf(stdout, "\n");
    fprintf(stdout, "  Assigning another C-style string to the instance:\n");
    rc = cstring_assign(pcs, "another string");
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents: %.*s\n", (int)pcs->len, pcs->ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Assigning part of another C-style string to the instance:\n");
    rc = cstring_assignLen(pcs, "some more contents", 17);
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents: %.*s\n", (int)pcs->len, pcs->ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Appending another C-style string to the instance:\n");
    rc = cstring_append(pcs, " - ");
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents: %.*s\n", (int)pcs->len, pcs->ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Appending part of another C-style string to the instance:\n");
    rc = cstring_appendLen(pcs, "and another string", 11);
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents: %.*s\n", (int)pcs->len, pcs->ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Appending part of another C-style string to the instance:\n");
    rc = cstring_append(pcs, "; and a whole lot more stringy stuff to try and precipitate a reallocation, in order to check that the 3.3 change will be tested");
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents: %.*s\n", (int)pcs->len, pcs->ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Appending part of another C-style string to the instance:\n");
    rc = cstring_append(pcs, "; and a last bit to try and get the remaining reallocation");
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents: %.*s\n", (int)pcs->len, pcs->ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Truncating the instance to 10 characters:\n");
    rc = cstring_truncate(pcs, 10);
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents: %.*s\n", (int)pcs->len, pcs->ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Copying the instance:\n");
    rc = cstring_copy(&cs2, pcs);
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents:         %p %.*s\n", pcs->ptr, (int)pcs->len, pcs->ptr);
        fprintf(stdout, "  Contents of copy: %p %.*s\n", cs2.ptr, (int)cs2.len, cs2.ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Copying the instance (by C-style string):\n");
    rc = cstring_createLenEx(&cs3, pcs->ptr, pcs->len, pcs->flags, NULL, 0);
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents:         %p %.*s\n", pcs->ptr, (int)pcs->len, pcs->ptr);
        fprintf(stdout, "  Contents of copy: %p %.*s\n", cs3.ptr, (int)cs3.len, cs3.ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Swapping with the copy:\n");
    rc = cstring_swap(&cs2, pcs);
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "    error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        fprintf(stdout, "  Contents:         %p %.*s\n", pcs->ptr, (int)pcs->len, pcs->ptr);
        fprintf(stdout, "  Contents of copy: %p %.*s\n", cs2.ptr, (int)cs2.len, cs2.ptr);
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "  Destroying the copy:\n");
    cstring_destroy(&cs2);
}

/* ////////////////////////////////////////////////////////////////////////// */

static int run_unittests(void)
{
    cstring_t   cs1;
    CSTRING_RC  rc;

    cstring_init(&cs1);

    rc = cstring_create(&cs1, "");
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "API error: %s\n", cstring_getStatusCodeString(rc));
        goto Failure;
    }
    else if(0 != cs1.len)
    {
        fprintf(stdout, "Length of empty string not 0; length=%lu\n", (unsigned long)cs1.len);
        goto Failure;
    }


    rc = cstring_setCapacity(&cs1, 100);
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "API error: %s\n", cstring_getStatusCodeString(rc));
        goto Failure;
    }
    else if(0 != cs1.len)
    {
        fprintf(stdout, "Length of empty string not 0; length=%lu\n", (unsigned long)cs1.len);
        goto Failure;
    }
    else if(cs1.capacity < 100)
    {
        fprintf(stdout, "Capacity of empty string not >=100; capacity=%lu\n", (unsigned long)cs1.capacity);
        goto Failure;
    }


    rc = cstring_assignLen(&cs1, "Lemon shoes", 11);
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "API error: %s\n", cstring_getStatusCodeString(rc));
        goto Failure;
    }
    else if(11 != cs1.len)
    {
        fprintf(stdout, "Length of string not 11; length=%lu\n", (unsigned long)cs1.len);
        goto Failure;
    }
    else if(0 != strcmp(cs1.ptr, "Lemon shoes"))
    {
        fprintf(stdout, "Invalid string contents; not \"Lemon shoes\", but \"%s\"\n", cs1.ptr);
        goto Failure;
    }
    else if(cs1.capacity < 100)
    {
        fprintf(stdout, "Capacity of empty string not >=100; capacity=%lu\n", (unsigned long)cs1.capacity);
        goto Failure;
    }


    rc = cstring_append(&cs1, " - and orange tie");
    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stdout, "API error: %s\n", cstring_getStatusCodeString(rc));
        goto Failure;
    }
    else if(28 != cs1.len)
    {
        fprintf(stdout, "Length of string not 28; length=%lu\n", (unsigned long)cs1.len);
        goto Failure;
    }
    else if(0 != strcmp(cs1.ptr, "Lemon shoes - and orange tie"))
    {
        fprintf(stdout, "Invalid string contents; not \"Lemon shoes - and orange tie\", but \"%s\"\n", cs1.ptr);
        goto Failure;
    }
    else if(cs1.capacity < 100)
    {
        fprintf(stdout, "Capacity of empty string not >=100; capacity=%lu\n", (unsigned long)cs1.capacity);
        goto Failure;
    }

    fprintf(stdout, "unit-tests: passed\n");
    return EXIT_SUCCESS;

Failure:

    cstring_destroy(&cs1);

    fprintf(stdout, "unit-tests: failed\n");
    return EXIT_FAILURE;
}

#if defined(WIN32)
static int on_allocFail(void *pv, size_t cb, cstring_flags_t flags, void *param)
{
    fprintf(stderr, "Allocation failed: pv=%p, cb=%lu, flags=0x%08x, param=%p\n", pv, (unsigned long)cb, (unsigned)flags, param);

    return 0;
}
#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */
