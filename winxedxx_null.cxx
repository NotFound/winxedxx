// winxedxx_null.cxx
// (C) 2011 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_null.h"

#include <iostream>
#include <sstream>

namespace WinxedXX
{

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

void * WxxNull::get_pointer()
{
    return 0;
}

void WxxNull::set_pointer(void *)
{
    nullaccess("set_pointer");
}

int WxxNull::elements() const
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

WxxObjectPtr WxxNull::add(const WxxObjectPtr &value)
{
    nullaccess("ass");
    return winxedxxnull;
}

WxxObjectPtr WxxNull::sub(const WxxObjectPtr &value)
{
    nullaccess("ass");
    return winxedxxnull;
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

WxxObjectPtr WxxNull::get_class()
{
    nullaccess("get_class");
    return winxedxxnull;
}

WxxObjectPtr WxxNull::instantiate()
{
    nullaccess("instantiate");
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

void WxxNull::nullaccess(const std::string &funcname) const
{
    throw wxx_error("Null WxxObject in " + funcname);
}

//*************************************************************

} // namespace WinxedXX

// End
