// winxedxx_util.cxx
// (C) 2011-2012 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"
#include "winxedxx_handle.h"
#include "winxedxx_ptr.h"
#include "winxedxx_bytebuffer.h"

#include <iostream>
#include <sstream>

#include <stdlib.h>
#include <math.h>

#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace WinxedXX
{

WxxObjectPtr winxedxxnull;

//*************************************************************

class WxxException : public WxxDefault
{
public:
    WxxException(const std::string &message = "",
            int severity = 2, int type = 0);
    void init_pmc(const WxxObjectPtr &arg);
    std::string get_string();
    WxxObjectPtr get_pmc_keyed(const std::string &str);
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
    set_attr_str(std::string("message"), WxxObjectPtr(new WxxString(message)));
    set_attr_str(std::string("severity"), WxxObjectPtr(severity));
    set_attr_str(std::string("type"), WxxObjectPtr(type));
}

void WxxException::init_pmc(const WxxObjectPtr &arg)
{
    WxxObjectPtr aux;
    aux = arg.get_pmc_keyed("message");
    if (! aux.is_null())
        set_attr_str(std::string("message"), aux);
    aux = arg.get_pmc_keyed("severity");
    if (! aux.is_null())
        set_attr_str(std::string("severity"), aux);
    aux = arg.get_pmc_keyed("type");
    if (! aux.is_null())
        set_attr_str(std::string("type"), aux);
}

std::string WxxException::get_string()
{ return msg; }

WxxObjectPtr WxxException::get_pmc_keyed(const std::string &str)
{
    return get_attr_str(str);
}

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

//*********** operator + ****************

int wxx_add(int i1, int i2)
{
    return i1 + i2;
}

double wxx_add(double f1, double f2)
{
    return f1 + f2;
}

double wxx_add(double f1, int  i2)
{
    return f1 + i2;
}

double wxx_add(int i1, double f2)
{
    return i1 + f2;
}

std::string wxx_add(int i1, std::string s2)
{
    return wxx_string_cast(i1) + s2;
}

std::string wxx_add(std::string s1, int i2)
{
    return s1 + wxx_string_cast(i2);
}

WxxObjectPtr wxx_add(int i1, const WxxObjectPtr &o2)
{
    return i1 + int(o2);
}

WxxObjectPtr wxx_add(const WxxObjectPtr &o1, int i2)
{
    return int(o1) + i2;
}

WxxObjectPtr wxx_add(WxxObjectPtr &o1, WxxObjectPtr &o2)
{
    return o1.add(o2);
}

//*********** operator - ****************

int wxx_sub(int i1, int i2)
{
    return i1 - i2;
}

double wxx_sub(double f1, double f2)
{
    return f1 - f2;
}

double wxx_sub(double f1, int  i2)
{
    return f1 - i2;
}

double wxx_sub(int i1, double f2)
{
    return i1 - f2;
}

WxxObjectPtr wxx_sub(int i1, const WxxObjectPtr &o2)
{
    return i1 - int(o2);
}

WxxObjectPtr wxx_sub(const WxxObjectPtr &o1, int i2)
{
    return int(o1) - i2;
}

//*********** operator * ****************

int wxx_mul(int i1, int i2)
{
    return i1 * i2;
}

double wxx_mul(double f1, double f2)
{
    return f1 * f2;
}

double wxx_mul(double f1, int  i2)
{
    return f1 * i2;
}

double wxx_mul(int i1, double f2)
{
    return i1 * f2;
}

WxxObjectPtr wxx_mul(int i1, const WxxObjectPtr &o2)
{
    return i1 * o2.get_integer();
}

WxxObjectPtr wxx_mul(const WxxObjectPtr &o1, int i2)
{
    return o1.get_integer() * i2;
}

WxxObjectPtr wxx_mul(WxxObjectPtr &o1, WxxObjectPtr &o2)
{
    return o1.get_integer() * o2.get_integer();
}

//*********** operator / ****************

static void checkdivzero(int value)
{
    // Type and severity hardcoded.
    if (value == 0)
        throw wxx_error("Division by zero", 2, 29);
}
static void checkdivzero(double value)
{
    if (value == 0)
        throw wxx_error("Division by zero");
}

int wxx_div(int i1, int i2)
{
    checkdivzero(i2);
    return i1 / i2;
}

double wxx_div(double f1, double f2)
{
    checkdivzero(f2);
    return f1 / f2;
}

double wxx_div(double f1, int  i2)
{
    checkdivzero(i2);
    return f1 / i2;
}

double wxx_div(int i1, double f2)
{
    checkdivzero(f2);
    return i1 / f2;
}

WxxObjectPtr wxx_div(int i1, const WxxObjectPtr &o2)
{
    int i2 = int(o2);
    checkdivzero(i2);
    return i1 / i2;
}

WxxObjectPtr wxx_div(const WxxObjectPtr &o1, int i2)
{
    checkdivzero(i2);
    return int(o1) / i2;
}

//******************************************************

int wxx_print(int i) { std::cout << i; return 0; }
int wxx_print(const std::string &s) { std::cout << s; return 0; }
int wxx_print(double n) { std::cout << n; return 0; }
int wxx_print(WxxObjectPtr obj) { std::cout << obj.get_string(); return 0; }

int wxx_eprint(int i) { std::cerr << i; return 0; }
int wxx_eprint(const std::string &s) { std::cerr << s; return 0; }
int wxx_eprint(double n) { std::cerr << n; return 0; }
int wxx_eprint(WxxObjectPtr obj) { std::cerr << obj.get_string(); return 0; }

int wxx_instanceof(WxxObjectPtr &obj, const std::string &type)
{
    return obj.instanceof(type);
}
int wxx_isnull(WxxObjectPtr obj)
{
    return obj.is_null();
}

int wxx_booland(int li, int ri)
{
    return li ? ri : li;

}
int wxx_boolor(int li, int ri)
{
    return li ? li : ri;
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

std::string wxx_substr(const std::string &from, int start, int length)
{
    if (start < 0)
        start += length;
    if (start < 0 || start > length || length < 0)
        throw wxx_error("Cannot take substr outside string");
    return from.substr(start, length);
}
std::string wxx_substr(const std::string &from, int start)
{
    return wxx_substr(from, start, from.length());
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

WxxObjectPtr wxx_typeof(WxxObjectPtr &thing)
{
    return thing.get_class();
}

std::string wxx_join(const std::string &sep, const WxxObjectPtr &arr)
{
    std::string result;
    int n = arr.elements();
    for (int i = 0; i < n; ++i)
    {
        if (i > 0)
            result += sep;
        result += arr.get_string_keyed(i);
    }
    return result;
}

WxxObjectPtr wxx_split(const std::string &sep, std::string src)
{
    WxxObjectPtr result(new WxxStringArray());
    std::string::size_type l = sep.length();
    std::string::size_type pos = 0;
    while ((pos = src.find(sep)) != std::string::npos)
    {
        result.push(src.substr(0, pos));
        src.erase(0, pos + l);
    }
    result.push(src);
    return result;
}

std::string wxx_escape(const std::string &src)
{
    std::ostringstream oss;
    for (std::string::size_type i = 0; i < src.size(); ++i) {
        unsigned char c = src[i];
        switch (c) {
        case '\n': oss << "\\n"; break;
        case '\r': oss << "\\n"; break;
        case '\t': oss << "\\t"; break;
        case '\\': oss << "\\\\"; break;
        default:
            if (c < 0x20 || c >= 0x80)
                oss << "\\x{" << std::hex << (int) c << "}";
            else
                oss << c;
        }
    }
    return oss.str();
}

std::string wxx_unescape(const std::string &src)
{
    const int l = src.length();
    std::string result = "";
    for (int i = 0; i < l; ++i) {
        char c = src[i];
        switch (c) {
            case '\\':
            c = src[++i];
            switch (c) {
              case 'n': result += '\n'; break;
              case 'r': result += '\r'; break;
              case 't': result += '\t'; break;
              case '\\': result += '\\'; break;
              default:
                throw wxx_error("unescape not fully implemented");
            }
            break;
          default:
            result += c;
        }
    }
    return result;
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

static WxxObject * new_string(const std::string name)
{
    // Sepcial cases for parrot PMC names
    if (name == "Integer" || name == "Boolean")
        return new WxxInteger(0);
    if (name == "Float")
        return new WxxFloat(0.0);
    if (name == "String")
        return new WxxString("");
    if (name == "Hash")
        return new WxxHash();
    if (name == "ResizableIntegerArray" || name == "FixedIntegerArray")
        return new WxxIntegerArray();
    if (name == "ResizableFloatArray" || name == "FixedFloatArray")
        return new WxxFloatArray();
    if (name == "ResizableStringArray" || name == "FixedStringArray")
        return new WxxStringArray();
    if (name == "ResizablePMCArray" || name == "FixedPMCArray")
        return new WxxObjectArray();
    if (name == "Exception")
        return new WxxException();
    if (name == "FileHandle")
        return new WxxFileHandle();
    if (name == "StringHandle")
        return new WxxStringHandle();
    if (name == "ByteBuffer")
        return new WxxByteBuffer();
    return 0;
}

WxxObjectPtr wxx_new_string(const std::string &name)
{
    WxxObject * obj = new_string(name);
    if (obj)
        return WxxObjectPtr(obj);
    else
        return wxx_new(name);
}

WxxObjectPtr wxx_new_string(const std::string &name, WxxObjectPtr arg)
{
    WxxObject * obj = new_string(name);
    if (! obj)
        obj = new WxxInstance(name);
    obj->init_pmc(arg);
    return WxxObjectPtr(obj);
}

WxxObjectPtr wxx_new_obj(const WxxObjectPtr &clobj)
{
    return clobj.instantiate();
}

WxxObjectPtr wxx_new_obj(const WxxObjectPtr &clobj,
        const std::string &constructor)
{
    WxxObjectPtr obj = clobj.instantiate();
    obj.call_method(constructor);
    return obj;
}

WxxObjectPtr wxx_new_obj(const WxxObjectPtr &clobj,
        const std::string &constructor, WxxObjectArray args)
{
    WxxObjectPtr obj = clobj.instantiate();
    obj.call_method(constructor, args);
    return obj;
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

WxxObjectPtr wxx_spawnw(WxxObjectPtr obj)
{
    int len = obj.elements();
    std::string args[len + 1];
    const char *argv[len + 1];
    for (int i = 0; i < len; ++i) {
        args[i] = obj.get_string_keyed(i);
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
    return WxxObjectPtr(new WxxInteger(0));
}

} // namespace WinxedXX

// End
