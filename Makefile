# Makefile for winxedxx tests

#-----------------------------------------------------------------------
# Configurable values

PARROT = parrot
WINXED = winxed
WINXEDLIB = -L /home/julian/winxed

CXX = g++
CXXOPTS = -g -Wall -ldl

#-----------------------------------------------------------------------

OBJS = \
		winxedxx_objectptr.o \
		winxedxx_classes.o \
		winxedxx_handle.o \
		winxedxx_util.o

#-----------------------------------------------------------------------

all: simple
	./simple

simple: simple.cxx winxedxx.h  $(OBJS)
	$(CXX) $(CXXOPTS) -o simple simple.cxx $(OBJS)

simple.cxx: simple.winxed winxedxx.pbc
	$(PARROT) $(WINXEDLIB) winxedxx.pbc -o simple.cxx simple.winxed

#-----------------------------------------------------------------------

winxedxx.pbc: winxedxx.winxed
	$(WINXED) $(WINXEDLIB) --target pbc -o winxedxx.pbc winxedxx.winxed

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

clean:
	rm -f \
		winxedxx.pbc \
		$(OBJS) \
		simple simple.cxx

# End
