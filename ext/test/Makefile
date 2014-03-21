#Program definitions
MKDEP:=-MD
COPY:=cp
SED:=sed
RM:=rm -f


# Python C++ flags
PYTHON_CXXFLAGS:=-I/usr/local/include/python2.5
PYTHON_CXXFLAGS+=-fno-strict-aliasing
PYTHON_CXXFLAGS+=-DNDEBUG
PYTHON_CXXFLAGS+=-fmessage-length=0
PYTHON_CXXFLAGS+=-Wall
PYTHON_CXXFLAGS+=-D_FORTIFY_SOURCE=2
PYTHON_CXXFLAGS+=-fstack-protector
PYTHON_CXXFLAGS+=-funwind-tables
PYTHON_CXXFLAGS+=-fasynchronous-unwind-tables
PYTHON_CXXFLAGS+=-g
PYTHON_CXXFLAGS+=-fwrapv
PYTHON_CXXFLAGS+=-fPIC

CXXFLAGS+=$(PYTHON_CXXFLAGS)


# Python linker flags
PYTHON_LDFLAGS:=-L/usr/local/lib/python2.5/config
PYTHON_LDFLAGS+=-lpthread
PYTHON_LDFLAGS+=-ldl
PYTHON_LDFLAGS+=-lutil
PYTHON_LDFLAGS+=-lm
PYTHON_LDFLAGS+=-lpython2.5

LDFLAGS+=$(PYTHON_LDFLAGS)


# Boost C++ flags
BOOST_CXXFLAGS+=-I/usr/local/include/boost_1_55_0

CXXFLAGS+=$(BOOST_CXXFLAGS)


# Boost linker flags
BOOST_LIB_ROOT:=/usr/local/lib/boost_1_55_0
BOOST_LIBS+=$(BOOST_LIB_ROOT)/libboost_system.a
BOOST_LIBS+=$(BOOST_LIB_ROOT)/libboost_filesystem.a
BOOST_LIBS+=$(BOOST_LIB_ROOT)/libboost_python.a

LDFLAGS+=$(BOOST_LIBS)


# Extra C++ flags
CXXFLAGS+=-ggdb
CXXFLAGS+=-O0


# targets
TARGET:=test

LIB_TARGET:=extension.so

all: $(LIB_TARGET) $(TARGET)


# source files
SOURCES:=main.cpp
SOURCES+=python_io_helpers.cpp

LIB_SOURCES:=extension.cpp



$(TARGET): $(SOURCES:.cpp=.o)
	$(LINK.cpp) $(LDFLAGS) -o $@ $^ $(LDFLAGS)


$(LIB_TARGET) : $(LIB_SOURCES:.cpp=.o)
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


## Include the .P files generated in the build to include the dependencies
-include $(SOURCES:.cpp=.P)
