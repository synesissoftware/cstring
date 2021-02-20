/* /////////////////////////////////////////////////////////////////////////
 * File:        implicit_link.cpp
 *
 * Purpose:     Implicit link file for the test.component.cstring_writeline project.
 *
 * Created:     10th August 2020
 * Updated:     20th February 2021
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2020-2021, Synesis Information Systems Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* cstring header files */
#include <cstring/implicit_link.h>

#include <platformstl/platformstl.h>
#if defined(_WIN32) && \
    defined(PLATFORMSTL_OS_IS_UNIX)
# include <unixem/implicit_link.h>
#endif

/* xTests header files */
#include <xtests/implicit_link.h>

/* ///////////////////////////// end of file //////////////////////////// */
