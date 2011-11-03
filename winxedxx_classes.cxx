// winxedxx_classes.cxx
// (C) 2011 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_null.h"
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

std::string WxxNull::class_name() const
{
    return "Null";
}

int WxxNull::is_null() const { return 1; }

int WxxNull::instanceof(const std::string &type)
{
    nullaccess("instanceof");
    return 0;
}

int WxxNull::get_bool()
{
    nullaccess("get_bool");
    return 0;
}

int WxxNull::get_integer()
{
    nullaccess("get_integer");
    return 0;
}

double WxxNull::get_number()
{
    nullaccess("get_number");
    return 0;
}

int WxxNull::elements()
{
    nullaccess("elements");
    return 0;
}

std::string WxxNull::get_string()
{
    nullaccess("get_string");
    return std::string();
}

int WxxNull::is_equal(const WxxObject &to)
{
    nullaccess("is_equal");
    return 0;
}

WxxObject & WxxNull::set(int value)
{
    nullaccess("set");
    return *this;
}

WxxObject & WxxNull::set(double value)
{
    nullaccess("set");
    return *this;
}

WxxObject & WxxNull::set(const char *s)
{
    nullaccess("set");
    return *this;
}

WxxObject & WxxNull::set(const std::string &s)
{
    nullaccess("set");
    return *this;
}

void WxxNull::increment()
{
    nullaccess("increment");
}

void WxxNull::decrement()
{
    nullaccess("decrement");
}

std::string WxxNull::get_string_keyed(int i)
{
    nullaccess("get_pmc_keyed");
    return std::string();
}

WxxObjectPtr WxxNull::get_pmc_keyed(int i)
{
    nullaccess("get_pmc_keyed");
    return winxedxxnull;
}

WxxObjectPtr WxxNull::get_pmc_keyed(const std::string &s)
{
    nullaccess("get_pmc_keyed");
    return winxedxxnull;
}

WxxObjectPtr WxxNull::get_pmc_keyed(const char *s)
{
    nullaccess("get_pmc_keyed");
    return winxedxxnull;
}

void WxxNull::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    nullaccess("set_pmc_keyed");
}

WxxObjectPtr & WxxNull::set_pmc_keyed(const std::string &s, const WxxObjectPtr &value)
{
    nullaccess("set_pmc_keyed");
    return winxedxxnull;
}

int WxxNull::exists(const std::string &key)
{
    nullaccess("exists");
    return 0;
}

WxxObjectPtr & WxxNull::get_attr_str(const std::string &s)
{
    nullaccess("get_attr_str");
    return winxedxxnull;
}

void WxxNull::set_attr_str(const std::string &s, const WxxObjectPtr &value)
{
    nullaccess("set_attr_str");
}

WxxObjectPtr WxxNull::get_iter()
{
    nullaccess("get_iter");
    return winxedxxnull;
}

WxxObjectPtr WxxNull::shift_pmc()
{
    nullaccess("shift_pmc");
    return winxedxxnull;
}

WxxObjectPtr WxxNull::operator()(WxxObjectArray &args)
{
    nullaccess("invoke");
    return winxedxxnull;
}

WxxObjectPtr WxxNull::call_method(const std::string &methname, WxxObjectArray &args)
{
    nullaccess("call_method");
    return winxedxxnull;
}

void WxxNull::print()
{
    nullaccess("print");
}

void WxxNull::print(WxxObjectPtr)
{
    nullaccess("print");
}

void WxxNull::nullaccess(const std::string &funcname)
{
    throw wxx_error("Null WxxObject in " + funcname);
}

//*************************************************************

WxxDefault::WxxDefault(const char *name)
{
    this->name = name;
}

WxxDefault::WxxDefault(const std::string &name)
{
    this->name = name;
}

WxxDefault::~WxxDefault()
{
    //std::cerr << "~WxxDefault " << name << "\n";
}

std::string WxxDefault::class_name() const
{
    return name;
}

int WxxDefault::is_null() const
{ return 0; }

std::string WxxDefault::getname() const { return name; }

int WxxDefault::instanceof(const std::string &type)
{
    return type == name;
}

int WxxDefault::get_bool()
{
    return get_integer();
}

int WxxDefault::get_integer()
{
    notimplemented("get_integer");
    return 0;
}

double WxxDefault::get_number()
{
    notimplemented("get_number");
    return 0;
}

int WxxDefault::elements()
{
    notimplemented("elements");
    return 0;
}

std::string WxxDefault::get_string()
{
    notimplemented("get_string");
    return std::string();
}

int WxxDefault::is_equal(const WxxObject &to)
{
    notimplemented("is_equal");
    return 0;
}

WxxObject & WxxDefault::set(int value)
{
    notimplemented("set");
    return *this;
}

WxxObject & WxxDefault::set(double value)
{
    notimplemented("set");
    return *this;
}

WxxObject & WxxDefault::set(const char *s)
{
    notimplemented("set");
    return *this;
}

WxxObject & WxxDefault::set(const std::string &s)
{
    notimplemented("set");
    return *this;
}

void WxxDefault::increment()
{
    notimplemented("increment");
}

void WxxDefault::decrement()
{
    notimplemented("decrement");
}

std::string WxxDefault::get_string_keyed(int i)
{
    return get_pmc_keyed(i);
}

WxxObjectPtr WxxDefault::get_pmc_keyed(int i)
{
    notimplemented("get_pmc_keyed");
    return winxedxxnull;
}

WxxObjectPtr WxxDefault::get_pmc_keyed(const std::string &s)
{
    notimplemented("get_pmc_keyed");
    return winxedxxnull;
}

WxxObjectPtr WxxDefault::get_pmc_keyed(const char *s)
{
    notimplemented("get_pmc_keyed");
    return winxedxxnull;
}

void WxxDefault::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    notimplemented("set_pmc_keyed");
}

WxxObjectPtr & WxxDefault::set_pmc_keyed(const std::string &s, const WxxObjectPtr &value)
{
    notimplemented("set_pmc_keyed");
    return winxedxxnull;
}
int WxxDefault::exists(const std::string &key)
{
    notimplemented("exists");
    return 0;
}

WxxObjectPtr & WxxDefault::get_attr_str(const std::string &s)
{
    std::map<std::string, WxxObjectPtr>::iterator attr = attributes.find(s);
    if (attr == attributes.end())
        return winxedxxnull;
    else
        return attr->second;
}

void WxxDefault::set_attr_str(const std::string &s, const WxxObjectPtr &value)
{
    attributes[s] = value;
}

WxxObjectPtr WxxDefault::get_iter()
{
    notimplemented("get_iter");
    return winxedxxnull;
}

WxxObjectPtr WxxDefault::shift_pmc()
{
    notimplemented("shift_pmc");
    return winxedxxnull;
}

WxxObjectPtr WxxDefault::operator()(WxxObjectArray &args)
{
    notimplemented("invoke");
    return winxedxxnull;
}

WxxObjectPtr WxxDefault::call_method(const std::string &methname, WxxObjectArray &args)
{
    throw wxx_error("Method '" + methname +
            "' not found for invocant of class '" + name + "'");
    return winxedxxnull;
}

void WxxDefault::print()
{
    std::cout << this->get_string();
}

void WxxDefault::print(WxxObjectPtr)
{
    notimplemented("print");
}

void WxxDefault::notimplemented(const std::string &funcname)
{
    throw wxx_error(funcname + " not implemented in " + name);
}

//*************************************************************

WxxInteger::WxxInteger(int value) : WxxDefault("Integer")
{
    i = value;
}

std::string WxxInteger::class_name() const
{
    return "Integer";
}

int WxxInteger::get_integer() { return i; };

double WxxInteger::get_number() { return i; }

std::string WxxInteger::get_string()
{
    std::ostringstream oss;
    oss << i;
    return oss.str();
}

int WxxInteger::is_equal(const WxxObject &to)
{
    if (const WxxInteger *fromint = dynamic_cast<const WxxInteger *>(& to))
        return i == fromint->i;
    else
        return false;
}

WxxObject & WxxInteger::set(int value)
{
    i = value;
    return *this;
}

WxxObject & WxxInteger::set(double value)
{
    i = value;
    return *this;
}

void WxxInteger::increment()
{
    ++i;
}

void WxxInteger::decrement()
{
    --i;
}

void WxxInteger::print() { std::cout << i; }

//*************************************************************

WxxFloat::WxxFloat(double value) : WxxDefault("Float")
{
    n = value;
}

std::string WxxFloat::class_name() const
{
    return "Float";
}

int WxxFloat::get_integer() { return n; };

double WxxFloat::get_number() { return n; }

std::string WxxFloat::get_string()
{
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

WxxObject & WxxFloat::set(int value)
{
    n = value;
    return *this;
}

WxxObject & WxxFloat::set(double value)
{
    n = value;
    return *this;
}

void WxxFloat::print() { std::cout << n; }

//*************************************************************

WxxString::WxxString(std::string value) : WxxDefault("String")
{
    str = value;
}

std::string WxxString::class_name() const
{
    return "String";
}

std::string WxxString::get_string() { return str; }

WxxObject & WxxString::set(const char *s)
{
    str = s;
    return *this;
}

WxxObject & WxxString::set(const std::string &s)
{
    str = s;
    return *this;
}

WxxObjectPtr WxxString::get_iter()
{
    return WxxObjectPtr(new WxxStringIterator(str));
}

void WxxString::print() { std::cout << str; }

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

WxxObjectArray& WxxObjectArray::push(const char *str)
{
    arr.push_back(new WxxObjectPtr(str));
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

WxxObjectPtr WxxHash::get_pmc_keyed(const char *s)
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


//*************************************************************

WxxInstance::WxxInstance(const std::string &clname) :
        WxxDefault(clname)
{
    cl = WxxClass::getclass(clname);
    if (! cl)
        throw wxx_error("class not found: " + clname);
}

std::string WxxInstance::class_name() const
{
    return cl->class_name();
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
