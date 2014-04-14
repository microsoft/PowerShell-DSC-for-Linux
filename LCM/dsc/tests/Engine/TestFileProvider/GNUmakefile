TESTTOP = ../..

DSCTOP = ../../..

TOP = ../../../..


include $(TOP)/config.mak

CXXUNITTEST = NITSDSCFileTestProvider


SOURCES= \
        module.c \
        schema.c \
        FileImp.c \
        MSFT_FileDirectoryConfiguration.c \

INCLUDES= \
	$(OMI) \
	$(OMI)/nits/base \
        $(DSCTOP)/engine/EngineHelper \
	$(OMI)/common \
	$(OMI)/common/inc \

DEFINES= TEST_BUILD

LIBRARIES = mi pal 

include $(OMI)/mak/rules.mak


regtest:
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc/configuration/registration/MSFT_FileDirectoryConfiguration
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc/configuration/schema/MSFT_FileDirectoryConfiguration
	cp -r $(TOP)/dsc/tests/Engine/TestFileProvider/MSFT_FileDirectoryConfiguration.schema.mof $(CONFIG_SYSCONFDIR)/dsc/configuration/schema/MSFT_FileDirectoryConfiguration
	cp -r $(TOP)/dsc/tests/Engine/TestFileProvider/MSFT_FileDirectoryConfiguration.registration.mof $(CONFIG_SYSCONFDIR)/dsc/configuration/registration/MSFT_FileDirectoryConfiguration
	$(BINDIR)/omireg -n dsc $(TARGET)


