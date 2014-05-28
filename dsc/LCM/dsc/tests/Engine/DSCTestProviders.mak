TEST_PROVIDER_DIRS = \
	TestFileProvider 

testproviders:
	for DIR in $(TEST_PROVIDER_DIRS); do \
		if test $$DIR = Test_Indication; then \
			$(MAKE) dep -C $$DIR; \
		fi; \
		$(MAKE) -C $$DIR; \
	done \

regtestproviders:
	for DIR in $(TEST_PROVIDER_DIRS); do \
		$(MAKE) regtest -C $$DIR; \
	done \

cleantestproviders:
	for DIR in $(TEST_PROVIDER_DIRS); do \
		$(MAKE) clean -C $$DIR; \
	done \
