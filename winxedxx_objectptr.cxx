// winxedxx_objectptr.cxx
// (C) 2011 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_null.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"
#include "winxedxx_namespace.h"


namespace WinxedXX
{

WxxObjectPtr::WxxObjectPtr() : object(new WxxNull())
{
    object->incref();
}

WxxObjectPtr::WxxObjectPtr(int value) : object(new WxxInteger(value))
{
    object->incref();
}

WxxObjectPtr::WxxObjectPtr(double value) : object(new WxxFloat(value))
{
    object->incref();
}

WxxObjectPtr::WxxObjectPtr(const std::string &value) :
        object(new WxxString(value))
{
    object->incref();
}

WxxObjectPtr::WxxObjectPtr(const WxxObjectPtr &old) :
    object(old.object)
{
    object->incref();
}

WxxObjectPtr::WxxObjectPtr(WxxObject * obj) : object(obj)
{
    object->incref();
}

WxxObjectPtr::WxxObjectPtr(WxxObjectPtr (*fn)(const WxxObjectArray&)) :
        object(new WxxSub(fn))
{
    object->incref();
}

WxxObjectPtr::WxxObjectPtr(WxxInnerFunction * obj) :
        object(new WxxClosure(obj))
{
    object->incref();
}

WxxObjectPtr::WxxObjectPtr(WxxNamespace * obj) :
        object(obj)
{
    object->incref();
}

WxxObjectPtr::~WxxObjectPtr()
{
    if (object)
        object->decref();
}

std::string WxxObjectPtr::class_name() const
{
    if (object)
        return object->class_name();
    else
        return "Null";
}

WxxObjectPtr & WxxObjectPtr::set(int value)
{
    object->set(value);
    return *this;
}

WxxObjectPtr & WxxObjectPtr::set(double value)
{
    object->set(value);
    return *this;
}

WxxObjectPtr & WxxObjectPtr::set(const std::string &s)
{
    object->set(s);
    return *this;
}

WxxObjectPtr & WxxObjectPtr::operator = (const WxxObjectPtr &from)
{
    from.object->incref();
    object->decref();
    object = from.object;
    return *this;
}

WxxObjectPtr & WxxObjectPtr::operator = (int i)
{
    object->decref();
    object = new WxxInteger(i);
    object->incref();
    return *this;
}

WxxObjectPtr & WxxObjectPtr::operator = (double value)
{
    object->decref();
    object = new WxxFloat(value);
    object->incref();
    return *this;
}

WxxObjectPtr & WxxObjectPtr::operator = (const std::string &s)
{
    object->decref();
    object = new WxxString(s);
    object->incref();
    return *this;
}

int WxxObjectPtr::is_equal (const WxxObjectPtr &from) const
{
    if (object == from.object)
        return true;
    return object->is_equal(*from.object);
}

int WxxObjectPtr::is_same(const WxxObjectPtr &from) const
{
    return object == from.object;
}

WxxObjectPtr::operator int() const
{
    return object->get_integer();
}

WxxObjectPtr::operator bool() const
{
    return object->get_bool();
}

WxxObjectPtr::operator double () const
{
    return object->get_number();
}

WxxObjectPtr::operator std::string () const
{
    return object->get_string();
}

WxxObjectPtr & WxxObjectPtr::operator++()
{
    object->increment();
    return *this;
}

WxxObjectPtr & WxxObjectPtr::operator--()
{
    object->decrement();
    return *this;
}

int WxxObjectPtr::is_null() const
{
    return object->is_null();
}

int WxxObjectPtr::instanceof(const std::string &type) const
{
    return object->instanceof(type);
}

int WxxObjectPtr::get_integer() const
{
    return object->get_integer();
}

double WxxObjectPtr::get_number() const
{
    return object->get_number();
}

std::string WxxObjectPtr::get_string() const
{
    return object->get_string();
}

void WxxObjectPtr::set_pointer(void *p) const
{
    object->set_pointer(p);
}

void * WxxObjectPtr::get_pointer() const
{
    return object->get_pointer();
}

int WxxObjectPtr::elements() const
{
return object->elements();
}

WxxObjectPtr WxxObjectPtr::add(const WxxObjectPtr &value)
{
    return object->add(value);
}

std::string WxxObjectPtr::get_string_keyed(int i) const
{
    return object->get_string_keyed(i);
}

WxxObjectPtr WxxObjectPtr::get_pmc_keyed(int i) const
{
    return object->get_pmc_keyed(i);
}

WxxObjectPtr WxxObjectPtr::get_pmc_keyed(const std::string &s) const
{
    return object->get_pmc_keyed(s);
}

WxxObjectPtr WxxObjectPtr::get_pmc_keyed(const WxxObjectPtr & key) const
{
    return object->get_pmc_keyed(key.get_string());
}

void WxxObjectPtr::set_pmc_keyed(int i, const WxxObjectPtr &value) const
{
    object->set_pmc_keyed(i, value);
}

void WxxObjectPtr::set_pmc_keyed(const std::string &s,
        const WxxObjectPtr &value) const
{
    object->set_pmc_keyed(s, value);
}

void WxxObjectPtr::set_pmc_keyed(const WxxObjectPtr &key,
        const WxxObjectPtr &value) const
{
    object->set_pmc_keyed(key.get_string(), value);
}

int WxxObjectPtr::exists(const std::string &key) const
{
    return object->exists(key);
}

WxxObjectPtr & WxxObjectPtr::get_attr_str(const std::string &s) const
{
    return object->get_attr_str(s);
}

void WxxObjectPtr::set_attr_str(const std::string &s,
        const WxxObjectPtr &value) const
{
    object->set_attr_str(s, value);
}

WxxObjectPtr WxxObjectPtr::get_iter() const
{
    return object->get_iter();
}

WxxObjectPtr WxxObjectPtr::shift_pmc() const
{
    return object->shift_pmc();
}

void WxxObjectPtr::push(WxxObjectPtr obj) const
{
    if (WxxArrayBase *arr = dynamic_cast<WxxArrayBase *>(object))
        arr->push(obj);
}

void WxxObjectPtr::push(int i) const
{
    if (WxxArrayBase *arr = dynamic_cast<WxxArrayBase *>(object))
        arr->push(i);
}

void WxxObjectPtr::push(double value) const
{
    if (WxxArrayBase *arr = dynamic_cast<WxxArrayBase *>(object))
        arr->push(value);
}

void WxxObjectPtr::push(const std::string &str) const
{
    if (WxxArrayBase *arr = dynamic_cast<WxxArrayBase *>(object))
        arr->push(str);
}

WxxObjectPtr WxxObjectPtr::get_class() const
{
    return object->get_class();
}

WxxObjectPtr WxxObjectPtr::instantiate() const
{
    return object->instantiate();
}

WxxObjectPtr WxxObjectPtr::operator()(const WxxObjectArray &args) const
{
    return (*object)(const_cast<WxxObjectArray &>(args));
}

WxxObjectPtr WxxObjectPtr::call_method(const std::string &methname) const
{
    WxxObjectArray args;
    return object->call_method(methname, args);
}

WxxObjectPtr WxxObjectPtr::call_method(const std::string &methname,
        WxxObjectArray &args) const
{
    return object->call_method(methname, args);
}

WxxLibrary * WxxObjectPtr::getlib() const
{
    return dynamic_cast<WxxLibrary *>(object);
}

} // namespace WinxedXX

// End
