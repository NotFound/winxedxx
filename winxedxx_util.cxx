// winxedxx_util.cxx
// (C) 2011-2012 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"
#include "winxedxx_handle.h"

#include <sstream>

#include <stdlib.h>
#include <math.h>

#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

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

int wxx_int_cast(int i)                   { return i; }
int wxx_int_cast(double n)                { return n; }
int wxx_int_cast(const std::string &str)  { return atoi(str.c_str()); }
int wxx_int_cast(const WxxObjectPtr &obj) { return obj.get_integer(); }


double wxx_num_cast(int i)                   { return i; }
double wxx_num_cast(double n)                { return n; }
double wxx_num_cast(const std::string &str)
{
    return atof(str.c_str());
}
double wxx_num_cast(const WxxObjectPtr &obj) { return obj.get_number(); }


std::string www_string_cast(int i)
{
    std::ostringstream oss;
    oss << i;
    return oss.str();
}
std::string www_string_cast(double n)
{
    std::ostringstream oss;
    oss << n;
    return oss.str();
}
std::string wxx_string_cast(const std::string &str)  { return str; }
std::string wxx_string_cast(const WxxObjectPtr &obj) { return obj.get_string(); }

std::string wxx_repeat_string(std::string s, int n)
{
    std::string result;
    for (int i = 0; i < n; ++i)
        result += s;
    return result;
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

WxxObjectPtr wxx_die(const std::string &message)
{
    return WxxObjectPtr((WxxObject *)new WxxException(message));
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

int wxx_time()
{
    return time(0);
}

double wxx_floattime()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return (double)t.tv_sec + (double)t.tv_usec / 1.0e6;
}

int wxx_sleep(int t)
{
    sleep(t);
    return 0;
}

int wxx_sleep(double t)
{
    if (t >= 1.0) {
        int seconds = floor(t);
	sleep(seconds);
	t -= seconds;
    }
    usleep(t * 1.0e6);
    return 0;
}

int wxx_length(const std::string &str)
{
    return str.length();
}
int wxx_length(const WxxObjectPtr &obj)
{
    return wxx_length(obj.get_string());
}

std::string wxx_chr(int code)
{
    return std::string(1, code);
}

int wxx_ord(std::string src)
{
    return (unsigned char)src.at(0);
}
int wxx_ord(std::string src, int pos)
{
    return (unsigned char)src.at(pos);
}

std::string wxx_substr(const std::string &from, int start)
{
    return from.substr(start);
}
std::string wxx_substr(const std::string &from, int start, int length)
{
    return from.substr(start, length);
}

int wxx_indexof(const std::string &from, const std::string &search)
{
    return from.find(search);
}
int wxx_indexof(const std::string &from, const std::string &search, int pos)
{
    return from.find(search, pos);
}

std::string wxx_chomp(const std::string &src)
{
    if (std::string::size_type l = src.size())
        if (src[l - 1] == '\n')
            return src.substr(0, l - 1);
    return src;
}

std::string wxx_escape(const std::string &src)
{
    std::ostringstream oss;
    for (std::string::size_type i = 0; i < src.size(); ++i) {
        unsigned char c = src[i];
        switch (c) {
        case '\n':
            oss << "\\n"; break;
        case '\t':
            oss << "\\t"; break;
        case '\\':
            oss << "\\\\"; break;
        default:
            if (c < 0x20 || c >= 0x80)
                oss << "\\x{" << std::hex << (int) c << "}";
            else
                oss << c;
        }
    }
    return oss.str();
}

WxxObjectPtr wxx_new(const std::string &name)
{
    //std::cerr << "wxx_new " << name << '\n';
    return new WxxInstance(name);
}

WxxObjectPtr wxx_new(const std::string &name, WxxObjectArray args)
{
    //std::cerr << "wxx_new " << name << '\n';
    WxxInstance *instance = new WxxInstance(name);
    WxxObjectPtr obj(instance);
    instance->call_method(name, args);
    return obj;
}

WxxObjectPtr wxx_new_string(const std::string &name)
{
    // Sepcial cases for parrot PMC names
    if (name == "Integer")
        return new WxxInteger(0);
    if (name == "Float")
        return new WxxFloat(0.0);
    if (name == "String")
        return new WxxString("");
    if (name == "Hash")
        return new WxxHash();
    if (name == "FileHandle")
        return new WxxFileHandle();

    return wxx_new(name);
}

WxxObjectPtr wxx_open(const std::string &filename)
{
    WxxFileHandle *handle = new WxxFileHandle();
    return handle->open(filename);
}

WxxObjectPtr wxx_open(const std::string &filename, const std::string &mode)
{
    WxxFileHandle *handle = new WxxFileHandle();
    return handle->open(filename, mode);
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
    int pid = fork();
    switch (pid) {
    case 0:
        execvp(argv[0], (char**)argv);
    case -1:
        throw wxx_error("fork failed in spawnw");
    default:
        waitpid(pid, NULL, 0);
    }
    return WxxObjectPtr(0);
}

//*************************************************************

void * wxx_ncigetfunc(WxxObjectPtr lib, const std::string &funcname)
{
    void *fun = 0;
    if (lib.is_null())
        fun = dlsym(NULL, funcname.c_str());
    else if (WxxLibrary *dlib = lib.getlib())
        fun = dlib->getsym(funcname.c_str());
    return fun;
}

} // namespace WinxedXX

// End
