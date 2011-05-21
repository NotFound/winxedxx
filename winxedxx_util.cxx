// winxedxx_util.cxx
// (C) 2011 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"
#include "winxedxx_handle.h"

#include <sstream>

#include <dlfcn.h>

namespace WinxedXX
{

WxxObjectPtr winxedxxnull;

//*************************************************************

class WxxException : public WxxDefault
{
public:
    WxxException(const std::string &message, int severity = 2, int type = 0);
    std::string get_string();
private:
    std::string msg;
    int sev;
    int typ;
};

WxxException::WxxException(const std::string &message, int severity, int type) :
        WxxDefault("Exception"),
        msg(message),
        sev(severity),
        typ(type)
{
    set_attr_str(std::string("message"), WxxObjectPtr(message));
    set_attr_str(std::string("severity"), WxxObjectPtr(severity));
    set_attr_str(std::string("type"), WxxObjectPtr(type));
}

std::string WxxException::get_string()
{ return msg; }

//*************************************************************

std::string wxx_int_to_string(int i)
{
    std::ostringstream oss;
    oss << i;
    return oss.str();
}

std::string wxx_num_to_string(double value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}


WxxObjectPtr wxx_error(const std::string &message)
{
    return WxxObjectPtr((WxxObject *)new WxxException(message));
}
WxxObjectPtr wxx_error(const std::string &message, int severity)
{
    return WxxObjectPtr((WxxObject *)new WxxException(message, severity));
}
WxxObjectPtr wxx_error(const std::string &message, int severity, int type)
{
    return WxxObjectPtr((WxxObject *)new WxxException(message, severity, type));
}

WxxObjectPtr wxx_getstdin()
{
    return WxxObjectPtr(new WxxFileHandle(1));
}
WxxObjectPtr wxx_getstdout()
{
    return WxxObjectPtr(new WxxFileHandle(2));
}
WxxObjectPtr wxx_getstderr()
{
    return WxxObjectPtr(new WxxFileHandle(3));
}

WxxObjectPtr wxx_loadlib(const std::string &libname)
{
    void *dl_handle = dlopen(libname.c_str(), RTLD_LAZY);
    if (dl_handle == NULL)
        return WxxObjectPtr(0); // Sort of Undef for a now
    else
        return WxxObjectPtr(new WxxLibrary(dl_handle));
}

WxxObjectPtr wxx_spawnw(WxxObjectPtr obj)
{
    int len = obj.elements();
    std::string args[len + 1];
    const char *argv[len + 1];
    for (int i = 0; i < len; ++i) {
        args[i] = std::string(obj.get_pmc_keyed(i));
        argv[i] = args[i].c_str();
    }
    argv[len] = 0;
    if (fork() != 0)
        execvp(argv[0], (char**)argv);
    return WxxObjectPtr(0);
}

} // namespace WinxedXX

// End
