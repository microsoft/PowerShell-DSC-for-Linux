TESTTOP = ../..

DSCTOP = ../../..

TOP = ../../../..


include $(TOP)/config.mak

CXXUNITTEST = NITSDSCTestProvider


SOURCES= \
        module.c \
        schema.c \
        TEST_Stop.c \
        TEST_Test2.c \
        TEST_Test1.c \
		TEST_Test4NoOMI.c \
        Test_Test3User.c \

INCLUDES= \
	$(OMI) \
	$(OMI)/common \
	$(OMI)/common/inc \

DEFINES= TEST_BUILD

LIBRARIES = mi  pal 

include $(OMI)/mak/rules.mak

