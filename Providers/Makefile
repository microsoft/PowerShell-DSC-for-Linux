# -*- mode: Makefile; -*- 
#--------------------------------------------------------------------------------
# Copyright (c) Microsoft Corporation.  All rights reserved.
#--------------------------------------------------------------------------------
# 2014-01-17
#--------------------------------------------------------------------------------

OMI_DIR := $(shell cd ../LCM; pwd)
BASE_DIR := $(shell pwd)
TARGET_DIR := $(BASE_DIR)/target

include $(BASE_DIR)/config.mak

ifndef ENABLE_DEBUG
$(error "ENABLE_DEBUG is not set.  Please re-run configure")
endif

SHARED_FLAGS := -shared
INCLUDE_FLAGS := -I$(OMI_DIR)/output/include -I$(BASE_DIR)/PythonHelper
LINK_LIBRARIES := -L$(OMI_DIR)/output/lib -lmicxx -lrt
PYTHON_CFLAGS = $(shell python-config --cflags)
BUILD_SHARED_LIBRARY := g++ $(SHARED_FLAGS) $(INCLUDE_FLAGS) $(LINK_LIBRARIES) $(PYTHON_CFLAGS) -fPIC 
BUILD_OBJECT_FILE := g++ -c $(INCLUDE_FLAGS) $(PYTHON_CFLAGS) -fPIC 



PROVIDER_LIST := nxFile \
		 nxScript \
		 nxUser

PROVIDER_LIST_OMI := $(addsuffix Resource,$(addprefix OMI_,$(PROVIDER_LIST)))
PROVIDER_LIBRARIES := $(addsuffix Resource.so,$(addprefix libOMI_,$(PROVIDER_LIST)))
PROVIDER_LIBRARIES_PATHS := $(addprefix $(TARGET_DIR)/,$(PROVIDER_LIBRARIES))

all: $(PROVIDER_LIBRARIES_PATHS)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)/objs

# PythonHelper static library
PYTHONHELPER_SRC := PythonHelper.cpp 
PYTHONHELPER_SRC_PATHS := $(addprefix $(BASE_DIR)/PythonHelper/,$(PYTHONHELPER_SRC))

PYTHONHELPER_OBJS := $(patsubst %.cpp,%.o,$(PYTHONHELPER_SRC))
PYTHONHELPER_OBJS_PATHS := $(addprefix $(TARGET_DIR)/objs/,$(PYTHONHELPER_OBJS))

$(TARGET_DIR)/objs/%.o: $(BASE_DIR)/PythonHelper/%.cpp
	$(BUILD_OBJECT_FILE) $^ -o $@

$(TARGET_DIR)/libpythonhelper.a: $(PYTHONHELPER_OBJS_PATHS)
	ar rcs $@ $^

# General Provider stuff
$(PROVIDER_LIBRARIES_PATHS): $(TARGET_DIR)/libpythonhelper.a

# nxFile
NXFILE_SRC :=   OMI_nxFileResource.cpp \
	        OMI_nxFileResource.h \
		module.c \
		schema.c

NXFILE_SRC_PATHS := $(addprefix $(BASE_DIR)/nxFile/,$(NXFILE_SRC))

$(NXFILE_SRC_PATHS): $(TARGET_DIR)

$(TARGET_DIR)/libOMI_nxFileResource.so: $(NXFILE_SRC_PATHS)
	$(BUILD_SHARED_LIBRARY) $^ -o $@

# nxScript
NXSCRIPT_SRC := OMI_nxScriptResource.cpp \
	        OMI_nxScriptResource.h \
		module.c \
		schema.c

NXSCRIPT_SRC_PATHS := $(addprefix $(BASE_DIR)/nxScript/,$(NXSCRIPT_SRC))

$(NXSCRIPT_SRC_PATHS): $(TARGET_DIR)

$(TARGET_DIR)/libOMI_nxScriptResource.so: $(NXSCRIPT_SRC_PATHS)
	$(BUILD_SHARED_LIBRARY) $^ -o $@

# nxUser
NXUSER_SRC := OMI_nxUserResource.cpp \
	        OMI_nxUserResource.h \
		module.c \
		schema.c

NXUSER_SRC_PATHS := $(addprefix $(BASE_DIR)/nxUser/,$(NXUSER_SRC))

$(NXUSER_SRC_PATHS): $(TARGET_DIR)

$(TARGET_DIR)/libOMI_nxUserResource.so: $(NXUSER_SRC_PATHS)
	$(BUILD_SHARED_LIBRARY) $^ -o $@

# nxEnvironment
$(TARGET_DIR)/libOMI_nxEnvironmentResource.so: $(NXENVIRONMENT_SRC_PATHS)
	$(BUILD_SHARED_LIBRARY) $^ -o $@


clean :
	-rm -r $(TARGET_DIR)


OMI_OUTPUT_DIR := $(OMI_DIR)/output
OMI_BINDIR := $(OMI_OUTPUT_DIR)/bin
OMI_LIBDIR := $(OMI_OUTPUT_DIR)/lib
OMIGEN := $(OMI_BINDIR)/omigen
OMIREG := $(OMI_BINDIR)/omireg

reg :
	mkdir -p $(TARGET_DIR)/omi
	sudo mkdir -p /etc/opt/microsoft/omi/conf/omiregister/dsc
	for prov in $(PROVIDER_LIST); do \
		export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(OMI_LIBDIR); cd $(TARGET_DIR)/omi; $(OMIREG) -n "dsc" -o @requestor@ $(TARGET_DIR)/libOMI_$${prov}Resource.so; \
		mkdir -p  $(OMI_DIR)/etc/dsc/configuration/{registration,schema}/OMI_$${prov}Resource; \
		cp $(BASE_DIR)/$${prov}/OMI_$${prov}Resource.schema.mof $(OMI_DIR)/etc/dsc/configuration/schema/OMI_$${prov}Resource/OMI_$${prov}Resource.schema.mof; \
		cp $(BASE_DIR)/$${prov}/OMI_$${prov}Resource.registration.mof $(OMI_DIR)/etc/dsc/configuration/registration/OMI_$${prov}Resource/OMI_$${prov}Resource.registration.mof; \
	done

