include config.mak

ifeq ($(BUILD_LOCAL),1)
all:
	make local

else
all:
 ifeq ($(BUILD_SSL_098),1)
	make kit098 
 endif
 ifeq ($(BUILD_SSL_100),1)
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
	make -C omi-1.0.8/installbuilder-generic SSL_VERSION=098 BUILD_RPM=$(BUILD_RPM) BUILD_DPKG=$(BUILD_DPKG)

omi100:
	make configureomi100
	rm -rf omi-1.0.8/output
	ln -s output_openssl_1.0.0 omi-1.0.8/output
	make -C omi-1.0.8
	make -C omi-1.0.8/installbuilder-generic SSL_VERSION=100 BUILD_RPM=$(BUILD_RPM) BUILD_DPKG=$(BUILD_DPKG)

configureomi098:
	(cd omi-1.0.8; chmod +x ./scripts/fixdist; ./scripts/fixdist; ./configure $(DEBUG_FLAGS) --enable-preexec --prefix=/opt/omi --outputdirname=output_openssl_0.9.8 --opensslcflags=$(openssl098_cflags) --openssllibs=$(openssl098_libs) --openssllibdir=$(openssl098_libdir))

configureomi100:
	(cd omi-1.0.8; chmod +x ./scripts/fixdist; ./scripts/fixdist; ./configure $(DEBUG_FLAGS) --enable-preexec --prefix=/opt/omi --outputdirname=output_openssl_1.0.0 --opensslcflags=$(openssl100_cflags) --openssllibs=$(openssl100_libs) --openssllibdir=$(openssl100_libdir))

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
		mkdir -p $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/{2.4x-2.5x,2.6x-2.7x,3.x}/Scripts; \
		cp Providers/$${current}/MSFT_$${current}Resource.schema.mof $$STAGINGDIR/MSFT_$${current}Resource/; \
		cp Providers/$${current}/MSFT_$${current}Resource.reg $$STAGINGDIR/MSFT_$${current}Resource/; \
		cp Providers/bin/libMSFT_$${current}Resource.so $$STAGINGDIR/MSFT_$${current}Resource/lib; \
		cp Providers/Scripts/2.4x-2.5x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/2.4x-2.5x/Scripts; \
		cp Providers/Scripts/2.6x-2.7x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/2.6x-2.7x/Scripts; \
		cp Providers/Scripts/3.x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/3.x/Scripts; \
	done;\
	cd output/staging; \
	zip -r $@_$${VERSION}.zip $@; \
	mkdir -p ../../release; \
	mv $@_$${VERSION}.zip ../../release/

nxNetworking:
	rm -rf output/staging; \
	VERSION="1.0"; \
	PROVIDERS="nxDNSServerAddress nxIPAddress"; \
	STAGINGDIR="output/staging/$@/DSCResources"; \
	for current in $$PROVIDERS; do \
		mkdir -p $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/{2.4x-2.5x,2.6x-2.7x,3.x}/Scripts; \
		cp Providers/$${current}/MSFT_$${current}Resource.schema.mof $$STAGINGDIR/MSFT_$${current}Resource/; \
		cp Providers/$${current}/MSFT_$${current}Resource.reg $$STAGINGDIR/MSFT_$${current}Resource/; \
		cp Providers/bin/libMSFT_$${current}Resource.so $$STAGINGDIR/MSFT_$${current}Resource/lib; \
		cp Providers/Scripts/2.4x-2.5x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/2.4x-2.5x/Scripts; \
		cp Providers/Scripts/2.6x-2.7x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/2.6x-2.7x/Scripts; \
		cp Providers/Scripts/3.x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/3.x/Scripts; \
	done;\
	cd output/staging; \
	zip -r $@_$${VERSION}.zip $@; \
	mkdir -p ../../release; \
	mv $@_$${VERSION}.zip ../../release/

distclean: clean

clean:
	make -C Providers clean
	make configureomi098
	make -C omi-1.0.8 distclean
	make configureomi100
	make -C omi-1.0.8 distclean
	rm -rf omi-1.0.8/output
	rm -rf output
	rm -rf release


# To build DSC without making kits (i.e. the old style), run 'make local'
local: lcm providers

lcm:
	make -C omi-1.0.8
	make -C LCM

reg: lcmreg providersreg

lcmreg:
	make -C LCM deploydsc

providersreg:
	make -C Providers reg
