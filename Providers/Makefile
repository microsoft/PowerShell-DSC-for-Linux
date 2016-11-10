SHELL=/bin/bash

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
include $(OMI_PATH)/output/config.mak
include ../config.mak

# additional include paths
INCLUDE_PATH+=$(INCDIR)
INCLUDE_PATH+=$(SRCDIR)
INCLUDE_PATH+=$(SRCDIR)/base
INCLUDE_PATH+=$(SRCDIR)/common
INCLUDE_PATH+=$(PROVIDER_PATH)
INCLUDE_PATH+=$(TOP)
CPPFLAGS+=$(addprefix -I,$(INCLUDE_PATH))

# add the OMI lib path to the library path
LDFLAGS+=-L$(LIBDIR)

# add some libraries
LDFLAGS+=-lmicxx
LDFLAGS+=-lrt

# extra compile flags
CXXFLAGS+=-fPIC
CXXFLAGS+=-DNDEBUG
CXXFLAGS+=-Wall
CXXFLAGS+=-ggdb
#CXXFLAGS+=-O2
CXXFLAGS+=-DDSC_SCRIPT_PATH=\"$(DSC_SCRIPT_PATH)\"

# common source files
COMMON_SOURCES:=debug_tags.cpp
COMMON_SOURCES+=PythonProvider.cpp

COMMON_OBJS:=$(COMMON_SOURCES:.cpp=.o)

# these are the names of the files that are auto-generated for each provider
GENERATED_SOURCES:=module.c
GENERATED_SOURCES+=schema.c
GENERATED_OBJS:=$(GENERATED_SOURCES:.c=.o)

# list of providers
ifeq ($(BUILD_OMS),BUILD_OMS)
PROVIDERS:=nxOMSPerfCounter
PROVIDERS+=nxOMSSyslog
PROVIDERS+=nxOMSCustomLog
PROVIDERS+=nxOMSGenerateInventoryMof
PROVIDERS+=nxService
PROVIDERS+=nxPackage
PROVIDERS+=nxUser
PROVIDERS+=nxGroup
PROVIDERS+=nxOMSPlugin
PROVIDERS+=nxAvailableUpdates
PROVIDERS+=nxOMSKeyMgmt
PROVIDERS+=nxFileInventory
PROVIDERS+=nxOMSAgentNPMConfig
else
PROVIDERS:=nxFile
PROVIDERS+=nxScript
PROVIDERS+=nxUser
PROVIDERS+=nxGroup
PROVIDERS+=nxService
PROVIDERS+=nxPackage
PROVIDERS+=nxEnvironment
PROVIDERS+=nxSshAuthorizedKeys
PROVIDERS+=nxIPAddress
PROVIDERS+=nxComputer
PROVIDERS+=nxFirewall
PROVIDERS+=nxDNSServerAddress
PROVIDERS+=nxFileLine
PROVIDERS+=nxArchive
PROVIDERS+=nxMySqlDatabase
PROVIDERS+=nxMySqlGrant
PROVIDERS+=nxMySqlUser
PROVIDERS+=nxAvailableUpdates
PROVIDERS+=nxFileInventory
endif

# this is used to enable the printing of xml style tags for help in debugging
PRINT_BOOKENDS?=0
CPPFLAGS+=-DPRINT_BOOKENDS=$(PRINT_BOOKENDS)


# the main target
################################################################################
all:


# reg target
################################################################################
OMI_BIN_PATH:=$(CONFIG_BINDIR)
OMI_LIB_PATH:=$(CONFIG_LIBDIR)
OMI_CONFIG_PATH:=$(CONFIG_SYSCONFDIR)/dsc/configuration
OMI_REG_PATH:=$(BIN_PATH)/omi
OMI_REG:=$(OMI_BIN_PATH)/omireg -n root/Microsoft/DesiredStateConfiguration \
	-o @requestor@
SCHEMA:=Resource.schema.mof
REGISTER:=Resource.registration.mof

# $(call REGISTER_PROVIDER,provider-name)
define REGISTER-PROVIDER
	echo ...registering: $1;
	$(MKDIR) $(OMI_CONFIG_PATH)/{registration,schema}/MSFT_$1Resource; \
	$(COPY) $(PROVIDER_PATH)/$1/MSFT_$1$(SCHEMA) \
	    $(OMI_CONFIG_PATH)/schema/MSFT_$1Resource/MSFT_$1$(SCHEMA); \
	$(COPY) $(PROVIDER_PATH)/$1/MSFT_$1$(REGISTER) \
	    $(OMI_CONFIG_PATH)/registration/MSFT_$1Resource/MSFT_$1$(REGISTER); \
	$(OMI_REG) $(BIN_PATH)/libMSFT_$1Resource.so;
endef

.PHONY: reg
reg :
	echo ...copying scripts
	$(MKDIR) -p $(DSC_SCRIPT_PATH)
	$(MKDIR) -p $(CONFIG_DATADIR)/dsc/modules
	$(COPY) -R $(PROVIDER_PATH)/Scripts/*.py $(DSC_SCRIPT_PATH)
	$(COPY) -R $(PROVIDER_PATH)/Scripts/2.4x-2.5x $(DSC_SCRIPT_PATH)
	$(COPY) -R $(PROVIDER_PATH)/Scripts/2.6x-2.7x $(DSC_SCRIPT_PATH)
	$(COPY) -R $(PROVIDER_PATH)/Scripts/3.x $(DSC_SCRIPT_PATH)
	$(COPY) -R $(TOP)/intermediate/Scripts/*.py $(TOP)/intermediate/Scripts/*.sh $(DSC_SCRIPT_PATH)
	chmod a+x $(DSC_SCRIPT_PATH)/*.py $(DSC_SCRIPT_PATH)/*.sh
	@$(foreach provider,$(PROVIDERS),$(call REGISTER-PROVIDER,$(provider)))


# compile rule
################################################################################
# this macro defines rules for compiling source files using extra flags,
# generating files with lists of dependencies, and alternate placement for those
# files
# $(call COMPILE-WITH-DEPEND,dest-path-prefix)
define COMPILE-WITH-DEPEND
	@echo ...compiling: $$(@F)
	$(COMPILE.cpp) $($2) $(MKDEP) $$< -o $$@
	@-$(COPY) $1$$*.d $1$$*.P;
	@$(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$$$//' -e '/^$$$$/ d' \
	    -e 's/$$$$/ :/' < $1$$*.d >> $1$$*.P;
	@$(RM) $1$$*.d
endef


# compile rule
$(BIN_PATH)/%.o : %.cpp
	@echo ...compiling: $(@F)
	$(COMPILE.cpp) $(MKDEP) $< -o $@
	@-$(COPY) $(BIN_PATH)/$*.d $(BIN_PATH)/$*.P;
	@$(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' \
	    -e 's/$$/ :/' < $(BIN_PATH)/$*.d >> $(BIN_PATH)/$*.P
	@$(RM) $(BIN_PATH)/$*.d


# add bin path dependencies to the object files
$(addprefix $(BIN_PATH)/,$(COMMON_OBJS)) : | $(BIN_PATH)


# per provider specific rules
################################################################################
# $(call PER-PROVIDER_RULES,provider)
define PER-PROVIDER-RULES

# compile rule
$(BIN_PATH)/$1_%.o : $(PROVIDER_PATH)/$1/%.c
	$(call COMPILE-WITH-DEPEND,$(BIN_PATH)/$1_)

$(BIN_PATH)/%.o : $(PROVIDER_PATH)/$1/%.cpp
	$(call COMPILE-WITH-DEPEND,$(BIN_PATH)/)

# add bin path dependencies to the object files
$(addprefix $(BIN_PATH)/$1_,$(GENERATED_OBJS)) : | $(BIN_PATH)

# add this shared object to the "all" target
all: $(BIN_PATH)/libMSFT_$1Resource.so

$(BIN_PATH)/libMSFT_$1Resource.so : \
	$(addprefix $(BIN_PATH)/,$(COMMON_OBJS)) \
	$(addprefix $(BIN_PATH)/$1_,$(GENERATED_OBJS)) \
	$(BIN_PATH)/MSFT_$1Resource.o
	@echo ...linking: $(BIN_PATH)/libMSFT_$1Resource.so
	$(CXX) -shared -o $$@ $$^ -L$(LIBDIR) -lmiapi -lmicodec -lmofparser -lmofparsererror -lprotocol -lomi_error -lxmlserializer -lbase -lpal
endef

# instantiate per provider rules
$(foreach provider,$(PROVIDERS),\
    $(eval $(call PER-PROVIDER-RULES,$(provider))))


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
