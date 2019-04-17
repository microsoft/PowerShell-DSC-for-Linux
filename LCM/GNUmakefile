TOP = .

include $(TOP)/config.mak

DIRECTORIES = omiutils
DIRECTORIES += codec/mof
DIRECTORIES += codec/mof/parser
DIRECTORIES += json_parson
DIRECTORIES += dsc/engine/EngineHelper
DIRECTORIES += dsc/engine/ca/CAInfrastructure
DIRECTORIES += dsc/engine/ca/CALogInfrastructure
DIRECTORIES += dsc/engine/ConfigurationManager
DIRECTORIES += dsc/engine/ModuleLoader/ModuleLibrary
DIRECTORIES += dsc/engine/lcm
DIRECTORIES += dsc/engine/ConsistencyInvoker
DIRECTORIES += dsc/engine/dsc_library
DIRECTORIES += dsc/engine/dsc_host

include $(OMI)/mak/rules.mak

deploydsc:
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc/configuration
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc/configuration/schema
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc/configuration/schema/MSFT_LogResource
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc/configuration/baseregistration
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc/configuration/registration
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc/configuration/registration/MSFT_LogResource
	mkdir -p $(CONFIG_SYSCONFDIR)/dsc/configuration/BuiltinProvCache
	mkdir -p $(CONFIG_DATADIR)/dsc
	mkdir -p $(CONFIG_DATADIR)/dsc/configuration
	mkdir -p $(CONFIG_DATADIR)/dsc/configuration/schema
	mkdir -p $(CONFIG_DATADIR)/dsc/configuration/registration
	cp  -r $(TOP)/dsc/mof/OMI_BaseResourceUE.mof $(CONFIG_SYSCONFDIR)/dsc/configuration/baseregistration/baseresource.schema.mof
	cp  -r $(TOP)/dsc/mof/MSFT_DSCMetaConfiguration.mof $(CONFIG_SYSCONFDIR)/dsc/configuration/baseregistration/MSFT_DSCMetaConfiguration.mof
	cp  -r $(TOP)/dsc/mof/MSFT_LogResource.schema.mof $(CONFIG_SYSCONFDIR)/dsc/configuration/schema/MSFT_LogResource
	cp  -r $(TOP)/dsc/mof/MSFT_LogResource.registration.mof $(CONFIG_SYSCONFDIR)/dsc/configuration/registration/MSFT_LogResource
	cp  $(TOP)/../Providers/Extras/Scripts/base_dsc.conf $(CONFIG_SYSCONFDIR)/dsc/dsc.conf
	test -L $(OMI) || cp $(BINDIR)/ConsistencyInvoker $(CONFIG_BINDIR)/
	cp $(BINDIR)/ConsistencyInvoker $(CONFIG_BINDIR)/
	$(CONFIG_BINDIR)/omireg -n "root/Microsoft/DesiredStateConfiguration" $(LIBDIR)/libdsccore.so
	ln -fs $(CONFIG_SYSCONFDIR)/omiregister/root-Microsoft-DesiredStateConfiguration $(CONFIG_SYSCONFDIR)/omiregister/root-Microsoft-Windows-DesiredStateConfiguration
