// winxedxx_objectptr.cxx
// (C) 2011 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_null.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"

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

WxxObjectPtr::WxxObjectPtr(const char *value) :
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

WxxObjectPtr & WxxObjectPtr::set(const char *s)
{
    object->set(s);
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

WxxObjectPtr & WxxObjectPtr::operator = (const char *s)
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
    return false;
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

int WxxObjectPtr::is_null() const
{
    return object->is_null();
}

int WxxObjectPtr::instanceof(const std::string &type)
{
    return object->instanceof(type);
}

std::string WxxObjectPtr::get_string() const
{
    return object->get_string();
}

int WxxObjectPtr::elements() const
{
return object->elements();
}

std::string WxxObjectPtr::get_string_keyed(int i)
{
    return object->get_string_keyed(i);
}

WxxObjectPtr WxxObjectPtr::get_pmc_keyed(int i)
{
    return object->get_pmc_keyed(i);
}

WxxObjectPtr WxxObjectPtr::get_pmc_keyed(const std::string &s)
{
    return object->get_pmc_keyed(s);
}

WxxObjectPtr WxxObjectPtr::get_pmc_keyed(const char *s)
{
    return object->get_pmc_keyed(s);
}

WxxObjectPtr WxxObjectPtr::get_pmc_keyed(const WxxObjectPtr & key)
{
    return object->get_pmc_keyed(std::string(key));
}

void WxxObjectPtr::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    object->set_pmc_keyed(i, value);
}

WxxObjectPtr & WxxObjectPtr::set_pmc_keyed(const std::string &s, const WxxObjectPtr &value)
{
    return object->set_pmc_keyed(s, value);
}

WxxObjectPtr & WxxObjectPtr::set_pmc_keyed(const WxxObjectPtr &key, const WxxObjectPtr &value)
{
    return object->set_pmc_keyed(std::string(key), value);
}

int WxxObjectPtr::exists(const std::string &key)
{
    return object->exists(key);
}

void WxxObjectPtr::print()
{
    object->print();
}

WxxObjectPtr & WxxObjectPtr::get_attr_str(const std::string &s)
{
    return object->get_attr_str(s);
}

void WxxObjectPtr::set_attr_str(const std::string &s, const WxxObjectPtr &value)
{
    object->set_attr_str(s, value);
}

void WxxObjectPtr::set_attr_str(const char *s, const WxxObjectPtr &value)
{
    object->set_attr_str(s, value);
}

WxxObjectPtr WxxObjectPtr::get_iter()
{
    return object->get_iter();
}

WxxObjectPtr WxxObjectPtr::shift_pmc()
{
    return object->shift_pmc();
}

void WxxObjectPtr::push(WxxObjectPtr obj)
{
    if (WxxArrayBase *arr = dynamic_cast<WxxArrayBase *>(object))
        arr->push(obj);
}

void WxxObjectPtr::push(int i)
{
    if (WxxArrayBase *arr = dynamic_cast<WxxArrayBase *>(object))
        arr->push(i);
}

void WxxObjectPtr::push(double value)
{
    if (WxxArrayBase *arr = dynamic_cast<WxxArrayBase *>(object))
        arr->push(value);
}

void WxxObjectPtr::push(const char *str)
{
    if (WxxArrayBase *arr = dynamic_cast<WxxArrayBase *>(object))
        arr->push(str);
}

void WxxObjectPtr::push(const std::string &str)
{
    if (WxxArrayBase *arr = dynamic_cast<WxxArrayBase *>(object))
        arr->push(str);
}

WxxObjectPtr WxxObjectPtr::operator()(const WxxObjectArray &args)
{
    return (*object)(const_cast<WxxObjectArray &>(args));
}

WxxObjectPtr WxxObjectPtr::call_method(const std::string &methname)
{
    WxxObjectArray args;
    return object->call_method(methname, args);
}

WxxObjectPtr WxxObjectPtr::call_method(const std::string &methname, WxxObjectArray &args)
{
    if (methname == "print") {
        int n = args.elements();
        for (int i = 0; i < n; ++i)
            object->print(args[i]);
        return WxxObjectPtr();
    }
    else
        return object->call_method(methname, args);
}

WxxLibrary * WxxObjectPtr::getlib()
{
    return dynamic_cast<WxxLibrary *>(object);
}

} // namespace WinxedXX

// End
