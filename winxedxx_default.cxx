// winxedxx_default.cxx
// (C) 2011 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace WinxedXX
{

//*************************************************************

WxxDefault::WxxDefault()
{
    throw std::runtime_error("Default instantiated");
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

void * WxxDefault::get_pointer()
{
    notimplemented("get_pointer");
    return 0;
}

void WxxDefault::set_pointer(void *)
{
    notimplemented("set_pointer");
}

int WxxDefault::elements() const
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

WxxObjectPtr WxxDefault::add(const WxxObjectPtr &value)
{
    notimplemented("add");
    return winxedxxnull;
}

WxxObjectPtr WxxDefault::sub(const WxxObjectPtr &value)
{
    notimplemented("sub");
    return winxedxxnull;
}

std::string WxxDefault::get_string_keyed(int i)
{
    return get_pmc_keyed(i).get_string();
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

WxxObjectPtr WxxDefault::get_class()
{
    //notimplemented("get_class");
    //return winxedxxnull;
    return this;
}

WxxObjectPtr WxxDefault::instantiate()
{
    notimplemented("instantiate");
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

void WxxDefault::notimplemented(const std::string &funcname) const
{
    throw wxx_error(funcname + " not implemented in " + name);
}

//*************************************************************

} // namespace WinxedXX

// End
