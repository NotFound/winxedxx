#ifndef INCLUDE_WINXEDXX_H
#define INCLUDE_WINXEDXX_H

// winxedxx.h
// (C) 2011 Julián Albo "NotFound"

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

namespace WinxedXX
{

class WxxObjectPtr;
class WxxObjectArray;

//*************************************************************

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

WxxNCI::WxxNCI(const std::string &funcname) :
        WxxDefault("NCI"),
        name(funcname)
{
}

WxxObjectPtr WxxNCI::operator()(WxxObjectArray &args)
{
    return winxedxxnull;
}

void * wxx_ncigetfunc(WxxObjectPtr lib, const std::string &funcname);


template <typename NciSig>
class WxxNCIcall<NciSig, 0> : public WxxNCI
{
public:
    WxxNCIcall(WxxObjectPtr lib, const std::string &funcname) :
        WxxNCI(funcname),
        fun((NciSig)wxx_ncigetfunc(lib, funcname))
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
        fun((NciSig)wxx_ncigetfunc(lib, funcname))
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

template <typename NciSig>
class WxxNCIcall<NciSig, 2> : public WxxNCI
{
public:
    WxxNCIcall(WxxObjectPtr lib, const std::string &funcname) :
        WxxNCI(funcname),
        fun((NciSig)wxx_ncigetfunc(lib, funcname))
    { }
    WxxObjectPtr operator()(WxxObjectArray &args)
    {
        if (! fun)
            throw wxx_error("dynamic function -2- is null: " + name);
        return (*fun)(args[0], args[1]);
    }
private:
    NciSig fun;
};

template <typename NciSig>
class WxxNCIcall<NciSig, 3> : public WxxNCI
{
public:
    WxxNCIcall(WxxObjectPtr lib, const std::string &funcname) :
        WxxNCI(funcname),
        fun((NciSig)wxx_ncigetfunc(lib, funcname))
    { }
    WxxObjectPtr operator()(WxxObjectArray &args)
    {
        if (! fun)
            throw wxx_error("dynamic function -2- is null: " + name);
        return (*fun)(args[0], args[1], args[2]);
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

WxxObjectPtr wxx_typeof(WxxObjectPtr &thing)
{
    // Bogus implementation that allows some tests
    return thing.class_name();
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

int operator == (const WxxObjectPtr &obj, const std::string &str)
{
    return obj.get_string() == str;
}
int operator == (const std::string &str, const WxxObjectPtr &obj)
{
    return obj.get_string() == str;
}
int operator != (const WxxObjectPtr &obj, const std::string &str)
{
    return obj.get_string() != str;
}
int operator != (const std::string &str, const WxxObjectPtr &obj)
{
    return obj.get_string() != str;
}
int operator == (const WxxObjectPtr &obj, int i)
{
    return int(obj) == i;
}
int operator == (int i, const WxxObjectPtr &obj)
{
    return int(obj) == i;
}
int operator != (const WxxObjectPtr &obj, int i)
{
    return int(obj) != i;
}
int operator != (int i, const WxxObjectPtr &obj)
{
    return int(obj) != i;
}
int operator > (const WxxObjectPtr &obj, int i)
{
    return int(obj) > i;
}
int operator > (int i, const WxxObjectPtr &obj)
{
    return i > int(obj);
}
int operator < (const WxxObjectPtr &obj, int i)
{
    return int(obj) < i;
}
int operator < (int i, const WxxObjectPtr &obj)
{
    return i < int(obj);
}
int operator >= (const WxxObjectPtr &obj, int i)
{
    return int(obj) >= i;
}
int operator >= (int i, const WxxObjectPtr &obj)
{
    return i >= int(obj);
}
int operator <= (const WxxObjectPtr &obj, int i)
{
    return int(obj) <= i;
}
int operator <= (int i, const WxxObjectPtr &obj)
{
    return i <= int(obj);
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

//*****************************************

template <typename NciSig, int nargs>
WxxObjectPtr wxx_dlfunc(WxxObjectPtr lib,
        std::string funcname)
{
    return WxxObjectPtr(new WxxNCIcall<NciSig, nargs>(lib, funcname));
}

} // namespace WinxedXX

#endif

// End of winxedxx.h
