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

ifeq ($(ENABLE_DEBUG),1)
ENABLE_DEBUG_DEFINE = ENABLE_DEBUG
endif

DEFINES = MI_CONST= $(ENABLE_DEBUG_DEFINE)

include $(OMI)/mak/rules.mak


