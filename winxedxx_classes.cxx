// winxedxx_classes.cxx
// (C) 2011 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"

#include <iostream>
#include <sstream>

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
        throw "Byebye";
    if (--refcount == 0)
        delete this;
}

//*************************************************************

WxxArrayBase::WxxArrayBase(const std::string &name) :
        WxxDefault(name)
{
}

int WxxArrayBase::get_integer()
{
    return elements();
}

WxxObjectPtr WxxArrayBase::get_iter()
{
    return WxxObjectPtr(new WxxArrayIterator(this));
}

//*************************************************************

WxxArrayIterator::WxxArrayIterator(WxxObject *container) :
        WxxDefault("ArrayIterator"),
        cnt(container),
        current(0)
{
    cnt->incref();
}

WxxArrayIterator::~WxxArrayIterator()
{
    cnt->decref();
}

int WxxArrayIterator::get_bool()
{
    return current < cnt->elements();
}

WxxObjectPtr WxxArrayIterator::shift_pmc()
{
    return cnt->get_pmc_keyed(current++);
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
    return std::string(1, cnt.at(current++));
}

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
        push(std::string(argv[argi]));
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
    arr.push_back(wxx_string_cast(i));
    return *this;
}

WxxStringArray& WxxStringArray::push(double value)
{
    arr.push_back(wxx_string_cast(value));
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

WxxObjectPtr WxxStringArray::call_method(const std::string &methname, WxxObjectArray &args)
{
    if (methname == "shift") {
        if (arr.size() == 0)
            throw wxx_error("Can't shift from an empty array");
        std::string result = this->operator[](0);
        arr.erase(arr.begin());
        return WxxObjectPtr(result);
    }
    return WxxDefault::call_method(methname, args);
}

//*************************************************************

WxxObjectArray::WxxObjectArray() :
        WxxArrayBase("ResizablePMCArray")
{
}

WxxObjectArray::~WxxObjectArray()
{
    for (unsigned int i = 0; i < arr.size(); ++i)
        delete arr[i];
}

int WxxObjectArray::elements()
{
    return arr.size();
}

WxxObjectPtr WxxObjectArray::get_pmc_keyed(int i)
{
    return this->operator[](i);
}

WxxObjectPtr WxxObjectArray::operator[](int i) const
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw wxx_error(getname() + ": index out of bounds!");
    if (i >= size)
         return winxedxxnull;
    return WxxObjectPtr(*(arr[i]));
}

WxxObjectArray& WxxObjectArray::push(WxxObjectPtr obj)
{
    arr.push_back(new WxxObjectPtr(obj));
    return *this;
}

WxxObjectArray& WxxObjectArray::push(int i)
{
    arr.push_back(new WxxObjectPtr(i));
    return *this;
}

WxxObjectArray& WxxObjectArray::push(double value)
{
    arr.push_back(new WxxObjectPtr(value));
    return *this;
}

WxxObjectArray& WxxObjectArray::push(const std::string &str)
{
    arr.push_back(new WxxObjectPtr(str));
    return *this;
}

void WxxObjectArray::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    arr[i] = new WxxObjectPtr(value);
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

WxxObjectPtr & WxxHash::set_pmc_keyed(const std::string &s, const WxxObjectPtr &value)
{
    hsh[s] = value;
    return hsh[s];
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

void * WxxLibrary::getsym(const std::string &funcname)
{
    return dlsym(dl_h, funcname.c_str());
}

//*************************************************************

} // namespace WinxedXX

// End
