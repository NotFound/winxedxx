# Makefile for winxedxx tests

#-----------------------------------------------------------------------
# Configurable values

PARROT = parrot
WINXED = winxed
WINXEDLIB =

CXX = g++
CXXOPTS = -g -Wall
LDOPTS = -ldl

#-----------------------------------------------------------------------

OBJS = \
		winxedxx_objectptr.o \
		winxedxx_classes.o \
		winxedxx_handle.o \
		winxedxx_util.o

#-----------------------------------------------------------------------

all: simple
	./simple

simple: simple.cxx winxedxx.h $(OBJS)
	$(CXX) $(CXXOPTS) -o simple simple.cxx $(OBJS) $(LDOPTS)

simple.cxx: simple.winxed winxedxx.pbc
	$(PARROT) $(WINXEDLIB) winxedxx.pbc -o simple.cxx simple.winxed

#-----------------------------------------------------------------------

winxedxx.pbc: winxedxx.pir
	$(PARROT) -o winxedxx.pbc winxedxx.pir

winxedxx.pir: winxedxx.winxed
	$(WINXED) $(WINXEDLIB) --target pir -o winxedxx.pir winxedxx.winxed

#-----------------------------------------------------------------------

winxedxx_objectptr.o: winxedxx_objectptr.cxx
	$(CXX) $(CXXOPTS) -c winxedxx_objectptr.cxx

winxedxx_classes.o: winxedxx_classes.cxx
	$(CXX) $(CXXOPTS) -c winxedxx_classes.cxx

winxedxx_handle.o: winxedxx_handle.cxx
	$(CXX) $(CXXOPTS) -c winxedxx_handle.cxx

winxedxx_util.o: winxedxx_util.cxx
	$(CXX) $(CXXOPTS) -c winxedxx_util.cxx

#-----------------------------------------------------------------------

test: winxedxx.pbc winxedxx.h $(OBJS)
	$(WINXED) t/runtests.t t/base/features.winxed

#-----------------------------------------------------------------------

clean:
	rm -f \
		winxedxx.pbc \
		winxedxx.pir \
		$(OBJS) \
		t/base/features \
		t/base/features.cxx \
		simple simple.cxx

# End
