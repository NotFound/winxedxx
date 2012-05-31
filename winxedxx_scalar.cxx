// winxedxx_scalar.cxx
// (C) 2011-2012 Julián Albo

// Scalar types: Integer, Float, String.

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"

#include <iostream>
#include <sstream>

namespace WinxedXX
{

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

WxxObjectPtr WxxInteger::add(const WxxObjectPtr &value)
{
    return new WxxInteger(i + int(value));
}

WxxObjectPtr WxxInteger::sub(const WxxObjectPtr &value)
{
    return new WxxInteger(i - int(value));
}

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

WxxObject & WxxString::set(const std::string &s)
{
    str = s;
    return *this;
}

WxxObjectPtr WxxString::get_iter()
{
    return WxxObjectPtr(new WxxStringIterator(str));
}

} // namespace WinxedXX

// End
