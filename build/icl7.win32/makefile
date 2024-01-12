############################################################################
# File:		makefile
#
# Purpose:	Generated makefile for the cstring project,
#           for the Intel C/C++ Compiler v7.0 compiler
#           on the Win32 platform
#
# Created:	16th December 2007
# Updated:	20th February 2021
#
############################################################################


############################################################################
# instructions (in no particular order)

############################################################################
# environment check

!ifndef STLSOFT
!error STLSOFT must be defined
!endif # !STLSOFT

############################################################################
# symbols

########################################
# project & compiler version

COMP_TAG			=	icl7
ARCH_TAG            =   
OS_TAG				=   
PROJ_TAG			=	cstring
PROJ_VER_MAJOR		=	4
PROJ_TAG_VER		=	$(PROJ_TAG).$(PROJ_VER_MAJOR)
COMP_ARCH_OS_TAG	=	$(COMP_TAG)$(OS_TAG)$(ARCH_TAG)

SHWILD_VER_MAJOR    =   0
SHWILD_TAG_VER      =   shwild.$(SHWILD_VER_MAJOR)

XTESTS_VER_MAJOR    =   0
XTESTS_TAG_VER      =   xtests.$(XTESTS_VER_MAJOR)

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

CC		=   icl
CPPC	=   icl
AR		=   xilib
LD		=   xilink
RM		=   del /f
CP		=   copy
RC		=   rc

########################################
# include directory symbols

INCLUDES_LEADER		=	

PROJ_INCLUDE		=	-I$(PROJ_INCLUDE_DIR)

ENV_INCLUDES		=

COMMON_INCLUDES		=

UNIXEM_INCLUDE		=

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
 $(UNIXEM_INCLUDE)\
 $(ENV_INCLUDES)\
 \

CC_INCLUDES_DLL_D =\
 $(CC_INCLUDES_BASE)\
 \

CC_INCLUDES_DLL_R =\
 $(CC_INCLUDES_BASE)\
 \

CC_INCLUDES_MT_D =\
 $(CC_INCLUDES_BASE)\
 \

CC_INCLUDES_MT_R =\
 $(CC_INCLUDES_BASE)\
 \

CC_INCLUDES_ST_D =\
 $(CC_INCLUDES_BASE)\
 \

CC_INCLUDES_ST_R =\
 $(CC_INCLUDES_BASE)\
 \



CC_SHWILD_INCLUDES_BASE =\
 $(CC_INCLUDES_BASE)\
 \

CC_SHWILD_INCLUDES_DLL_D =\
 $(CC_SHWILD_INCLUDES_BASE)\
 \

CC_SHWILD_INCLUDES_DLL_R =\
 $(CC_SHWILD_INCLUDES_BASE)\
 \

CC_SHWILD_INCLUDES_MT_D =\
 $(CC_SHWILD_INCLUDES_BASE)\
 \

CC_SHWILD_INCLUDES_MT_R =\
 $(CC_SHWILD_INCLUDES_BASE)\
 \

CC_SHWILD_INCLUDES_ST_D =\
 $(CC_SHWILD_INCLUDES_BASE)\
 \

CC_SHWILD_INCLUDES_ST_R =\
 $(CC_SHWILD_INCLUDES_BASE)\
 \


CC_XTESTS_INCLUDES_BASE =\
 $(CC_INCLUDES_BASE)\
 \

CC_XTESTS_INCLUDES_DLL_D =\
 $(CC_XTESTS_INCLUDES_BASE)\
 \

CC_XTESTS_INCLUDES_DLL_R =\
 $(CC_XTESTS_INCLUDES_BASE)\
 \

CC_XTESTS_INCLUDES_MT_D =\
 $(CC_XTESTS_INCLUDES_BASE)\
 \

CC_XTESTS_INCLUDES_MT_R =\
 $(CC_XTESTS_INCLUDES_BASE)\
 \

CC_XTESTS_INCLUDES_ST_D =\
 $(CC_XTESTS_INCLUDES_BASE)\
 \

CC_XTESTS_INCLUDES_ST_R =\
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
 $(UNIXEM_INCLUDE)\
 $(ENV_INCLUDES)\
 \

CPPC_INCLUDES_DLL_D =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_INCLUDES_DLL_R =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_INCLUDES_MT_D =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_INCLUDES_MT_R =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_INCLUDES_ST_D =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_INCLUDES_ST_R =\
 $(CPPC_INCLUDES_BASE)\
 \



CPPC_SHWILD_INCLUDES_BASE =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_SHWILD_INCLUDES_DLL_D =\
 $(CPPC_SHWILD_INCLUDES_BASE)\
 \

CPPC_SHWILD_INCLUDES_DLL_R =\
 $(CPPC_SHWILD_INCLUDES_BASE)\
 \

CPPC_SHWILD_INCLUDES_MT_D =\
 $(CPPC_SHWILD_INCLUDES_BASE)\
 \

CPPC_SHWILD_INCLUDES_MT_R =\
 $(CPPC_SHWILD_INCLUDES_BASE)\
 \

CPPC_SHWILD_INCLUDES_ST_D =\
 $(CPPC_SHWILD_INCLUDES_BASE)\
 \

CPPC_SHWILD_INCLUDES_ST_R =\
 $(CPPC_SHWILD_INCLUDES_BASE)\
 \


CPPC_XTESTS_INCLUDES_BASE =\
 $(CPPC_INCLUDES_BASE)\
 \

CPPC_XTESTS_INCLUDES_DLL_D =\
 $(CPPC_XTESTS_INCLUDES_BASE)\
 \

CPPC_XTESTS_INCLUDES_DLL_R =\
 $(CPPC_XTESTS_INCLUDES_BASE)\
 \

CPPC_XTESTS_INCLUDES_MT_D =\
 $(CPPC_XTESTS_INCLUDES_BASE)\
 \

CPPC_XTESTS_INCLUDES_MT_R =\
 $(CPPC_XTESTS_INCLUDES_BASE)\
 \

CPPC_XTESTS_INCLUDES_ST_D =\
 $(CPPC_XTESTS_INCLUDES_BASE)\
 \

CPPC_XTESTS_INCLUDES_ST_R =\
 $(CPPC_XTESTS_INCLUDES_BASE)\
 \



########################################
# library directory symbols

LIBS_LEADER 			=	

# lib paths

ENV_LIBPATHS			=
COMMON_LIBPATHS			=


LIBPATHS=\
 $(LIBS_LEADER)\
 $(COMMON_LIBPATHS)\
 $(ENV_LIBPATHS)\
 \


########################################
# library names

TARGET_LIB_DLL_D=\
 advapi32.lib kernel32.lib ole32.lib oleaut32.lib shlwapi.lib user32.lib uuid.lib version.lib wininet.lib ws2_32.lib\
 \

TARGET_LIB_DLL_R=\
 advapi32.lib kernel32.lib ole32.lib oleaut32.lib shlwapi.lib user32.lib uuid.lib version.lib wininet.lib ws2_32.lib\
 \

TARGET_LIB_MT_D=\
 advapi32.lib kernel32.lib ole32.lib oleaut32.lib shlwapi.lib user32.lib uuid.lib version.lib wininet.lib ws2_32.lib\
 \

TARGET_LIB_MT_R=\
 advapi32.lib kernel32.lib ole32.lib oleaut32.lib shlwapi.lib user32.lib uuid.lib version.lib wininet.lib ws2_32.lib\
 \

TARGET_LIB_ST_D=\
 advapi32.lib kernel32.lib ole32.lib oleaut32.lib shlwapi.lib user32.lib uuid.lib version.lib wininet.lib ws2_32.lib\
 \

TARGET_LIB_ST_R=\
 advapi32.lib kernel32.lib ole32.lib oleaut32.lib shlwapi.lib user32.lib uuid.lib version.lib wininet.lib ws2_32.lib\
 \


########################################
# #defines

OS_DEFS				=	-DWIN32

COMMON_DEFS 		=	-DWIN32

CUSTOM_DEFS			=


# CC flags

CC_F_NOLOGO           =   -nologo
CC_F_COMPILE_ONLY     =   -c
CC_F_WARNING_MAX      =   -W4
CC_F_WARNING_ERR      =   -W3 -Qwd193 -Qwd279
CC_F_MINIMUM_SIZE     =   -O1
CC_F_MAXIMUM_SPEED	=	-O2

CC_FLAGS_BASE =\
 $(CC_F_NOLOGO)\
 $(CC_F_COMPILE_ONLY)\
 $(CC_F_WARNING_MAX)\
 $(CC_F_WARNING_ERR)\
 \

CC_FLAGS_DLL_D =\
 $(CC_FLAGS_BASE)\
 \

CC_FLAGS_DLL_R =\
 $(CC_FLAGS_BASE)\
 \

CC_FLAGS_MT_D =\
 $(CC_FLAGS_BASE)\
 \

CC_FLAGS_MT_R =\
 $(CC_FLAGS_BASE)\
 \

CC_FLAGS_ST_D =\
 $(CC_FLAGS_BASE)\
 \

CC_FLAGS_ST_R =\
 $(CC_FLAGS_BASE)\
 \


# CPPC flags

CPPC_F_NOLOGO           =   -nologo
CPPC_F_COMPILE_ONLY     =   -c
CPPC_F_WARNING_MAX      =   -W3 -Qwd171 -Qwd193 -Qwd279 -Qwd383
CPPC_F_WARNING_ERR      =   -WX
CPPC_F_EXCEPTIONS_ON	=	-GX
CPPC_F_EXCEPTIONS_OFF	=	-GX-
CPPC_F_EXCEPTIONS		=	$(CPPC_F_EXCEPTIONS_ON)
CPPC_F_RTTI_ON			=	-GR
CPPC_F_RTTI_OFF 		=	-GR-
CPPC_F_RTTI				=	$(CPPC_F_RTTI_ON)
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

CPPC_FLAGS_DLL_D =\
 $(CPPC_FLAGS_BASE)\
 \

CPPC_FLAGS_DLL_R =\
 $(CPPC_FLAGS_BASE)\
 \

CPPC_FLAGS_MT_D =\
 $(CPPC_FLAGS_BASE)\
 \

CPPC_FLAGS_MT_R =\
 $(CPPC_FLAGS_BASE)\
 \

CPPC_FLAGS_ST_D =\
 $(CPPC_FLAGS_BASE)\
 \

CPPC_FLAGS_ST_R =\
 $(CPPC_FLAGS_BASE)\
 \


# CC defines

CC_DEFS_BASE =\
 $(COMMON_DEFS)\
 $(CUSTOM_DEFS)\
 \


CC_DEFS_DLL_D =\
 $(CC_DEFS_BASE)\
 \

CC_DEFS_DLL_R =\
 $(CC_DEFS_BASE)\
 \

CC_DEFS_MT_D =\
 $(CC_DEFS_BASE)\
 \

CC_DEFS_MT_R =\
 $(CC_DEFS_BASE)\
 \

CC_DEFS_ST_D =\
 $(CC_DEFS_BASE)\
 \

CC_DEFS_ST_R =\
 $(CC_DEFS_BASE)\
 \


# CPPC defines

CPPC_DEFS_BASE =\
 $(COMMON_DEFS)\
 $(CUSTOM_DEFS)\
 \


CPPC_DEFS_DLL_D =\
 $(CPPC_DEFS_BASE)\
 \

CPPC_DEFS_DLL_R =\
 $(CPPC_DEFS_BASE)\
 \

CPPC_DEFS_MT_D =\
 $(CPPC_DEFS_BASE)\
 \

CPPC_DEFS_MT_R =\
 $(CPPC_DEFS_BASE)\
 \

CPPC_DEFS_ST_D =\
 $(CPPC_DEFS_BASE)\
 \

CPPC_DEFS_ST_R =\
 $(CPPC_DEFS_BASE)\
 \



# CC args (= flags + defines + includes)

CC_ARGS_DLL_D=\
 $(CC_FLAGS_DLL_D)\
 -MDd -D_DEBUG\
 $(CC_DEFS_DLL_D)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CC_INCLUDES_DLL_D)
CC_ARGS_DLL_R=\
 $(CC_FLAGS_DLL_R)\
 -MD -DNDEBUG $(CC_F_MAXIMUM_SPEED)\
 $(CC_DEFS_DLL_R)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CC_INCLUDES_DLL_R)
CC_ARGS_MT_D=\
 $(CC_FLAGS_MT_D)\
 -MTd -D_DEBUG\
 $(CC_DEFS_MT_D)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CC_INCLUDES_MT_D)
CC_ARGS_MT_R=\
 $(CC_FLAGS_MT_R)\
 -MT -DNDEBUG $(CC_F_MAXIMUM_SPEED)\
 $(CC_DEFS_MT_R)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CC_INCLUDES_MT_R)
CC_ARGS_ST_D=\
 $(CC_FLAGS_ST_D)\
 -MLd -D_DEBUG\
 $(CC_DEFS_ST_D)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CC_INCLUDES_ST_D)
CC_ARGS_ST_R=\
 $(CC_FLAGS_ST_R)\
 -ML -DNDEBUG $(CC_F_MAXIMUM_SPEED)\
 $(CC_DEFS_ST_R)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CC_INCLUDES_ST_R)

# CPPC args (= flags + defines + includes)

CPPC_ARGS_DLL_D=\
 $(CPPC_FLAGS_DLL_D)\
 -MDd -D_DEBUG\
 $(CPPC_DEFS_DLL_D)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CPPC_INCLUDES_DLL_D)
CPPC_ARGS_DLL_R=\
 $(CPPC_FLAGS_DLL_R)\
 -MD -DNDEBUG $(CPPC_F_MAXIMUM_SPEED)\
 $(CPPC_DEFS_DLL_R)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CPPC_INCLUDES_DLL_R)
CPPC_ARGS_MT_D=\
 $(CPPC_FLAGS_MT_D)\
 -MTd -D_DEBUG\
 $(CPPC_DEFS_MT_D)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CPPC_INCLUDES_MT_D)
CPPC_ARGS_MT_R=\
 $(CPPC_FLAGS_MT_R)\
 -MT -DNDEBUG $(CPPC_F_MAXIMUM_SPEED)\
 $(CPPC_DEFS_MT_R)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CPPC_INCLUDES_MT_R)
CPPC_ARGS_ST_D=\
 $(CPPC_FLAGS_ST_D)\
 -MLd -D_DEBUG\
 $(CPPC_DEFS_ST_D)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CPPC_INCLUDES_ST_D)
CPPC_ARGS_ST_R=\
 $(CPPC_FLAGS_ST_R)\
 -ML -DNDEBUG $(CPPC_F_MAXIMUM_SPEED)\
 $(CPPC_DEFS_ST_R)\
 -DXTESTS_NO_IMPLICIT_LINK\
 $(CPPC_INCLUDES_ST_R)



# AR args

AR_ARGS 			=	-nologo


# LD flags

LD_F_NOLOGO				=   -nologo

LD_FLAGS_BASE =\
 $(LD_F_NOLOGO)\
 \

LD_FLAGS_DLL_D =\
 $(LD_FLAGS_BASE)\
 \

LD_FLAGS_DLL_R =\
 $(LD_FLAGS_BASE)\
 \

LD_FLAGS_MT_D =\
 $(LD_FLAGS_BASE)\
 \

LD_FLAGS_MT_R =\
 $(LD_FLAGS_BASE)\
 \

LD_FLAGS_ST_D =\
 $(LD_FLAGS_BASE)\
 \

LD_FLAGS_ST_R =\
 $(LD_FLAGS_BASE)\
 \


# LD includes

LD_INCLUDES_BASE =\
 $(LIBPATHS)\
 \

LD_INCLUDES_DLL_D =\
 $(LD_INCLUDES_BASE)\
 \

LD_INCLUDES_DLL_R =\
 $(LD_INCLUDES_BASE)\
 \

LD_INCLUDES_MT_D =\
 $(LD_INCLUDES_BASE)\
 \

LD_INCLUDES_MT_R =\
 $(LD_INCLUDES_BASE)\
 \

LD_INCLUDES_ST_D =\
 $(LD_INCLUDES_BASE)\
 \

LD_INCLUDES_ST_R =\
 $(LD_INCLUDES_BASE)\
 \


# LD args

LD_ARGS_DLL_D=  $(LD_FLAGS_DLL_D)  $(LD_INCLUDES_DLL_D)
LD_ARGS_DLL_R=  $(LD_FLAGS_DLL_R)  $(LD_INCLUDES_DLL_R)
LD_ARGS_MT_D=  $(LD_FLAGS_MT_D)  $(LD_INCLUDES_MT_D)
LD_ARGS_MT_R=  $(LD_FLAGS_MT_R)  $(LD_INCLUDES_MT_R)
LD_ARGS_ST_D=  $(LD_FLAGS_ST_D)  $(LD_INCLUDES_ST_D)
LD_ARGS_ST_R=  $(LD_FLAGS_ST_R)  $(LD_INCLUDES_ST_R)

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
LIB_CORE_DLL_D			=	$(PROJ_LIB_DIR)\$(PROJ_TAG_VER).core.$(COMP_ARCH_OS_TAG).dll.debug.lib
LIB_CORE_DLL_R			=	$(PROJ_LIB_DIR)\$(PROJ_TAG_VER).core.$(COMP_ARCH_OS_TAG).dll.lib
LIB_CORE_MT_D			=	$(PROJ_LIB_DIR)\$(PROJ_TAG_VER).core.$(COMP_ARCH_OS_TAG).mt.debug.lib
LIB_CORE_MT_R			=	$(PROJ_LIB_DIR)\$(PROJ_TAG_VER).core.$(COMP_ARCH_OS_TAG).mt.lib
LIB_CORE_ST_D			=	$(PROJ_LIB_DIR)\$(PROJ_TAG_VER).core.$(COMP_ARCH_OS_TAG).debug.lib
LIB_CORE_ST_R			=	$(PROJ_LIB_DIR)\$(PROJ_TAG_VER).core.$(COMP_ARCH_OS_TAG).lib

# shwild - testing only
LIB_SHWILD_DLL_D		=	$(PROJ_LIB_DIR)\$(SHWILD_TAG_VER).xt.$(COMP_ARCH_OS_TAG).dll.debug.lib
LIB_SHWILD_DLL_R		=	$(PROJ_LIB_DIR)\$(SHWILD_TAG_VER).xt.$(COMP_ARCH_OS_TAG).dll.lib
LIB_SHWILD_MT_D		=	$(PROJ_LIB_DIR)\$(SHWILD_TAG_VER).xt.$(COMP_ARCH_OS_TAG).mt.debug.lib
LIB_SHWILD_MT_R		=	$(PROJ_LIB_DIR)\$(SHWILD_TAG_VER).xt.$(COMP_ARCH_OS_TAG).mt.lib
LIB_SHWILD_ST_D		=	$(PROJ_LIB_DIR)\$(SHWILD_TAG_VER).xt.$(COMP_ARCH_OS_TAG).debug.lib
LIB_SHWILD_ST_R		=	$(PROJ_LIB_DIR)\$(SHWILD_TAG_VER).xt.$(COMP_ARCH_OS_TAG).lib

# xTests - testing only
LIB_XTESTS_DLL_D		=	$(PROJ_LIB_DIR)\$(XTESTS_TAG_VER).xt.$(COMP_ARCH_OS_TAG).dll.debug.lib
LIB_XTESTS_DLL_R		=	$(PROJ_LIB_DIR)\$(XTESTS_TAG_VER).xt.$(COMP_ARCH_OS_TAG).dll.lib
LIB_XTESTS_MT_D		=	$(PROJ_LIB_DIR)\$(XTESTS_TAG_VER).xt.$(COMP_ARCH_OS_TAG).mt.debug.lib
LIB_XTESTS_MT_R		=	$(PROJ_LIB_DIR)\$(XTESTS_TAG_VER).xt.$(COMP_ARCH_OS_TAG).mt.lib
LIB_XTESTS_ST_D		=	$(PROJ_LIB_DIR)\$(XTESTS_TAG_VER).xt.$(COMP_ARCH_OS_TAG).debug.lib
LIB_XTESTS_ST_R		=	$(PROJ_LIB_DIR)\$(XTESTS_TAG_VER).xt.$(COMP_ARCH_OS_TAG).lib

########################################
# examples


########################################
# tests

##############################
# component tests

TARG_TEST_COMP_readln_DLL_D	=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.cstring_readline.$(COMP_ARCH_OS_TAG).dll.debug.exe
TARG_TEST_COMP_readln_DLL_R	=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.cstring_readline.$(COMP_ARCH_OS_TAG).dll.exe
TARG_TEST_COMP_readln_MT_D	=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.cstring_readline.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_COMP_readln_MT_R	=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.cstring_readline.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_COMP_readln_ST_D	=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.cstring_readline.$(COMP_ARCH_OS_TAG).debug.exe
TARG_TEST_COMP_readln_ST_R	=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.cstring_readline.$(COMP_ARCH_OS_TAG).exe

##############################
# scratch tests

TARG_TEST_SCRT_api_DLL_D		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.$(COMP_ARCH_OS_TAG).dll.debug.exe
TARG_TEST_SCRT_cr_DLL_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring_create.$(COMP_ARCH_OS_TAG).dll.debug.exe
TARG_TEST_SCRT_dl_DLL_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.dynload.$(COMP_ARCH_OS_TAG).dll.debug.exe
TARG_TEST_SCRT_aubuf_DLL_D		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.auto_buffer.$(COMP_ARCH_OS_TAG).dll.debug.exe
TARG_TEST_SCRT_api_DLL_R		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.$(COMP_ARCH_OS_TAG).dll.exe
TARG_TEST_SCRT_cr_DLL_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring_create.$(COMP_ARCH_OS_TAG).dll.exe
TARG_TEST_SCRT_dl_DLL_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.dynload.$(COMP_ARCH_OS_TAG).dll.exe
TARG_TEST_SCRT_aubuf_DLL_R		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.auto_buffer.$(COMP_ARCH_OS_TAG).dll.exe
TARG_TEST_SCRT_api_MT_D		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_SCRT_cr_MT_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring_create.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_SCRT_dl_MT_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.dynload.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_SCRT_aubuf_MT_D		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.auto_buffer.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_SCRT_api_MT_R		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_SCRT_cr_MT_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring_create.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_SCRT_dl_MT_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.dynload.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_SCRT_aubuf_MT_R		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.auto_buffer.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_SCRT_api_ST_D		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.$(COMP_ARCH_OS_TAG).debug.exe
TARG_TEST_SCRT_cr_ST_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring_create.$(COMP_ARCH_OS_TAG).debug.exe
TARG_TEST_SCRT_dl_ST_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.dynload.$(COMP_ARCH_OS_TAG).debug.exe
TARG_TEST_SCRT_aubuf_ST_D		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.auto_buffer.$(COMP_ARCH_OS_TAG).debug.exe
TARG_TEST_SCRT_api_ST_R		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.$(COMP_ARCH_OS_TAG).exe
TARG_TEST_SCRT_cr_ST_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring_create.$(COMP_ARCH_OS_TAG).exe
TARG_TEST_SCRT_dl_ST_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.cstring.dynload.$(COMP_ARCH_OS_TAG).exe
TARG_TEST_SCRT_aubuf_ST_R		=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.auto_buffer.$(COMP_ARCH_OS_TAG).exe

##############################
# unit tests

TARG_TEST_UNIT_1_DLL_D			=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.1.$(COMP_ARCH_OS_TAG).dll.debug.exe
TARG_TEST_UNIT_2_DLL_D			=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.2.$(COMP_ARCH_OS_TAG).dll.debug.exe
TARG_TEST_UNIT_GSCS_DLL_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.cstring_getStatusCodeString.$(COMP_ARCH_OS_TAG).dll.debug.exe
TARG_TEST_UNIT_AB_DLL_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.auto_buffer.$(COMP_ARCH_OS_TAG).dll.debug.exe
TARG_TEST_UNIT_1_DLL_R			=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.1.$(COMP_ARCH_OS_TAG).dll.exe
TARG_TEST_UNIT_2_DLL_R			=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.2.$(COMP_ARCH_OS_TAG).dll.exe
TARG_TEST_UNIT_GSCS_DLL_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.cstring_getStatusCodeString.$(COMP_ARCH_OS_TAG).dll.exe
TARG_TEST_UNIT_AB_DLL_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.auto_buffer.$(COMP_ARCH_OS_TAG).dll.exe
TARG_TEST_UNIT_1_MT_D			=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.1.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_UNIT_2_MT_D			=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.2.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_UNIT_GSCS_MT_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.cstring_getStatusCodeString.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_UNIT_AB_MT_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.auto_buffer.$(COMP_ARCH_OS_TAG).mt.debug.exe
TARG_TEST_UNIT_1_MT_R			=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.1.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_UNIT_2_MT_R			=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.2.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_UNIT_GSCS_MT_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.cstring_getStatusCodeString.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_UNIT_AB_MT_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.auto_buffer.$(COMP_ARCH_OS_TAG).mt.exe
TARG_TEST_UNIT_1_ST_D			=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.1.$(COMP_ARCH_OS_TAG).debug.exe
TARG_TEST_UNIT_2_ST_D			=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.2.$(COMP_ARCH_OS_TAG).debug.exe
TARG_TEST_UNIT_GSCS_ST_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.cstring_getStatusCodeString.$(COMP_ARCH_OS_TAG).debug.exe
TARG_TEST_UNIT_AB_ST_D		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.auto_buffer.$(COMP_ARCH_OS_TAG).debug.exe
TARG_TEST_UNIT_1_ST_R			=	$(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.1.$(COMP_ARCH_OS_TAG).exe
TARG_TEST_UNIT_2_ST_R			=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.2.$(COMP_ARCH_OS_TAG).exe
TARG_TEST_UNIT_GSCS_ST_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.cstring_getStatusCodeString.$(COMP_ARCH_OS_TAG).exe
TARG_TEST_UNIT_AB_ST_R		=   $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.cstring.auto_buffer.$(COMP_ARCH_OS_TAG).exe

############################################################
# objects

########################################
# libraries

# core

OBJ_lib_core_DLL_D =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).core.dll.debug.obj
OBJ_lib_vect_DLL_D =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).vect.dll.debug.obj

OBJ_CORE_DLL_D=\
 $(OBJ_lib_core_DLL_D)\
 $(OBJ_lib_vect_DLL_D)\
 \

OBJ_lib_core_DLL_R =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).core.dll.obj
OBJ_lib_vect_DLL_R =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).vect.dll.obj

OBJ_CORE_DLL_R=\
 $(OBJ_lib_core_DLL_R)\
 $(OBJ_lib_vect_DLL_R)\
 \

OBJ_lib_core_MT_D =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).core.mt.debug.obj
OBJ_lib_vect_MT_D =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).vect.mt.debug.obj

OBJ_CORE_MT_D=\
 $(OBJ_lib_core_MT_D)\
 $(OBJ_lib_vect_MT_D)\
 \

OBJ_lib_core_MT_R =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).core.mt.obj
OBJ_lib_vect_MT_R =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).vect.mt.obj

OBJ_CORE_MT_R=\
 $(OBJ_lib_core_MT_R)\
 $(OBJ_lib_vect_MT_R)\
 \

OBJ_lib_core_ST_D =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).core.debug.obj
OBJ_lib_vect_ST_D =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).vect.debug.obj

OBJ_CORE_ST_D=\
 $(OBJ_lib_core_ST_D)\
 $(OBJ_lib_vect_ST_D)\
 \

OBJ_lib_core_ST_R =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).core.obj
OBJ_lib_vect_ST_R =			$(PROJ_OBJ_DIR)\$(PROJ_TAG).vect.obj

OBJ_CORE_ST_R=\
 $(OBJ_lib_core_ST_R)\
 $(OBJ_lib_vect_ST_R)\
 \


# shwild

OBJ_shw_api_DLL_D            = $(PROJ_OBJ_DIR)\shwild.cs.api.dll.debug.obj
OBJ_shw_matches_DLL_D        = $(PROJ_OBJ_DIR)\shwild.cs.matches.dll.debug.obj
OBJ_shw_pattern_DLL_D        = $(PROJ_OBJ_DIR)\shwild.cs.pattern.dll.debug.obj

OBJ_SHWILD_DLL_D=\
 $(OBJ_shw_api_DLL_D)\
 $(OBJ_shw_matches_DLL_D)\
 $(OBJ_shw_pattern_DLL_D)\
 \

OBJ_shw_api_DLL_R            = $(PROJ_OBJ_DIR)\shwild.cs.api.dll.obj
OBJ_shw_matches_DLL_R        = $(PROJ_OBJ_DIR)\shwild.cs.matches.dll.obj
OBJ_shw_pattern_DLL_R        = $(PROJ_OBJ_DIR)\shwild.cs.pattern.dll.obj

OBJ_SHWILD_DLL_R=\
 $(OBJ_shw_api_DLL_R)\
 $(OBJ_shw_matches_DLL_R)\
 $(OBJ_shw_pattern_DLL_R)\
 \

OBJ_shw_api_MT_D            = $(PROJ_OBJ_DIR)\shwild.cs.api.mt.debug.obj
OBJ_shw_matches_MT_D        = $(PROJ_OBJ_DIR)\shwild.cs.matches.mt.debug.obj
OBJ_shw_pattern_MT_D        = $(PROJ_OBJ_DIR)\shwild.cs.pattern.mt.debug.obj

OBJ_SHWILD_MT_D=\
 $(OBJ_shw_api_MT_D)\
 $(OBJ_shw_matches_MT_D)\
 $(OBJ_shw_pattern_MT_D)\
 \

OBJ_shw_api_MT_R            = $(PROJ_OBJ_DIR)\shwild.cs.api.mt.obj
OBJ_shw_matches_MT_R        = $(PROJ_OBJ_DIR)\shwild.cs.matches.mt.obj
OBJ_shw_pattern_MT_R        = $(PROJ_OBJ_DIR)\shwild.cs.pattern.mt.obj

OBJ_SHWILD_MT_R=\
 $(OBJ_shw_api_MT_R)\
 $(OBJ_shw_matches_MT_R)\
 $(OBJ_shw_pattern_MT_R)\
 \

OBJ_shw_api_ST_D            = $(PROJ_OBJ_DIR)\shwild.cs.api.debug.obj
OBJ_shw_matches_ST_D        = $(PROJ_OBJ_DIR)\shwild.cs.matches.debug.obj
OBJ_shw_pattern_ST_D        = $(PROJ_OBJ_DIR)\shwild.cs.pattern.debug.obj

OBJ_SHWILD_ST_D=\
 $(OBJ_shw_api_ST_D)\
 $(OBJ_shw_matches_ST_D)\
 $(OBJ_shw_pattern_ST_D)\
 \

OBJ_shw_api_ST_R            = $(PROJ_OBJ_DIR)\shwild.cs.api.obj
OBJ_shw_matches_ST_R        = $(PROJ_OBJ_DIR)\shwild.cs.matches.obj
OBJ_shw_pattern_ST_R        = $(PROJ_OBJ_DIR)\shwild.cs.pattern.obj

OBJ_SHWILD_ST_R=\
 $(OBJ_shw_api_ST_R)\
 $(OBJ_shw_matches_ST_R)\
 $(OBJ_shw_pattern_ST_R)\
 \



# xTests

OBJ_xts_core_DLL_D          =	$(PROJ_OBJ_DIR)\xtests.cs.core.dll.debug.obj

OBJ_XTESTS_DLL_D=\
 $(OBJ_xts_core_DLL_D)\
 \

OBJ_xts_core_DLL_R          =	$(PROJ_OBJ_DIR)\xtests.cs.core.dll.obj

OBJ_XTESTS_DLL_R=\
 $(OBJ_xts_core_DLL_R)\
 \

OBJ_xts_core_MT_D          =	$(PROJ_OBJ_DIR)\xtests.cs.core.mt.debug.obj

OBJ_XTESTS_MT_D=\
 $(OBJ_xts_core_MT_D)\
 \

OBJ_xts_core_MT_R          =	$(PROJ_OBJ_DIR)\xtests.cs.core.mt.obj

OBJ_XTESTS_MT_R=\
 $(OBJ_xts_core_MT_R)\
 \

OBJ_xts_core_ST_D          =	$(PROJ_OBJ_DIR)\xtests.cs.core.debug.obj

OBJ_XTESTS_ST_D=\
 $(OBJ_xts_core_ST_D)\
 \

OBJ_xts_core_ST_R          =	$(PROJ_OBJ_DIR)\xtests.cs.core.obj

OBJ_XTESTS_ST_R=\
 $(OBJ_xts_core_ST_R)\
 \



########################################
# examples


########################################
# tests

##############################
# component tests

OBJ_TEST_COMP_readln_DLL_D =   $(PROJ_OBJ_DIR)\test.component.cstring_readline.dll.debug.obj
OBJ_TEST_COMP_readln_DLL_R =   $(PROJ_OBJ_DIR)\test.component.cstring_readline.dll.obj
OBJ_TEST_COMP_readln_MT_D =   $(PROJ_OBJ_DIR)\test.component.cstring_readline.mt.debug.obj
OBJ_TEST_COMP_readln_MT_R =   $(PROJ_OBJ_DIR)\test.component.cstring_readline.mt.obj
OBJ_TEST_COMP_readln_ST_D =   $(PROJ_OBJ_DIR)\test.component.cstring_readline.debug.obj
OBJ_TEST_COMP_readln_ST_R =   $(PROJ_OBJ_DIR)\test.component.cstring_readline.obj

##############################
# scratch tests

OBJ_TEST_SCRT_api_DLL_D	=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dll.debug.obj
OBJ_TEST_SCRT_cr_DLL_D		=   $(PROJ_OBJ_DIR)\test.scratch.cstring_create.dll.debug.obj
OBJ_TEST_SCRT_dl_DLL_D		=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dynload.dll.debug.obj
OBJ_TEST_SCRT_aubuf_DLL_D	=   $(PROJ_OBJ_DIR)\test.scratch.auto_buffer.dll.debug.obj
OBJ_TEST_SCRT_api_DLL_R	=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dll.obj
OBJ_TEST_SCRT_cr_DLL_R		=   $(PROJ_OBJ_DIR)\test.scratch.cstring_create.dll.obj
OBJ_TEST_SCRT_dl_DLL_R		=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dynload.dll.obj
OBJ_TEST_SCRT_aubuf_DLL_R	=   $(PROJ_OBJ_DIR)\test.scratch.auto_buffer.dll.obj
OBJ_TEST_SCRT_api_MT_D	=   $(PROJ_OBJ_DIR)\test.scratch.cstring.mt.debug.obj
OBJ_TEST_SCRT_cr_MT_D		=   $(PROJ_OBJ_DIR)\test.scratch.cstring_create.mt.debug.obj
OBJ_TEST_SCRT_dl_MT_D		=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dynload.mt.debug.obj
OBJ_TEST_SCRT_aubuf_MT_D	=   $(PROJ_OBJ_DIR)\test.scratch.auto_buffer.mt.debug.obj
OBJ_TEST_SCRT_api_MT_R	=   $(PROJ_OBJ_DIR)\test.scratch.cstring.mt.obj
OBJ_TEST_SCRT_cr_MT_R		=   $(PROJ_OBJ_DIR)\test.scratch.cstring_create.mt.obj
OBJ_TEST_SCRT_dl_MT_R		=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dynload.mt.obj
OBJ_TEST_SCRT_aubuf_MT_R	=   $(PROJ_OBJ_DIR)\test.scratch.auto_buffer.mt.obj
OBJ_TEST_SCRT_api_ST_D	=   $(PROJ_OBJ_DIR)\test.scratch.cstring.debug.obj
OBJ_TEST_SCRT_cr_ST_D		=   $(PROJ_OBJ_DIR)\test.scratch.cstring_create.debug.obj
OBJ_TEST_SCRT_dl_ST_D		=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dynload.debug.obj
OBJ_TEST_SCRT_aubuf_ST_D	=   $(PROJ_OBJ_DIR)\test.scratch.auto_buffer.debug.obj
OBJ_TEST_SCRT_api_ST_R	=   $(PROJ_OBJ_DIR)\test.scratch.cstring.obj
OBJ_TEST_SCRT_cr_ST_R		=   $(PROJ_OBJ_DIR)\test.scratch.cstring_create.obj
OBJ_TEST_SCRT_dl_ST_R		=   $(PROJ_OBJ_DIR)\test.scratch.cstring.dynload.obj
OBJ_TEST_SCRT_aubuf_ST_R	=   $(PROJ_OBJ_DIR)\test.scratch.auto_buffer.obj

##############################
# unit tests

OBJ_TEST_UNIT_1_DLL_D		=   $(PROJ_OBJ_DIR)\test.unit.cstring.1.dll.debug.obj
OBJ_TEST_UNIT_2_DLL_D		=   $(PROJ_OBJ_DIR)\test.unit.cstring.2.dll.debug.obj
OBJ_TEST_UNIT_GSCS_DLL_D	=   $(PROJ_OBJ_DIR)\test.unit.cstring.cstring_getStatusCodeString.dll.debug.obj
OBJ_TEST_UNIT_AB_DLL_D		=   $(PROJ_OBJ_DIR)\test.unit.cstring.auto_buffer.dll.debug.obj
OBJ_TEST_UNIT_1_DLL_R		=   $(PROJ_OBJ_DIR)\test.unit.cstring.1.dll.obj
OBJ_TEST_UNIT_2_DLL_R		=   $(PROJ_OBJ_DIR)\test.unit.cstring.2.dll.obj
OBJ_TEST_UNIT_GSCS_DLL_R	=   $(PROJ_OBJ_DIR)\test.unit.cstring.cstring_getStatusCodeString.dll.obj
OBJ_TEST_UNIT_AB_DLL_R		=   $(PROJ_OBJ_DIR)\test.unit.cstring.auto_buffer.dll.obj
OBJ_TEST_UNIT_1_MT_D		=   $(PROJ_OBJ_DIR)\test.unit.cstring.1.mt.debug.obj
OBJ_TEST_UNIT_2_MT_D		=   $(PROJ_OBJ_DIR)\test.unit.cstring.2.mt.debug.obj
OBJ_TEST_UNIT_GSCS_MT_D	=   $(PROJ_OBJ_DIR)\test.unit.cstring.cstring_getStatusCodeString.mt.debug.obj
OBJ_TEST_UNIT_AB_MT_D		=   $(PROJ_OBJ_DIR)\test.unit.cstring.auto_buffer.mt.debug.obj
OBJ_TEST_UNIT_1_MT_R		=   $(PROJ_OBJ_DIR)\test.unit.cstring.1.mt.obj
OBJ_TEST_UNIT_2_MT_R		=   $(PROJ_OBJ_DIR)\test.unit.cstring.2.mt.obj
OBJ_TEST_UNIT_GSCS_MT_R	=   $(PROJ_OBJ_DIR)\test.unit.cstring.cstring_getStatusCodeString.mt.obj
OBJ_TEST_UNIT_AB_MT_R		=   $(PROJ_OBJ_DIR)\test.unit.cstring.auto_buffer.mt.obj
OBJ_TEST_UNIT_1_ST_D		=   $(PROJ_OBJ_DIR)\test.unit.cstring.1.debug.obj
OBJ_TEST_UNIT_2_ST_D		=   $(PROJ_OBJ_DIR)\test.unit.cstring.2.debug.obj
OBJ_TEST_UNIT_GSCS_ST_D	=   $(PROJ_OBJ_DIR)\test.unit.cstring.cstring_getStatusCodeString.debug.obj
OBJ_TEST_UNIT_AB_ST_D		=   $(PROJ_OBJ_DIR)\test.unit.cstring.auto_buffer.debug.obj
OBJ_TEST_UNIT_1_ST_R		=   $(PROJ_OBJ_DIR)\test.unit.cstring.1.obj
OBJ_TEST_UNIT_2_ST_R		=   $(PROJ_OBJ_DIR)\test.unit.cstring.2.obj
OBJ_TEST_UNIT_GSCS_ST_R	=   $(PROJ_OBJ_DIR)\test.unit.cstring.cstring_getStatusCodeString.obj
OBJ_TEST_UNIT_AB_ST_R		=   $(PROJ_OBJ_DIR)\test.unit.cstring.auto_buffer.obj

# target groups

########################################
# objects

# core
OBJ_CORE=\
# $(OBJ_UTIL_DLL_D)\
 $(OBJ_CORE_DLL_D)\
# $(OBJ_UTIL_DLL_R)\
 $(OBJ_CORE_DLL_R)\
# $(OBJ_UTIL_MT_D)\
 $(OBJ_CORE_MT_D)\
# $(OBJ_UTIL_MT_R)\
 $(OBJ_CORE_MT_R)\
# $(OBJ_UTIL_ST_D)\
 $(OBJ_CORE_ST_D)\
# $(OBJ_UTIL_ST_R)\
 $(OBJ_CORE_ST_R)\
 \

# shwild
OBJ_SHWILD=\
 $(OBJ_SHWILD_DLL_D)\
 $(OBJ_SHWILD_DLL_R)\
 $(OBJ_SHWILD_MT_D)\
 $(OBJ_SHWILD_MT_R)\
 $(OBJ_SHWILD_ST_D)\
 $(OBJ_SHWILD_ST_R)\
 \

# examples
OBJ_EXAMPLE=\
 \

# Component Tests
OBJ_TEST_COMPONENT=\
 $(OBJ_TEST_COMP_readln_DLL_D)\
 $(OBJ_TEST_COMP_readln_DLL_R)\
 $(OBJ_TEST_COMP_readln_MT_D)\
 $(OBJ_TEST_COMP_readln_MT_R)\
 $(OBJ_TEST_COMP_readln_ST_D)\
 $(OBJ_TEST_COMP_readln_ST_R)\
 \

# Scratch Tests
OBJ_TEST_SCRATCH=\
 $(OBJ_TEST_SCRT_api_DLL_D)\
 $(OBJ_TEST_SCRT_cr_DLL_D)\
 $(OBJ_TEST_SCRT_dl_DLL_D)\
 $(OBJ_TEST_SCRT_aubuf_DLL_D)\
 $(OBJ_TEST_SCRT_api_DLL_R)\
 $(OBJ_TEST_SCRT_cr_DLL_R)\
 $(OBJ_TEST_SCRT_dl_DLL_R)\
 $(OBJ_TEST_SCRT_aubuf_DLL_R)\
 $(OBJ_TEST_SCRT_api_MT_D)\
 $(OBJ_TEST_SCRT_cr_MT_D)\
 $(OBJ_TEST_SCRT_dl_MT_D)\
 $(OBJ_TEST_SCRT_aubuf_MT_D)\
 $(OBJ_TEST_SCRT_api_MT_R)\
 $(OBJ_TEST_SCRT_cr_MT_R)\
 $(OBJ_TEST_SCRT_dl_MT_R)\
 $(OBJ_TEST_SCRT_aubuf_MT_R)\
 $(OBJ_TEST_SCRT_api_ST_D)\
 $(OBJ_TEST_SCRT_cr_ST_D)\
 $(OBJ_TEST_SCRT_dl_ST_D)\
 $(OBJ_TEST_SCRT_aubuf_ST_D)\
 $(OBJ_TEST_SCRT_api_ST_R)\
 $(OBJ_TEST_SCRT_cr_ST_R)\
 $(OBJ_TEST_SCRT_dl_ST_R)\
 $(OBJ_TEST_SCRT_aubuf_ST_R)\
 \

# Unit Tests
OBJ_TEST_UNIT=\
 $(OBJ_TEST_UNIT_1_DLL_D)\
 $(OBJ_TEST_UNIT_2_DLL_D)\
 $(OBJ_TEST_UNIT_GSCS_DLL_D)\
 $(OBJ_TEST_UNIT_AB_DLL_D)\
 $(OBJ_TEST_UNIT_1_DLL_R)\
 $(OBJ_TEST_UNIT_2_DLL_R)\
 $(OBJ_TEST_UNIT_GSCS_DLL_R)\
 $(OBJ_TEST_UNIT_AB_DLL_R)\
 $(OBJ_TEST_UNIT_1_MT_D)\
 $(OBJ_TEST_UNIT_2_MT_D)\
 $(OBJ_TEST_UNIT_GSCS_MT_D)\
 $(OBJ_TEST_UNIT_AB_MT_D)\
 $(OBJ_TEST_UNIT_1_MT_R)\
 $(OBJ_TEST_UNIT_2_MT_R)\
 $(OBJ_TEST_UNIT_GSCS_MT_R)\
 $(OBJ_TEST_UNIT_AB_MT_R)\
 $(OBJ_TEST_UNIT_1_ST_D)\
 $(OBJ_TEST_UNIT_2_ST_D)\
 $(OBJ_TEST_UNIT_GSCS_ST_D)\
 $(OBJ_TEST_UNIT_AB_ST_D)\
 $(OBJ_TEST_UNIT_1_ST_R)\
 $(OBJ_TEST_UNIT_2_ST_R)\
 $(OBJ_TEST_UNIT_GSCS_ST_R)\
 $(OBJ_TEST_UNIT_AB_ST_R)\
 \

########################################
# libraries

TARGETS_LIB_CORE=\
 $(LIB_CORE_DLL_D)\
 $(LIB_CORE_DLL_R)\
 $(LIB_CORE_MT_D)\
 $(LIB_CORE_MT_R)\
 $(LIB_CORE_ST_D)\
 $(LIB_CORE_ST_R)\
 \

TARGETS_LIB_ALL=\
 $(TARGETS_LIB_CORE)\
 \

TARGETS_LIB_SHWILD=\
 $(LIB_SHWILD_DLL_D)\
 $(LIB_SHWILD_DLL_R)\
 $(LIB_SHWILD_MT_D)\
 $(LIB_SHWILD_MT_R)\
 $(LIB_SHWILD_ST_D)\
 $(LIB_SHWILD_ST_R)\
 \

TARGETS_LIB_XTESTS = \
 $(LIB_XTESTS_DLL_D)\
 $(LIB_XTESTS_DLL_R)\
 $(LIB_XTESTS_MT_D)\
 $(LIB_XTESTS_MT_R)\
 $(LIB_XTESTS_ST_D)\
 $(LIB_XTESTS_ST_R)\
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
 $(TARG_TEST_COMP_readln_DLL_D)\
 $(TARG_TEST_COMP_readln_DLL_R)\
 $(TARG_TEST_COMP_readln_MT_D)\
 $(TARG_TEST_COMP_readln_MT_R)\
 $(TARG_TEST_COMP_readln_ST_D)\
 $(TARG_TEST_COMP_readln_ST_R)\
 \

TARGETS_TEST_SCRATCH=\
 $(TARG_TEST_SCRT_api_DLL_D)\
 $(TARG_TEST_SCRT_cr_DLL_D)\
 $(TARG_TEST_SCRT_dl_DLL_D)\
 $(TARG_TEST_SCRT_aubuf_DLL_D)\
 $(TARG_TEST_SCRT_api_DLL_R)\
 $(TARG_TEST_SCRT_cr_DLL_R)\
 $(TARG_TEST_SCRT_dl_DLL_R)\
 $(TARG_TEST_SCRT_aubuf_DLL_R)\
 $(TARG_TEST_SCRT_api_MT_D)\
 $(TARG_TEST_SCRT_cr_MT_D)\
 $(TARG_TEST_SCRT_dl_MT_D)\
 $(TARG_TEST_SCRT_aubuf_MT_D)\
 $(TARG_TEST_SCRT_api_MT_R)\
 $(TARG_TEST_SCRT_cr_MT_R)\
 $(TARG_TEST_SCRT_dl_MT_R)\
 $(TARG_TEST_SCRT_aubuf_MT_R)\
 $(TARG_TEST_SCRT_api_ST_D)\
 $(TARG_TEST_SCRT_cr_ST_D)\
 $(TARG_TEST_SCRT_dl_ST_D)\
 $(TARG_TEST_SCRT_aubuf_ST_D)\
 $(TARG_TEST_SCRT_api_ST_R)\
 $(TARG_TEST_SCRT_cr_ST_R)\
 $(TARG_TEST_SCRT_dl_ST_R)\
 $(TARG_TEST_SCRT_aubuf_ST_R)\
 \

TARGETS_TEST_UNIT=\
 $(TARG_TEST_UNIT_1_DLL_D)\
 $(TARG_TEST_UNIT_2_DLL_D)\
 $(TARG_TEST_UNIT_GSCS_DLL_D)\
 $(TARG_TEST_UNIT_AB_DLL_D)\
 $(TARG_TEST_UNIT_1_DLL_R)\
 $(TARG_TEST_UNIT_2_DLL_R)\
 $(TARG_TEST_UNIT_GSCS_DLL_R)\
 $(TARG_TEST_UNIT_AB_DLL_R)\
 $(TARG_TEST_UNIT_1_MT_D)\
 $(TARG_TEST_UNIT_2_MT_D)\
 $(TARG_TEST_UNIT_GSCS_MT_D)\
 $(TARG_TEST_UNIT_AB_MT_D)\
 $(TARG_TEST_UNIT_1_MT_R)\
 $(TARG_TEST_UNIT_2_MT_R)\
 $(TARG_TEST_UNIT_GSCS_MT_R)\
 $(TARG_TEST_UNIT_AB_MT_R)\
 $(TARG_TEST_UNIT_1_ST_D)\
 $(TARG_TEST_UNIT_2_ST_D)\
 $(TARG_TEST_UNIT_GSCS_ST_D)\
 $(TARG_TEST_UNIT_AB_ST_D)\
 $(TARG_TEST_UNIT_1_ST_R)\
 $(TARG_TEST_UNIT_2_ST_R)\
 $(TARG_TEST_UNIT_GSCS_ST_R)\
 $(TARG_TEST_UNIT_AB_ST_R)\
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
	$(TARG_TEST_COMP_readln_DLL_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_COMP_readln_DLL_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_COMP_readln_MT_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_COMP_readln_MT_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_COMP_readln_ST_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_COMP_readln_ST_R) --verbosity=$(TEST_VERBOSITY)

test.scratch_:
	@echo Running Test:Scratch programs ...
	$(TARG_TEST_SCRT_api_DLL_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_cr_DLL_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_dl_DLL_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_aubuf_DLL_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_api_DLL_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_cr_DLL_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_dl_DLL_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_aubuf_DLL_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_api_MT_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_cr_MT_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_dl_MT_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_aubuf_MT_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_api_MT_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_cr_MT_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_dl_MT_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_aubuf_MT_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_api_ST_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_cr_ST_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_dl_ST_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_aubuf_ST_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_api_ST_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_cr_ST_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_dl_ST_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_SCRT_aubuf_ST_R) --verbosity=$(TEST_VERBOSITY)

test.unit_:
	@echo Running Test:Unit programs ...
	$(TARG_TEST_UNIT_1_DLL_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_2_DLL_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_GSCS_DLL_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_AB_DLL_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_1_DLL_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_2_DLL_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_GSCS_DLL_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_AB_DLL_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_1_MT_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_2_MT_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_GSCS_MT_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_AB_MT_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_1_MT_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_2_MT_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_GSCS_MT_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_AB_MT_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_1_ST_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_2_ST_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_GSCS_ST_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_AB_ST_D) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_1_ST_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_2_ST_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_GSCS_ST_R) --verbosity=$(TEST_VERBOSITY)
	$(TARG_TEST_UNIT_AB_ST_R) --verbosity=$(TEST_VERBOSITY)

test.component:			$(PROJ_MAKEFILE_NAME)	build.test.component test.component_

test.scratch:			$(PROJ_MAKEFILE_NAME)	build.test.scratch test.scratch_

test.unit:				$(PROJ_MAKEFILE_NAME)	build.test.unit test.unit_

test:											test.unit test.component

test.all:										test test.scratch
test-all:				test.all


# clean targets

clean.libs.core:
	@echo Cleaning Core libraries ...
	@-if exist cstring.core.*.obj $(RM) cstring.core.*.obj
	@-if exist $(LIB_CORE_DLL_D) $(RM) $(LIB_CORE_DLL_D)
	@-if exist $(LIB_CORE_DLL_R) $(RM) $(LIB_CORE_DLL_R)
	@-if exist $(LIB_CORE_MT_D) $(RM) $(LIB_CORE_MT_D)
	@-if exist $(LIB_CORE_MT_R) $(RM) $(LIB_CORE_MT_R)
	@-if exist $(LIB_CORE_ST_D) $(RM) $(LIB_CORE_ST_D)
	@-if exist $(LIB_CORE_ST_R) $(RM) $(LIB_CORE_ST_R)

clean.libs.shwild:
	@echo Cleaning shwild libraries ...
	@-if exist shwild.*.obj $(RM) shwild.*.obj
	@-if exist $(LIB_SHWILD_DLL_D) $(RM) $(LIB_SHWILD_DLL_D)
	@-if exist $(LIB_SHWILD_DLL_R) $(RM) $(LIB_SHWILD_DLL_R)
	@-if exist $(LIB_SHWILD_MT_D) $(RM) $(LIB_SHWILD_MT_D)
	@-if exist $(LIB_SHWILD_MT_R) $(RM) $(LIB_SHWILD_MT_R)
	@-if exist $(LIB_SHWILD_ST_D) $(RM) $(LIB_SHWILD_ST_D)
	@-if exist $(LIB_SHWILD_ST_R) $(RM) $(LIB_SHWILD_ST_R)

clean.libs.xtests:
	@echo Cleaning xTests libraries ...
	@-if exist xtests.*.obj $(RM) xtests.*.obj
	@-if exist $(LIB_XTESTS_DLL_D) $(RM) $(LIB_XTESTS_DLL_D)
	@-if exist $(LIB_XTESTS_DLL_R) $(RM) $(LIB_XTESTS_DLL_R)
	@-if exist $(LIB_XTESTS_MT_D) $(RM) $(LIB_XTESTS_MT_D)
	@-if exist $(LIB_XTESTS_MT_R) $(RM) $(LIB_XTESTS_MT_R)
	@-if exist $(LIB_XTESTS_ST_D) $(RM) $(LIB_XTESTS_ST_D)
	@-if exist $(LIB_XTESTS_ST_R) $(RM) $(LIB_XTESTS_ST_R)

clean.test.component:
	@echo cleaning Test:Component libraries ...
	@-if exist test.component.*.obj $(RM) test.component.*.obj
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).dll.debug.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).dll.debug.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).dll.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).dll.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).mt.debug.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).mt.debug.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).mt.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).mt.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).debug.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).debug.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.component.*.$(COMP_ARCH_OS_TAG).exe

clean.test.scratch:
	@echo cleaning Test:Scratch libraries ...
	@-if exist test.scratch.*.obj $(RM) test.scratch.*.obj
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).dll.debug.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).dll.debug.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).dll.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).dll.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).mt.debug.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).mt.debug.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).mt.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).mt.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).debug.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).debug.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.scratch.*.$(COMP_ARCH_OS_TAG).exe

clean.test.unit:
	@echo cleaning Test:Unit libraries ...
	@-if exist test.unit.*.obj $(RM) test.unit.*.obj
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).dll.debug.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).dll.debug.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).dll.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).dll.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).mt.debug.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).mt.debug.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).mt.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).mt.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).debug.exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).debug.exe
	@-if exist $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).exe $(RM) $(PROJ_BIN_DIR)\$(PROJ_TAG_VER).test.unit.*.$(COMP_ARCH_OS_TAG).exe

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

$(LIB_CORE_DLL_D): $(OBJ_CORE_DLL_D) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_CORE_DLL_D)

$(OBJ_lib_core_DLL_D):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.core.c
	$(CC) $(CC_ARGS_DLL_D) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.core.c
$(OBJ_lib_vect_DLL_D):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.vector.c
	$(CC) $(CC_ARGS_DLL_D) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.vector.c

$(LIB_CORE_DLL_R): $(OBJ_CORE_DLL_R) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_CORE_DLL_R)

$(OBJ_lib_core_DLL_R):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.core.c
	$(CC) $(CC_ARGS_DLL_R) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.core.c
$(OBJ_lib_vect_DLL_R):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.vector.c
	$(CC) $(CC_ARGS_DLL_R) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.vector.c

$(LIB_CORE_MT_D): $(OBJ_CORE_MT_D) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_CORE_MT_D)

$(OBJ_lib_core_MT_D):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.core.c
	$(CC) $(CC_ARGS_MT_D) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.core.c
$(OBJ_lib_vect_MT_D):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.vector.c
	$(CC) $(CC_ARGS_MT_D) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.vector.c

$(LIB_CORE_MT_R): $(OBJ_CORE_MT_R) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_CORE_MT_R)

$(OBJ_lib_core_MT_R):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.core.c
	$(CC) $(CC_ARGS_MT_R) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.core.c
$(OBJ_lib_vect_MT_R):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.vector.c
	$(CC) $(CC_ARGS_MT_R) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.vector.c

$(LIB_CORE_ST_D): $(OBJ_CORE_ST_D) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_CORE_ST_D)

$(OBJ_lib_core_ST_D):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.core.c
	$(CC) $(CC_ARGS_ST_D) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.core.c
$(OBJ_lib_vect_ST_D):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.vector.c
	$(CC) $(CC_ARGS_ST_D) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.vector.c

$(LIB_CORE_ST_R): $(OBJ_CORE_ST_R) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_CORE_ST_R)

$(OBJ_lib_core_ST_R):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.core.c
	$(CC) $(CC_ARGS_ST_R) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.core.c
$(OBJ_lib_vect_ST_R):	$(PROJ_MAKEFILE_NAME) $(PROJ_SRC_DIR)\cstring.vector.c
	$(CC) $(CC_ARGS_ST_R) $(CC_INCLUDES) -Fo$@ $(PROJ_SRC_DIR)\cstring.vector.c

########################################
# shwild library - 'shwild.X.cs.core.a'

$(LIB_SHWILD_DLL_D): $(OBJ_SHWILD_DLL_D) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_SHWILD_DLL_D)

$(OBJ_shw_api_DLL_D): $(SHWILD_SRC_DIR)\api.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) $(CPPC_SHWILD_INCLUDES_DLL_D) -Fo$@ $(SHWILD_SRC_DIR)\api.cpp
$(OBJ_shw_matches_DLL_D): $(SHWILD_SRC_DIR)\matches.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) $(CPPC_SHWILD_INCLUDES_DLL_D) -Fo$@ $(SHWILD_SRC_DIR)\matches.cpp
$(OBJ_shw_pattern_DLL_D): $(SHWILD_SRC_DIR)\pattern.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) $(CPPC_SHWILD_INCLUDES_DLL_D) -Fo$@ $(SHWILD_SRC_DIR)\pattern.cpp

$(LIB_SHWILD_DLL_R): $(OBJ_SHWILD_DLL_R) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_SHWILD_DLL_R)

$(OBJ_shw_api_DLL_R): $(SHWILD_SRC_DIR)\api.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) $(CPPC_SHWILD_INCLUDES_DLL_R) -Fo$@ $(SHWILD_SRC_DIR)\api.cpp
$(OBJ_shw_matches_DLL_R): $(SHWILD_SRC_DIR)\matches.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) $(CPPC_SHWILD_INCLUDES_DLL_R) -Fo$@ $(SHWILD_SRC_DIR)\matches.cpp
$(OBJ_shw_pattern_DLL_R): $(SHWILD_SRC_DIR)\pattern.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) $(CPPC_SHWILD_INCLUDES_DLL_R) -Fo$@ $(SHWILD_SRC_DIR)\pattern.cpp

$(LIB_SHWILD_MT_D): $(OBJ_SHWILD_MT_D) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_SHWILD_MT_D)

$(OBJ_shw_api_MT_D): $(SHWILD_SRC_DIR)\api.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) $(CPPC_SHWILD_INCLUDES_MT_D) -Fo$@ $(SHWILD_SRC_DIR)\api.cpp
$(OBJ_shw_matches_MT_D): $(SHWILD_SRC_DIR)\matches.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) $(CPPC_SHWILD_INCLUDES_MT_D) -Fo$@ $(SHWILD_SRC_DIR)\matches.cpp
$(OBJ_shw_pattern_MT_D): $(SHWILD_SRC_DIR)\pattern.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) $(CPPC_SHWILD_INCLUDES_MT_D) -Fo$@ $(SHWILD_SRC_DIR)\pattern.cpp

$(LIB_SHWILD_MT_R): $(OBJ_SHWILD_MT_R) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_SHWILD_MT_R)

$(OBJ_shw_api_MT_R): $(SHWILD_SRC_DIR)\api.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) $(CPPC_SHWILD_INCLUDES_MT_R) -Fo$@ $(SHWILD_SRC_DIR)\api.cpp
$(OBJ_shw_matches_MT_R): $(SHWILD_SRC_DIR)\matches.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) $(CPPC_SHWILD_INCLUDES_MT_R) -Fo$@ $(SHWILD_SRC_DIR)\matches.cpp
$(OBJ_shw_pattern_MT_R): $(SHWILD_SRC_DIR)\pattern.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) $(CPPC_SHWILD_INCLUDES_MT_R) -Fo$@ $(SHWILD_SRC_DIR)\pattern.cpp

$(LIB_SHWILD_ST_D): $(OBJ_SHWILD_ST_D) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_SHWILD_ST_D)

$(OBJ_shw_api_ST_D): $(SHWILD_SRC_DIR)\api.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) $(CPPC_SHWILD_INCLUDES_ST_D) -Fo$@ $(SHWILD_SRC_DIR)\api.cpp
$(OBJ_shw_matches_ST_D): $(SHWILD_SRC_DIR)\matches.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) $(CPPC_SHWILD_INCLUDES_ST_D) -Fo$@ $(SHWILD_SRC_DIR)\matches.cpp
$(OBJ_shw_pattern_ST_D): $(SHWILD_SRC_DIR)\pattern.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) $(CPPC_SHWILD_INCLUDES_ST_D) -Fo$@ $(SHWILD_SRC_DIR)\pattern.cpp

$(LIB_SHWILD_ST_R): $(OBJ_SHWILD_ST_R) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_SHWILD_ST_R)

$(OBJ_shw_api_ST_R): $(SHWILD_SRC_DIR)\api.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) $(CPPC_SHWILD_INCLUDES_ST_R) -Fo$@ $(SHWILD_SRC_DIR)\api.cpp
$(OBJ_shw_matches_ST_R): $(SHWILD_SRC_DIR)\matches.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) $(CPPC_SHWILD_INCLUDES_ST_R) -Fo$@ $(SHWILD_SRC_DIR)\matches.cpp
$(OBJ_shw_pattern_ST_R): $(SHWILD_SRC_DIR)\pattern.cpp $(SHWILD_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) $(CPPC_SHWILD_INCLUDES_ST_R) -Fo$@ $(SHWILD_SRC_DIR)\pattern.cpp

########################################
# xTests library - 'xtests.X.cs.core.a'

$(LIB_XTESTS_DLL_D): $(OBJ_XTESTS_DLL_D) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_XTESTS_DLL_D)

$(OBJ_xts_core_DLL_D): $(XTESTS_SRC_DIR)\xtests.core.cpp $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) $(CPPC_XTESTS_INCLUDES_DLL_D) -Fo$@ $(XTESTS_SRC_DIR)\xtests.core.cpp

$(LIB_XTESTS_DLL_R): $(OBJ_XTESTS_DLL_R) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_XTESTS_DLL_R)

$(OBJ_xts_core_DLL_R): $(XTESTS_SRC_DIR)\xtests.core.cpp $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) $(CPPC_XTESTS_INCLUDES_DLL_R) -Fo$@ $(XTESTS_SRC_DIR)\xtests.core.cpp

$(LIB_XTESTS_MT_D): $(OBJ_XTESTS_MT_D) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_XTESTS_MT_D)

$(OBJ_xts_core_MT_D): $(XTESTS_SRC_DIR)\xtests.core.cpp $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) $(CPPC_XTESTS_INCLUDES_MT_D) -Fo$@ $(XTESTS_SRC_DIR)\xtests.core.cpp

$(LIB_XTESTS_MT_R): $(OBJ_XTESTS_MT_R) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_XTESTS_MT_R)

$(OBJ_xts_core_MT_R): $(XTESTS_SRC_DIR)\xtests.core.cpp $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) $(CPPC_XTESTS_INCLUDES_MT_R) -Fo$@ $(XTESTS_SRC_DIR)\xtests.core.cpp

$(LIB_XTESTS_ST_D): $(OBJ_XTESTS_ST_D) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_XTESTS_ST_D)

$(OBJ_xts_core_ST_D): $(XTESTS_SRC_DIR)\xtests.core.cpp $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) $(CPPC_XTESTS_INCLUDES_ST_D) -Fo$@ $(XTESTS_SRC_DIR)\xtests.core.cpp

$(LIB_XTESTS_ST_R): $(OBJ_XTESTS_ST_R) $(PROJ_MAKEFILE_NAME)
	@-if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) -out:$@ $(OBJ_XTESTS_ST_R)

$(OBJ_xts_core_ST_R): $(XTESTS_SRC_DIR)\xtests.core.cpp $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) $(CPPC_XTESTS_INCLUDES_ST_R) -Fo$@ $(XTESTS_SRC_DIR)\xtests.core.cpp

##################################################
# examples

##################################################
# tests

##############################
# component tests

$(TARG_TEST_COMP_readln_DLL_D):    \
		$(OBJ_TEST_COMP_readln_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_D) -out:$@ \
		$(OBJ_TEST_COMP_readln_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(TARGET_LIB_DLL_D)

$(OBJ_TEST_COMP_readln_DLL_D): $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) -Fo$@ $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp

$(TARG_TEST_COMP_readln_DLL_R):    \
		$(OBJ_TEST_COMP_readln_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_R) -out:$@ \
		$(OBJ_TEST_COMP_readln_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(TARGET_LIB_DLL_R)

$(OBJ_TEST_COMP_readln_DLL_R): $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) -Fo$@ $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp

$(TARG_TEST_COMP_readln_MT_D):    \
		$(OBJ_TEST_COMP_readln_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_D) -out:$@ \
		$(OBJ_TEST_COMP_readln_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(TARGET_LIB_MT_D)

$(OBJ_TEST_COMP_readln_MT_D): $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) -Fo$@ $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp

$(TARG_TEST_COMP_readln_MT_R):    \
		$(OBJ_TEST_COMP_readln_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_R) -out:$@ \
		$(OBJ_TEST_COMP_readln_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(TARGET_LIB_MT_R)

$(OBJ_TEST_COMP_readln_MT_R): $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) -Fo$@ $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp

$(TARG_TEST_COMP_readln_ST_D):    \
		$(OBJ_TEST_COMP_readln_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_D) -out:$@ \
		$(OBJ_TEST_COMP_readln_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(TARGET_LIB_ST_D)

$(OBJ_TEST_COMP_readln_ST_D): $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) -Fo$@ $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp

$(TARG_TEST_COMP_readln_ST_R):    \
		$(OBJ_TEST_COMP_readln_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_R) -out:$@ \
		$(OBJ_TEST_COMP_readln_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(TARGET_LIB_ST_R)

$(OBJ_TEST_COMP_readln_ST_R): $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) -Fo$@ $(PROJ_TEST_COMPONENT_DIR)\test.component.cstring_readline\test.component.cstring_readline.cpp

##############################
# scratch tests

$(TARG_TEST_SCRT_api_DLL_D):    \
		$(OBJ_TEST_SCRT_api_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_D) -out:$@ \
		$(OBJ_TEST_SCRT_api_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(TARGET_LIB_DLL_D)

$(OBJ_TEST_SCRT_api_DLL_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_DLL_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c

$(TARG_TEST_SCRT_api_DLL_R):    \
		$(OBJ_TEST_SCRT_api_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_R) -out:$@ \
		$(OBJ_TEST_SCRT_api_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(TARGET_LIB_DLL_R)

$(OBJ_TEST_SCRT_api_DLL_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_DLL_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c

$(TARG_TEST_SCRT_api_MT_D):    \
		$(OBJ_TEST_SCRT_api_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_D) -out:$@ \
		$(OBJ_TEST_SCRT_api_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(TARGET_LIB_MT_D)

$(OBJ_TEST_SCRT_api_MT_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c

$(TARG_TEST_SCRT_api_MT_R):    \
		$(OBJ_TEST_SCRT_api_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_R) -out:$@ \
		$(OBJ_TEST_SCRT_api_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(TARGET_LIB_MT_R)

$(OBJ_TEST_SCRT_api_MT_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c

$(TARG_TEST_SCRT_api_ST_D):    \
		$(OBJ_TEST_SCRT_api_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_D) -out:$@ \
		$(OBJ_TEST_SCRT_api_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(TARGET_LIB_ST_D)

$(OBJ_TEST_SCRT_api_ST_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_ST_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c

$(TARG_TEST_SCRT_api_ST_R):    \
		$(OBJ_TEST_SCRT_api_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_R) -out:$@ \
		$(OBJ_TEST_SCRT_api_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(TARGET_LIB_ST_R)

$(OBJ_TEST_SCRT_api_ST_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_ST_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring\test.scratch.cstring.c

$(TARG_TEST_SCRT_cr_DLL_D):    \
		$(OBJ_TEST_SCRT_cr_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_D) -out:$@ \
		$(OBJ_TEST_SCRT_cr_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(TARGET_LIB_DLL_D)

$(OBJ_TEST_SCRT_cr_DLL_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_DLL_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c

$(TARG_TEST_SCRT_cr_DLL_R):    \
		$(OBJ_TEST_SCRT_cr_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_R) -out:$@ \
		$(OBJ_TEST_SCRT_cr_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(TARGET_LIB_DLL_R)

$(OBJ_TEST_SCRT_cr_DLL_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_DLL_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c

$(TARG_TEST_SCRT_cr_MT_D):    \
		$(OBJ_TEST_SCRT_cr_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_D) -out:$@ \
		$(OBJ_TEST_SCRT_cr_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(TARGET_LIB_MT_D)

$(OBJ_TEST_SCRT_cr_MT_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c

$(TARG_TEST_SCRT_cr_MT_R):    \
		$(OBJ_TEST_SCRT_cr_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_R) -out:$@ \
		$(OBJ_TEST_SCRT_cr_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(TARGET_LIB_MT_R)

$(OBJ_TEST_SCRT_cr_MT_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c

$(TARG_TEST_SCRT_cr_ST_D):    \
		$(OBJ_TEST_SCRT_cr_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_D) -out:$@ \
		$(OBJ_TEST_SCRT_cr_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(TARGET_LIB_ST_D)

$(OBJ_TEST_SCRT_cr_ST_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_ST_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c

$(TARG_TEST_SCRT_cr_ST_R):    \
		$(OBJ_TEST_SCRT_cr_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_R) -out:$@ \
		$(OBJ_TEST_SCRT_cr_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(TARGET_LIB_ST_R)

$(OBJ_TEST_SCRT_cr_ST_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_ST_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring_create\test.scratch.cstring_create.c

$(TARG_TEST_SCRT_dl_DLL_D):    \
		$(OBJ_TEST_SCRT_dl_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_D) -out:$@ \
		$(OBJ_TEST_SCRT_dl_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(TARGET_LIB_DLL_D)

$(OBJ_TEST_SCRT_dl_DLL_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp

$(TARG_TEST_SCRT_dl_DLL_R):    \
		$(OBJ_TEST_SCRT_dl_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_R) -out:$@ \
		$(OBJ_TEST_SCRT_dl_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(TARGET_LIB_DLL_R)

$(OBJ_TEST_SCRT_dl_DLL_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp

$(TARG_TEST_SCRT_dl_MT_D):    \
		$(OBJ_TEST_SCRT_dl_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_D) -out:$@ \
		$(OBJ_TEST_SCRT_dl_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(TARGET_LIB_MT_D)

$(OBJ_TEST_SCRT_dl_MT_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp

$(TARG_TEST_SCRT_dl_MT_R):    \
		$(OBJ_TEST_SCRT_dl_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_R) -out:$@ \
		$(OBJ_TEST_SCRT_dl_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(TARGET_LIB_MT_R)

$(OBJ_TEST_SCRT_dl_MT_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp

$(TARG_TEST_SCRT_dl_ST_D):    \
		$(OBJ_TEST_SCRT_dl_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_D) -out:$@ \
		$(OBJ_TEST_SCRT_dl_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(TARGET_LIB_ST_D)

$(OBJ_TEST_SCRT_dl_ST_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp

$(TARG_TEST_SCRT_dl_ST_R):    \
		$(OBJ_TEST_SCRT_dl_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_R) -out:$@ \
		$(OBJ_TEST_SCRT_dl_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(TARGET_LIB_ST_R)

$(OBJ_TEST_SCRT_dl_ST_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.cstring.dynload\test.scratch.cstring.dynload.cpp

$(TARG_TEST_SCRT_aubuf_DLL_D):    \
		$(OBJ_TEST_SCRT_aubuf_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_D) -out:$@ \
		$(OBJ_TEST_SCRT_aubuf_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(TARGET_LIB_DLL_D)

$(OBJ_TEST_SCRT_aubuf_DLL_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_DLL_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c

$(TARG_TEST_SCRT_aubuf_DLL_R):    \
		$(OBJ_TEST_SCRT_aubuf_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_R) -out:$@ \
		$(OBJ_TEST_SCRT_aubuf_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(TARGET_LIB_DLL_R)

$(OBJ_TEST_SCRT_aubuf_DLL_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_DLL_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c

$(TARG_TEST_SCRT_aubuf_MT_D):    \
		$(OBJ_TEST_SCRT_aubuf_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_D) -out:$@ \
		$(OBJ_TEST_SCRT_aubuf_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(TARGET_LIB_MT_D)

$(OBJ_TEST_SCRT_aubuf_MT_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c

$(TARG_TEST_SCRT_aubuf_MT_R):    \
		$(OBJ_TEST_SCRT_aubuf_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_R) -out:$@ \
		$(OBJ_TEST_SCRT_aubuf_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(TARGET_LIB_MT_R)

$(OBJ_TEST_SCRT_aubuf_MT_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_MT_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c

$(TARG_TEST_SCRT_aubuf_ST_D):    \
		$(OBJ_TEST_SCRT_aubuf_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_D) -out:$@ \
		$(OBJ_TEST_SCRT_aubuf_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(TARGET_LIB_ST_D)

$(OBJ_TEST_SCRT_aubuf_ST_D): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_ST_D) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c

$(TARG_TEST_SCRT_aubuf_ST_R):    \
		$(OBJ_TEST_SCRT_aubuf_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_R) -out:$@ \
		$(OBJ_TEST_SCRT_aubuf_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(TARGET_LIB_ST_R)

$(OBJ_TEST_SCRT_aubuf_ST_R): $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CC) $(CC_ARGS_ST_R) -Fo$@ $(PROJ_TEST_SCRATCH_DIR)\test.scratch.auto_buffer\test.scratch.auto_buffer.c

##############################
# unit tests

$(TARG_TEST_UNIT_1_DLL_D):    \
		$(OBJ_TEST_UNIT_1_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_D) -out:$@ \
		$(OBJ_TEST_UNIT_1_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(TARGET_LIB_DLL_D)

$(OBJ_TEST_UNIT_1_DLL_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp

$(TARG_TEST_UNIT_1_DLL_R):    \
		$(OBJ_TEST_UNIT_1_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_R) -out:$@ \
		$(OBJ_TEST_UNIT_1_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(TARGET_LIB_DLL_R)

$(OBJ_TEST_UNIT_1_DLL_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp

$(TARG_TEST_UNIT_1_MT_D):    \
		$(OBJ_TEST_UNIT_1_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_D) -out:$@ \
		$(OBJ_TEST_UNIT_1_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(TARGET_LIB_MT_D)

$(OBJ_TEST_UNIT_1_MT_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp

$(TARG_TEST_UNIT_1_MT_R):    \
		$(OBJ_TEST_UNIT_1_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_R) -out:$@ \
		$(OBJ_TEST_UNIT_1_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(TARGET_LIB_MT_R)

$(OBJ_TEST_UNIT_1_MT_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp

$(TARG_TEST_UNIT_1_ST_D):    \
		$(OBJ_TEST_UNIT_1_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_D) -out:$@ \
		$(OBJ_TEST_UNIT_1_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(TARGET_LIB_ST_D)

$(OBJ_TEST_UNIT_1_ST_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp

$(TARG_TEST_UNIT_1_ST_R):    \
		$(OBJ_TEST_UNIT_1_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_R) -out:$@ \
		$(OBJ_TEST_UNIT_1_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(TARGET_LIB_ST_R)

$(OBJ_TEST_UNIT_1_ST_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.1\test.unit.cstring.1.cpp

$(TARG_TEST_UNIT_2_DLL_D):    \
		$(OBJ_TEST_UNIT_2_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_D) -out:$@ \
		$(OBJ_TEST_UNIT_2_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(TARGET_LIB_DLL_D)

$(OBJ_TEST_UNIT_2_DLL_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp

$(TARG_TEST_UNIT_2_DLL_R):    \
		$(OBJ_TEST_UNIT_2_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_R) -out:$@ \
		$(OBJ_TEST_UNIT_2_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(TARGET_LIB_DLL_R)

$(OBJ_TEST_UNIT_2_DLL_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp

$(TARG_TEST_UNIT_2_MT_D):    \
		$(OBJ_TEST_UNIT_2_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_D) -out:$@ \
		$(OBJ_TEST_UNIT_2_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(TARGET_LIB_MT_D)

$(OBJ_TEST_UNIT_2_MT_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp

$(TARG_TEST_UNIT_2_MT_R):    \
		$(OBJ_TEST_UNIT_2_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_R) -out:$@ \
		$(OBJ_TEST_UNIT_2_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(TARGET_LIB_MT_R)

$(OBJ_TEST_UNIT_2_MT_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp

$(TARG_TEST_UNIT_2_ST_D):    \
		$(OBJ_TEST_UNIT_2_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_D) -out:$@ \
		$(OBJ_TEST_UNIT_2_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(TARGET_LIB_ST_D)

$(OBJ_TEST_UNIT_2_ST_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp

$(TARG_TEST_UNIT_2_ST_R):    \
		$(OBJ_TEST_UNIT_2_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_R) -out:$@ \
		$(OBJ_TEST_UNIT_2_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(TARGET_LIB_ST_R)

$(OBJ_TEST_UNIT_2_ST_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.2\test.unit.cstring.2.cpp

$(TARG_TEST_UNIT_GSCS_DLL_D):    \
		$(OBJ_TEST_UNIT_GSCS_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_D) -out:$@ \
		$(OBJ_TEST_UNIT_GSCS_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(TARGET_LIB_DLL_D)

$(OBJ_TEST_UNIT_GSCS_DLL_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp

$(TARG_TEST_UNIT_GSCS_DLL_R):    \
		$(OBJ_TEST_UNIT_GSCS_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_R) -out:$@ \
		$(OBJ_TEST_UNIT_GSCS_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(TARGET_LIB_DLL_R)

$(OBJ_TEST_UNIT_GSCS_DLL_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp

$(TARG_TEST_UNIT_GSCS_MT_D):    \
		$(OBJ_TEST_UNIT_GSCS_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_D) -out:$@ \
		$(OBJ_TEST_UNIT_GSCS_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(TARGET_LIB_MT_D)

$(OBJ_TEST_UNIT_GSCS_MT_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp

$(TARG_TEST_UNIT_GSCS_MT_R):    \
		$(OBJ_TEST_UNIT_GSCS_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_R) -out:$@ \
		$(OBJ_TEST_UNIT_GSCS_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(TARGET_LIB_MT_R)

$(OBJ_TEST_UNIT_GSCS_MT_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp

$(TARG_TEST_UNIT_GSCS_ST_D):    \
		$(OBJ_TEST_UNIT_GSCS_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_D) -out:$@ \
		$(OBJ_TEST_UNIT_GSCS_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(TARGET_LIB_ST_D)

$(OBJ_TEST_UNIT_GSCS_ST_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp

$(TARG_TEST_UNIT_GSCS_ST_R):    \
		$(OBJ_TEST_UNIT_GSCS_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_R) -out:$@ \
		$(OBJ_TEST_UNIT_GSCS_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(TARGET_LIB_ST_R)

$(OBJ_TEST_UNIT_GSCS_ST_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.cstring_getStatusCodeString\test.unit.cstring.cstring_getStatusCodeString.cpp

$(TARG_TEST_UNIT_AB_DLL_D):    \
		$(OBJ_TEST_UNIT_AB_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_D) -out:$@ \
		$(OBJ_TEST_UNIT_AB_DLL_D)\
		$(LIB_CORE_DLL_D)\
		$(LIB_SHWILD_DLL_D)\
		$(LIB_XTESTS_DLL_D)\
		$(TARGET_LIB_DLL_D)

$(OBJ_TEST_UNIT_AB_DLL_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp

$(TARG_TEST_UNIT_AB_DLL_R):    \
		$(OBJ_TEST_UNIT_AB_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_DLL_R) -out:$@ \
		$(OBJ_TEST_UNIT_AB_DLL_R)\
		$(LIB_CORE_DLL_R)\
		$(LIB_SHWILD_DLL_R)\
		$(LIB_XTESTS_DLL_R)\
		$(TARGET_LIB_DLL_R)

$(OBJ_TEST_UNIT_AB_DLL_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_DLL_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp

$(TARG_TEST_UNIT_AB_MT_D):    \
		$(OBJ_TEST_UNIT_AB_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_D) -out:$@ \
		$(OBJ_TEST_UNIT_AB_MT_D)\
		$(LIB_CORE_MT_D)\
		$(LIB_SHWILD_MT_D)\
		$(LIB_XTESTS_MT_D)\
		$(TARGET_LIB_MT_D)

$(OBJ_TEST_UNIT_AB_MT_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp

$(TARG_TEST_UNIT_AB_MT_R):    \
		$(OBJ_TEST_UNIT_AB_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_MT_R) -out:$@ \
		$(OBJ_TEST_UNIT_AB_MT_R)\
		$(LIB_CORE_MT_R)\
		$(LIB_SHWILD_MT_R)\
		$(LIB_XTESTS_MT_R)\
		$(TARGET_LIB_MT_R)

$(OBJ_TEST_UNIT_AB_MT_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_MT_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp

$(TARG_TEST_UNIT_AB_ST_D):    \
		$(OBJ_TEST_UNIT_AB_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_D) -out:$@ \
		$(OBJ_TEST_UNIT_AB_ST_D)\
		$(LIB_CORE_ST_D)\
		$(LIB_SHWILD_ST_D)\
		$(LIB_XTESTS_ST_D)\
		$(TARGET_LIB_ST_D)

$(OBJ_TEST_UNIT_AB_ST_D): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_D) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp

$(TARG_TEST_UNIT_AB_ST_R):    \
		$(OBJ_TEST_UNIT_AB_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(PROJ_MAKEFILE_NAME)
	$(LD) $(LD_ARGS_ST_R) -out:$@ \
		$(OBJ_TEST_UNIT_AB_ST_R)\
		$(LIB_CORE_ST_R)\
		$(LIB_SHWILD_ST_R)\
		$(LIB_XTESTS_ST_R)\
		$(TARGET_LIB_ST_R)

$(OBJ_TEST_UNIT_AB_ST_R): $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp $(CORE_HEADERS) $(SHWILD_HEADERS) $(XTESTS_HEADERS) $(PROJ_MAKEFILE_NAME)
	$(CPPC) $(CPPC_ARGS_ST_R) -Fo$@ $(PROJ_TEST_UNIT_DIR)\test.unit.cstring.auto_buffer\test.unit.cstring.auto_buffer.cpp

############################### end of file ################################
