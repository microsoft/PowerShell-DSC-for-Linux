# -*- mode: Makefile; -*- 
#--------------------------------------------------------------------------------
# Copyright (c) Microsoft Corporation.  All rights reserved.
#--------------------------------------------------------------------------------
# 2014-01-17
#--------------------------------------------------------------------------------

BASE_DIR := $(subst /build,,$(PWD))
OMI_ROOT := $(shell cd ../../omi/Unix; pwd -P)
SCXPAL_DIR := $(shell cd ../../pal; pwd -P)

PF_POSIX := 1
include $(SCXPAL_DIR)/build/config.mak
include $(BASE_DIR)/build/config.mak
include $(BASE_DIR)/build/Makefile.version
include $(SCXPAL_DIR)/build/Makefile.pal

ifndef ENABLE_DEBUG
$(error "ENABLE_DEBUG is not set.  Please re-run configure")
endif

SOURCE_DIR := $(BASE_DIR)/source/code
TEST_DIR := $(BASE_DIR)/test/code

PROVIDER_DIR := $(SOURCE_DIR)/providers
PROVIDER_TEST_DIR := $(TEST_DIR)/providers
PROVIDER_TEST_SUPPORT_DIR := $(PROVIDER_TEST_DIR)/support
PAL_INCLUDE_DIR := $(SCXPAL_DIR)/source/code/include
PAL_TESTUTILS_DIR := $(SCXPAL_DIR)/test/code/testutils

INTERMEDIATE_DIR=$(BASE_DIR)/intermediate/$(BUILD_CONFIGURATION)
TARGET_DIR := $(BASE_DIR)/target/$(BUILD_CONFIGURATION)
PROVIDER_LIBRARY := $(TARGET_DIR)/libmysqlProvider.so
OMI_PREEXEC := $(TARGET_DIR)/omi_preexec
MYAUTH_PROG := $(TARGET_DIR)/mycimprovauth

INSTALLER_TMPDIR := $(TARGET_DIR)/installer_tmp

# Include files

INCLUDE_VERSION := $(TARGET_DIR)/buildversion.h
INCLUDE_DEFINES := $(TARGET_DIR)/defines.h

# Compiler flags

OMI_INCLUDE_FLAGS := -I$(OMI_ROOT)/output/include
PROVIDER_INCLUDE_FLAGS := -I$(PROVIDER_DIR)/support -I$(PAL_INCLUDE_DIR) -I$(TARGET_DIR)

PROVIDER_TEST_INCLUDE_FLAGS := -Wmissing-include-dirs -Wno-non-virtual-dtor -I$(SCXPAL_DIR)/source/code/include -I$(TARGET_DIR) -I$(SCXPAL_DIR)/test/ext/include -I$(OMI_ROOT)/output/include -I$(OMI_ROOT) -I$(OMI_ROOT)/common -I$(SCXPAL_DIR)/test/code/include $(PROVIDER_INCLUDE_FLAGS) -I$(PROVIDER_DIR) -I$(PROVIDER_TEST_SUPPORT_DIR)

ifeq ($(ENABLE_DEBUG),1)
PROV_DEBUG_FLAGS := -g
endif

COMPILE_FLAGS := $(PROV_DEBUG_FLAGS) -D_REENTRANT -fstack-protector-all -Wall -fno-nonansi-builtins  -Woverloaded-virtual -Wformat -Wformat-security -Wcast-align -Wswitch-enum -Wshadow -Wwrite-strings -Wredundant-decls -Werror  -Wcast-qual -fPIC
PROVIDER_COMPILE_FLAGS := $(COMPILE_FLAGS) `mysql_config --cflags`
MYAUTH_COMPILE_FLAGS := $(COMPILE_FLAGS) -I$(PAL_INCLUDE_DIR) -I$(PROVIDER_DIR)/support -I$(TARGET_DIR) `mysql_config --cflags`
PREEXEC_COMPILE_FLAGS := $(COMPILE_FLAGS) -I$(PAL_INCLUDE_DIR) -I$(PROVIDER_DIR)/support -I$(TARGET_DIR) 

LINK_LIBRARIES := -Wl,-rpath=/opt/microsoft/mysql-cimprov/lib -L$(OMI_ROOT)/output/lib -lmicxx -L$(SCXPAL_TARGET_DIR) -lscxcore -lUtil -lscxassertabort -lrt `mysql_config --libs`
MYAUTH_LINK_LIBRARIES := -Wl,-rpath=/opt/microsoft/mysql-cimprov/lib -L$(SCXPAL_TARGET_DIR) -lscxcore -lUtil -lscxassertabort -lrt `mysql_config --libs`
PREEXEC_LINK_LIBRARIES := -L$(SCXPAL_TARGET_DIR) -lscxcore -lUtil -lscxassertabort -lrt
PROVIDER_TEST_LINK_LIBRARIES := -lbase -lpal -L$(SCXPAL_TARGET_DIR) -lscxcore $(SCXPAL_DIR)/test/ext/lib/linux/$(ARCH)/cppunit/libcppunit.a -lpthread -lrt

SHARED_FLAGS := -shared

# Support for installbuilder

STAGING_DIR := $(TARGET_DIR)/staging

# Support for src_to_obj handling

INCLUDES = $(OMI_INCLUDE_FLAGS) $(PROVIDER_INCLUDE_FLAGS)
CFLAGS = $(COMPILE_FLAGS)
CXXFLAGS = $(COMPILE_FLAGS)

#--------------------------------------------------------------------------------
# Build targets

ifeq ($(ULINUX),1)
all : $(OMI_ROOT)/output $(SCXPAL_INTERMEDIATE_DIR) PROVIDER_STATUS $(PROVIDER_LIBRARY) MYAUTH_STATUS $(MYAUTH_PROG) OMI_PREEXEC_STATUS $(OMI_PREEXEC) KIT_STATUS kit
else
all : $(OMI_ROOT)/output $(SCXPAL_INTERMEDIATE_DIR) PROVIDER_STATUS $(PROVIDER_LIBRARY) MYAUTH_STATUS $(MYAUTH_PROG) OMI_PREEXEC_STATUS $(OMI_PREEXEC)
endif

clean :
	$(RMDIR) $(BASE_DIR)/build/cppunit_result.* $(BASE_DIR)/build/scxtestrunner.log $(BASE_DIR)/installer/intermediate $(BASE_DIR)/intermediate $(BASE_DIR)/target $(PROVIDER_TEST_DIR)/providertestutils.cpp
	-find $(BASE_DIR) -name \*~ -exec rm {} \;

distclean : clean
	$(RM) $(BASE_DIR)/build/config.mak
	-make -C $(OMI_ROOT) distclean
	-make -C $(SCXPAL_DIR)/build distclean
	-$(RMDIR) $(OMI_ROOT)/output*
	-$(RM) $(SCXPAL_DIR)/build/config.mak
	-$(RM) $(SCXPAL_DIR)/build/Makefile.config_cache

# Install the OMI provider for test purposes
# This assumes that:
#   1) OMI already has registration files for libmysqlProvider.so

install : /opt/microsoft/omi/lib/libmysqlProvider.so
	@[ -e $(TARGET_DIR)/tmp_start_omi  ] && rm $(TARGET_DIR)/tmp_start_omi  && sudo /etc/init.d/omiserverd start || exit 0

/opt/microsoft/omi/lib/libmysqlProvider.so : $(PROVIDER_LIBRARY)
	@echo "========================= Performing Installing OMI provider"
	-sudo /etc/init.d/omiserverd stop
	touch $(TARGET_DIR)/tmp_start_omi
	sudo cp -v $(PROVIDER_LIBRARY) /opt/microsoft/omi/lib/

restart :
	@-sudo /etc/init.d/omiserverd stop
	@sudo /etc/init.d/omiserverd start


PROVIDER_STATUS:
	@echo "========================= Performing Building provider"

MYAUTH_STATUS:
	@echo "========================= Performing Building mycimprovauth executable"

OMI_PREEXEC_STATUS:
	@echo "========================= Performing Building OMI preexec executable"

KIT_STATUS:
	@echo "========================= Performing Building provider tests"

#--------------------------------------------------------------------------------
# OMI build
#
# Build the OMI distribution
#
# Technically, we should go to build OMI all the time. But I'd rather not spend
# the time doing it here EVERY TIME, when we never normally change OMI. This is
# a good tradeoff (build if not built, otherwise assume all is well).
#
# Doing a 'make clean' in OMI directory will force us to rebuild.

$(OMI_ROOT)/output : $(OMI_ROOT)/output/lib/libmicxx.so

$(OMI_ROOT)/output/lib/libmicxx.so :
	@echo "========================= Performing Building OMI"
	make -C $(OMI_ROOT)
ifeq ($(PERFORM_OMI_MAKEINSTALL),1)
	make -C $(OMI_ROOT) install
endif

#--------------------------------------------------------------------------------
# PAL build
#
# Build the PAL (Platform Abstraction Layer)
#
# Doing a 'make clean' in PAL directory will force us to rebuild.

$(SCXPAL_INTERMEDIATE_DIR) :
	@echo "========================= Performing Building PAL"
	make -C $(SCXPAL_DIR)/build

#--------------------------------------------------------------------------------
# Version information header file
#
# Build the version header file

$(INCLUDE_VERSION) : $(BASE_DIR)/build/Makefile.version
	-$(MKPATH) $(@D)
	@$(ECHO) "Creating $@" 
	@$(call pf_fwrite,"/*------------------------------------------------------------------------------",  $@)
	@$(call pf_fappend,"    Copyright (C) 2007-2014 Microsoft Corp.                                     ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"*/                                                                              ", $@)
	@$(call pf_fappend,"/**                                                                             ", $@)
	@$(call pf_fappend,"    \file                                                                       ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"    \brief       Auto generated file containing build version information       ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"    \author      Automated Build System                                         ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"    DO NOT EDIT THIS FILE!                                                      ", $@)
	@$(call pf_fappend,"    DO NOT CHECK IN THIS FILE!                                                  ", $@)
	@$(call pf_fappend,"*/                                                                              ", $@)
	@$(call pf_fappend,"/*----------------------------------------------------------------------------*/", $@)
	@$(call pf_fappend,"#ifndef BUILDVERSION_H                                                          ", $@)
	@$(call pf_fappend,"#define BUILDVERSION_H                                                          ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"#include <string>                                                               ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"/** Major version number */                                                     ", $@)
	@$(call pf_fappend,"const int CIMPROV_BUILDVERSION_MAJOR = $(SCX_BUILDVERSION_MAJOR);               ", $@)
	@$(call pf_fappend,"/** Minor version number */                                                     ", $@)
	@$(call pf_fappend,"const int CIMPROV_BUILDVERSION_MINOR = $(SCX_BUILDVERSION_MINOR);               ", $@)
	@$(call pf_fappend,"/** Patch version number */                                                     ", $@)
	@$(call pf_fappend,"const int CIMPROV_BUILDVERSION_PATCH = $(SCX_BUILDVERSION_PATCH);               ", $@)
	@$(call pf_fappend,"/** Build number */                                                             ", $@)
	@$(call pf_fappend,"const int CIMPROV_BUILDVERSION_BUILDNR = $(SCX_BUILDVERSION_BUILDNR);           ", $@)
	@$(call pf_fappend,"/** Build date */                                                               ", $@)
	@$(call pf_fappend,"const std::wstring CIMPROV_BUILDVERSION_DATE(L\"$(SCX_BUILDVERSION_DATE)\");    ", $@)
	@$(call pf_fappend,"/** Build status */                                                             ", $@)
	@$(call pf_fappend,"const std::wstring CIMPROV_BUILDVERSION_STATUS(L\"$(SCX_BUILDVERSION_STATUS)\");  ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"#endif /* BUILDVERSION_H */                                                     ", $@)
	@$(call pf_fappend,"/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/", $@)

#================================================================================
# File depends.h (compiler dependencies)
#================================================================================

$(INCLUDE_DEFINES) : $(BASE_DIR)/build/config.mak
	-$(MKPATH) $(@D)
	@$(ECHO) "Creating $@" 
	@$(call pf_fwrite,"/*------------------------------------------------------------------------------",  $@)
	@$(call pf_fappend,"    Copyright (C) 2007 Microsoft Corp.                                          ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"*/                                                                              ", $@)
	@$(call pf_fappend,"/**                                                                             ", $@)
	@$(call pf_fappend,"    \file                                                                       ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"    \brief       Auto generated file containing build definitions               ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"    \author      Automated Build System                                         ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"    DO NOT EDIT THIS FILE!                                                      ", $@)
	@$(call pf_fappend,"    DO NOT CHECK IN THIS FILE!                                                  ", $@)
	@$(call pf_fappend,"*/                                                                              ", $@)
	@$(call pf_fappend,"/*----------------------------------------------------------------------------*/", $@)
	@$(call pf_fappend,"#ifndef DEFINES_H                                                               ", $@)
	@$(call pf_fappend,"#define DEFINES_H                                                               ", $@)
	@$(call pf_fappend,"                                                                                ", $@)
ifneq ($(PF_DISTRO),)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"#ifndef PF_DISTRO_$(PF_DISTRO)                                                  ", $@)
	@$(call pf_fappend,"#define PF_DISTRO_$(PF_DISTRO)                                                  ", $@)
	@$(call pf_fappend,"#endif                                                                          ", $@)
endif
ifneq ($(PF_MAJOR),)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"#ifndef PF_MAJOR                                                                 ", $@)
	@$(call pf_fappend,"#define PF_MAJOR $(PF_MAJOR)                                                    ", $@)
	@$(call pf_fappend,"#endif                                                                          ", $@)
endif
ifneq ($(PF_MINOR),)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"#ifndef PF_MINOR                                                                 ", $@)
	@$(call pf_fappend,"#define PF_MINOR $(PF_MINOR)                                                    ", $@)
	@$(call pf_fappend,"#endif                                                                          ", $@)
endif
ifneq ($(ARCH),)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"#ifndef $(ARCH)                                                                 ", $@)
	@$(call pf_fappend,"#define $(ARCH)                                                                 ", $@)
	@$(call pf_fappend,"#endif                                                                          ", $@)
endif
ifeq ($(BUILD_TYPE),Debug)
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"#ifndef _DEBUG                                                                  ", $@)
	@$(call pf_fappend,"#define _DEBUG                                                                  ", $@)
	@$(call pf_fappend,"#endif                                                                          ", $@)
else
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"#ifndef NDEBUG                                                                  ", $@)
	@$(call pf_fappend,"#define NDEBUG                                                                  ", $@)
	@$(call pf_fappend,"#endif                                                                          ", $@)
endif
	@$(call pf_fappend,"                                                                                ", $@)
	@$(call pf_fappend,"#endif /* DEFINES_H */                                                          ", $@)
	@$(call pf_fappend,"/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/", $@)

#================================================================================
# Internal functions
#================================================================================

# Convert a list of src files with absolute paths under BASE_DIR to corresponding
# object files under intermediate directory 
# src_to_obj(list_of_cppfiles)
src_to_obj = $(patsubst $(BASE_DIR)%, $(INTERMEDIATE_DIR)%, $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(1))))

# No default rules, please
.SUFFIX: 

# Rule for compiling cpp files in source tree, ouptut in mirrored intermediate dir
$(INTERMEDIATE_DIR)/%.o : $(BASE_DIR)/%.cpp  $(INCLUDE_DEFINES) $(INCLUDE_VERSION)
	$(MKPATH) $(@D)
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -I$(<D) -o $@ $<

$(INTERMEDIATE_DIR)/%.o : $(BASE_DIR)/%.c $(INCLUDE_DEFINES) $(INCLUDE_VERSION)
	$(MKPATH) $(@D)
	$(CXX) -c $(CFLAGS) $(INCLUDES) -I$(<D) -o $@ $<

#--------------------------------------------------------------------------------
# MySQL Provider
#
# Build the Provider Library 

STATIC_PROVIDERLIB_SRCFILES = \
	$(PROVIDER_DIR)/MySQL_Server_Class_Provider.cpp \
	$(PROVIDER_DIR)/MySQL_ServerStatistics_Class_Provider.cpp \
	$(PROVIDER_DIR)/MySQL_Server_Database_Class_Provider.cpp

STATIC_PROVIDERLIB_SRCFILES += \
	$(PROVIDER_DIR)/module.cpp \
	$(PROVIDER_DIR)/schema.c \
	$(PROVIDER_DIR)/stubs.cpp

STATIC_PROVIDERLIB_SRCFILES += \
	$(PROVIDER_DIR)/support/logstartup.cpp \
	$(PROVIDER_DIR)/support/mycnf-paths.cpp \
	$(PROVIDER_DIR)/support/productdependencies.cpp \
	$(PROVIDER_DIR)/support/sqlauth.cpp \
	$(PROVIDER_DIR)/support/sqlbinding.cpp

STATIC_PROVIDERLIB_LOGPOLICY += \
	$(PROVIDER_DIR)/support/logpolicy.cpp

PROVIDER_HEADERS = \
	$(PROVIDER_DIR)/support/logstartup.h \
	$(PROVIDER_DIR)/support/sqlauth.h \
	$(PROVIDER_DIR)/support/sqlbinding.h

STATIC_PROVIDERLIB_OBJFILES = $(call src_to_obj,$(STATIC_PROVIDERLIB_SRCFILES))

$(PROVIDER_LIBRARY): INCLUDES += $(PROVIDER_INCLUDE_FLAGS)
$(PROVIDER_LIBRARY): CFLAGS += $(PROVIDER_COMPILE_FLAGS)
$(PROVIDER_LIBRARY): CXXFLAGS += $(PROVIDER_COMPILE_FLAGS)
$(PROVIDER_LIBRARY): $(STATIC_PROVIDERLIB_OBJFILES) $(STATIC_PROVIDERLIB_LOGPOLICY) $(INCLUDE_DEFINES) $(INCLUDE_VERSION) $(PROVIDER_HEADERS)
	$(MKPATH) $(INTERMEDIATE_DIR)
	$(MKPATH) $(TARGET_DIR)
	g++ $(PROVIDER_COMPILE_FLAGS) $(SHARED_FLAGS) $(PROVIDER_INCLUDE_FLAGS) -o $@ $(STATIC_PROVIDERLIB_OBJFILES) $(STATIC_PROVIDERLIB_LOGPOLICY) $(LINK_LIBRARIES)

#--------------------------------------------------------------------------------
# MySQL mycimprovauth executable
#
# Build the mycimprovauth executable (authentication file maintenance)

STATIC_MYAUTH_SRCFILES = \
	$(PROVIDER_DIR)/support/logstartup.cpp \
	$(PROVIDER_DIR)/support/productdependencies.cpp \
	$(PROVIDER_DIR)/support/sqlauth.cpp \
	$(PROVIDER_DIR)/support/sqlbinding.cpp \
	$(PROVIDER_DIR)/support/mycnf-paths.cpp \
	$(SOURCE_DIR)/myauth/myauth.cpp

STATIC_MYAUTH_HEADERS = \
	$(PROVIDER_DIR)/support/sqlauth.h

STATIC_MYAUTH_OBJFILES = $(call src_to_obj,$(STATIC_MYAUTH_SRCFILES))

$(MYAUTH_PROG): CFLAGS += $(MYAUTH_COMPILE_FLAGS)
$(MYAUTH_PROG): CXXFLAGS += $(MYAUTH_COMPILE_FLAGS)
$(MYAUTH_PROG): $(STATIC_MYAUTH_OBJFILES) $(STATIC_MYAUTH_HEADERS) $(INCLUDE_DEFINES) $(INCLUDE_VERSION)
	$(MKPATH) $(INTERMEDIATE_DIR)
	$(MKPATH) $(TARGET_DIR)
	g++ $(MYAUTH_COMPILE_FLAGS) -o $@ $(STATIC_MYAUTH_OBJFILES) $(STATIC_PROVIDERLIB_LOGPOLICY) $(MYAUTH_LINK_LIBRARIES)

#--------------------------------------------------------------------------------
# MySQL OMI_PREEXEC
#
# Build the omi_preexec executable (for PAL logging and state information)

STATIC_OMI_PREEXEC_SRCFILES = \
	$(PROVIDER_DIR)/support/logstartup.cpp \
	$(PROVIDER_DIR)/support/mycnf-paths.cpp \
	$(PROVIDER_DIR)/support/productdependencies.cpp \
	$(PROVIDER_DIR)/support/sqlauth.cpp \
	$(SOURCE_DIR)/omi_preexec/omi-mysql.cpp \
	$(SOURCE_DIR)/omi_preexec/omi-preexec.cpp

STATIC_OMI_PREEXEC_HEADERS = \
	$(PROVIDER_DIR)/support/mycnf-paths.h \
	$(SOURCE_DIR)/omi_preexec/omi-preexec.h

STATIC_OMI_PREEXEC_OBJFILES = $(call src_to_obj,$(STATIC_OMI_PREEXEC_SRCFILES))

$(OMI_PREEXEC): CFLAGS += $(PREEXEC_COMPILE_FLAGS)
$(OMI_PREEXEC): CXXFLAGS += $(PREEXEC_COMPILE_FLAGS)
$(OMI_PREEXEC): $(STATIC_OMI_PREEXEC_OBJFILES) $(STATIC_OMI_PREEXEC_HEADERS) $(INCLUDE_DEFINES) $(INCLUDE_VERSION)
	$(MKPATH) $(INTERMEDIATE_DIR)
	$(MKPATH) $(TARGET_DIR)
	g++ $(PREEXEC_COMPILE_FLAGS) -o $@ $(STATIC_OMI_PREEXEC_OBJFILES) $(STATIC_PROVIDERLIB_LOGPOLICY) $(PREEXEC_LINK_LIBRARIES)

#--------------------------------------------------------------------------------
# MySQL Provider Unit Tests
#
# Build and run the Provider Unit Tests

# For now, providertestutils.cpp lives in PAL, but is built in OM.  This creates
# some build issues.  To resolve, create a link to the real file.

$(PROVIDER_TEST_DIR)/providertestutils.cpp: $(PAL_TESTUTILS_DIR)/providertestutils.cpp
# We need to recreate the symlink if the link is older than what it points to.
	$(RM) $(PROVIDER_TEST_DIR)/providers/providertestutils.cpp
	ln -s $(PAL_TESTUTILS_DIR)/providertestutils.cpp $(PROVIDER_TEST_DIR)/providertestutils.cpp

STATIC_PROVIDER_UNITFILES_INCLUDE = \
	$(PROVIDER_TEST_SUPPORT_DIR)/sqlcredentials.h

STATIC_PROVIDER_UNITFILES = \
	$(PROVIDER_TEST_DIR)/auth_test.cpp \
	$(PROVIDER_TEST_DIR)/binding_test.cpp \
	$(PROVIDER_TEST_DIR)/sqlserver_test.cpp \
	$(PROVIDER_TEST_DIR)/sqlstats_test.cpp \
	$(PROVIDER_TEST_DIR)/sqldatabase_test.cpp \
	$(PROVIDER_TEST_DIR)/support/testrunnerlogpolicy.cpp \
	$(TEST_DIR)/myauth/myauth_test.cpp \
	$(PROVIDER_TEST_DIR)/providertestutils.cpp

STATIC_PROVIDER_PAL_UNITFILES = \
	$(PAL_TESTUTILS_DIR)/scxassert_cppunit.cpp \
	$(PAL_TESTUTILS_DIR)/testrunner.cpp

STATIC_PROVIDER_TEST_OBJFILES = $(call src_to_obj,$(STATIC_PROVIDER_UNITFILES))

$(TARGET_DIR)/testrunner: INCLUDES += $(PROVIDER_TEST_INCLUDE_FLAGS) -I$(PAL_INCLUDE_DIR) -I$(PAL_TESTUTILS_DIR)
$(TARGET_DIR)/testrunner: CFLAGS += $(PROVIDER_COMPILE_FLAGS)
$(TARGET_DIR)/testrunner: CXXFLAGS += $(PROVIDER_COMPILE_FLAGS)
$(TARGET_DIR)/testrunner : $(STATIC_PROVIDER_UNITFILES_INCLUDE) $(STATIC_PROVIDER_TEST_OBJFILES) $(STATIC_PROVIDERLIB_OBJFILES) $(INCLUDE_DEFINES) $(INCLUDE_VERSION) $(PROVIDER_HEADERS) $(MYAUTH_PROG)
	$(MKPATH) $(INTERMEDIATE_DIR)
	$(MKPATH) $(TARGET_DIR)
	g++ $(PROVIDER_COMPILE_FLAGS) $(PROVIDER_TEST_INCLUDE_FLAGS) -o $@ $(STATIC_PROVIDER_PAL_UNITFILES) $(STATIC_PROVIDER_TEST_OBJFILES) $(STATIC_PROVIDERLIB_OBJFILES) $(LINK_LIBRARIES) $(PROVIDER_TEST_LINK_LIBRARIES)

testrun : test

TEST_STATUS:
	@echo "========================= Performing Building provider tests"

test : TEST_STATUS $(SCXPAL_INTERMEDIATE_DIR) $(TARGET_DIR)/testrunner
	@echo "========================= Performing MySQL testrun execution"
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(OMI_ROOT)/output/lib; cd $(TARGET_DIR); ./testrunner

#--------------------------------------------------------------------------------
# Build the distribution kit
#
# Build the packages via installbuilder
#
# While the "formal build" only builds ULINUX, we may build something else for DEV purposes.
# Assume we ALWAYS build RPM, but only build DPKG if --enable-ulinux is speified in configure.

kit : MYSQLLIB_FULLFILENAME = $(shell ldd $(PROVIDER_LIBRARY) | grep libmysqlclient.so | awk '{print $$3}')
kit : MYSQLLIB_FILENAME = $(shell basename $(MYSQLLIB_FULLFILENAME))
kit : $(OMI_ROOT)/output $(PROVIDER_LIBRARY) $(MYAUTH_PROG) $(OMI_PREEXEC)
ifeq ($(ULINUX),1)

	@echo "========================= Performing Building RPM and DPKG packages"
	$(MKPATH) $(INSTALLER_TMPDIR)
	sudo $(RMDIR) $(STAGING_DIR)
	$(MKPATH) $(TARGET_DIR)
	python $(SCXPAL_DIR)/installer/InstallBuilder/installbuilder.py \
		--BASE_DIR=$(BASE_DIR) \
		--TARGET_DIR=$(TARGET_DIR) \
		--INTERMEDIATE_DIR=$(INSTALLER_TMPDIR) \
		--STAGING_DIR=$(STAGING_DIR) \
		--BUILD_TYPE=$(BUILD_TYPE) \
		--BUILD_CONFIGURATION=$(BUILD_CONFIGURATION) \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=$(PF_DISTRO) \
		--PFMAJOR=$(PF_MAJOR) \
		--PFMINOR=$(PF_MINOR) \
		--VERSION=$(SCX_BUILDVERSION_MAJOR).$(SCX_BUILDVERSION_MINOR).$(SCX_BUILDVERSION_PATCH) \
		--RELEASE=$(SCX_BUILDVERSION_BUILDNR) \
		--MYSQL_BUILD_LIBRARY=$(MYSQLLIB_FILENAME) \
		--DATAFILE_PATH=$(BASE_DIR)/installer/datafiles \
		base_mysql.data linux.data linux_rpm.data

	# The kit has a name including .universalr., and the 'r' is only desired for OM
	sed -e 's/\.universalr\./.universal./' $(TARGET_DIR)/package_filename > $(TARGET_DIR)/package_file.tmp
	mv $(TARGET_DIR)/`cat $(TARGET_DIR)/package_filename` $(TARGET_DIR)/`cat $(TARGET_DIR)/package_file.tmp`
	mv $(TARGET_DIR)/package_file.tmp $(TARGET_DIR)/package_filename

	sudo $(RMDIR) $(STAGING_DIR)
	$(MKPATH) $(TARGET_DIR)
	python $(SCXPAL_DIR)/installer/InstallBuilder/installbuilder.py \
		--BASE_DIR=$(BASE_DIR) \
		--TARGET_DIR=$(TARGET_DIR) \
		--INTERMEDIATE_DIR=$(INSTALLER_TMPDIR) \
		--STAGING_DIR=$(STAGING_DIR) \
		--BUILD_TYPE=$(BUILD_TYPE) \
		--BUILD_CONFIGURATION=$(BUILD_CONFIGURATION) \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=$(PF_DISTRO) \
		--PFMAJOR=$(PF_MAJOR) \
		--PFMINOR=$(PF_MINOR) \
		--VERSION=$(SCX_BUILDVERSION_MAJOR).$(SCX_BUILDVERSION_MINOR).$(SCX_BUILDVERSION_PATCH) \
		--RELEASE=$(SCX_BUILDVERSION_BUILDNR) \
		--MYSQL_BUILD_LIBRARY=$(MYSQLLIB_FILENAME) \
		--DPKG_LOCATION=$(SCXPAL_DIR)/installer/InstallBuilder/tools/bin/dpkg-deb-$(PF_ARCH) \
		--DATAFILE_PATH=$(BASE_DIR)/installer/datafiles \
		base_mysql.data linux.data linux_dpkg.data

	# The kit has a name including .universald., and the 'd' is only desired for OM
	sed -e 's/\.universald\./.universal./' $(TARGET_DIR)/package_filename > $(TARGET_DIR)/package_file.tmp
	mv $(TARGET_DIR)/`cat $(TARGET_DIR)/package_filename` $(TARGET_DIR)/`cat $(TARGET_DIR)/package_file.tmp`
	mv $(TARGET_DIR)/package_file.tmp $(TARGET_DIR)/package_filename

	# Strip the package extension from the package filename
	sed -re 's/.rpm$$|.deb$$//' $(TARGET_DIR)/package_filename > $(TARGET_DIR)/package_file.tmp
	mv $(TARGET_DIR)/package_file.tmp $(TARGET_DIR)/package_filename

	# The MP needs architecture of i686 (for x86) and x86_64 (for x64).
	sed -e 's/\.x86$$/\.i686/' $(TARGET_DIR)/package_filename | sed 's/\.x64$$/.x86_64/' > $(TARGET_DIR)/package_file.tmp
	mv $(TARGET_DIR)/`cat $(TARGET_DIR)/package_filename`.rpm $(TARGET_DIR)/`cat $(TARGET_DIR)/package_file.tmp`.rpm
	mv $(TARGET_DIR)/`cat $(TARGET_DIR)/package_filename`.deb $(TARGET_DIR)/`cat $(TARGET_DIR)/package_file.tmp`.deb
	mv $(TARGET_DIR)/package_file.tmp $(TARGET_DIR)/package_filename

	# Build the tar file containing both .rpm and .deb packages
	cd $(TARGET_DIR); tar cvf `cat $(TARGET_DIR)/package_filename`.tar `cat $(TARGET_DIR)/package_filename`.rpm `cat $(TARGET_DIR)/package_filename`.deb

else

	@echo "========================= Performing Building RPM and DPKG packages"
	$(MKPATH) $(INSTALLER_TMPDIR)
	sudo $(RMDIR) $(STAGING_DIR)
	python $(SCXPAL_DIR)/installer/InstallBuilder/installbuilder.py \
		--BASE_DIR=$(BASE_DIR) \
		--TARGET_DIR=$(TARGET_DIR) \
		--INTERMEDIATE_DIR=$(INSTALLER_TMPDIR) \
		--STAGING_DIR=$(STAGING_DIR) \
		--BUILD_TYPE=$(BUILD_TYPE) \
		--BUILD_CONFIGURATION=$(BUILD_CONFIGURATION) \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=$(PF_DISTRO) \
		--PFMAJOR=$(PF_MAJOR) \
		--PFMINOR=$(PF_MINOR) \
		--VERSION=$(SCX_BUILDVERSION_MAJOR).$(SCX_BUILDVERSION_MINOR).$(SCX_BUILDVERSION_PATCH) \
		--RELEASE=$(SCX_BUILDVERSION_BUILDNR) \
		--MYSQL_BUILD_LIBRARY=$(MYSQLLIB_FILENAME) \
		--DATAFILE_PATH=$(BASE_DIR)/installer/datafiles \
		base_mysql.data linux.data linux_rpm.data

	# Strip the package extension from the package filename
	sed -re 's/.rpm$$|.deb$$//' $(TARGET_DIR)/package_filename > $(TARGET_DIR)/package_file.tmp
	mv $(TARGET_DIR)/package_file.tmp $(TARGET_DIR)/package_filename

	# The MP needs architecture of i686 (for x86) and x86_64 (for x64).
	sed -e 's/\.x86$$/\.i686/' $(TARGET_DIR)/package_filename | sed 's/\.x64$$/.x86_64/' > $(TARGET_DIR)/package_file.tmp
	mv $(TARGET_DIR)/`cat $(TARGET_DIR)/package_filename`.rpm $(TARGET_DIR)/`cat $(TARGET_DIR)/package_file.tmp`.rpm
	mv $(TARGET_DIR)/package_file.tmp $(TARGET_DIR)/package_filename

	# Build the tar file containing the .rpm package
	cd $(TARGET_DIR); tar cvf `cat $(TARGET_DIR)/package_filename`.tar `cat $(TARGET_DIR)/package_filename`.rpm

endif

	../installer/bundle/create_bundle.sh $(PF)_$(PF_DISTRO) \
                                             $(TARGET_DIR) \
                                             `cat $(TARGET_DIR)/package_filename`
	rm $(TARGET_DIR)/package_filename

#
# The following is all for OMI "bootstrap" stuff (allowing omigen and omireg to run)
#

ifeq ($(PERFORM_OMI_MAKEINSTALL),1)

CLASSES = \
	MySQL_Server \
	MySQL_ServerStatistics \
	MySQL_Server_Database

OMI_DIR = $(OMI_ROOT)/output/install_local
OMI_BINDIR = $(OMI_DIR)/bin
OMI_LIBDIR = $(OMI_DIR)/lib
OMIGEN = $(OMI_BINDIR)/omigen

MOF_DIR = $(SOURCE_DIR)/mof

# For these targets to run, configure MUST be run with the --enable-omi-tools qualifier, like this:
#   ./configure --enable-debug --enable-omi-tools

schema_gen :
	# The omigen facility is unhappy if no ~/.omigenrc file exists, so create one for this run
	touch ~/.omigenrc
	$(MKPATH) $(TARGET_DIR)/omi
	cd $(TARGET_DIR)/omi; $(OMIGEN) $(MOF_DIR)/mysql.mof -d $(PROVIDER_DIR) $(CLASSES) --cpp -I $(OMI_DIR)/share/omischema
	$(RM) ~/.omigenrc

omi_reg :
	$(MKPATH) $(TARGET_DIR)/omi
	$(MKPATH) $(OMI_DIR)/etc/omiregister/root-mysql
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(OMI_LIBDIR); cd $(TARGET_DIR)/omi; $(OMI_BINDIR)/omireg -n root/mysql -o @requestor@ $(PROVIDER_LIBRARY)
	cp -r $(OMI_DIR)/etc/omiregister/root-mysql $(TARGET_DIR)/omi

endif # $(PERFORM_OMI_MAKEINSTALL),1
