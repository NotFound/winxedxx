# Makefile for winxedxx tests

#-----------------------------------------------------------------------
# Configurable values

PARROT = parrot
WINXED = winxed
WINXEDLIB =

CXX = g++
CXXOPTS = -g -Wall -fPIC
LDOPTS = -ldl

#-----------------------------------------------------------------------

OBJS = \
                winxedxx_null.o \
                winxedxx_default.o \
		winxedxx_objectptr.o \
		winxedxx_scalar.o \
		winxedxx_array.o \
		winxedxx_classes.o \
		winxedxx_handle.o \
		winxedxx_namespace.o \
		winxedxx_nci.o \
		winxedxx_util.o

LIB = winxedxx.so

FRONTEND = winxedxc.pbc

#-----------------------------------------------------------------------

default: pbc lib

pbc: winxedxx.pbc $(FRONTEND)

#-----------------------------------------------------------------------

lib: winxedxx.so

winxedxx.so: $(OBJS)
	$(CXX) -shared -o winxedxx.so $(OBJS)

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

winxedxx_scalar.o: winxedxx_scalar.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h
	$(CXX) $(CXXOPTS) -c winxedxx_scalar.cxx

winxedxx_array.o: winxedxx_array.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h
	$(CXX) $(CXXOPTS) -c winxedxx_array.cxx

winxedxx_classes.o: winxedxx_classes.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h
	$(CXX) $(CXXOPTS) -c winxedxx_classes.cxx

winxedxx_handle.o: winxedxx_handle.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h winxedxx_handle.h
	$(CXX) $(CXXOPTS) -c winxedxx_handle.cxx

winxedxx_namespace.o: winxedxx_namespace.cxx winxedxx_namespace.h
	$(CXX) $(CXXOPTS) -c winxedxx_namespace.cxx

winxedxx_nci.o: winxedxx_nci.cxx winxedxx.h
	$(CXX) $(CXXOPTS) -c winxedxx_nci.cxx

winxedxx_util.o: winxedxx_util.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h winxedxx_handle.h
	$(CXX) $(CXXOPTS) -c winxedxx_util.cxx

#-----------------------------------------------------------------------

winxedxc.pir: winxedxc.winxed winxedxx.winxhead
	$(WINXED) -c winxedxc.winxed

winxedxc.pbc: winxedxc.pir
	$(PARROT) -o winxedxc.pbc winxedxc.pir

#-----------------------------------------------------------------------

test: winxedxx.pbc $(FRONTEND) winxedxx.h $(LIB)
	prove -v -e "$(WINXED) t/runtests.winxed" t/base/features.t

#-----------------------------------------------------------------------

exetest: t/runtests
	prove -v -e t/runtests t/base/features.t

t/runtests: winxedxx.pbc $(FRONTEND) winxedxx.h $(LIB) t/runtests.winxed
	$(PARROT) $(FRONTEND) --target=exe -o t/runtests t/runtests.winxed

#-----------------------------------------------------------------------

clean:
	rm -f \
		winxedxx \
		winxedxx.c \
		winxedxx.o \
		winxedxx.pbc \
		winxedxx.pir \
		winxedxc.pbc \
		winxedxc.pir \
		$(LIB) \
		$(OBJS) \
		t/runtests \
		t/runtests.o \
		t/runtests.cxx \
		t/base/features \
		t/base/features.o \
		t/base/features.cxx

# End
