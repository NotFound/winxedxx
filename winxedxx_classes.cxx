// winxedxx_classes.cxx
// (C) 2011 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_null.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"

namespace WinxedXX
{

//*************************************************************

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

} // namespace WinxedXX

// End
