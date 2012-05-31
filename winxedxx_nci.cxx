// winxedxx_nci.cxx
// (C) 2012 Julián Albo

#include "winxedxx.h"

#include <dlfcn.h>

namespace WinxedXX
{

//*************************************************************

WxxNCI::WxxNCI(const std::string &funcname) :
        WxxDefault("NCI"),
        name(funcname)
{
}

WxxObjectPtr WxxNCI::operator()(WxxObjectArray &args)
{
    return winxedxxnull;
}


//*************************************************************

WxxObjectPtr wxx_loadlib(const std::string &libname)
{
    void *dl_handle = dlopen(libname.c_str(), RTLD_LAZY);
    if (dl_handle == NULL)
        return WxxObjectPtr(0); // Sort of Undef for a now
    else
        return WxxObjectPtr(new WxxLibrary(dl_handle));
}

void * wxx_ncigetfunc(WxxObjectPtr lib, const std::string &funcname)
{
    void *fun = 0;
    if (lib.is_null())
        fun = dlsym(0, funcname.c_str());
    else if (WxxLibrary *dlib = lib.getlib())
        fun = dlib->getsym(funcname.c_str());
    return fun;
}

} // namespace WinxedXX

// End of winxedxx_nci.cxx
