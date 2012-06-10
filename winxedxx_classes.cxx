// winxedxx_classes.cxx
// (C) 2011-2012 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <stdlib.h>

#include <dlfcn.h>

namespace WinxedXX
{

//*************************************************************

WxxRefcounted::WxxRefcounted() : refcount(0)
{
}

WxxRefcounted::WxxRefcounted(size_t initial) : refcount(initial)
{
}

WxxRefcounted::~WxxRefcounted()
{
}

void WxxRefcounted::incref()
{
    ++refcount;
}

void WxxRefcounted::decref()
{
    if (refcount <= 0)
        throw std::logic_error("refcounting error");
    if (--refcount == 0)
        delete this;
}

//*************************************************************

WxxStringIterator::WxxStringIterator(const std::string &container) :
        WxxDefault("StringIterator"),
        cnt(container),
        current(0)
{
}

WxxStringIterator::~WxxStringIterator()
{
}

int WxxStringIterator::get_bool()
{
    return current < int(cnt.size());
}

WxxObjectPtr WxxStringIterator::shift_pmc()
{
    return new WxxString(std::string(1, cnt.at(current++)));
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

int WxxHash::elements() const
{
    return hsh.size();
}

WxxObjectPtr WxxHash::get_pmc_keyed(const std::string &s)
{
    return hsh[s];
}

void WxxHash::set_pmc_keyed(const std::string &s, const WxxObjectPtr &value)
{
    hsh[s] = value;
}

int WxxHash::exists(const std::string &key)
{
    return hsh.find(key) != hsh.end();
}

//*************************************************************

WxxSub::WxxSub(WxxObjectPtr(*fnarg)(const WxxObjectArray &)) :
        WxxDefault("Sub"),
	fn(fnarg)
{
}

WxxSub::WxxSub(WxxObjectPtr(*fnarg)(const WxxObjectArray &),
            const std::string &subname) :
        WxxDefault("Sub"),
        name(subname),
	fn(fnarg)
{
}

std::string WxxSub::get_string()
{
    return name;
}

void * WxxSub::get_pointer()
{
    return (void *)fn;
}

WxxObjectPtr WxxSub::operator()(WxxObjectArray &args)
{
    return (*fn)(args);
}

//*************************************************************

WxxClosure::WxxClosure(WxxInnerFunction * fnarg) :
        WxxDefault("Sub"),
	fn(fnarg)
{
    fn->incref();
}

WxxClosure::~WxxClosure()
{
    fn->decref();
}

WxxObjectPtr WxxClosure::operator()(WxxObjectArray &args)
{
    return (*fn)(args);
}

//*************************************************************

typedef std::map<std::string, WxxClass *> WxxClassReg;
typedef std::vector<std::string> attrs_t;
typedef std::map<std::string, WxxClass::memberfun> regfun_t;

static WxxClassReg *wxxclassreg = 0;

WxxClass * WxxClass::getclass(const std::string &name)
{
    if (wxxclassreg)
        return (*wxxclassreg)[name];
    else
        return 0;
}

WxxClass::WxxClass(const std::string &name) :
        WxxDefault("Class"),
        clname(name)
{
    if (! wxxclassreg)
        wxxclassreg = new WxxClassReg();
    (*wxxclassreg)[name] = this;
}

std::string WxxClass::get_string()
{
    return clname;
}

std::string WxxClass::class_name() const
{
    return clname;
}

void WxxClass::addbase(WxxClass *base)
{
    if (!base)
        throw std::runtime_error("Invalid call to addbase");
    attrs_t & baseattrs = base->attrs;
    for (attrs_t::iterator it = baseattrs.begin(); it != baseattrs.end(); ++it)
        addattribute(*it);
    regfun_t & baseregfun = base->regfun;
    for (regfun_t::iterator it = baseregfun.begin(); it != baseregfun.end(); ++it)
        addfunction(it->first, it->second);
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

WxxObjectPtr WxxClass::get_class()
{
    return this;
}

WxxObjectPtr WxxClass::instantiate()
{
    return new WxxInstance(*this);
}

WxxObjectPtr WxxClass::call_method(const std::string &methname, WxxObjectArray &args)
{
    if (methname == "new")
        return instantiate();
    else
        return WxxDefault::call_method(methname, args);
}

//*************************************************************

WxxInstance::WxxInstance(const std::string &clname) :
        WxxDefault(clname)
{
    cl = WxxClass::getclass(clname);
    if (! cl)
        throw wxx_error("class not found: " + clname);
}

WxxInstance::WxxInstance(WxxClass &classobj) :
        WxxDefault(classobj.class_name()),
        cl(& classobj)
{
}

std::string WxxInstance::class_name() const
{
    return cl->class_name();
}

WxxObjectPtr WxxInstance::get_class()
{
    return cl;
}

WxxObjectPtr WxxInstance::call_method(const std::string &methname, WxxObjectArray &args)
{
    WxxClass::memberfun fun = cl->getfunction(methname);
    if (fun) {
        WxxObjectPtr obj(this);
        return (*fun)(obj, args);
    }
    else
        throw wxx_error("method '" + methname + "' not found in '" + class_name() + "'");
    return winxedxxnull;
}

//*************************************************************

WxxLibrary::WxxLibrary(void *dl_handle) :
        WxxDefault("ParrotLibrary"),
        dl_h(dl_handle)
{
}

int WxxLibrary::get_bool()
{
    return dl_h != 0;
}

int WxxLibrary::get_integer()
{
    return dl_h != 0;
}

void * WxxLibrary::get_pointer()
{
    return dl_h;
}

void * WxxLibrary::getsym(const std::string &funcname)
{
    return dlsym(dl_h, funcname.c_str());
}

//*************************************************************

} // namespace WinxedXX

// End
