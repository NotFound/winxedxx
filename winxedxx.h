#ifndef INCLUDE_WINXEDXX_H
#define INCLUDE_WINXEDXX_H

// winxedxx.h
// (C) 2011 Julián Albo "NotFound"

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_null.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"
#include "winxedxx_handle.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <dlfcn.h>

namespace WinxedXX
{

class WxxObjectPtr;
class WxxObjectArray;

std::string wxx_int_to_string(int i);
std::string wxx_num_to_string(double value);
std::string wxx_repeat_string(std::string s, int n);


class WxxIntegerArray : public WxxArrayBase
{
public:
    WxxIntegerArray();
    ~WxxIntegerArray();
    int elements();
    int operator[](int i) const;
    WxxObjectPtr get_pmc_keyed(int i);
    WxxIntegerArray& push(WxxObjectPtr obj);
    WxxIntegerArray& push(int i);
    WxxIntegerArray& push(double value);
    WxxIntegerArray& push(const char *str);
    WxxIntegerArray& push(const std::string &str);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
private:
    std::vector<int> arr;
};

class WxxFloatArray : public WxxArrayBase
{
public:
    WxxFloatArray();
    ~WxxFloatArray();
    int elements();
    double operator[](int i) const;
    WxxObjectPtr get_pmc_keyed(int i);
    WxxFloatArray& push(WxxObjectPtr obj);
    WxxFloatArray& push(int i);
    WxxFloatArray& push(double value);
    WxxFloatArray& push(const char *str);
    WxxFloatArray& push(const std::string &str);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
private:
    std::vector<double> arr;
};

class WxxStringArray : public WxxArrayBase
{
public:
    WxxStringArray();
    WxxStringArray(char **argv);
    ~WxxStringArray();
    int elements();
    std::string operator[](int i) const;
    std::string get_string_keyed(int i);
    WxxObjectPtr get_pmc_keyed(int i);
    WxxStringArray& push(WxxObjectPtr obj);
    WxxStringArray& push(int i);
    WxxStringArray& push(double value);
    WxxStringArray& push(const char *str);
    WxxStringArray& push(const std::string &str);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
private:
    std::vector<std::string> arr;
};

class WxxHash : public WxxDefault
{
public:
    WxxHash();
    WxxHash & set(const std::string &key, WxxObjectPtr value);
    using WxxDefault::set_pmc_keyed;
    WxxObjectPtr &set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    WxxObjectPtr get_pmc_keyed(const char *s);
private:
    std::map<std::string, WxxObjectPtr> hsh;
};

class WxxNCI : public WxxDefault
{
public:
    WxxNCI(const std::string &funcname);
    WxxObjectPtr operator()(WxxObjectArray &args);
protected:
    std::string name;
};

template <typename NciSig, int nargs>
class WxxNCIcall : public WxxNCI
{
public:
    WxxNCIcall(WxxObjectPtr lib, const std::string &funcname);
    WxxObjectPtr operator()(WxxObjectArray &args);
private:
    WxxObjectPtr call(WxxObjectArray &args);
    NciSig fun;
};

//*************************************************************

WxxIntegerArray::WxxIntegerArray() :
        WxxArrayBase("ResizableIntegerArray")
{
}

WxxIntegerArray::~WxxIntegerArray()
{
}

int WxxIntegerArray::elements()
{
    return arr.size();
}

WxxObjectPtr WxxIntegerArray::get_pmc_keyed(int i)
{
    return this->operator[](i);
}

int WxxIntegerArray::operator[](int i) const
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw wxx_error(getname() + ": index out of bounds!");
    if (i >= size)
         return winxedxxnull;
    return arr[i];
}

WxxIntegerArray& WxxIntegerArray::push(WxxObjectPtr obj)
{
    arr.push_back(obj);
    return *this;
}

WxxIntegerArray& WxxIntegerArray::push(int i)
{
    arr.push_back(i);
    return *this;
}

WxxIntegerArray& WxxIntegerArray::push(double value)
{
    arr.push_back(value);
    return *this;
}

WxxIntegerArray& WxxIntegerArray::push(const char *str)
{
    arr.push_back(atoi(str));
    return *this;
}

WxxIntegerArray& WxxIntegerArray::push(const std::string &str)
{
    arr.push_back(atoi(str.c_str()));
    return *this;
}

void WxxIntegerArray::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    arr[i] = value;
}

//*************************************************************

WxxFloatArray::WxxFloatArray() :
        WxxArrayBase("ResizableFloatArray")
{
}

WxxFloatArray::~WxxFloatArray()
{
}

int WxxFloatArray::elements()
{
    return arr.size();
}

WxxObjectPtr WxxFloatArray::get_pmc_keyed(int i)
{
    return this->operator[](i);
}

double WxxFloatArray::operator[](int i) const
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw wxx_error(getname() + ": index out of bounds!");
    if (i >= size)
         return winxedxxnull;
    return arr[i];
}

WxxFloatArray& WxxFloatArray::push(WxxObjectPtr obj)
{
    arr.push_back(obj);
    return *this;
}

WxxFloatArray& WxxFloatArray::push(int i)
{
    arr.push_back(i);
    return *this;
}

WxxFloatArray& WxxFloatArray::push(double value)
{
    arr.push_back(value);
    return *this;
}

WxxFloatArray& WxxFloatArray::push(const char *str)
{
    arr.push_back(strtod(str, 0));
    return *this;
}

WxxFloatArray& WxxFloatArray::push(const std::string &str)
{
    arr.push_back(strtod(str.c_str(), 0));
    return *this;
}

void WxxFloatArray::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    arr[i] = value;
}

//*************************************************************

WxxStringArray::WxxStringArray() :
        WxxArrayBase("ResizableStringArray")
{
}

// Special purpose initialization intended only for usage from main.
WxxStringArray::WxxStringArray(char **argv) :
        WxxArrayBase("ResizableStringArray")
{
    for (int argi = 0; argv[argi]; ++argi)
        push(argv[argi]);
}

WxxStringArray::~WxxStringArray()
{
}

int WxxStringArray::elements()
{
    return arr.size();
}

std::string WxxStringArray::get_string_keyed(int i)
{
    return this->operator[](i);
}

WxxObjectPtr WxxStringArray::get_pmc_keyed(int i)
{
    return this->operator[](i);
}

std::string WxxStringArray::operator[](int i) const
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw wxx_error(getname() + ": index out of bounds!");
    if (i >= size)
         return winxedxxnull;
    return arr[i];
}

WxxStringArray& WxxStringArray::push(WxxObjectPtr obj)
{
    arr.push_back(obj);
    return *this;
}

WxxStringArray& WxxStringArray::push(int i)
{
    arr.push_back(wxx_int_to_string(i));
    return *this;
}

WxxStringArray& WxxStringArray::push(double value)
{
    arr.push_back(wxx_num_to_string(value));
    return *this;
}

WxxStringArray& WxxStringArray::push(const char *str)
{
    arr.push_back(std::string(str));
    return *this;
}

WxxStringArray& WxxStringArray::push(const std::string &str)
{
    arr.push_back(str);
    return *this;
}

void WxxStringArray::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    arr[i] = std::string(value);
}

//*************************************************************

WxxHash::WxxHash() : WxxDefault("Hash")
{
}

WxxHash &WxxHash::set(const std::string &key, WxxObjectPtr value)
{
    hsh[key] = value;
    return *this;
}

WxxObjectPtr WxxHash::get_pmc_keyed(const std::string &s)
{
    return hsh[s];
}

WxxObjectPtr WxxHash::get_pmc_keyed(const char *s)
{
    return hsh[s];
}

WxxObjectPtr & WxxHash::set_pmc_keyed(const std::string &s, const WxxObjectPtr &value)
{
    hsh[s] = value;
    return hsh[s];
}

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

void * wxxncigetfunc(WxxObjectPtr lib, const std::string &funcname)
{
    void *fun = 0;
    if (lib.is_null())
        fun = dlsym(NULL, funcname.c_str());
    else if (WxxLibrary *dlib = lib.getlib())
        fun = dlib->getsym(funcname.c_str());
    return fun;
}


template <typename NciSig>
class WxxNCIcall<NciSig, 0> : public WxxNCI
{
public:
    WxxNCIcall(WxxObjectPtr lib, const std::string &funcname) :
        WxxNCI(funcname),
        fun((NciSig)wxxncigetfunc(lib, funcname))
    { }
    WxxObjectPtr operator()(WxxObjectArray &args)
    {
        if (! fun)
            throw wxx_error("dynamic function -0- is null: " + name);
        return (*fun)();
    }
private:
    NciSig fun;
};

template <typename NciSig>
class WxxNCIcall<NciSig, 1> : public WxxNCI
{
public:
    WxxNCIcall(WxxObjectPtr lib, const std::string &funcname) :
        WxxNCI(funcname),
        fun((NciSig)wxxncigetfunc(lib, funcname))
    { }
    WxxObjectPtr operator()(WxxObjectArray &args)
    {
        if (! fun)
            throw wxx_error("dynamic function -1- is null: " + name);
        return (*fun)(args[0]);
    }
private:
    NciSig fun;
};

template <typename NciSig, int nargs>
WxxObjectPtr WxxNCIcall<NciSig, nargs>::operator()(WxxObjectArray &args)
{
    if (! fun)
        throw wxx_error("dynamic function is null: " + name);
    return winxedxxnull;
}

//*************************************************************

class WxxClass : public WxxDefault
{
public:
    typedef WxxObjectPtr (*memberfun)(WxxObjectPtr &, const WxxObjectArray &);

    WxxClass(const std::string &name);
    void addattribute(const std::string &attrname);
    void addfunction(const std::string &fname, memberfun);
    memberfun getfunction(const std::string &fname);
    static WxxClass * getclass(const std::string &name);
private:
    std::string clname;
    std::vector<std::string> attrs;
    static std::map<std::string, WxxClass *> reg;
    std::map<std::string, memberfun> regfun;
};

std::map<std::string, WxxClass *> WxxClass::reg;

WxxClass * WxxClass::getclass(const std::string &name)
{
    return reg[name];
}

WxxClass::WxxClass(const std::string &name) :
        WxxDefault("Class"),
        clname(name)
{
    reg[name] = this;
}

void WxxClass::addattribute(const std::string &attrname)
{
    attrs.push_back(attrname);
}

void WxxClass::addfunction(const std::string &fname, memberfun fun)
{
    regfun[fname] = fun;
}

WxxClass::memberfun WxxClass::getfunction(const std::string &fname)
{
    return regfun[fname];
}


class WxxInstance : public WxxDefault
{
public:
    WxxInstance(const std::string &clname);
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
private:
    WxxClass *cl;
};

WxxInstance::WxxInstance(const std::string &clname) :
        WxxDefault(clname)
{
    cl = WxxClass::getclass(clname);
    if (! cl)
        throw wxx_error("class not found: " + clname);
}

WxxObjectPtr WxxInstance::call_method(const std::string &methname, WxxObjectArray &args)
{
    WxxClass::memberfun fun = cl->getfunction(methname);
    if (fun) {
        WxxObjectPtr obj(this);
        return (*fun)(obj, args);
    }
    else
        throw wxx_error("method not found");
    return winxedxxnull;
}

//*************************************************************

WxxObjectPtr wxx_new(std::string name)
{
    //std::cerr << "wxx_new " << name << '\n';
    return new WxxInstance(name);
}

WxxObjectPtr wxx_new(std::string name, WxxObjectArray args)
{
    //std::cerr << "wxx_new " << name << '\n';
    WxxInstance *instance = new WxxInstance(name);
    WxxObjectPtr obj(instance);
    instance->call_method(name, args);
    return obj;
}

int wxx_print(int i) { std::cout << i; return 0; }
int wxx_print(const char *s) { std::cout << s; return 0; }
int wxx_print(const std::string &s) { std::cout << s; return 0; }
int wxx_print(double n) { std::cout << n; return 0; }
int wxx_print(WxxObjectPtr obj) { obj.print(); return 0; }

int wxx_eprint(int i) { std::cerr << i; return 0; }
int wxx_eprint(const char *s) { std::cerr << s; return 0; }
int wxx_eprint(const std::string &s) { std::cerr << s; return 0; }
int wxx_eprint(double n) { std::cerr << n; return 0; }
// TODO
int wxx_eprint(WxxObjectPtr obj) { obj.print(); return 0; }

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

WxxObjectPtr wxx_typeof(WxxObjectPtr &thing)
{
    return winxedxxnull;
}

std::string wxx_join(const std::string &sep, WxxObjectPtr &arr)
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

std::string operator + (WxxObjectPtr obj, const std::string &s)
{
    return obj.get_string() + s;
}

std::string operator + (WxxObjectPtr obj, const char *s)
{
    return obj.get_string() + s;
}

std::string operator + (const std::string &s, WxxObjectPtr obj)
{
    return s + obj.get_string();
}

std::string operator + (const char *s, WxxObjectPtr obj)
{
    return s + obj.get_string();
}

int operator == (const WxxObjectPtr &obj, const std::string &str)
{
    return obj.get_string() == str;
}
int operator == (const std::string &str, const WxxObjectPtr &obj)
{
    return obj.get_string() == str;
}
int operator != (WxxObjectPtr &obj, const std::string &str)
{
    return obj.get_string() != str;
}
int operator != (const std::string &str, WxxObjectPtr &obj)
{
    return obj.get_string() != str;
}
int operator == (WxxObjectPtr &obj, int i)
{
    return int(obj) == i;
}
int operator == (int i, WxxObjectPtr &obj)
{
    return int(obj) == i;
}
int operator > (WxxObjectPtr &obj, int i)
{
    return int(obj) > i;
}
int operator > (int i, WxxObjectPtr &obj)
{
    return i > int(obj);
}
int operator < (WxxObjectPtr &obj, int i)
{
    return int(obj) < i;
}
int operator < (int i, WxxObjectPtr &obj)
{
    return i < int(obj);
}
int operator >= (WxxObjectPtr &obj, int i)
{
    return int(obj) >= i;
}
int operator >= (int i, WxxObjectPtr &obj)
{
    return i >= int(obj);
}
int operator <= (WxxObjectPtr &obj, int i)
{
    return int(obj) <= i;
}
int operator <= (int i, WxxObjectPtr &obj)
{
    return i <= int(obj);
}

template <typename NciSig, int nargs>
WxxObjectPtr wxx_dlfunc(WxxObjectPtr lib,
        std::string funcname)
{
    return WxxObjectPtr(new WxxNCIcall<NciSig, nargs>(lib, funcname));
}

} // namespace WinxedXX

#endif

// End of winxedxx.h
