/* /////////////////////////////////////////////////////////////////////////////
 * File:        test.scratch.cstring_create.c
 *
 * Purpose:     Implementation file for the test.scratch.cstring_create project.
 *
 * Created:     18th August 2005
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

/* /////////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

int main()
{
    /* . */
    cstring_t   cs;
    CSTRING_RC  rc  =   cstring_create(&cs, "String-#1");

    if(CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "Error: %s\n", cstring_getStatusCodeString(rc));
    }
    else
    {
        cstring_destroy(&cs);
    }

    return 0;
}

/* ///////////////////////////// end of file //////////////////////////// */
