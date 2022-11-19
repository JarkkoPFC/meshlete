#============================================================================
# Meshlete - Meshlet-based 3D object converter
#
# Copyright (c) 2022, Jarkko Lempiainen
# All rights reserved.
#----------------------------------------------------------------------------
#
# make options:
#   build=<build>       - options: debug (default), release, retail
#   platform=<platform> - options: linux32, linux64 (default), win32, win64
# make targets:
#   exes                - compile all libraries and executables (default)
#   libs                - compile all libraries
#   clean               - delete libraries and object files for the target
#   <exe name>          - compile given executable, e.g. sxe_editor
#   <library name>      - compile given engine library, e.g. core
#
# examples:
# to compile linux64 release build of all libraries:
#   make build=release libs
#
# to compile win64 release build of the meshlete library:
#   make build=release platform=win64 meshlete
#
# to clean all linux64 release build files:
#   make build=release clean
#
# to compile linux64 release build of all executables:
#   make build=release exes
#
# to clean and rebuild linux64 debug libraries and executables:
#   make clean exes


# build settings
ifndef build
build=debug
endif
$(if $(filter $(build),debug release retail),,$(error unknown target build "$(build)"))
ifeq "$(build)" "debug"
CFLAGS=-ggdb
CDEFS=-D PFC_DEBUG
else ifeq "$(build)" "release"
CFLAGS=-O2 -fno-strict-aliasing
CDEFS=-D PFC_RELEASE
else ifeq "$(build)" "retail"
CFLAGS=-O3 -fno-strict-aliasing
CDEFS=-D PFC_RETAIL
endif

# platform settings
ifndef platform
platform=linux64
endif
$(if $(filter $(platform),linux32 linux64 win32 win64),,$(error unknown target platform "$(platform)"))
ifeq "$(platform)" "linux32"
CFLAGS+=-m32
CDEFS+=-D PFC_PLATFORM_LINUX32
else ifeq "$(platform)" "linux64"
CFLAGS+=-m64 -mcx16
CDEFS+=-D PFC_PLATFORM_LINUX64
else ifeq "$(platform)" "win32"
CFLAGS+=-m32
CDEFS+=-D PFC_PLATFORM_WIN32
else ifeq "$(platform)" "win64"
CFLAGS+=-m64
CDEFS+=-D PFC_PLATFORM_WIN64
endif

# generic settings
.DEFAULT_GOAL:=libs
MD=mkdir -p $(1)
RD=rm -r -f $(1)
RM=rm -f $(1)
EXEDIR=../../bin
INTDIR_ROOT=../../_intermediate
INTDIR=$(INTDIR_ROOT)/$(platform)_gcc/$(build)
LIBDIR=../../lib/$(platform)_gcc
EXTLIBDIR=../../mini_sxp/sxp_extlibs/lib/$(platform)_gcc
SRCDIR=../..
MINI_SXP_LIB=../../mini_sxp/lib/$(platform)_gcc/mini_sxp_$(build).a
EXTLIBS=zlib
CLIBS=
# CLIBS=-lgdi32 -lcomdlg32 -lcomctl32 -lole32 -loleaut32 -luuid

# compiler settings
CC=g++
CINCS=-I../.. -I../../mini_sxp -I../../mini_sxp/sxp_extlibs/zlib/src -I../../mini_sxp/sxp_extlibs/libogg/src/include
CWARNS=-Wall -Wno-non-template-friend -Wno-comments -Wno-unknown-pragmas -Wno-int-in-bool-context
CDEFS+=-D PFC_COMPILER_GCC
CFLAGS+=-c -msse2 $(CWARNS) $(CDEFS) $(CINCS)

# linker settings
LD=g++
LDFLAGS=-pthread

# archiver settings
AR=ar
ARFLAGS=rcs

# libraries
LIBRARIES=MESHLETE
# sxp library
MESHLETE_LIB:=$(LIBDIR)/meshlete_$(build).a
MESHLETE_LIB_DIRS:=src src/rasterizer

# executables
EXECUTABLES=MESHLETE
# unittest exe
MESHLETE_EXE:=$(EXEDIR)/meshlete_$(platform)_$(build)
MESHLETE_EXE_DIRS:=tool_src
MESHLETE_EXE_LDFLAGS:=-Wl,--no-as-needed -lrt
SAMPLE_EXE:=$(EXEDIR)/sample_$(platform)_$(build)
SAMPLE_EXE_DIRS:=samples
SAMPLE_EXE_LDFLAGS:=-Wl,--no-as-needed -lrt

# helper functions
SRC_FILES=$(filter-out $(2),$(foreach DIR,$(1),$(wildcard $(SRCDIR)/$(DIR)/*.cpp)))
OBJ_FILES=$(subst $(SRCDIR),$(INTDIR),$(1:.cpp=.o))

# library target template
define LIB_TEMPLATE
ALL_LIBS+=$($(1)_LIB)
ALL_LIB_DIRS+=$(firstword $(subst /, ,$($(1)_LIB_DIRS)))
$(1)_LIB_SRC:=$(call SRC_FILES,$($(1)_LIB_DIRS),$($(1)_LIB_EXCL))
$(1)_LIB_OBJ:=$$(call OBJ_FILES,$$($(1)_LIB_SRC))
.PHONY $(notdir $($(1)_LIB:_$(build).a=)):
$(notdir $($(1)_LIB:_$(build).a=)) $($(1)_LIB): $($(1)_LIB_DEPS) $$($(1)_LIB_OBJ)
	@echo Creating library $($(1)_LIB)
	@$(call MD,$(dir $($(1)_LIB)))
	@$(AR) $(ARFLAGS) $($(1)_LIB) $$($(1)_LIB_OBJ)
endef

# executable target template
define EXE_TEMPLATE
ALL_EXES+=$($(1)_EXE)
ALL_EXE_DIRS+=$(firstword $(subst /, ,$($(1)_EXE_DIRS)))
$(1)_EXE_SRC:=$(call SRC_FILES,$($(1)_EXE_DIRS),$($(1)_EXE_EXCL))
$(1)_EXE_OBJ:=$$(call OBJ_FILES,$$($(1)_EXE_SRC))
.PHONY $(notdir $($(1)_EXE:_$(platform)_$(build).exe=)):
$(notdir $($(1)_EXE:_$(platform)_$(build).exe=)) $($(1)_EXE): $($(1)_EXE_DEPS) $(ALL_LIBS) $$($(1)_EXE_OBJ)
	@echo Creating executable $($(1)_EXE)
#	@$(MD) $(dir $($(1)_EXE))
	@$(LD) $(LDFLAGS) $($(1)_EXE_LDFLAGS) -o $($(1)_EXE) $$($(1)_EXE_OBJ) $(ALL_LIBS) $(MINI_SXP_LIB) $$(addprefix $(EXTLIBDIR)/,$(addsuffix _$(build).a,$(EXTLIBS))) $(CLIBS)
endef

# setup targets for all libraries and exes
$(foreach LIB,$(LIBRARIES),$(eval $(call LIB_TEMPLATE,$(LIB))))
$(foreach EXE,$(EXECUTABLES),$(eval $(call EXE_TEMPLATE,$(EXE))))

.PHONY: libs
libs: $(ALL_LIBS)

.PHONY: exes
exes: $(ALL_EXES)

$(INTDIR)/%.o: $(SRCDIR)/%.cpp
	@echo $(subst $(SRCDIR)/,,$<)
	@$(call MD,$(dir $@))
	@$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo Deleting libraries and executables
	@$(foreach LIB,$(ALL_LIBS),$(call RM,$(LIB)))
	@$(foreach EXE,$(ALL_EXES),$(call RM,$(EXE)))
	@echo Deleting intermediate directories
	@$(call RD,$(INTDIR_ROOT))
	@$(foreach EDIR,$(ALL_EXE_DIRS),$(call RD,$(INTDIR)/$(EDIR)))

.PHONY: clean_int
clean_int:
	@echo Deleting intermediate directories
	@$(call RD,$(INTDIR_ROOT))
