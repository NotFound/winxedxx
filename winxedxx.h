#ifndef INCLUDE_WINXEDXX_H
#define INCLUDE_WINXEDXX_H

// winxedxx.h
// (C) 2011-2012 Julián Albo "NotFound"

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

int wxx_print(int i);
int wxx_print(const std::string &s);
int wxx_print(double n);
int wxx_print(WxxObjectPtr obj);

int wxx_eprint(int i);
int wxx_eprint(const std::string &s);
int wxx_eprint(double n);
int wxx_eprint(WxxObjectPtr obj);

int wxx_instanceof(WxxObjectPtr &obj, const std::string &type);

int wxx_isnull(WxxObjectPtr obj);

int wxx_booland(int li, int ri);
int wxx_boolor(int li, int ri);

WxxObjectPtr wxx_typeof(WxxObjectPtr &thing);

std::string wxx_join(const std::string &sep, const WxxObjectPtr &arr);

WxxObjectPtr wxx_split(const std::string &sep, std::string src);

inline int operator == (const WxxObjectPtr &obj, const std::string &str)
{
    return obj.get_string() == str;
}
inline int operator == (const std::string &str, const WxxObjectPtr &obj)
{
    return obj.get_string() == str;
}
inline int operator != (const WxxObjectPtr &obj, const std::string &str)
{
    return obj.get_string() != str;
}
inline int operator != (const std::string &str, const WxxObjectPtr &obj)
{
    return obj.get_string() != str;
}
inline int operator == (const WxxObjectPtr &obj, int i)
{
    return int(obj) == i;
}
inline int operator == (int i, const WxxObjectPtr &obj)
{
    return int(obj) == i;
}
inline int operator != (const WxxObjectPtr &obj, int i)
{
    return int(obj) != i;
}
inline int operator != (int i, const WxxObjectPtr &obj)
{
    return int(obj) != i;
}
inline int operator > (const WxxObjectPtr &obj, int i)
{
    return int(obj) > i;
}
inline int operator > (int i, const WxxObjectPtr &obj)
{
    return i > int(obj);
}
inline int operator < (const WxxObjectPtr &obj, int i)
{
    return int(obj) < i;
}
inline int operator < (int i, const WxxObjectPtr &obj)
{
    return i < int(obj);
}
inline int operator >= (const WxxObjectPtr &obj, int i)
{
    return int(obj) >= i;
}
inline int operator >= (int i, const WxxObjectPtr &obj)
{
    return i >= int(obj);
}
inline int operator <= (const WxxObjectPtr &obj, int i)
{
    return int(obj) <= i;
}
inline int operator <= (int i, const WxxObjectPtr &obj)
{
    return i <= int(obj);
}

//*********** operator + ****************

int wxx_add(int i1, int i2);
double wxx_add(double f1, double f2);
double wxx_add(double f1, int  i2);
double wxx_add(int i1, double f2);
std::string wxx_add(int i1, std::string s2);
std::string wxx_add(std::string s1, int i2);
WxxObjectPtr wxx_add(int i1, const WxxObjectPtr &o2);
WxxObjectPtr wxx_add(const WxxObjectPtr &o1, int i2);

//*********** operator - ****************

int wxx_sub(int i1, int i2);
double wxx_sub(double f1, double f2);
double wxx_sub(double f1, int  i2);
double wxx_sub(int i1, double f2);
WxxObjectPtr wxx_sub(int i1, const WxxObjectPtr &o2);
WxxObjectPtr wxx_sub(const WxxObjectPtr &o1, int i2);

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
