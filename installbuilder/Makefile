TOP := $(shell cd ..; pwd)

include $(TOP)/build/Makefile.version

OUTPUT_DIR := $(TOP)/output
STAGING_DIR := $(OUTPUT_DIR)/staging
INTERMEDIATE_DIR := $(OUTPUT_DIR)/intermediate
RELEASE_DIR := $(OUTPUT_DIR)/release

IB_DIR := $(shell cd ../../pal/installer/InstallBuilder; pwd)
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),x86_64)
 PF_ARCH := x64
else
 PF_ARCH := x86
endif
CONFIG_VERSION := 1.0.0

all:
ifeq ($(BUILD_RPM),1)
	@echo "========================= Make DSC installer"
	sudo rm -rf $(STAGING_DIR) $(INTERMEDIATE_DIR) 
	mkdir -p $(RELEASE_DIR) $(STAGING_DIR) $(INTERMEDIATE_DIR)
	python $(IB_DIR)/installbuilder.py \
		--BASE_DIR=$(TOP) \
		--TARGET_DIR=$(RELEASE_DIR) \
		--INTERMEDIATE_DIR=$(INTERMEDIATE_DIR) \
		--STAGING_DIR=$(STAGING_DIR) \
		--PACKAGE_TYPE=RPM \
		--PF=Linux \
		--PFMAJOR=1 \
		--PFMINOR=0 \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=ULINUX \
		--VERSION=$(CONFIG_VERSION) \
		--RELEASE=$(SCX_BUILDVERSION_BUILDNR) \
		--OUTPUTFILE=dsc-$(CONFIG_VERSION)-$(SCX_BUILDVERSION_BUILDNR).ssl_$(SSL_VERSION).$(PF_ARCH) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		Base_DSC.data
endif
ifeq ($(BUILD_DPKG),1)
	@echo "========================= Make DSC installer"
	sudo rm -rf $(STAGING_DIR) $(INTERMEDIATE_DIR) 
	mkdir -p $(RELEASE_DIR) $(STAGING_DIR) $(INTERMEDIATE_DIR)
	python $(IB_DIR)/installbuilder.py \
		--BASE_DIR=$(TOP) \
		--TARGET_DIR=$(RELEASE_DIR) \
		--INTERMEDIATE_DIR=$(INTERMEDIATE_DIR) \
		--STAGING_DIR=$(STAGING_DIR) \
		--PACKAGE_TYPE=DPKG \
		--PF=Linux \
		--PFMAJOR=1 \
		--PFMINOR=0 \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=ULINUX \
		--VERSION=$(CONFIG_VERSION) \
		--RELEASE=$(SCX_BUILDVERSION_BUILDNR) \
		--OUTPUTFILE=dsc-$(CONFIG_VERSION)-$(SCX_BUILDVERSION_BUILDNR).ssl_$(SSL_VERSION).$(PF_ARCH) \
		--DPKG_LOCATION=$(IB_DIR)/tools/bin/dpkg-deb-$(PF_ARCH) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		Base_DSC.data
endif
