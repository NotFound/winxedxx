# Makefile for winxedxx tests

#-----------------------------------------------------------------------
# Configurable values

WINXEDLIB = -L /home/julian/winxed
CXX = g++
CXXOPTS = -g -Wall

#-----------------------------------------------------------------------

all: simple
	./simple

simple: simple.cxx winxedxx.h
	$(CXX) $(CXXOPTS) -o simple simple.cxx

simple.cxx: simple.winxed winxedxx.winxed
	winxed $(WINXEDLIB) winxedxx.winxed -o simple.cxx simple.winxed

#-----------------------------------------------------------------------

clean:
	rm -f simple
	rm -f simple.cxx

# End
