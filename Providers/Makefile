# -*- mode: Makefile; -*- 
#-------------------------------------------------------------------------------
# Copyright (c) Microsoft Corporation.  All rights reserved.
#-------------------------------------------------------------------------------
# 2014-01-17
#-------------------------------------------------------------------------------

# define some aliases
MKDIR:=mkdir -p -m 755
RM:=rm -f
SED:=sed
COPY:=cp
MKDEP:=-MD

# define some source paths
TOP?=$(shell cd ..; pwd)
OMI_PATH?=$(TOP)/omi-1.0.8
PROVIDER_PATH?=$(TOP)/Providers

# define the root output path
BIN_PATH:=$(PROVIDER_PATH)/bin

# included makefiles for additional definitions
include $(PROVIDER_PATH)/config.mak
include $(OMI_PATH)/output/config.mak

# test that configure has been run
ifndef ENABLE_DEBUG
$(error "ENABLE_DEBUG is not set.  Please re-run configure")
endif

# additional include paths
INCLUDE_PATH+=$(INCDIR)
INCLUDE_PATH+=$(PROVIDER_PATH)/PythonHelper
CPPFLAGS+=$(addprefix -I,$(INCLUDE_PATH))

# add the OMI lib path to the library path
LDFLAGS+=-L$(LIBDIR)

# add some libraries
LDFLAGS+=-lmicxx
LDFLAGS+=-lrt

# boost include path
CPPFLAGS+=-I/usr/local/include/boost_1_55_0

# boost libraries
BOOST_LIB_ROOT:=/usr/local/lib/boost_1_55_0
LDFLAGS+=$(BOOST_LIB_ROOT)/libboost_system.a
LDFLAGS+=$(BOOST_LIB_ROOT)/libboost_filesystem.a

# extra compile flags
CXXFLAGS+=-fPIC
CXXFLAGS+=-DNDEBUG
CXXFLAGS+=-Wall
CXXFLAGS+=-ggdb
CXXFLAGS+=-O2

# include extra source paths
VPATH:=$(PROVIDER_PATH)/PythonHelper

# common source files
COMMON_SOURCES:=debug_tags.cpp
COMMON_SOURCES+=python_file_resource.cpp
COMMON_SOURCES+=python_helper.cpp
COMMON_SOURCES+=python_io_helper.cpp
COMMON_SOURCES+=python_scoped_context.cpp
COMMON_OBJS:=$(COMMON_SOURCES:.cpp=.o)

# these are the names of the files that are auto-generated for each provider
GENERATED_SOURCES:=module.c
GENERATED_SOURCES+=schema.c
GENERATED_OBJS:=$(GENERATED_SOURCES:.c=.o)

# list of providers
PROVIDERS:=nxFile
PROVIDERS+=nxScript
PROVIDERS+=nxUser
PROVIDERS+=nxGroup
PROVIDERS+=nxService

# list of the different python versions to build against
#PYTHON_VERSIONS:=2.4
PYTHON_VERSIONS+=2.5
PYTHON_VERSIONS+=2.6
PYTHON_VERSIONS+=2.7
PYTHON_VERSIONS+=3.2
PYTHON_VERSIONS+=3.3

# this is used to enable the printing of xml style tags for help in debugging
PRINT_BOOKENDS?=0
CPPFLAGS+=-DPRINT_BOOKENDS=$(PRINT_BOOKENDS)


# the main target
################################################################################
all:


# reg target
################################################################################
##OMI_BIN_PATH:=$(OMI_PATH)/output/bin
#OMI_BIN_PATH:=$(BINDIR)
##OMI_LIB_PATH:=$(OMI_PATH)/output/lib
#OMI_LIB_PATH:=$(LIBDIR)
##OMI_CONFIG_PATH:=$(OMI_PATH)/etc/dsc/configuration
#OMI_CONFIG_PATH:=$(CONFIG_SYSCONFDIR)/dsc/configuration
#OMI_REG_PATH:=$(BIN_PATH)/omi
#OMI_REG:=$(OMI_BIN_PATH)/omireg -n root/Microsoft/DesiredStateConfiguration \
#	-o @requestor@
#SCHEMA:=Resource.schema.mof
#REGISTER:=Resource.registration.mof

## $(call REGISTER_PROVIDER,provider-name)
#define REGISTER-PROVIDER
#	echo ...registering: $1;
#	export LD_LIBRARY_PATH=$(BOOST_LIB_ROOT):$$LD_LIBRARY_PATH; \
#	$(MKDIR) $(OMI_CONFIG_PATH)/{registration,schema}/MSFT_$1Resource; \
#	$(COPY) $(PROVIDER_PATH)/$1/MSFT_$1$(SCHEMA) \
#	    $(OMI_CONFIG_PATH)/schema/MSFT_$1Resource/MSFT_$1$(SCHEMA); \
#	$(COPY) $(PROVIDER_PATH)/$1/MSFT_$1$(REGISTER) \
#	    $(OMI_CONFIG_PATH)/registration/MSFT_$1Resource/MSFT_$1$(REGISTER); \
#	$(OMI_REG) $(BIN_PATH)/libMSFT_$1Resource.so;
#endef

#.PHONY: reg
#reg :
#	echo ...copying scripts
#	$(COPY) -R $(PROVIDER_PATH)/Scripts $(OMI_LIB_PATH)
#	@$(foreach provider,$(PROVIDERS),$(call REGISTER-PROVIDER,$(provider)))


# compile rule
################################################################################
# this macro defines rules for compiling source files using extra flags,
# generating files with lists of dependencies, and alternate placement for those
# files
# $(call COMPILE-WITH-DEPEND,dest-path-prefix,flags)
define COMPILE-WITH-DEPEND
	@echo ...compiling: $$(@F)
	$(COMPILE.cpp) $($2) $(MKDEP) $$< -o $$@
	@-$(COPY) $1$$*.d $1$$*.P;
	@$(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$$$//' -e '/^$$$$/ d' \
	    -e 's/$$$$/ :/' < $1$$*.d >> $1$$*.P;
	@$(RM) $1$$*.d
endef


# per python version specific rules
################################################################################
# $(call PER-PYTHON-VERSION-RULES,python-version)
define PER-PYTHON-VERSION-RULES

# compiler flags
$(eval PYFLAGS_$1:=\
    $(filter-out -Wstrict-prototypes,$(shell python$1-config --cflags)))

# bin path
$(eval BIN_PATH$1:=$(BIN_PATH)/$1)

# bin path rule
$(BIN_PATH$1): | $(BIN_PATH)
	@echo $(MKDIR) $(BIN_PATH$1)...
	$(MKDIR) $(BIN_PATH$1)

# compile rule
$(BIN_PATH$1)/%.o : %.cpp
	$(call COMPILE-WITH-DEPEND,$(BIN_PATH$1)/,PYFLAGS_$1)

# add bin path dependencies to the object files
$(addprefix $(BIN_PATH$1)/,$(COMMON_OBJS)) : | $(BIN_PATH$1)
$(BIN_PATH$1)/MSFT_$1Resource.o : $(BIN_PATH$1)

# clean bin directory rule
.phony : clean$1
clean$1:
	@$(RM) $(BIN_PATH$1)/*.o $(BIN_PATH$1)/*.d $(BIN_PATH$1)/*.P \
	    $(BIN_PATH$1)/*.so

# add this to the clean target
clean-action : clean$1

# include dependency file rule
-include $(BIN_PATH$1)/*.P

endef

# instantiate per python version rules
$(foreach version,$(PYTHON_VERSIONS),\
    $(eval $(call PER-PYTHON-VERSION-RULES,$(version))))


# per provider specific rules
################################################################################
# $(call PER-PROVIDER-RULES,python-version)
define PER-PROVIDER-RULES

# compile rule
$(BIN_PATH)/$1_%.o : $(PROVIDER_PATH)/$1/%.c
	$(call COMPILE-WITH-DEPEND,$(BIN_PATH)/$1_)

# add bin path dependencies to the object files
$(addprefix $(BIN_PATH)/$1_,$(GENERATED_OBJS)) : | $(BIN_PATH)

endef

# instantiate per provider rules
$(foreach provider,$(PROVIDERS),\
    $(eval $(call PER-PROVIDER-RULES,$(provider))))


# per provider X per python version specific rules
################################################################################
# $(call PROVIDER-X-PYTHON-RULES,provider,python-version)
define PROVIDER-X-PYTHON-RULES

# compile rule
$(BIN_PATH$2)/%.o : $(PROVIDER_PATH)/$1/%.cpp
	$(call COMPILE-WITH-DEPEND,$(BIN_PATH$2)/,PYFLAGS_$2)

# add this shared object to the "all" target
all: $(BIN_PATH$2)/libMSFT_$1Resource.so

LDFLAGS_%2:=$(LDFLAGS) $(filter-out -L%,$(shell python$2-config --ldflags))

$(BIN_PATH$2)/libMSFT_$1Resource.so : \
	$(addprefix $(BIN_PATH$2)/,$(COMMON_OBJS)) \
	$(addprefix $(BIN_PATH)/$1_,$(GENERATED_OBJS)) \
	$(BIN_PATH$2)/MSFT_$1Resource.o
	@echo ...linking: $(BIN_PATH$2)/libMSFT_$1Resource.so
	$(CXX) -shared -Wl $(LDFLAGS_%2) $(BOOST_LIB_ROOT)/libboost_python$2.a \
        $$^ -o $$@

endef

# instantiate per provider X per python version rules
$(foreach provider,$(PROVIDERS), \
    $(foreach version,$(PYTHON_VERSIONS), \
        $(eval $(call PROVIDER-X-PYTHON-RULES,$(provider),$(version)))))


# miscellaneous rules
################################################################################

# a rule to make root bin directory
$(BIN_PATH) :
	$(MKDIR) $(BIN_PATH)

# rules for output when running the clean target
.phony : clean-text
clean-text :
	@echo ...deleting: library, object, and dependency files!

# rules doing the cleanup in the root bin directory
.phony : clean-action
clean-action :
	@$(RM) $(BIN_PATH)/*.o $(BIN_PATH)/*.d $(BIN_PATH)/*.P $(BIN_PATH)/*.so
	@$(RM) -r $(OMI_REG_PATH)

# master clean target
clean : clean-text clean-action

# include shared dependency files
-include $(BIN_PATH)/*.P
