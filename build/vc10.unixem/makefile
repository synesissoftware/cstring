############################################################################
# File:		makefile
#
# Purpose:	Generated makefile for the cstring project,
#           for the Visual C++ 10.0 (x86 UNIXem) compiler
#           on the UNIX platform
#
# Created:	16th December 2007
# Updated:	17th December 2020
#
############################################################################


############################################################################
# instructions (in no particular order)

############################################################################
# environment check

!ifndef STLSOFT
!error STLSOFT must be defined
!endif # !STLSOFT

!ifndef PTHREADS_WIN32
!error PTHREADS_WIN32 must be defined
!endif # !PTHREADS_WIN32

!ifndef UNIXEM
!error UNIXEM must be defined
!endif # !UNIXEM

############################################################################
# symbols

########################################
# project & compiler version

COMP_TAG			=	vc10
ARCH_TAG            =   
OS_TAG				=   .unix
PROJ_TAG			=	cstring
PROJ_VER_MAJOR		=	4
PROJ_TAG_VER		=	$(PROJ_TAG).$(PROJ_VER_MAJOR)
COMP_ARCH_OS_TAG	=	$(COMP_TAG)$(OS_TAG)$(ARCH_TAG)

SHWILD_VER_MAJOR    =   0
SHWILD_TAG_VER      =   shwild.$(SHWILD_VER_MAJOR)

XTESTS_VER_MAJOR    =   0
XTESTS_TAG_VER      =   xtests.$(XTESTS_VER_MAJOR)

UNIXEM_VER_MAJOR	=	1
UNIXEM_TAG_VER      =   unixem.$(UNIXEM_VER_MAJOR)

PROJ_MAKEFILE_NAME  =   makefile

########################################
# miscellaneous

NOTHING				=

########################################
# testing verbosity

!ifndef TEST_VERBOSITY
TEST_VERBOSITY      =   2
!endif # !TEST_VERBOSITY

########################################
# directories

PROJ_BASE_DIR				=	..\..
PROJ_BIN_DIR				=	$(PROJ_BASE_DIR)\bin
PROJ_INCLUDE_DIR			=	$(PROJ_BASE_DIR)\include
PROJ_LIB_DIR				=	$(PROJ_BASE_DIR)\lib
PROJ_OBJ_DIR				=	.
PROJ_SRC_DIR				=	$(PROJ_BASE_DIR)\src


PROJ_EXAMPLES_DIR			=	$(PROJ_BASE_DIR)\examples
PROJ_SAMPLES_DIR			=	$(PROJ_BASE_DIR)\samples
PROJ_TEST_ROOT_DIR			=	$(PROJ_BASE_DIR)\test
PROJ_TEST_COMPONENT_DIR		=	$(PROJ_TEST_ROOT_DIR)\component
PROJ_TEST_PERFORMANCE_DIR	=	$(PROJ_TEST_ROOT_DIR)\performance
PROJ_TEST_SCRATCH_DIR		=	$(PROJ_TEST_ROOT_DIR)\scratch
PROJ_TEST_UNIT_DIR			=	$(PROJ_TEST_ROOT_DIR)\unit

SHWILD_PROJ_INCLUDE			=	
!ifdef CSTRING_SHWILD_BASE_DIR
SHWILD_INCLUDE_DIR			=   $(CSTRING_SHWILD_BASE_DIR)\include
SHWILD_SRC_DIR				=   $(CSTRING_SHWILD_BASE_DIR)\src
SHWILD_PROJ_INCLUDE			=	-I$(SHWILD_INCLUDE_DIR)
!else
SHWILD_INCLUDE_DIR			=   $(PROJ_BASE_DIR)\include
SHWILD_SRC_DIR				=   $(PROJ_SRC_DIR)\shwild
!endif # !CSTRING_SHWILD_BASE_DIR

XTESTS_PROJ_INCLUDE			=	
!ifdef CSTRING_XTESTS_BASE_DIR
XTESTS_INCLUDE_DIR			=   $(CSTRING_XTESTS_BASE_DIR)\include
XTESTS_SRC_DIR				=   $(CSTRING_XTESTS_BASE_DIR)\src
XTESTS_PROJ_INCLUDE			=	-I$(XTESTS_INCLUDE_DIR)
!else
XTESTS_INCLUDE_DIR			=   $(PROJ_BASE_DIR)\include
XTESTS_SRC_DIR				=   $(PROJ_SRC_DIR)\xtests
!endif # !CSTRING_XTESTS_BASE_DIR

STLSOFT_PROJ_INCLUDE		=	-I"$(STLSOFT)\include"

########################################
# tools

CC		=   cl
CPPC	=   cl
AR		=   lib
LD		=   link
RM		=   del /f
CP		=   copy
RC		=   rc

########################################
# include directory symbols

INCLUDES_LEADER		=	

PROJ_INCLUDE		=	-I$(PROJ_INCLUDE_DIR)

ENV_INCLUDES		=

COMMON_INCLUDES		=	-I$(SYNESIS_DEV)/include -I$(SYNESIS_DEV)/libraries/include

UNIXEM_INCLUDE		=	-I"$(UNIXEM)\include"

# CC includes

CC_INCLUDES_BASE=\
 $(INCLUDES_LEADER)\
 $(PROJ_INCLUDE)\
 \
 $(SHWILD_PROJ_INCLUDE)\
 \
 \
 $(XTESTS_PROJ_INCLUDE)\
 $(STLSOFT_PROJ_INCLUDE)\
 $(COMMON_INCLUDES)\
 -I"$(PTHREADS_WIN32)\include"\
 $(UNIXEM_INCLUDE)\
 $(ENV_INCLUDES)\
 \

CC_INCLUDES_MT_UX_DEBUG =\
 $(CC_INCLUDES_BASE)\
 \

CC_INCLUDES_MT_UX =\
 $(CC_INCLUDES_BASE)\
 \



CC_SHWILD_INCLUDES_BASE =\
 $(CC_INCLUDES_BASE)\
 \

CC_SHWILD_INCLUDES_MT_UX_DEBUG =\
 $(CC_SHWILD_INCLUDES_BASE)\
 \

CC_SHWILD_INCLUDES_MT_UX =\
 $(CC_SHWILD_INCLUDES_BASE)\
 \


CC_XTESTS_INCLUDES_BASE =\
 $(CC_INCLUDES_BASE)\
 \

CC_XTESTS_INCLUDES_MT_UX_DEBUG =\
 $(CC_XTESTS_INCLUDES_BASE)\
 \

CC_XTESTS_INCLUDES_MT_UX =\
 $(CC_XTESTS_INCLUDES_BASE)\
 \


# CPPC includes

CPPC_INCLUDES_BASE=\
 $(INCLUDES_LEADER)\
 $(PROJ_INCLUDE)\
 \
 $(SHWILD_PROJ_INCLUDE)\
 \
 \
 $(XTESTS_PROJ_INCLUDE)\
 $(STLSOFT_PROJ_INCLUDE)\
 $(COMMON_INCLUDES)\
 -I"$(PTHREADS_WIN32)\include"\
 $(UNIXEM_INCLUDE)\
 $(ENV_INCLUDES)\
 \

CPPC_INCLUDES_MT_UX_DEBUG =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_INCLUDES_MT_UX =\
 $(CPPC_INCLUDES_BASE)\
 \



CPPC_SHWILD_INCLUDES_BASE =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_SHWILD_INCLUDES_MT_UX_DEBUG =\
 $(CPPC_SHWILD_INCLUDES_BASE)\
 \

CPPC_SHWILD_INCLUDES_MT_UX =\
 $(CPPC_SHWILD_INCLUDES_BASE)\
 \


CPPC_XTESTS_INCLUDES_BASE =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_XTESTS_INCLUDES_MT_UX_DEBUG =\
 $(CPPC_XTESTS_INCLUDES_BASE)\
 \

CPPC_XTESTS_INCLUDES_MT_UX =\
 $(CPPC_XTESTS_INCLUDES_BASE)\
 \



########################################
# library directory symbols

LIBS_LEADER 			=	

# lib paths

ENV_LIBPATHS			=
COMMON_LIBPATHS			=	-libpath:$(SYNESIS_DEV)/lib 


LIBPATHS=\
 $(LIBS_LEADER)\
 -libpath:"$(PTHREADS_WIN32)\lib"\
 -libpath:"$(UNIXEM)\lib"\
 $(COMMON_LIBPATHS)\
 $(ENV_LIBPATHS)\
 \


########################################
# library names

TARGET_LIB_MT_UX_DEBUG=\
 pthreadVC.lib advapi32.lib kernel32.lib ole32.lib oleaut32.lib shlwapi.lib user32.lib uuid.lib version.lib wininet.lib ws2_32.lib\
 \

TARGET_LIB_MT_UX=\
 pthreadVC.lib advapi32.lib kernel32.lib ole32.lib oleaut32.lib shlwapi.lib user32.lib uuid.lib version.lib wininet.lib ws2_32.lib\
 \


########################################
# #defines

OS_DEFS				=	-DUNIX

COMMON_DEFS 		=	-DUNIX

CUSTOM_DEFS			=


# CC flags

CC_F_NOLOGO           =   -nologo
CC_F_COMPILE_ONLY     =   -c
CC_F_WARNING_MAX      =   -W4
CC_F_WARNING_ERR      =   -WX
CC_F_MINIMUM_SIZE     =   -O1
CC_F_MAXIMUM_SPEED	=	-O2

CC_FLAGS_BASE =\
 $(CC_F_NOLOGO)\
 $(CC_F_COMPILE_ONLY)\
 $(CC_F_WARNING_MAX)\
 $(CC_F_WARNING_ERR)\
 \

CC_FLAGS_MT_UX_DEBUG =\
 $(CC_FLAGS_BASE)\
 \

CC_FLAGS_MT_UX =\
 $(CC_FLAGS_BASE)\
 \


# CPPC flags

CPPC_F_NOLOGO           =   -nologo
CPPC_F_COMPILE_ONLY     =   -c
CPPC_F_WARNING_MAX      =   -W4
CPPC_F_WARNING_ERR      =   -WX
CPPC_F_EXCEPTIONS_ON	=	-EHsc
CPPC_F_EXCEPTIONS_OFF	=	-wd4530
CPPC_F_EXCEPTIONS		=	
CPPC_F_RTTI_ON			=	-GR
CPPC_F_RTTI_OFF 		=	-GR-
CPPC_F_RTTI				=	
CPPC_F_MINIMUM_SIZE     =   -O1
CPPC_F_MAXIMUM_SPEED	=	-O2

CPPC_FLAGS_BASE =\
 $(CPPC_F_NOLOGO)\
 $(CPPC_F_COMPILE_ONLY)\
 $(CPPC_F_WARNING_MAX)\
 $(CPPC_F_WARNING_ERR)\
 $(CPPC_F_EXCEPTIONS)\
 $(CPPC_F_RTTI)\
 \

CPPC_FLAGS_MT_UX_DEBUG =\
 $(CPPC_FLAGS_BASE)\
 \

CPPC_FLAGS_MT_UX =\
 $(CPPC_FLAGS_BASE)\
 \


# CC defines

CC_DEFS_BASE =\
 $(COMMON_DEFS)\
 $(CUSTOM_DEFS)\
 \


CC_DEFS_MT_UX_DEBUG =\
 $(CC_DEFS_BASE)\
 \

CC_DEFS_MT_UX =\
 $(CC_DEFS_BASE)\
 \


# CPPC defines

CPPC_DEFS_BASE =\
 $(COMMON_DEFS)\
 $(CUSTOM_DEFS)\
 \


CPPC_DEFS_MT_UX_DEBUG =\
 $(CPPC_DEFS_BASE)\
 \

CPPC_DEFS_MT_UX =\
 $(CPPC_DEFS_BASE)\
 \



# CC args (= flags + defines + includes)

CC_ARGS_MT_UX_DEBUG=\
 $(CC_FLAGS_MT_UX_DEBUG)\
 $(CPPC_F_WITH_EXCEPTIONS) -MTd -D_DEBUG -D_STLSOFT_FORCE_ANY_COMPILER -Zi -Fd$*.pdb\
 $(CC_DEFS_MT_UX_DEBUG)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CC_INCLUDES_MT_UX_DEBUG)
CC_ARGS_MT_UX=\
 $(CC_FLAGS_MT_UX)\
 $(CPPC_F_WITH_EXCEPTIONS) -MTd -DNDEBUG $(CC_F_MAXIMUM_SPEED) -D_STLSOFT_FORCE_ANY_COMPILER -Zi -Fd$*.pdb\
 $(CC_DEFS_MT_UX)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CC_INCLUDES_MT_UX)

# CPPC args (= flags + defines + includes)

CPPC_ARGS_MT_UX_DEBUG=\
 $(CPPC_FLAGS_MT_UX_DEBUG)\
 $(CPPC_F_WITH_EXCEPTIONS) -MTd -D_DEBUG -D_STLSOFT_FORCE_ANY_COMPILER -Zi -Fd$*.pdb\
 $(CPPC_DEFS_MT_UX_DEBUG)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CPPC_INCLUDES_MT_UX_DEBUG)
CPPC_ARGS_MT_UX=\
 $(CPPC_FLAGS_MT_UX)\
 $(CPPC_F_WITH_EXCEPTIONS) -MTd -DNDEBUG $(CPPC_F_MAXIMUM_SPEED) -D_STLSOFT_FORCE_ANY_COMPILER -Zi -Fd$*.pdb\
 $(CPPC_DEFS_MT_UX)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CPPC_INCLUDES_MT_UX)



# AR args

AR_ARGS 			=	-nologo


# LD flags

LD_F_NOLOGO				=   -nologo

LD_FLAGS_BASE =\
 $(LD_F_NOLOGO)\
 \

LD_FLAGS_MT_UX_DEBUG =\
 $(LD_FLAGS_BASE)\
 \

LD_FLAGS_MT_UX =\
 $(LD_FLAGS_BASE)\
 \


# LD includes

LD_INCLUDES_BASE =\
 $(LIBPATHS)\
 \

LD_INCLUDES_MT_UX_DEBUG =\
 $(LD_INCLUDES_BASE)\
 \

LD_INCLUDES_MT_UX =\
 $(LD_INCLUDES_BASE)\
 \


# LD args

LD_ARGS_MT_UX_DEBUG=  $(LD_FLAGS_MT_UX_DEBUG) libWinSysLog.$(COMP_TAG).mt.debug.lib unixem.1.$(COMP_TAG).mt.debug.lib -debug $(LD_INCLUDES_MT_UX_DEBUG)
LD_ARGS_MT_UX=  $(LD_FLAGS_MT_UX) libWinSysLog.$(COMP_TAG).mt.lib unixem.1.$(COMP_TAG).mt.lib -release $(LD_INCLUDES_MT_UX)

############################################################################
# headers

CORE_HEADERS=\
 $(PROJ_INCLUDE_DIR)\cstring\cstring.h \
 $(PROJ_INCLUDE_DIR)\cstring\implicit_link.h \
 \

SHWILD_HEADERS=\
 $(SHWILD_INCLUDE_DIR)\shwild\shwild.h\
 $(SHWILD_INCLUDE_DIR)\shwild\shwild.hpp\
 \

XTESTS_HEADERS=\
 $(XTESTS_INCLUDE_DIR)\xtests\xtests.h\
 $(XTESTS_INCLUDE_DIR)\xtests\implicit_link.h\
 $(XTESTS_INCLUDE_DIR)\xtests\internal\safestr.h\
 \

############################################################################
# names

############################################################
# targets

########################################
# libraries

# core
LIB_CORE_MT_UX_DEBUG			=	$(PROJ_LIB_DIR)\$(PROJ_TAG_VER).$(COMP_ARCH_OS_TAG).mt.debug.lib
LIB_CORE_MT_UX			=	$(PROJ_LIB_DIR)\$(PROJ_TAG_VER).$(COMP_ARCH_OS_TAG).mt.lib

# shwild - testing only
LIB_SHWILD_MT_UX_DEBUG		=	$(PROJ_LIB_DIR)\$(SHWILD_TAG_VER).xt.$(COMP_ARCH_OS_TAG).mt.debug.lib
LIB_SHWILD_MT_UX		=	$(PROJ_LIB_DIR)\$(SHWILD_TAG_VER).xt.$(COMP_ARCH_OS_TAG).mt.lib

# xTests - testing only
LIB_XTESTS_MT_UX_DEBUG		=	$(PROJ_LIB_DIR)\$(XTESTS_TAG_VER).xt.$(COMP_ARCH_OS_TAG).mt.debug.lib
LIB_XTESTS_MT_UX		=	$(PROJ_LIB_DIR)\$(XTESTS_TAG_VER).xt.$(COMP_ARCH_OS_TAG).mt.lib

########################################
# examples


########################################
# tests

##############################
# component tests

TARG_TEST_COMP_readln_MT_UX_DEBUG	=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.cstring_readline.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_COMP_readln_MT_UX	=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.cstring_readline.$(COMP_ARCH_OS_TAG).mt.exe

##############################
# scratch tests

TARG_TEST_SCRT_api_MT_UX_DEBUG		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_SCRT_cr_MT_UX_DEBUG		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring_create.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_SCRT_dl_MT_UX_DEBUG		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.dynload.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_SCRT_aubuf_MT_UX_DEBUG		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.auto_buffer.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_SCRT_api_MT_UX		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_SCRT_cr_MT_UX		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring_create.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_SCRT_dl_MT_UX		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.dynload.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_SCRT_aubuf_MT_UX		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.auto_buffer.$(COMP_ARCH_OS_TAG).mt.exe

##############################
# unit tests

TARG_TEST_UNIT_1_MT_UX_DEBUG			=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.1.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_UNIT_2_MT_UX_DEBUG			=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.2.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_UNIT_GSCS_MT_UX_DEBUG		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.cstring_getStatusCodeString.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_UNIT_AB_MT_UX_DEBUG		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.auto_buffer.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_UNIT_1_MT_UX			=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.1.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_UNIT_2_MT_UX			=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.2.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_UNIT_GSCS_MT_UX		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.cstring_getStatusCodeString.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_UNIT_AB_MT_UX		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.auto_buffer.$(COMP_ARCH_OS_TAG).mt.exe

############################################################
# objects

########################################
# libraries

# core

OBJ_lib_core_MT_UX_DEBUG =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).core.mt.debug.obj

OBJ_CORE_MT_UX_DEBUG=\
 $(OBJ_lib_core_MT_UX_DEBUG)\
 \

OBJ_lib_core_MT_UX =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).core.mt.obj

OBJ_CORE_MT_UX=\
 $(OBJ_lib_core_MT_UX)\
 \


# shwild

OBJ_shw_api_MT_UX_DEBUG            = $(PROJ_OBJ_DIR)\shwild.cs.api.mt.debug.obj
OBJ_shw_matches_MT_UX_DEBUG        = $(PROJ_OBJ_DIR)\shwild.cs.matches.mt.debug.obj
OBJ_shw_pattern_MT_UX_DEBUG        = $(PROJ_OBJ_DIR)\shwild.cs.pattern.mt.debug.obj
PDB_shw_api_MT_UX_DEBUG            = $(PROJ_OBJ_DIR)\shwild.cs.api.mt.debug.pdb
PDB_shw_matches_MT_UX_DEBUG        = $(PROJ_OBJ_DIR)\shwild.cs.matches.mt.debug.pdb
PDB_shw_pattern_MT_UX_DEBUG        = $(PROJ_OBJ_DIR)\shwild.cs.pattern.mt.debug.pdb

OBJ_SHWILD_MT_UX_DEBUG=\
 $(OBJ_shw_api_MT_UX_DEBUG)\
 $(OBJ_shw_matches_MT_UX_DEBUG)\
 $(OBJ_shw_pattern_MT_UX_DEBUG)\
 \

PDB_SHWILD_MT_UX_DEBUG=\
 $(PDB_shw_api_MT_UX_DEBUG)\
 $(PDB_shw_matches_MT_UX_DEBUG)\
 $(PDB_shw_pattern_MT_UX_DEBUG)\
 \

OBJ_shw_api_MT_UX            = $(PROJ_OBJ_DIR)\shwild.cs.api.mt.obj
OBJ_shw_matches_MT_UX        = $(PROJ_OBJ_DIR)\shwild.cs.matches.mt.obj
OBJ_shw_pattern_MT_UX        = $(PROJ_OBJ_DIR)\shwild.cs.pattern.mt.obj

OBJ_SHWILD_MT_UX=\
 $(OBJ_shw_api_MT_UX)\
 $(OBJ_shw_matches_MT_UX)\
 $(OBJ_shw_pattern_MT_UX)\
 \



# xTests

OBJ_xts_core_MT_UX_DEBUG          =	$(PROJ_OBJ_DIR)\xtests.cs.core.mt.debug.obj
PDB_xts_core_MT_UX_DEBUG			=	$(PROJ_OBJ_DIR)\xtests.cs.core.mt.debug.pdb

OBJ_XTESTS_MT_UX_DEBUG=\
 $(OBJ_xts_core_MT_UX_DEBUG)\
 \

PDB_XTESTS_MT_UX_DEBUG=\
 $(PDB_xts_core_MT_UX_DEBUG)\
 \

OBJ_xts_core_MT_UX          =	$(PROJ_OBJ_DIR)\xtests.cs.core.mt.obj

OBJ_XTESTS_MT_UX=\
 $(OBJ_xts_core_MT_UX)\
 \



########################################
# examples


########################################
# tests

##############################
# component tests

OBJ_TEST_COMP_readln_MT_UX_DEBUG =   $(PROJ_OBJ_DIR)\test.component.cstring_readline.mt.debug.obj
OBJ_TEST_COMP_readln_MT_UX =   $(PROJ_OBJ_DIR)\test.component.cstring_readline.mt.obj

##############################
# scratch tests

OBJ_TEST_SCRT_api_MT_UX_DEBUG	=   $(PROJ_OBJ_DIR)\test.scratch.cstring.mt.debug.obj
OBJ_TEST_SCRT_cr_MT_UX_DEBUG		=   $(PROJ_OBJ_DIR)\test.scratch.cstring_create.mt.debug.obj
OBJ_TEST_SCRT_dl_MT_UX_DEBUG		=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dynload.mt.debug.obj
OBJ_TEST_SCRT_aubuf_MT_UX_DEBUG	=   $(PROJ_OBJ_DIR)\test.scratch.auto_buffer.mt.debug.obj
OBJ_TEST_SCRT_api_MT_UX	=   $(PROJ_OBJ_DIR)\test.scratch.cstring.mt.obj
OBJ_TEST_SCRT_cr_MT_UX		=   $(PROJ_OBJ_DIR)\test.scratch.cstring_create.mt.obj
OBJ_TEST_SCRT_dl_MT_UX		=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dynload.mt.obj
OBJ_TEST_SCRT_aubuf_MT_UX	=   $(PROJ_OBJ_DIR)\test.scratch.auto_buffer.mt.obj

##############################
# unit tests

OBJ_TEST_UNIT_1_MT_UX_DEBUG		=   $(PROJ_OBJ_DIR)\test.unit.cstring.1.mt.debug.obj
OBJ_TEST_UNIT_2_MT_UX_DEBUG		=   $(PROJ_OBJ_DIR)\test.unit.cstring.2.mt.debug.obj
OBJ_TEST_UNIT_GSCS_MT_UX_DEBUG	=   $(PROJ_OBJ_DIR)\test.unit.cstring.cstring_getStatusCodeString.mt.debug.obj
OBJ_TEST_UNIT_AB_MT_UX_DEBUG		=   $(PROJ_OBJ_DIR)\test.unit.cstring.auto_buffer.mt.debug.obj
OBJ_TEST_UNIT_1_MT_UX		=   $(PROJ_OBJ_DIR)\test.unit.cstring.1.mt.obj
OBJ_TEST_UNIT_2_MT_UX		=   $(PROJ_OBJ_DIR)\test.unit.cstring.2.mt.obj
OBJ_TEST_UNIT_GSCS_MT_UX	=   $(PROJ_OBJ_DIR)\test.unit.cstring.cstring_getStatusCodeString.mt.obj
OBJ_TEST_UNIT_AB_MT_UX		=   $(PROJ_OBJ_DIR)\test.unit.cstring.auto_buffer.mt.obj

# target groups

########################################
# objects

# core
OBJ_CORE=\
# $(OBJ_UTIL_MT_UX_DEBUG)\
 $(OBJ_CORE_MT_UX_DEBUG)\
# $(OBJ_UTIL_MT_UX)\
 $(OBJ_CORE_MT_UX)\
 \

# shwild
OBJ_SHWILD=\
 $(OBJ_SHWILD_MT_UX_DEBUG)\
 $(OBJ_SHWILD_MT_UX)\
 \

# examples
OBJ_EXAMPLE=\
 \

# Component Tests
OBJ_TEST_COMPONENT=\
 $(OBJ_TEST_COMP_readln_MT_UX_DEBUG)\
 $(OBJ_TEST_COMP_readln_MT_UX)\
 \

# Scratch Tests
OBJ_TEST_SCRATCH=\
 $(OBJ_TEST_SCRT_api_MT_UX_DEBUG)\
 $(OBJ_TEST_SCRT_cr_MT_UX_DEBUG)\
 $(OBJ_TEST_SCRT_dl_MT_UX_DEBUG)\
 $(OBJ_TEST_SCRT_aubuf_MT_UX_DEBUG)\
 $(OBJ_TEST_SCRT_api_MT_UX)\
 $(OBJ_TEST_SCRT_cr_MT_UX)\
 $(OBJ_TEST_SCRT_dl_MT_UX)\
 $(OBJ_TEST_SCRT_aubuf_MT_UX)\
 \

# Unit Tests
OBJ_TEST_UNIT=\
 $(OBJ_TEST_UNIT_1_MT_UX_DEBUG)\
 $(OBJ_TEST_UNIT_2_MT_UX_DEBUG)\
 $(OBJ_TEST_UNIT_GSCS_MT_UX_DEBUG)\
 $(OBJ_TEST_UNIT_AB_MT_UX_DEBUG)\
 $(OBJ_TEST_UNIT_1_MT_UX)\
 $(OBJ_TEST_UNIT_2_MT_UX)\
 $(OBJ_TEST_UNIT_GSCS_MT_UX)\
 $(OBJ_TEST_UNIT_AB_MT_UX)\
 \

########################################
# libraries

TARGETS_LIB_CORE=\
 $(LIB_CORE_MT_UX_DEBUG)\
 $(LIB_CORE_MT_UX)\
 \

TARGETS_LIB_ALL=\
 $(TARGETS_LIB_CORE)\
 \

TARGETS_LIB_SHWILD=\
 $(LIB_SHWILD_MT_UX_DEBUG)\
 $(LIB_SHWILD_MT_UX)\
 \

TARGETS_LIB_XTESTS = \
 $(LIB_XTESTS_MT_UX_DEBUG)\
 $(LIB_XTESTS_MT_UX)\
 \

########################################
# programs

TARGETS_EXAMPLE_C=\
 \

TARGETS_EXAMPLE_CPP=\
 \

TARGETS_EXAMPLE=\
 $(TARGETS_EXAMPLE_C)\
 $(TARGETS_EXAMPLE_CPP)\
 \


TARGETS_SAMPLE=\
 \

TARGETS_TEST_COMPONENT=\
 $(TARG_TEST_COMP_readln_MT_UX_DEBUG)\
 $(TARG_TEST_COMP_readln_MT_UX)\
 \

TARGETS_TEST_SCRATCH=\
 $(TARG_TEST_SCRT_api_MT_UX_DEBUG)\
 $(TARG_TEST_SCRT_cr_MT_UX_DEBUG)\
 $(TARG_TEST_SCRT_dl_MT_UX_DEBUG)\
 $(TARG_TEST_SCRT_aubuf_MT_UX_DEBUG)\
 $(TARG_TEST_SCRT_api_MT_UX)\
 $(TARG_TEST_SCRT_cr_MT_UX)\
 $(TARG_TEST_SCRT_dl_MT_UX)\
 $(TARG_TEST_SCRT_aubuf_MT_UX)\
 \

TARGETS_TEST_UNIT=\
 $(TARG_TEST_UNIT_1_MT_UX_DEBUG)\
 $(TARG_TEST_UNIT_2_MT_UX_DEBUG)\
 $(TARG_TEST_UNIT_GSCS_MT_UX_DEBUG)\
 $(TARG_TEST_UNIT_AB_MT_UX_DEBUG)\
 $(TARG_TEST_UNIT_1_MT_UX)\
 $(TARG_TEST_UNIT_2_MT_UX)\
 $(TARG_TEST_UNIT_GSCS_MT_UX)\
 $(TARG_TEST_UNIT_AB_MT_UX)\
 \


############################################################
# third-party libraries

############################################################################
# external targets (invokable by make)

# primary

_default:					build

usage:
	@echo "make [usage | compile | build | test | clean] - default is 'build'"
	@echo ""
	@echo "NOTE: the following variables may be defined in order to alter the build:"
	@echo ""
	@echo "- CSTRING_SHWILD_BASE_DIR - to specify an alternative root directory for the source of the shwild library"
	@echo "- CSTRING_XTESTS_BASE_DIR - to specify an alternative root directory for the source of the xTests library"

# infrastructure

check.lib.dir:				$(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)

check.bin.dir:				$(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_BIN_DIR)\NUL mkdir $(PROJ_BIN_DIR)


# compile targets

compile.libs.core:			$(PROJ_MAKEFILE_NAME)	$(OBJ_CORE)

compile.libs:										compile.libs.core

compile.libs.shwild:		$(PROJ_MAKEFILE_NAME)	$(OBJ_SHWILD)

compile.libs.3pty:									compile.libs.shwild

compile.libs.all:                                   compile.libs compile.libs.3pty

compile.examples:			$(PROJ_MAKEFILE_NAME)	$(OBJ_EXAMPLE)

compile.samples:			$(PROJ_MAKEFILE_NAME)	$(OBJ_SAMPLE)

compile.test.component:		$(PROJ_MAKEFILE_NAME)	$(OBJ_TEST_COMPONENT)

compile.test.scratch:		$(PROJ_MAKEFILE_NAME)	$(OBJ_TEST_SCRATCH)

compile.test.unit:			$(PROJ_MAKEFILE_NAME)	$(OBJ_TEST_UNIT)

compile.test:										compile.test.unit compile.test.component compile.test.scratch

compile:											compile.libs compile.libs.3pty compile.test compile.examples compile.samples

compile.all:										compile




# build targets

build.libs.core:			check.lib.dir			$(TARGETS_LIB_CORE)

build.libs:											build.libs.core

build.libs.shwild:			check.lib.dir			$(TARGETS_LIB_SHWILD)

build.libs.xtests:			check.lib.dir			$(TARGETS_LIB_XTESTS)

build.libs.3pty:									build.libs.shwild build.libs.xtests

build.libs.all:										build.libs build.libs.3pty

build.examples:				check.bin.dir			$(TARGETS_EXAMPLE)

build.samples:				check.bin.dir			$(TARGETS_SAMPLE)

build.test.component:		check.bin.dir			$(TARGETS_TEST_COMPONENT)

build.test.scratch:			check.bin.dir			$(TARGETS_TEST_SCRATCH)

build.test.unit:			check.bin.dir			$(TARGETS_TEST_UNIT)

build.test:											build.test.unit build.test.component build.test.scratch

build:												compile build.libs build.test build.examples build.samples

build.all:											build.libs.all build



# test targets

test.component_:
	@echo Running Test:Component programs ...
	$(TARG_TEST_COMP_readln_MT_UX_DEBUG) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_COMP_readln_MT_UX) --verbosity=$(TEST_VERBOSITY)

test.scratch_:
	@echo Running Test:Scratch programs ...
	$(TARG_TEST_SCRT_api_MT_UX_DEBUG) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_cr_MT_UX_DEBUG) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_dl_MT_UX_DEBUG) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_aubuf_MT_UX_DEBUG) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_api_MT_UX) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_cr_MT_UX) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_dl_MT_UX) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_aubuf_MT_UX) --verbosity=$(TEST_VERBOSITY)

test.unit_:
	@echo Running Test:Unit programs ...
	$(TARG_TEST_UNIT_1_MT_UX_DEBUG) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_2_MT_UX_DEBUG) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_GSCS_MT_UX_DEBUG) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_AB_MT_UX_DEBUG) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_1_MT_UX) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_2_MT_UX) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_GSCS_MT_UX) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_AB_MT_UX) --verbosity=$(TEST_VERBOSITY)

test.component:			$(PROJ_MAKEFILE_NAME)	build.test.component test.component_

test.scratch:			$(PROJ_MAKEFILE_NAME)	build.test.scratch test.scratch_

test.unit:				$(PROJ_MAKEFILE_NAME)	build.test.unit test.unit_

test:											test.unit test.component

test.all:										test test.scratch
test-all:				test.all


# clean targets

clean.libs.core:
	@echo Cleaning Core libraries ...
	@-$(RM) $(LIB_CORE_MT_UX_DEBUG)
	@-$(RM) $(LIB_UTIL_MT_UX_DEBUG)
	@-$(RM) $(LIB_CORE_MT_UX)
	@-$(RM) $(LIB_UTIL_MT_UX)
	@-$(RM) $(OBJ_CORE_MT_UX_DEBUG)
	@-$(RM) $(OBJ_UTIL_MT_UX_DEBUG)
	@-$(RM) $(PDB_CORE_MT_UX_DEBUG)
	@-$(RM) $(OBJ_CORE_MT_UX)
	@-$(RM) $(OBJ_UTIL_MT_UX)

clean.libs.shwild:
	@echo Cleaning shwild libraries ...
	@-$(RM) $(LIB_SHWILD_MT_UX_DEBUG)
	@-$(RM) $(LIB_SHWILD_MT_UX)
	@-$(RM) $(OBJ_SHWILD_MT_UX_DEBUG)
	@-$(RM) $(PDB_SHWILD_MT_UX_DEBUG)
	@-$(RM) $(OBJ_SHWILD_MT_UX)

clean.libs.xtests:
	@echo Cleaning xTests libraries ...
	@-$(RM) $(LIB_XTESTS_MT_UX_DEBUG)
	@-$(RM) $(LIB_XTESTS_MT_UX)
	@-$(RM) $(OBJ_XTESTS_MT_UX_DEBUG)
	@-$(RM) $(PDB_XTESTS_MT_UX_DEBUG)
	@-$(RM) $(OBJ_XTESTS_MT_UX)

clean.test.component:
	@echo cleaning Test:Component libraries ...
	$(RM) test.component*.obj
	$(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).mt.debug.exe
	$(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).mt.exe

clean.test.scratch:
	@echo cleaning Test:Scratch libraries ...
	$(RM) test.scratch*.obj
	$(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).mt.debug.exe
	$(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).mt.exe

clean.test.unit:
	@echo cleaning Test:Unit libraries ...
	$(RM) test.unit*.obj
	$(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).mt.debug.exe
	$(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).mt.exe

clean.libs: 									clean.libs.core

clean.libs.3pty:								clean.libs.shwild clean.libs.xtests

clean.libs.all: 								clean.libs clean.libs.3pty

clean.examples:			$(PROJ_MAKEFILE_NAME)

clean.samples:			$(PROJ_MAKEFILE_NAME)

clean.test:										clean.test.component clean.test.scratch clean.test.unit

clean:					$(PROJ_MAKEFILE_NAME)	clean.libs.all clean.test clean.examples clean.samples



############################################################################
# build targets

##################################################
# libraries

########################################
# Main library - 'cstring.X.a'

$(LIB_CORE_MT_UX_DEBUG): $(OBJ_CORE_MT_UX_DEBUG) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_CORE_MT_UX_DEBUG)

$(OBJ_lib_core_MT_UX_DEBUG):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.core.c
	$(CC) $(CC_ARGS_MT_UX_DEBUG) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.core.c

$(LIB_CORE_MT_UX): $(OBJ_CORE_MT_UX) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_CORE_MT_UX)

$(OBJ_lib_core_MT_UX):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.core.c
	$(CC) $(CC_ARGS_MT_UX) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.core.c

########################################
# shwild library - 'shwild.X.cs.core.a'

$(LIB_SHWILD_MT_UX_DEBUG): $(OBJ_SHWILD_MT_UX_DEBUG) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_SHWILD_MT_UX_DEBUG)

$(OBJ_shw_api_MT_UX_DEBUG): $(SHWILD_SRC_DIR)\api.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) $(CPPC_SHWILD_INCLUDES_MT_UX_DEBUG) -Fo$@ $(SHWILD_SRC_DIR)\api.cpp
$(OBJ_shw_matches_MT_UX_DEBUG): $(SHWILD_SRC_DIR)\matches.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) $(CPPC_SHWILD_INCLUDES_MT_UX_DEBUG) -Fo$@ $(SHWILD_SRC_DIR)\matches.cpp
$(OBJ_shw_pattern_MT_UX_DEBUG): $(SHWILD_SRC_DIR)\pattern.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) $(CPPC_SHWILD_INCLUDES_MT_UX_DEBUG) -Fo$@ $(SHWILD_SRC_DIR)\pattern.cpp

$(LIB_SHWILD_MT_UX): $(OBJ_SHWILD_MT_UX) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_SHWILD_MT_UX)

$(OBJ_shw_api_MT_UX): $(SHWILD_SRC_DIR)\api.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) $(CPPC_SHWILD_INCLUDES_MT_UX) -Fo$@ $(SHWILD_SRC_DIR)\api.cpp
$(OBJ_shw_matches_MT_UX): $(SHWILD_SRC_DIR)\matches.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) $(CPPC_SHWILD_INCLUDES_MT_UX) -Fo$@ $(SHWILD_SRC_DIR)\matches.cpp
$(OBJ_shw_pattern_MT_UX): $(SHWILD_SRC_DIR)\pattern.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) $(CPPC_SHWILD_INCLUDES_MT_UX) -Fo$@ $(SHWILD_SRC_DIR)\pattern.cpp

########################################
# xTests library - 'xtests.X.cs.core.a'

$(LIB_XTESTS_MT_UX_DEBUG): $(OBJ_XTESTS_MT_UX_DEBUG) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_XTESTS_MT_UX_DEBUG)

$(OBJ_xts_core_MT_UX_DEBUG): $(XTESTS_SRC_DIR)\xtests.core.cpp $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) $(CPPC_XTESTS_INCLUDES_MT_UX_DEBUG) -Fo$@ $(XTESTS_SRC_DIR)\xtests.core.cpp

$(LIB_XTESTS_MT_UX): $(OBJ_XTESTS_MT_UX) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_XTESTS_MT_UX)

$(OBJ_xts_core_MT_UX): $(XTESTS_SRC_DIR)\xtests.core.cpp $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) $(CPPC_XTESTS_INCLUDES_MT_UX) -Fo$@ $(XTESTS_SRC_DIR)\xtests.core.cpp

##################################################
# examples

##################################################
# tests

##############################
# component tests

$(TARG_TEST_COMP_readln_MT_UX_DEBUG):    \
		$(OBJ_TEST_COMP_readln_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX_DEBUG) -out:$@ \
		$(OBJ_TEST_COMP_readln_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(TARGET_LIB_MT_UX_DEBUG)

$(OBJ_TEST_COMP_readln_MT_UX_DEBUG): $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) -Fo$@ $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp

$(TARG_TEST_COMP_readln_MT_UX):    \
		$(OBJ_TEST_COMP_readln_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX) -out:$@ \
		$(OBJ_TEST_COMP_readln_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(TARGET_LIB_MT_UX)

$(OBJ_TEST_COMP_readln_MT_UX): $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) -Fo$@ $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp

##############################
# scratch tests

$(TARG_TEST_SCRT_api_MT_UX_DEBUG):    \
		$(OBJ_TEST_SCRT_api_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX_DEBUG) -out:$@ \
		$(OBJ_TEST_SCRT_api_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(TARGET_LIB_MT_UX_DEBUG)

$(OBJ_TEST_SCRT_api_MT_UX_DEBUG): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_UX_DEBUG) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c

$(TARG_TEST_SCRT_api_MT_UX):    \
		$(OBJ_TEST_SCRT_api_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX) -out:$@ \
		$(OBJ_TEST_SCRT_api_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(TARGET_LIB_MT_UX)

$(OBJ_TEST_SCRT_api_MT_UX): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_UX) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c

$(TARG_TEST_SCRT_cr_MT_UX_DEBUG):    \
		$(OBJ_TEST_SCRT_cr_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX_DEBUG) -out:$@ \
		$(OBJ_TEST_SCRT_cr_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(TARGET_LIB_MT_UX_DEBUG)

$(OBJ_TEST_SCRT_cr_MT_UX_DEBUG): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_UX_DEBUG) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c

$(TARG_TEST_SCRT_cr_MT_UX):    \
		$(OBJ_TEST_SCRT_cr_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX) -out:$@ \
		$(OBJ_TEST_SCRT_cr_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(TARGET_LIB_MT_UX)

$(OBJ_TEST_SCRT_cr_MT_UX): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_UX) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c

$(TARG_TEST_SCRT_dl_MT_UX_DEBUG):    \
		$(OBJ_TEST_SCRT_dl_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX_DEBUG) -out:$@ \
		$(OBJ_TEST_SCRT_dl_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(TARGET_LIB_MT_UX_DEBUG)

$(OBJ_TEST_SCRT_dl_MT_UX_DEBUG): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp

$(TARG_TEST_SCRT_dl_MT_UX):    \
		$(OBJ_TEST_SCRT_dl_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX) -out:$@ \
		$(OBJ_TEST_SCRT_dl_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(TARGET_LIB_MT_UX)

$(OBJ_TEST_SCRT_dl_MT_UX): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp

$(TARG_TEST_SCRT_aubuf_MT_UX_DEBUG):    \
		$(OBJ_TEST_SCRT_aubuf_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX_DEBUG) -out:$@ \
		$(OBJ_TEST_SCRT_aubuf_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(TARGET_LIB_MT_UX_DEBUG)

$(OBJ_TEST_SCRT_aubuf_MT_UX_DEBUG): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_UX_DEBUG) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c

$(TARG_TEST_SCRT_aubuf_MT_UX):    \
		$(OBJ_TEST_SCRT_aubuf_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX) -out:$@ \
		$(OBJ_TEST_SCRT_aubuf_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(TARGET_LIB_MT_UX)

$(OBJ_TEST_SCRT_aubuf_MT_UX): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_UX) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c

##############################
# unit tests

$(TARG_TEST_UNIT_1_MT_UX_DEBUG):    \
		$(OBJ_TEST_UNIT_1_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX_DEBUG) -out:$@ \
		$(OBJ_TEST_UNIT_1_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(TARGET_LIB_MT_UX_DEBUG)

$(OBJ_TEST_UNIT_1_MT_UX_DEBUG): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp

$(TARG_TEST_UNIT_1_MT_UX):    \
		$(OBJ_TEST_UNIT_1_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX) -out:$@ \
		$(OBJ_TEST_UNIT_1_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(TARGET_LIB_MT_UX)

$(OBJ_TEST_UNIT_1_MT_UX): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp

$(TARG_TEST_UNIT_2_MT_UX_DEBUG):    \
		$(OBJ_TEST_UNIT_2_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX_DEBUG) -out:$@ \
		$(OBJ_TEST_UNIT_2_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(TARGET_LIB_MT_UX_DEBUG)

$(OBJ_TEST_UNIT_2_MT_UX_DEBUG): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp

$(TARG_TEST_UNIT_2_MT_UX):    \
		$(OBJ_TEST_UNIT_2_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX) -out:$@ \
		$(OBJ_TEST_UNIT_2_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(TARGET_LIB_MT_UX)

$(OBJ_TEST_UNIT_2_MT_UX): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp

$(TARG_TEST_UNIT_GSCS_MT_UX_DEBUG):    \
		$(OBJ_TEST_UNIT_GSCS_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX_DEBUG) -out:$@ \
		$(OBJ_TEST_UNIT_GSCS_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(TARGET_LIB_MT_UX_DEBUG)

$(OBJ_TEST_UNIT_GSCS_MT_UX_DEBUG): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp

$(TARG_TEST_UNIT_GSCS_MT_UX):    \
		$(OBJ_TEST_UNIT_GSCS_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX) -out:$@ \
		$(OBJ_TEST_UNIT_GSCS_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(TARGET_LIB_MT_UX)

$(OBJ_TEST_UNIT_GSCS_MT_UX): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp

$(TARG_TEST_UNIT_AB_MT_UX_DEBUG):    \
		$(OBJ_TEST_UNIT_AB_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX_DEBUG) -out:$@ \
		$(OBJ_TEST_UNIT_AB_MT_UX_DEBUG)\
		$(LIB_CORE_MT_UX_DEBUG)\
		$(LIB_SHWILD_MT_UX_DEBUG)\
		$(LIB_XTESTS_MT_UX_DEBUG)\
		$(TARGET_LIB_MT_UX_DEBUG)

$(OBJ_TEST_UNIT_AB_MT_UX_DEBUG): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX_DEBUG) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp

$(TARG_TEST_UNIT_AB_MT_UX):    \
		$(OBJ_TEST_UNIT_AB_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_UX) -out:$@ \
		$(OBJ_TEST_UNIT_AB_MT_UX)\
		$(LIB_CORE_MT_UX)\
		$(LIB_SHWILD_MT_UX)\
		$(LIB_XTESTS_MT_UX)\
		$(TARGET_LIB_MT_UX)

$(OBJ_TEST_UNIT_AB_MT_UX): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_UX) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp

############################### end of file ################################
