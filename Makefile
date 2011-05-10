# Makefile for winxedxx tests

#-----------------------------------------------------------------------
# Configurable values

PARROT = parrot
WINXED = winxed
WINXEDLIB = -L /home/julian/winxed

CXX = g++
CXXOPTS = -g -Wall -ldl

#-----------------------------------------------------------------------

all: simple
	./simple

simple: simple.cxx winxedxx.h
	$(CXX) $(CXXOPTS) -o simple simple.cxx

simple.cxx: simple.winxed winxedxx.pbc
	$(PARROT) $(WINXEDLIB) winxedxx.pbc -o simple.cxx simple.winxed

#-----------------------------------------------------------------------

winxedxx.pbc: winxedxx.winxed
	$(WINXED) $(WINXEDLIB) --target pbc -o winxedxx.pbc winxedxx.winxed

#-----------------------------------------------------------------------

clean:
	rm -f \
		winxedxx.pbc \
		simple simple.cxx

# End
