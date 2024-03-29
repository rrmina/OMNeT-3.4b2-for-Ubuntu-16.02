#
# Definitions to be customized by 'configure'
#
CXX=g++
AR=ar cr
SHLIB_LD=g++ -shared -fPIC
RANLIB=ranlib
MAKEDEPEND=opp_makedep -Y --objdirtree

CFLAGS=-O2 -DNDEBUG=1 -fPIC  -DWITH_PARSIM -DWITH_NETBUILDER

OMNETPP_INCL_DIR=/home/rusty/Desktop/omnetpp-3.4b2/include
OMNETPP_LIB_DIR=/home/rusty/Desktop/omnetpp-3.4b2/lib

OMNETPP_VERSION=3.4b2
OMNETPP_EDITION=Academic Public License

# LIB_SUFFIX is either A_LIB_SUFFIX or SO_LIB_SUFFIX
LIB_SUFFIX=$(SO_LIB_SUFFIX)

A_LIB_SUFFIX=.a
SO_LIB_SUFFIX=.so

#
# Local definitions
#
COPTS=$(CFLAGS) -I$(OMNETPP_INCL_DIR) -I../envir -DBUILDING_CMDENV

OBJS = cmdenv.o enumstr.o heap.o

#
# Automatic rules
#
.SUFFIXES : .cc

.cc.o:
	$(CXX) -c $(COPTS) -o $@ $<

#
# Targets
#
all: libcmdenv$(LIB_SUFFIX)

libcmdenv$(A_LIB_SUFFIX) : $(OBJS)
	$(AR) libcmdenv$(A_LIB_SUFFIX) $(OBJS)
	$(RANLIB) libcmdenv$(A_LIB_SUFFIX)
	../utils/install-lib libcmdenv$(A_LIB_SUFFIX).$(OMNETPP_VERSION) $(OMNETPP_LIB_DIR) libcmdenv$(A_LIB_SUFFIX)

libcmdenv$(SO_LIB_SUFFIX) : $(OBJS)
	$(SHLIB_LD) -o libcmdenv$(SO_LIB_SUFFIX) $(OBJS)
	../utils/install-lib libcmdenv$(SO_LIB_SUFFIX).$(OMNETPP_VERSION) $(OMNETPP_LIB_DIR) libcmdenv$(SO_LIB_SUFFIX)

depend:
	$(MAKEDEPEND) -I. -I../envir -I../../include -- *.cc
	$(MAKEDEPEND) -I. -I../envir -I../../include -fMakefile.in -- *.cc

clean:
	rm -f *.o libcmdenv$(A_LIB_SUFFIX) libcmdenv$(SO_LIB_SUFFIX)

# DO NOT DELETE THIS LINE -- make depend depends on it.
cmdenv.o: cmdenv.cc \
  cmddefs.h \
  cmdenv.h \
  enumstr.h \
  ../envir/appreg.h \
  ../../include/csimplemodule.h \
  ../../include/cmessage.h \
  ../envir/args.h \
  ../envir/speedmtr.h \
  ../../include/platdep/time.h \
  ../../include/defs.h \
  ../../include/ctypes.h \
  ../../include/csimul.h \
  ../envir/omnetapp.h \
  ../../include/globals.h \
  ../../include/cobject.h \
  ../../include/onstartup.h \
  ../../include/cenvir.h \
  ../../include/util.h \
  ../../include/cpolymorphic.h \
  ../../include/cexception.h \
  ../../include/cvisitor.h \
  ../../include/opp_string.h \
  ../../include/errmsg.h \
  ../../include/cmsgheap.h \
  ../../include/ccoroutine.h \
  ../../include/coutvect.h \
  ../../include/carray.h \
  ../envir/envdefs.h \
  ../../include/envirext.h \
  ../../include/cconfig.h \
  ../../include/cmodule.h \
  ../../include/cqueue.h \
  ../../include/cgate.h \
  ../../include/cdefaultlist.h \
  ../../include/cpar.h
enumstr.o: enumstr.cc \
  enumstr.h
heap.o: heap.cc
