kit: kit098 kit100 nxNetworking
	mkdir -p release; \
	rm -rf release/*.{rpm,deb}; \
	mv omi-1.0.8/output_openssl_0.9.8/release/*.{rpm,deb} omi-1.0.8/output_openssl_1.0.0/release/*.{rpm,deb} output/release/*.{rpm,deb} release/

kit098: omi098 dsc098

kit100: omi100 dsc100

dsc098: lcm098 providers
	make -C installbuilder SSL_VERSION=098

dsc100: lcm100 providers
	make -C installbuilder SSL_VERSION=100

omi098:
	./configure-release-098
	rm -rf omi-1.0.8/output
	ln -s output_openssl_0.9.8 omi-1.0.8/output
	make -C omi-1.0.8
	make -C omi-1.0.8/installbuilder-generic SSL_VERSION=098

omi100:
	./configure-release-100
	rm -rf omi-1.0.8/output
	ln -s output_openssl_1.0.0 omi-1.0.8/output
	make -C omi-1.0.8
	make -C omi-1.0.8/installbuilder-generic SSL_VERSION=100

lcm098:
	make -C LCM

lcm100:
	make -C LCM

providers:
	make -C Providers

nxComputerManagement:
	ls # placeholder until we're building nxComputer

nxNetworking:
	rm -rf output/staging; \
	VERSION="1.0"; \
	PROVIDERS="nxDNSServerAddress"; \
	STAGINGDIR="output/staging/nxNetworking/DSCResources"; \
	for current in $$PROVIDERS; do \
		mkdir -p $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/{2.4x-2.5x,2.6x-2.7x,3.x}/Scripts; \
		cp Providers/$${current}/MSFT_$${current}Resource.schema.mof $$STAGINGDIR/MSFT_$${current}Resource/; \
		cp Providers/bin/libMSFT_$${current}Resource.so $$STAGINGDIR/MSFT_$${current}Resource/lib; \
		cp Providers/Scripts/2.4x-2.5x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/2.4x-2.5x/Scripts; \
		cp Providers/Scripts/2.6x-2.7x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/2.6x-2.7x/Scripts; \
		cp Providers/Scripts/3.x/Scripts/$${current}.py $$STAGINGDIR/MSFT_$${current}Resource/lib/Scripts/3.x/Scripts; \
	done;\
	cd output/staging; \
	zip -r nxNetworking_$${VERSION}.zip nxNetworking; \
	mkdir -p ../../release; \
	mv nxNetworking_$${VERSION}.zip ../../release/

distclean: clean

clean:
	make -C Providers clean
	./configure-release-098
	make -C omi-1.0.8 distclean
	./configure-release-100
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
