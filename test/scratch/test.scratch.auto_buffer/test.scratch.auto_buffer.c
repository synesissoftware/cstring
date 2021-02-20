/* /////////////////////////////////////////////////////////////////////////////
 * File:        test.scratch.auto_buffer.c
 *
 * Purpose:     Implementation file for the test.scratch.auto_buffer project.
 *
 * Created:     28th July 2011
 * Updated:     20th February 2021
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright 2011-2021, Synesis Software Pty Ltd.
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

/* STLSoft header files */
#if 0
#include <stlsoft/stlsoft.h>
#if _STLSOFT_VER >= 0x0a000000
# if defined(_WIN32)
#  include <winstl/diagnostics/output_debug_line.h>
# endif
#endif
#endif /* 0 */

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

int main()
{
    /* Create on a fixed buffer. */
    cstring_t   cs;
	char		buff[10];
	int			flags	=	0
						|	CSTRING_F_MEMORY_IS_BORROWED
						|	CSTRING_F_MEMORY_CAN_GROW_TO_HEAP
						;
    CSTRING_RC  rc		=   cstring_createEx(&cs, "String-#1", flags, buff, sizeof(buff));

    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "Error: %s\n", cstring_getStatusCodeString(rc));

		return EXIT_FAILURE;
    }

	/* add some more to exceed capacity */
	rc = cstring_append(&cs, " : something very long");

    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "Error: %s\n", cstring_getStatusCodeString(rc));

		return EXIT_FAILURE;
    }


    cstring_destroy(&cs);

    return EXIT_SUCCESS;
}

/* ///////////////////////////// end of file //////////////////////////// */
