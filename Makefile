# Makefile for winxedxx tests

#-----------------------------------------------------------------------
# Configurable values

PARROT = parrot
PBC_TO_EXE = pbc_to_exe
WINXED = winxed
WINXEDLIB =

CXX = g++
CXXOPTS = -g -Wall
LDOPTS = -ldl

#-----------------------------------------------------------------------

OBJS = \
                winxedxx_null.o \
                winxedxx_default.o \
		winxedxx_objectptr.o \
		winxedxx_classes.o \
		winxedxx_handle.o \
		winxedxx_util.o

#-----------------------------------------------------------------------

default: pbc $(OBJS)

exe: winxedxx $(OBJS)

pbc: winxedxx.pbc

#-----------------------------------------------------------------------

winxedxx: winxedxx.pbc
	$(PBC_TO_EXE) winxedxx.pbc

#-----------------------------------------------------------------------

winxedxx.pbc: winxedxx.pir
	$(PARROT) -o winxedxx.pbc winxedxx.pir

winxedxx.pir: winxedxx.winxed
	$(WINXED) $(WINXEDLIB) --target=pir -o winxedxx.pir winxedxx.winxed

#-----------------------------------------------------------------------

winxedxx_null.o: winxedxx_null.cxx winxedxx_types.h winxedxx_object.h winxedxx_null.h
	$(CXX) $(CXXOPTS) -c winxedxx_null.cxx

winxedxx_default.o: winxedxx_default.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h
	$(CXX) $(CXXOPTS) -c winxedxx_default.cxx

winxedxx_objectptr.o: winxedxx_objectptr.cxx winxedxx_types.h winxedxx_object.h winxedxx_null.h winxedxx_default.h winxedxx_integer.h
	$(CXX) $(CXXOPTS) -c winxedxx_objectptr.cxx

winxedxx_classes.o: winxedxx_classes.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h
	$(CXX) $(CXXOPTS) -c winxedxx_classes.cxx

winxedxx_handle.o: winxedxx_handle.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h winxedxx_handle.h
	$(CXX) $(CXXOPTS) -c winxedxx_handle.cxx

winxedxx_util.o: winxedxx_util.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h winxedxx_handle.h
	$(CXX) $(CXXOPTS) -c winxedxx_util.cxx

#-----------------------------------------------------------------------

test: winxedxx.pbc winxedxx.h $(OBJS)
	prove -v -e "$(WINXED) t/runtests.winxed" t/base/features.t

#-----------------------------------------------------------------------

exetest: t/runtests
	prove -v -e t/runtests t/base/features.t

t/runtests: t/runtests.winxed exe $(OBJS)
	./winxedxx --target=exe -o t/runtests t/runtests.winxed

#-----------------------------------------------------------------------

clean:
	rm -f \
		winxedxx \
		winxedxx.c \
		winxedxx.o \
		winxedxx.pbc \
		winxedxx.pir \
		$(OBJS) \
		t/runtests \
		t/runtests.cxx \
		t/base/features \
		t/base/features.cxx

# End
