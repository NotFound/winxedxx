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


WxxObjectPtr wxx_loadlib(const std::string &libname);
void * wxx_ncigetfunc(WxxObjectPtr lib, const std::string &funcname);

//*************************************************************

class WxxNCI : public WxxDefault
{
public:
    WxxNCI(const std::string &funcname);
    int get_integer();
    void * get_pointer();
    WxxObjectPtr operator() (WxxObjectArray &args);
protected:
    virtual WxxObjectPtr call(WxxObjectArray &args) = 0;
    std::string name;
    virtual void *getNciFun() = 0;
};


template<typename NciParam>
NciParam getarg(const WxxObjectArray &args, int i);

template<>
int getarg(const WxxObjectArray &args, int i)
{ return args[i].get_integer(); }
template<>
double getarg(const WxxObjectArray &args, int i)
{ return args[i].get_number(); }
template<>
std::string getarg(const WxxObjectArray &args, int i)
{ return args[i].get_string(); }


template <typename NciSig>
class WxxNCIbase : public WxxNCI
{
public:
    typedef NciSig signature_t;
    WxxNCIbase(WxxObjectPtr lib, const std::string &funcname) :
        WxxNCI(funcname),
        fun((signature_t)wxx_ncigetfunc(lib, funcname))
    { }
protected:
    NciSig fun;
    void runcheck()
    {
        if (! fun)
            throw wxx_error("dynamic function is null");
    }
private:
    WxxObjectPtr call(WxxObjectArray &args) { return operator()(args); }
    void *getNciFun() { return (void *) fun; }
};



inline void checkargs(WxxObjectArray &args, int n)
{
    if (args.elements() != n)
        throw wxx_error("wrong number of args in nci call");
}

template <typename NciSig>
struct callfunc;

template <typename Ret>
struct callfunc<Ret (*)()>
{
    static WxxObjectPtr doit(Ret (*f)(), WxxObjectArray &args)
    {
        checkargs(args, 0);
        return (*f)();
    }
};
template <>
struct callfunc<void(*)()>
{
    static WxxObjectPtr doit(void (*f)(), WxxObjectArray &args)
    {
        checkargs(args, 0);
        (*f)();
        return winxedxxnull;
    }
};

template <typename Ret, typename Arg0>
struct callfunc<Ret (*)(Arg0)>
{
    static WxxObjectPtr doit(Ret (*f)(Arg0), WxxObjectArray &args)
    {
        checkargs(args, 1);
        return (*f)(getarg<Arg0>(args, 0));
    }
};
template <typename Arg0>
struct callfunc<void (*) (Arg0)>
{
    static WxxObjectPtr doit(void (*f)(Arg0), WxxObjectArray &args)
    {
        checkargs(args, 1);
        (*f)(getarg<Arg0>(args, 0));
        return winxedxxnull;
    }
};

template <typename Ret, typename Arg0, typename Arg1>
struct callfunc<Ret (*)(Arg0, Arg1)>
{
    static WxxObjectPtr doit(Ret (*f)(Arg0, Arg1), WxxObjectArray &args)
    {
        checkargs(args, 2);
        return (*f)(getarg<Arg0>(args, 0), getarg<Arg1>(args, 1));
    }
};
template <typename Arg0, typename Arg1>
struct callfunc<void (*) (Arg0, Arg1)>
{
    static WxxObjectPtr doit(void (*f)(Arg0, Arg1), WxxObjectArray &args)
    {
        checkargs(args, 2);
        (*f)(getarg<Arg0>(args, 0), getarg<Arg1>(args, 1));
        return winxedxxnull;
    }
};

template <typename Ret, typename Arg0, typename Arg1, typename Arg2>
struct callfunc<Ret (*)(Arg0, Arg1, Arg2)>
{
    static WxxObjectPtr doit(Ret (*f)(Arg0, Arg1, Arg2), WxxObjectArray &args)
    {
        checkargs(args, 3);
        return (*f)(getarg<Arg0>(args, 0), getarg<Arg1>(args, 1), getarg<Arg2>(args, 2));
    }
};
template <typename Arg0, typename Arg1, typename Arg2>
struct callfunc<void (*) (Arg0, Arg1, Arg2)>
{
    static WxxObjectPtr doit(void (*f)(Arg0, Arg1, Arg2), WxxObjectArray &args)
    {
        checkargs(args, 3);
        (*f)(getarg<Arg0>(args, 0), getarg<Arg1>(args, 1), getarg<Arg2>(args, 2));
        return winxedxxnull;
    }
};

template <typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct callfunc<Ret (*)(Arg0, Arg1, Arg2, Arg3)>
{
    static WxxObjectPtr doit(Ret (*f)(Arg0, Arg1, Arg2, Arg3), WxxObjectArray &args)
    {
        checkargs(args, 3);
        return (*f)(getarg<Arg0>(args, 0), getarg<Arg1>(args, 1), getarg<Arg2>(args, 2), getarg<Arg3>(args, 3));
    }
};
template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
struct callfunc<void (*)(Arg0, Arg1, Arg2, Arg3)>
{
    static WxxObjectPtr doit(void (*f)(Arg0, Arg1, Arg2, Arg3), WxxObjectArray &args)
    {
        checkargs(args, 3);
        (*f)(getarg<Arg0>(args, 0), getarg<Arg1>(args, 1), getarg<Arg2>(args, 2), getarg<Arg3>(args, 3));
        return winxedxxnull;
    }
};

template <typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct callfunc<Ret (*)(Arg0, Arg1, Arg2, Arg3, Arg4)>
{
    static WxxObjectPtr doit(Ret (*f)(Arg0, Arg1, Arg2, Arg3, Arg4), WxxObjectArray &args)
    {
        checkargs(args, 3);
        return (*f)(getarg<Arg0>(args, 0), getarg<Arg1>(args, 1), getarg<Arg2>(args, 2), getarg<Arg3>(args, 3), getarg<Arg4>(args, 4));
    }
};
template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct callfunc<void (*)(Arg0, Arg1, Arg2, Arg3, Arg4)>
{
    static WxxObjectPtr doit(void (*f)(Arg0, Arg1, Arg2, Arg3, Arg4), WxxObjectArray &args)
    {
        checkargs(args, 3);
        (*f)(getarg<Arg0>(args, 0), getarg<Arg1>(args, 1), getarg<Arg2>(args, 2), getarg<Arg3>(args, 3), getarg<Arg4>(args, 4));
        return winxedxxnull;
    }
};


template <typename NciSig>
class WxxNCIcaller : public WxxNCIbase<NciSig>
{
    typedef WxxNCIbase<NciSig> base;
public:
    WxxNCIcaller(WxxObjectPtr lib, const std::string &funcname) :
        base(lib, funcname)
    { }
    WxxObjectPtr operator()(WxxObjectArray &args)
    {
        base::runcheck();
        return callfunc<NciSig>::doit(base::fun, args);
    }
protected:
};



template <typename Ret>
WxxObjectPtr wxx_dlfunc(WxxObjectPtr lib,
        std::string funcname)
{
    return WxxObjectPtr(new WxxNCIcaller<Ret(*)()>(lib, funcname));
}
template <typename Ret, typename Arg0>
WxxObjectPtr wxx_dlfunc(WxxObjectPtr lib,
        std::string funcname)
{
    return WxxObjectPtr(new WxxNCIcaller<Ret(*)(Arg0)>(lib, funcname));
}
template <typename Ret, typename Arg0, typename Arg1>
WxxObjectPtr wxx_dlfunc(WxxObjectPtr lib,
        std::string funcname)
{
    return WxxObjectPtr(new WxxNCIcaller<Ret(*)(Arg0, Arg1)>(lib, funcname));
}
template <typename Ret, typename Arg0, typename Arg1, typename Arg2>
WxxObjectPtr wxx_dlfunc(WxxObjectPtr lib,
        std::string funcname)
{
    return WxxObjectPtr(new WxxNCIcaller<Ret(*)(Arg0, Arg1, Arg2)>(lib, funcname));
}
template <typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
WxxObjectPtr wxx_dlfunc(WxxObjectPtr lib,
        std::string funcname)
{
    return WxxObjectPtr(new WxxNCIcaller<Ret(*)(Arg0, Arg1, Arg2, Arg3)>(lib, funcname));
}
template <typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
WxxObjectPtr wxx_dlfunc(WxxObjectPtr lib,
        std::string funcname)
{
    return WxxObjectPtr(new WxxNCIcaller<Ret(*)(Arg0, Arg1, Arg2, Arg3, Arg4)>(lib, funcname));
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

} // namespace WinxedXX

#endif

// End of winxedxx.h
