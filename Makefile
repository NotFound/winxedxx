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
		winxedxx_ptr.o \
		winxedxx_bytebuffer.o \
		winxedxx_builtin_test_more.o \
		winxedxx_util.o

LIB = winxedxx.so

FRONTEND = winxedxc.pbc

#-----------------------------------------------------------------------

default: pbc lib

pbc: winxedxx.pbc $(FRONTEND)

#-----------------------------------------------------------------------

winxedxc: winxedxc.pbc
	pbc_to_exe winxedxc.pbc

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

winxedxx_ptr.o: winxedxx_ptr.cxx winxedxx.h
	$(CXX) $(CXXOPTS) -c winxedxx_ptr.cxx

winxedxx_bytebuffer.o: winxedxx_bytebuffer.cxx winxedxx.h winxedxx_bytebuffer.h
	$(CXX) $(CXXOPTS) -c winxedxx_bytebuffer.cxx

winxedxx_nci.o: winxedxx_nci.cxx winxedxx.h
	$(CXX) $(CXXOPTS) -c winxedxx_nci.cxx

winxedxx_util.o: winxedxx_util.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h winxedxx_handle.h
	$(CXX) $(CXXOPTS) -c winxedxx_util.cxx

winxedxx_builtin_test_more.o: winxedxx_builtin_test_more.cxx winxedxx_types.h winxedxx_object.h winxedxx_default.h winxedxx_integer.h winxedxx_handle.h
	$(CXX) $(CXXOPTS) -c winxedxx_builtin_test_more.cxx

#-----------------------------------------------------------------------

winxedxc.pir: winxedxc.winxed winxedxx.winxhead
	$(WINXED) -c winxedxc.winxed

winxedxc.pbc: winxedxc.pir
	$(PARROT) -o winxedxc.pbc winxedxc.pir

#-----------------------------------------------------------------------

TESTS = t/base/00test.t \
	t/base/02opadd.t t/base/02opmul.t t/base/02opsub.t \
	t/base/02preincdec.t \
	t/base/02bitwiseops.t \
	t/base/02varcast.t \
	t/base/03pmc.t t/base/03class.t \
	t/base/06localfunctions.t \
	t/base/10closure.t \
	t/base/features.t

test: winxedxx.pbc $(FRONTEND) winxedxx.h $(LIB)
	prove -v -e "$(WINXED) t/runtests.winxed" $(TESTS)

#-----------------------------------------------------------------------

exetest: t/runtests
	prove -v -e t/runtests $(TESTS)

t/runtests: winxedxx.pbc $(FRONTEND) winxedxx.h $(LIB) t/runtests.winxed
	$(PARROT) $(FRONTEND) --target=exe -o t/runtests t/runtests.winxed

#-----------------------------------------------------------------------

cleantest:
	rm -f -- \
		t/runtests \
		t/runtests.o \
		t/runtests.cxx \
		t/base/dotest t/base/*.o t/base/*.cxx

clean: cleantest
	rm -f -- \
		winxedxx \
		winxedxx.c \
		winxedxx.o \
		winxedxx.pbc \
		winxedxx.pir \
		winxedxc \
		winxedxc.o \
		winxedxc.c \
		winxedxc.pbc \
		winxedxc.pir \
		$(LIB) \
		$(OBJS)

# End
