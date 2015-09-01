include config.mak
-include omi-1.0.8/output/config.mak
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),x86_64)
 PF_ARCH := x64
else
 PF_ARCH := x86
endif

all:
	mkdir -p intermediate/Scripts
ifeq ($(BUILD_LOCAL),1)
	make local
else
	cd ../pal/build; ./configure
	for f in Providers/Scripts/InstalledScripts/*.py; do \
	  cat $$f | \
	  sed "s@<CONFIG_BINDIR>@/opt/omi/bin@" | \
	  sed "s@<CONFIG_LIBDIR>@/opt/omi/lib@" | \
	  sed "s@<CONFIG_SYSCONFDIR>@/etc/opt/omi/conf@" | \
	  sed "s@<DSC_PATH>@/opt/microsoft/dsc@" > intermediate/Scripts/`basename $$f`; \
	  chmod a+x intermediate/Scripts/`basename $$f`; \
	done
 ifeq ($(BUILD_SSL_098),1)
	rm -rf omi-1.0.8/output_openssl_0.9.8/lib/libdsccore.so
	make kit098 
 endif
 ifeq ($(BUILD_SSL_100),1)
	rm -rf omi-1.0.8/output_openssl_1.0.0/lib/libdsccore.so
	make kit100 
 endif
	make nxNetworking
	make nxComputerManagement
	mkdir -p release; \
	rm -rf release/*.{rpm,deb}; \
	mv omi-1.0.8/output_openssl_0.9.8/release/*.{rpm,deb} omi-1.0.8/output_openssl_1.0.0/release/*.{rpm,deb} output/release/*.{rpm,deb} release/
endif

kit098: omi098 dsc098

kit100: omi100 dsc100

dsc098: lcm098 providers
	make -C installbuilder SSL_VERSION=098 BUILD_RPM=$(BUILD_RPM) BUILD_DPKG=$(BUILD_DPKG)

dsc100: lcm100 providers
	make -C installbuilder SSL_VERSION=100 BUILD_RPM=$(BUILD_RPM) BUILD_DPKG=$(BUILD_DPKG)

omi098:
	make configureomi098
	rm -rf omi-1.0.8/output
	ln -s output_openssl_0.9.8 omi-1.0.8/output
	make -C omi-1.0.8
	make -C omi-1.0.8/installbuilder SSL_VERSION=098 BUILD_RPM=$(BUILD_RPM) BUILD_DPKG=$(BUILD_DPKG)

omi100:
	make configureomi100
	rm -rf omi-1.0.8/output
	ln -s output_openssl_1.0.0 omi-1.0.8/output
	make -C omi-1.0.8
	make -C omi-1.0.8/installbuilder SSL_VERSION=100 BUILD_RPM=$(BUILD_RPM) BUILD_DPKG=$(BUILD_DPKG)

configureomi098:
	(cd omi-1.0.8; chmod +x ./scripts/fixdist; ./scripts/fixdist; ./configure $(DEBUG_FLAGS) --enable-preexec --prefix=/opt/omi --outputdirname=output_openssl_0.9.8 --sysconfdir=/etc/opt/omi/conf --certsdir=/etc/opt/omi/ssl --opensslcflags=$(openssl098_cflags) --openssllibs=$(openssl098_libs) --openssllibdir=$(openssl098_libdir))

configureomi100:
	(cd omi-1.0.8; chmod +x ./scripts/fixdist; ./scripts/fixdist; ./configure $(DEBUG_FLAGS) --enable-preexec --prefix=/opt/omi --outputdirname=output_openssl_1.0.0 --sysconfdir=/etc/opt/omi/conf --certsdir=/etc/opt/omi/ssl --opensslcflags=$(openssl100_cflags) --openssllibs=$(openssl100_libs) --openssllibdir=$(openssl100_libdir))

lcm098:
	make -C LCM

lcm100:
	make -C LCM

providers:
	make -C Providers

nxComputerManagement:
	rm -rf output/staging; \
	VERSION="1.0"; \
	PROVIDERS="nxComputer"; \
	STAGINGDIR="output/staging/$@/DSCResources"; \
	for current in $$PROVIDERS; do \
		mkdir -p $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH)/Scripts/{2.4x-2.5x,2.6x-2.7x,3.x}/Scripts; \
		cp Providers/Modules/$@.psd1 output/staging/$@/; \
		cp Providers/$${current}/MSFT_$${current}Resource.schema.mof $$STAGINGDIR/MSFT_$${current}Resource/; \
		cp Providers/$${current}/MSFT_$${current}Resource.reg $$STAGINGDIR/MSFT_$${current}Resource/; \
		cp Providers/bin/libMSFT_$${current}Resource.so $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH); \
		cp Providers/Scripts/2.4x-2.5x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH)/Scripts/2.4x-2.5x/Scripts; \
		cp Providers/Scripts/2.6x-2.7x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH)/Scripts/2.6x-2.7x/Scripts; \
		cp Providers/Scripts/3.x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH)/Scripts/3.x/Scripts; \
	done;\
	cd output/staging; \
	zip -r $@_$${VERSION}.zip $@; \
	mkdir -p ../../release; \
	mv $@_$${VERSION}.zip ../../release/

nxNetworking:
	rm -rf output/staging; \
	VERSION="1.0"; \
	PROVIDERS="nxDNSServerAddress nxIPAddress nxFirewall"; \
	STAGINGDIR="output/staging/$@/DSCResources"; \
	for current in $$PROVIDERS; do \
		mkdir -p $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH)/Scripts/{2.4x-2.5x,2.6x-2.7x,3.x}/Scripts; \
		cp Providers/Modules/$@.psd1 output/staging/$@/; \
		cp Providers/$${current}/MSFT_$${current}Resource.schema.mof $$STAGINGDIR/MSFT_$${current}Resource/; \
		cp Providers/$${current}/MSFT_$${current}Resource.reg $$STAGINGDIR/MSFT_$${current}Resource/; \
		cp Providers/bin/libMSFT_$${current}Resource.so $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH); \
		cp Providers/Scripts/2.4x-2.5x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH)/Scripts/2.4x-2.5x/Scripts; \
		cp Providers/Scripts/2.6x-2.7x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH)/Scripts/2.6x-2.7x/Scripts; \
		cp Providers/Scripts/3.x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/$(PF_ARCH)/Scripts/3.x/Scripts; \
	done;\
	cd output/staging; \
	zip -r $@_$${VERSION}.zip $@; \
	mkdir -p ../../release; \
	mv $@_$${VERSION}.zip ../../release/

distclean: clean

clean:
ifeq ($(BUILD_LOCAL),1)
	make -C Providers clean
	make -C omi-1.0.8 distclean
	rm -rf omi-1.0.8/output
	rm -rf output
	rm -rf release
	rm -rf intermediate
else
	make -C Providers clean
	make configureomi098
	make -C omi-1.0.8 distclean
	make configureomi100
	make -C omi-1.0.8 distclean
	rm -rf omi-1.0.8/output
	rm -rf output
	rm -rf release
	rm -rf intermediate
endif


# To build DSC without making kits (i.e. the old style), run 'make local'
local: lcm providers

lcm:
	make -C omi-1.0.8
	make -C LCM

reg: lcmreg providersreg

lcmreg:
	make -C LCM deploydsc

providersreg:
	for f in Providers/Scripts/InstalledScripts/*.py; do \
	  cat $$f | \
	  sed "s@<CONFIG_BINDIR>@$(CONFIG_BINDIR)@" | \
	  sed "s@<CONFIG_LIBDIR>@$(CONFIG_LIBDIR)@" | \
	  sed "s@<CONFIG_SYSCONFDIR>@$(CONFIG_SYSCONFDIR)@" | \
	  sed "s@<DSC_PATH>@$(CONFIG_DATADIR)/dsc@" > intermediate/Scripts/`basename $$f`; \
	  chmod a+x intermediate/Scripts/`basename $$f`; \
	done 
	make -C Providers reg
