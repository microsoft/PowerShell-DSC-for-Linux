#Program definitions
MKDEP:=-MD
COPY:=cp
SED:=sed
RM:=rm -f

TOP?=$(shell cd ../..; pwd)


PY_VERSION:=2.5


# Python C++ flags
CXXFLAGS:=-fPIC
PYTHON_CXXFLAGS:=$(shell python2.5-config --cflags)
CXXFLAGS+=$(filter-out -Wstrict-prototypes,$(PYTHON_CXXFLAGS))


# Python linker flags
LDFLAGS+=$(filter-out -L%,$(shell python$(PY_VERSION)-config --ldflags))


# Boost C++ flags
CXXFLAGS+=-I/usr/local/include/boost_1_55_0


# Boost linker flags
BOOST_LIB_ROOT:=/usr/local/lib/boost_1_55_0
BOOST_LIBS+=$(BOOST_LIB_ROOT)/libboost_system.a
BOOST_LIBS+=$(BOOST_LIB_ROOT)/libboost_filesystem.a
BOOST_LIBS+=$(BOOST_LIB_ROOT)/libboost_python$(PY_VERSION).a
LDFLAGS+=$(BOOST_LIBS)


# Extra C++ flags
CXXFLAGS+=-ggdb
CXXFLAGSy+=-O0


# Extra preprocessor flags
CPPFLAGS+=-I$(TOP)/Providers/PythonHelper


# targets
TARGET:=test

LIB_TARGET:=extension.so

all: $(LIB_TARGET) $(TARGET)


# source files
SOURCES:=main.cpp


# this object is part of the Providers project
OBJS:=$(TOP)/Providers/bin/$(PY_VERSION)/python_io_helper.o

# this rule calls the Providers makefile to build this object
$(TOP)/Providers/bin/$(PY_VERSION)/python_io_helper.o :
	$(MAKE) --directory=$(TOP)/Providers $@


LIB_SOURCES:=extension.cpp


$(TARGET): $(SOURCES:.cpp=.o) $(OBJS)
	$(LINK.cpp) $(LDFLAGS) -o $@ $^ $(LDFLAGS)


$(LIB_TARGET) : $(LIB_SOURCES:.cpp=.o $(OBJS))
	$(CXX) -shared -o $@ $^ $(BOOST_LIBS)


clean:
	rm -f $(TARGET) $(LIB_TARGET) $(SOURCES:.cpp=.o) $(SOURCES:.cpp=.d) \
	    $(SOURCES:.cpp=.P) $(LIB_SOURCES:.cpp=.o) $(LIB_SOURCES:.cpp=.d) \
	    $(LIB_SOURCES:.cpp=.P)


%.o : %.cpp
	$(COMPILE.cpp) $(MKDEP) -o $@ $<
	-@$(COPY) $*.d $*.P;
	@$(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	    -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P;
	@$(RM) $*.d


-include $(SOURCES:.cpp=.P)
