// winxedxx_array.cxx
// (C) 2011-2012 Julián Albo

// Array types

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"

namespace WinxedXX
{

WxxObjectPtr out_of_bounds(const WxxArrayBase &arr)
{
    // Hardcoded values
    return wxx_error(arr.class_name() + ": index out of bounds!", 2, 33);
}

WxxObjectPtr cannot_resize(const WxxArrayBase &arr)
{
    // Hardcoded values
    return wxx_error(arr.class_name() + ": Can't resize!", 2, 33);
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

WxxIntegerArray::WxxIntegerArray(const std::string &name) :
       WxxArrayBase(name)
{
}

WxxIntegerArray::WxxIntegerArray(const std::string &name, int size) :
       WxxArrayBase(name)
{
    resize(size);
}

WxxIntegerArray::WxxIntegerArray() :
        WxxArrayBase("FixedIntegerArray")
{
}

WxxIntegerArray::WxxIntegerArray(int size) :
        WxxArrayBase("FixedIntegerArray")
{
    resize(size);
}

WxxIntegerArray::~WxxIntegerArray()
{
}

void WxxIntegerArray::resize(int size)
{
    if (elements())
        throw cannot_resize(*this);
    arr.resize(size);
}

int WxxIntegerArray::elements() const
{
    return arr.size();
}

WxxObject & WxxIntegerArray::set(int value)
{
    resize(value);
    return *this;
}

int WxxIntegerArray::operator[](int i) const
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw out_of_bounds(*this);
    if (i >= size)
        return 0;
    return arr[i];
}

int & WxxIntegerArray::operator[](int i)
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw out_of_bounds(*this);
    if (i >= size)
         resize(i + 1);
    return arr[i];
}

int WxxIntegerArray::get_integer_keyed(int i)
{
    return this->operator[](i);
}

double WxxIntegerArray::get_number_keyed(int i)
{
    return this->operator[](i);
}

std::string WxxIntegerArray::get_string_keyed(int i)
{
    return wxx_string_cast(this->operator[](i));
}

WxxObjectPtr WxxIntegerArray::get_pmc_keyed(int i)
{
    return this->operator[](i);
}

WxxIntegerArray& WxxIntegerArray::set_keyed(int i, int value)
{
    this->operator[](i) = value;
    return *this;
}

void WxxIntegerArray::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    arr[i] = value;
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
    arr.push_back(wxx_int_cast(str));
    return *this;
}

WxxIntegerArray& WxxIntegerArray::push(WxxObjectPtr obj)
{
    arr.push_back(obj);
    return *this;
}

//-------------------------------------------------------------

WxxResizableIntegerArray::WxxResizableIntegerArray() :
        WxxIntegerArray("ResizableIntegerArray")
{
}

WxxResizableIntegerArray::WxxResizableIntegerArray(int size) :
        WxxIntegerArray("ResizableIntegerArray", size)
{
}

void WxxResizableIntegerArray::resize(int size)
{
    arr.resize(size);
}

//*************************************************************

WxxFloatArray::WxxFloatArray(const std::string &name) :
       WxxArrayBase(name)
{
}

WxxFloatArray::WxxFloatArray(const std::string &name, int size) :
       WxxArrayBase(name)
{
    resize(size);
}

WxxFloatArray::WxxFloatArray() :
        WxxArrayBase("FixedFloatArray")
{
}

WxxFloatArray::WxxFloatArray(int size) :
        WxxArrayBase("FixedFloatArray")
{
    resize(size);
}

WxxFloatArray::~WxxFloatArray()
{
}

void WxxFloatArray::resize(int size)
{
    if (elements())
        throw cannot_resize(*this);
    arr.resize(size);
}

int WxxFloatArray::elements() const
{
    return arr.size();
}

WxxObject & WxxFloatArray::set(int value)
{
    resize(value);
    return *this;
}

double WxxFloatArray::operator[](int i) const
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw out_of_bounds(*this);
    if (i >= size)
        return 0;
    return arr[i];
}

double & WxxFloatArray::operator[](int i)
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw out_of_bounds(*this);
    if (i >= size)
        resize(i + 1);
    return arr[i];
}

int WxxFloatArray::get_integer_keyed(int i)
{
    return this->operator[](i);
}

double WxxFloatArray::get_number_keyed(int i)
{
    return this->operator[](i);
}

std::string WxxFloatArray::get_string_keyed(int i)
{
    return wxx_string_cast(this->operator[](i));
}

WxxObjectPtr WxxFloatArray::get_pmc_keyed(int i)
{
    return this->operator[](i);
}

WxxFloatArray& WxxFloatArray::set_keyed(int i, float value)
{
    this->operator[](i) = value;
    return *this;
}

void WxxFloatArray::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    arr[i] = value;
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
    arr.push_back(wxx_num_cast(str));
    return *this;
}

WxxFloatArray& WxxFloatArray::push(WxxObjectPtr obj)
{
    arr.push_back(obj);
    return *this;
}

//-------------------------------------------------------------

WxxResizableFloatArray::WxxResizableFloatArray() :
        WxxFloatArray("ResizableFloatArray")
{
}

WxxResizableFloatArray::WxxResizableFloatArray(int size) :
        WxxFloatArray("ResizableFloatArray", size)
{
}

void WxxResizableFloatArray::resize(int size)
{
    arr.resize(size);
}

//*************************************************************

WxxStringArray::WxxStringArray(const std::string &name) :
       WxxArrayBase(name)
{
}

WxxStringArray::WxxStringArray(const std::string &name, int size) :
       WxxArrayBase(name)
{
    resize(size);
}

WxxStringArray::WxxStringArray() :
        WxxArrayBase("FixedStringArray")
{
}

WxxStringArray::WxxStringArray(int size) :
        WxxArrayBase("FixedStringArray")
{
    resize(size);
}

WxxStringArray::~WxxStringArray()
{
}

void WxxStringArray::resize(int size)
{
    if (elements())
        throw cannot_resize(*this);
    arr.resize(size);
}

int WxxStringArray::elements() const
{
    return arr.size();
}

WxxObject & WxxStringArray::set(int value)
{
    resize(value);
    return *this;
}

std::string WxxStringArray::operator[](int i) const
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw out_of_bounds(*this);
    if (i >= size)
        return std::string();
    return arr[i];
}

std::string & WxxStringArray::operator[](int i)
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw out_of_bounds(*this);
    if (i >= size)
        resize(i + 1);
    return arr[i];
}

int WxxStringArray::get_integer_keyed(int i)
{
    return wxx_int_cast(this->operator[](i));
}

double WxxStringArray::get_number_keyed(int i)
{
    return wxx_num_cast(this->operator[](i));
}

std::string WxxStringArray::get_string_keyed(int i)
{
    return this->operator[](i);
}

WxxObjectPtr WxxStringArray::get_pmc_keyed(int i)
{
    return new WxxString(this->operator[](i));
}

WxxStringArray& WxxStringArray::set_keyed(int i, const std::string &value)
{
    this->operator[](i) = value;
    return *this;
}

void WxxStringArray::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    arr[i] = value.get_string();
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

WxxStringArray& WxxStringArray::push(WxxObjectPtr obj)
{
    arr.push_back(obj.get_string());
    return *this;
}

WxxObjectPtr WxxStringArray::call_method(const std::string &methname, WxxObjectArray &args)
{
    if (methname == "shift") {
        if (arr.size() == 0)
            throw wxx_error("Can't shift from an empty array");
        std::string result = this->operator[](0);
        arr.erase(arr.begin());
        return WxxObjectPtr(new WxxString(result));
    }
    return WxxDefault::call_method(methname, args);
}

//-------------------------------------------------------------

WxxResizableStringArray::WxxResizableStringArray() :
        WxxStringArray("ResizableStringArray")
{
}

WxxResizableStringArray::WxxResizableStringArray(int size) :
        WxxStringArray("ResizableStringArray", size)
{
}

// Special purpose initialization intended only for usage from main.
WxxResizableStringArray::WxxResizableStringArray(int argc, char **argv) :
        WxxStringArray("ResizableStringArray", argc)
{
    for (int argi = 0; argi < argc; ++argi)
        arr[argi] = std::string(argv[argi]);
}

void WxxResizableStringArray::resize(int size)
{
    arr.resize(size);
}

//*************************************************************

WxxObjectArray::WxxObjectArray() :
        WxxArrayBase("ResizablePMCArray")
{
}

WxxObjectArray::~WxxObjectArray()
{
}

int WxxObjectArray::elements() const
{
    return arr.size();
}

WxxObject & WxxObjectArray::set(int value)
{
    arr.resize(value);
    return *this;
}

WxxObjectPtr WxxObjectArray::operator[](int i) const
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw out_of_bounds(*this);
    if (i >= size)
         return winxedxxnull;
    return arr[i];
}

int WxxObjectArray::get_integer_keyed(int i)
{
    return this->operator[](i).get_integer();
}

double WxxObjectArray::get_number_keyed(int i)
{
    return this->operator[](i).get_number();
}

std::string WxxObjectArray::get_string_keyed(int i)
{
    return this->operator[](i).get_string();
}

WxxObjectPtr WxxObjectArray::get_pmc_keyed(int i) const
{
    return this->operator[](i);
}

WxxObjectPtr WxxObjectArray::get_pmc_keyed(int i)
{
    return this->operator[](i);
}

void WxxObjectArray::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    arr[i] = value;
}

WxxObjectArray& WxxObjectArray::push(int i)
{
    arr.push_back(WxxObjectPtr(i));
    return *this;
}

WxxObjectArray& WxxObjectArray::push(double value)
{
    arr.push_back(WxxObjectPtr(value));
    return *this;
}

WxxObjectArray& WxxObjectArray::push(const std::string &str)
{
    arr.push_back(WxxObjectPtr(new WxxString(str)));
    return *this;
}

WxxObjectArray& WxxObjectArray::push(WxxObjectPtr obj)
{
    arr.push_back(WxxObjectPtr(obj));
    return *this;
}

//*************************************************************

} // namespace WinxedXX

// End
