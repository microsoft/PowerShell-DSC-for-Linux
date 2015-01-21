kit: omi098 dsc098 omi100 dsc100
	OMI098_RPM=`ls omi-1.0.8/output_openssl_0.9.8/release/*.rpm`; \
	DSC098_RPM=`ls output/release/*.rpm`; \
	OMI098_DEB=`ls omi-1.0.8/output_openssl_0.9.8/release/*.deb`; \
	DSC098_DEB=`ls output/release/*.deb`; \
	OMI100_RPM=`ls omi-1.0.8/output_openssl_1.0.0/release/*.rpm`; \
	DSC100_RPM=`ls output/release/*.rpm`; \
	OMI100_DEB=`ls omi-1.0.8/output_openssl_1.0.0/release/*.deb`; \
	DSC100_DEB=`ls output/release/*.deb`; \
	rm -rf release; \
	mkdir -p release; \
	mv omi-1.0.8/output_openssl_0.9.8/release/*.{rpm,deb} omi-1.0.8/output_openssl_1.0.0/release/*.{rpm,deb} output/release/*.{rpm,deb} release/

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
