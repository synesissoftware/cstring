# cstring - History


----


28th January 2024 - 4.0.9 released
-----------------------------------

 * improved CMake support
 * CMake language standards now C-11 and C++14
 * fixed typo defect in definition of `CSTRING_F_USE_WINDOWS_PROCESSHEAP_MEMORY``
 + project boilerplate files


12th January 2024 - 4.0.8 released
-----------------------------------

 * added **cstring.vector API**
 * added API function `cstring_write()`
 * wide string support (indicated via `CSTRING_USE_WIDE_STRINGS`
 * partial CMake support
 * added result code `CSTRING_RC_REQUESTTOOLARGE`
 * added component test **test.component.cstring_writeline**
 * added scratch test **test.scratch.cstring_vector**
 * added unit test **test.unit.cstring.cstring_vector**


20th February 2012 - 3.6.2 released
-----------------------------------

 * added CSTRING_RC_SYSTEMSPECIFICFAILURE
 * all makefiles now build cstring.3.core*.(lib|a) rather than cstring.3*.(lib|a) : this was erroneously omitted from the 3.6.1 release


24th January 2012 - 3.6.1 released
-----------------------------------

 * added CSTRING_F_MEMORY_CAN_GROW_TO_HEAP flag, which allows a borrowed buffer to grow (into the heap)
 * renamed output library to cstring.core.* (in preparation for coming 4.x expansions)
 * added string access shims for CSTRING_RC
 * added cstring_getStatusCodeStringLength()
 * renamed cstring_error() => cstring_getStatusCodeString()
 * added VC10 solution and project files
 * added VC9 solution and project files
 * added test.unit.cstring.auto_buffer
 * added test.unit.cstring.cstring_getStatusCodeString
 * added test.scratch.auto_buffer
 * full Win64 compatibility
 * fixed up minor documentation mistakes


22nd January 2012 - 3.5.4 released
----------------------------------

 * Win64-compatibility
 * added test.scratch.HGLOBAL_on_x64 project
 * VC++ 10 compatibility


11th January 2010 - 3.5.3 released
----------------------------------

 * trivial formatting changes


11th July 2009 - 3.5.2 released
-------------------------------

 * fixed implicit link defects
 * completed Win64 compatibility
 * minor adjustments to compiler warnings


10th July 2009 - 3.5.1 released
-------------------------------

 * added new API functions for cstring I/O, replacing and inserting substrings, and initialisation
 * added compatibility with Borland C/C++ 5.8.2, 5.9 and 6.1, Intel C/C++ 9-11, and GCC 4.1-4.4
 * added three unit/component test programs


13th May 2007 - 3.4.4 released
------------------------------

 * additional error codes in API
 * compatible with Win64
 * compatible with Safe String library


26th January 2007 - 3.4.3 released
----------------------------------

 * distribution now roots under cstring-X.Y, e.g. cstring-3.4.3


30th April 2006 - 3.4.2 released
--------------------------------

 * Only minor edits, and little fixes.


7th October 2005 - 3.4.1 released
---------------------------------

 * added flag; added new API function; fixes to makefiles


8th August 2005 - 3.3.1 released
--------------------------------

 * change memory allocation algorithm
 * reduced system library dependencies


29th July 2005 - 3.2.1 released
-------------------------------

 * initial public release


=============================== End of file ================================
