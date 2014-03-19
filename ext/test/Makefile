# Python stuff
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

##PYTHON_LDFLAGS=$(shell python-config --ldflags)
#PYTHON_LDFLAGS:=-L/usr/local/lib/python2.5/config
PYTHON_LDFLAGS+=-lpthread
PYTHON_LDFLAGS+=-ldl
PYTHON_LDFLAGS+=-lutil
PYTHON_LDFLAGS+=-lm
##PYTHON_LDFLAGS+=-lpython2.6
#PYTHON_LDFLAGS+=-lpython2.5
PYTHON_LDFLAGS+=/usr/local/lib/python2.5/config/libpython2.5.a

CXXFLAGS+=$(PYTHON_CXXFLAGS)
#CFLAGS+=$(PYTHON_CXXFLAGS)
#LDLIBS or LDFLAGS?
LDFLAGS+=$(PYTHON_LDFLAGS)


# Boost stuff
#BOOST_CFLAGS=-I$(BOOST_ROOT)
#BOOST_CXXFLAGS:=-static
BOOST_CXXFLAGS+=-I/usr/local/include/boost_1_55_0


# this does not work
#BOOST_LIBS+=libboost_system.a
#BOOST_LIBS+=libboost_filesystem.a
#BOOST_LIBS+=libboost_python.a

BOOST_LIB_ROOT:=/usr/local/lib/boost_1_55_0
BOOST_LIBS+=$(BOOST_LIB_ROOT)/libboost_system.a
BOOST_LIBS+=$(BOOST_LIB_ROOT)/libboost_filesystem.a
BOOST_LIBS+=$(BOOST_LIB_ROOT)/libboost_python.a

#BOOST_LIBS:=-L/usr/local/lib/boost_1_55_0
#BOOST_LIBS+=-lboost_system
#BOOST_LIBS+=-lboost_python
#BOOST_LIBS+=-lboost_filesystem

#LDLIBS or LDFLAGS?
LDFLAGS+=$(BOOST_LIBS)

#CFLAGS+=$(BOOST_CXXFLAGS)
CXXFLAGS+=$(BOOST_CXXFLAGS)


# Extra stuff
#CXXFLAGS+=-DPy_UNICODE_SIZE=4
CXXFLAGS+=-ggdb
CXXFLAGS+=-O0
#CFLAGS+=-ggdb
#CFLAGS+=-O0


TARGET:=test

LIB_TARGET:=extension.so


SOURCES:=main.cpp


LIB_SOURCES:=extension.cpp


all: $(LIB_TARGET) $(TARGET)

# this adds some help
#$(TARGET): $(SOURCES:.cpp=.o)
#	$(LINK.cpp) -o $@ $^ $(BOOST_LIBS)

$(TARGET): $(SOURCES:.cpp=.o)
	$(LINK.cpp) $(LDFLAGS) -o $@ $^ $(LDFLAGS)


#$(TARGET): $(SOURCES:.cpp=.o)
#	$(LINK.cpp) -o $@ $^ $(LD_LIBS)


#$(LIB_TARGET): $(LIB_SOURCES:.cpp=.o)
#	$(AR) r $@ $^

$(LIB_TARGET) : $(LIB_SOURCES:.cpp=.o)
#	$(CXX) -shared -o $@ $^ $(BOOST_LIBS)

clean:
	rm -f $(TARGET) $(LIB_TARGET) $(SOURCES:.cpp=.o) $(LIB_SOURCES:.cpp=.o)
