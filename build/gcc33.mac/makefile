################################################################################
# File:		makefile.mac
#
# Purpose:	Makefile for the cstring project, for the GCC 3.3
#           compiler, on UNIX
#
# Created:	15th Feburary 2005
# Updated:	13th May 2008
#
################################################################################



################################################################################
# Symbols

# Identification

COMP_TAG			=	gcc33
PROJ_TAG			=	cstring
PROJ_VER_MAJOR		=	3
PROJ_TAG_VER		=	$(PROJ_TAG).$(PROJ_VER_MAJOR)

CC					=	gcc-3.3
CPPC				=	g++-3.3
AR					=	ar
LD					=	g++
RM					=	rm -f
CP					=	cp

# Directories

PROJ_BASE_DIR		=	../..
PROJ_BIN_DIR		=	$(PROJ_BASE_DIR)/bin
PROJ_BUILD_DIR		=	$(PROJ_BASE_DIR)/build
PROJ_INCLUDE_DIR	=	$(PROJ_BASE_DIR)/include
PROJ_LIB_DIR		=	$(PROJ_BASE_DIR)/lib
PROJ_OBJ_DIR		=	.
PROJ_SRC_DIR		=	$(PROJ_BASE_DIR)/src
PROJ_TEST_DIR		=	$(PROJ_BASE_DIR)/test

# Includes

INCLUDES_LEADER		=	

PROJ_INCLUDE		=	-I$(PROJ_INCLUDE_DIR)

COMMON_INCLUDES		=	

CC_INCLUDES = \
 $(INCLUDES_LEADER) \
 $(PROJ_INCLUDE) \
 $(COMMON_INCLUDES) \
 \

# Lib

LIBS_LEADER			=	

COMMON_LIB			=	

# #defines

COMMON_DEFS			=	-Dunix

CC_DEFS				=	$(COMMON_DEFS)

# Flags

CC_F_NOLOGO				=	
CC_F_COMPILE_ONLY		=	-c
CC_F_WARNING_MAX		=	-Wall -pedantic -Wno-long-long -Wno-long-double -Wno-unused-value -Wundef -Wendif-labels -Wshadow
CC_F_WARNING_ERR		=	-Werror

CC_TOOL_FLAGS		=	

CC_FLAGS = \
 $(CC_TOOL_FLAGS) \
 $(CC_F_NOLOGO) \
 $(CC_F_COMPILE_ONLY) \
 $(CC_F_WARNING_MAX) \
 $(CC_F_WARNING_ERR)

# Arguments (= flags + defines + includes)

CC_ARGS_ST_DEBUG				=	-D_DEBUG -UNDEBUG $(CC_FLAGS) $(CC_DEFS) $(CC_INCLUDES)
CC_ARGS_ST_RELEASE				=	-DNDEBUG -U_DEBUG $(CC_FLAGS) $(CC_DEFS) $(CC_INCLUDES)

AR_ARGS				=	

LD_F_NOLOGO = 

LD_ARGS_ST_DEBUG				=	 $(LD_F_NOLOGO) $(COMMON_LIB)
LD_ARGS_ST_RELEASE				=	 $(LD_F_NOLOGO) $(COMMON_LIB)

LIBRARIES = \
 \

LIBRARIES_DMC =\
 \

################################################################################
# Targets

# sos


# libs
TARGET_LIB_ST_DEBUG			=	$(PROJ_LIB_DIR)/lib$(PROJ_TAG_VER).$(COMP_TAG).debug.a
TARGET_LIB_UN_ST_DEBUG		=	$(PROJ_LIB_DIR)/lib$(PROJ_TAG).$(COMP_TAG).debug.a

TARGET_LIB_ST_RELEASE			=	$(PROJ_LIB_DIR)/lib$(PROJ_TAG_VER).$(COMP_TAG).a
TARGET_LIB_UN_ST_RELEASE		=	$(PROJ_LIB_DIR)/lib$(PROJ_TAG).$(COMP_TAG).a


# test programs
TARGET_TEST_C_ST_DEBUG		=	$(PROJ_BIN_DIR)/$(PROJ_TAG_VER).test.C.$(COMP_TAG).debug
TARGET_TEST_C_ST_RELEASE		=	$(PROJ_BIN_DIR)/$(PROJ_TAG_VER).test.C.$(COMP_TAG)

TARGETS = \
 $(TARGET_LIB_ST_DEBUG) \
 $(TARGET_LIB_UN_ST_DEBUG) \
 $(TARGET_LIB_ST_RELEASE) \
 $(TARGET_LIB_UN_ST_RELEASE) \
 \
 \
 $(TARGET_TEST_C_ST_DEBUG) \
 $(TARGET_TEST_C_ST_RELEASE) \
 \

# objects

# for libs

OBJ_LIB_cstring__ST_DEBUG = $(PROJ_OBJ_DIR)/cstring.debug.o

OBJ_LIB_ST_DEBUG = \
 $(OBJ_LIB_cstring__ST_DEBUG) \
 \


OBJ_LIB_cstring__ST_RELEASE = $(PROJ_OBJ_DIR)/cstring.o

OBJ_LIB_ST_RELEASE = \
 $(OBJ_LIB_cstring__ST_RELEASE) \
 \



LIB_OBJS = \
 $(OBJ_LIB_ST_DEBUG) \
 $(OBJ_LIB_ST_RELEASE) \
 \

# for test programs

OBJ_C_ST_DEBUG			=	./C.debug.o
OBJ_C_ST_RELEASE			=	./C.o

TEST_OBJS = \
 $(OBJ_C_ST_DEBUG) \
 $(OBJ_C_ST_RELEASE) \
 \

LIB_HEADERS	= \
 $(PROJ_INCLUDE_DIR)/cstring/cstring.h \
 \

TEST_C_HEADERS = \
 $(LIB_HEADERS) \
 \

target:		$(TARGETS)

compile:	$(LIB_OBJS) $(TEST_OBJS)

all: \
 target \
 \

usage:
	@echo "make [usage | clean | compile | all | test | target] - default is 'all'"

clean:
	@-$(RM) $(TARGET_LIB_ST_DEBUG)
	@-$(RM) $(TARGET_LIB_UN_ST_DEBUG)
	@-$(RM) $(OBJ_LIB_ST_DEBUG)
	@-$(RM) $(TARGET_LIB_ST_RELEASE)
	@-$(RM) $(TARGET_LIB_UN_ST_RELEASE)
	@-$(RM) $(OBJ_LIB_ST_RELEASE)
	@-$(RM) $(OBJ_C_ST_DEBUG)
	@-$(RM) $(OBJ_C_ST_RELEASE)
	@-$(RM) $(TARGET_TEST_C_ST_DEBUG)
	@-$(RM) $(TARGET_TEST_C_ST_RELEASE)

test_:
	$(TARGET_TEST_C_ST_DEBUG) --unittest
	$(TARGET_TEST_C_ST_RELEASE) --unittest

test:	target test_

# build targets

# sos

# libs


$(TARGET_LIB_UN_ST_DEBUG): $(TARGET_LIB_ST_DEBUG)
	@$(CP) $(TARGET_LIB_ST_DEBUG) $@

$(TARGET_LIB_ST_DEBUG): $(OBJ_LIB_ST_DEBUG) makefile.mac
	@-mkdir -p $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) rcs $@ $(OBJ_LIB_ST_DEBUG)

$(OBJ_LIB_cstring__ST_DEBUG): $(PROJ_SRC_DIR)/cstring.c $(LIB_HEADERS) makefile.mac
	$(CC) $(CC_ARGS_ST_DEBUG) -o $@ $(PROJ_SRC_DIR)/cstring.c


$(TARGET_LIB_UN_ST_RELEASE): $(TARGET_LIB_ST_RELEASE)
	@$(CP) $(TARGET_LIB_ST_RELEASE) $@

$(TARGET_LIB_ST_RELEASE): $(OBJ_LIB_ST_RELEASE) makefile.mac
	@-mkdir -p $(PROJ_LIB_DIR)
	$(AR) $(AR_ARGS) rcs $@ $(OBJ_LIB_ST_RELEASE)

$(OBJ_LIB_cstring__ST_RELEASE): $(PROJ_SRC_DIR)/cstring.c $(LIB_HEADERS) makefile.mac
	$(CC) $(CC_ARGS_ST_RELEASE) -o $@ $(PROJ_SRC_DIR)/cstring.c


# C test clients

# full
$(TARGET_TEST_C_ST_DEBUG):	$(OBJ_C_ST_DEBUG) makefile.mac
	@-mkdir -p $(PROJ_BIN_DIR)
	$(LD) $(LD_ARGS_ST_DEBUG) -o $@ $(OBJ_C_ST_DEBUG) $(TARGET_LIB_ST_DEBUG) $(LIBRARIES)


$(OBJ_C_ST_DEBUG):	$(PROJ_TEST_DIR)/C/C.c $(TEST_C_HEADERS) makefile.mac
	$(CC) $(CC_ARGS_ST_DEBUG) -o $@ $(PROJ_TEST_DIR)/C/C.c

# full
$(TARGET_TEST_C_ST_RELEASE):	$(OBJ_C_ST_RELEASE) makefile.mac
	@-mkdir -p $(PROJ_BIN_DIR)
	$(LD) $(LD_ARGS_ST_RELEASE) -o $@ $(OBJ_C_ST_RELEASE) $(TARGET_LIB_ST_RELEASE) $(LIBRARIES)


$(OBJ_C_ST_RELEASE):	$(PROJ_TEST_DIR)/C/C.c $(TEST_C_HEADERS) makefile.mac
	$(CC) $(CC_ARGS_ST_RELEASE) -o $@ $(PROJ_TEST_DIR)/C/C.c


