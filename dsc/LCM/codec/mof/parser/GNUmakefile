TOP = ../../..
include $(TOP)/config.mak

LIBRARY = mofparser

SOURCES = \
	buffer.c \
	moflex.c \
	ptrarray.c \
	types.c \
	utility.c \
	mofparser.c \
	mofyacc.c \
	mofhash.c 

INCLUDES = $(OMI)/common  $(OMI) $(TOP) $(TOP)/codec/common $(OMI)/nits/base 

DEFINES = MI_CONST= 

include $(OMI)/mak/rules.mak

