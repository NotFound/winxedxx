#ifndef INCLUDE_WINXEDXX_H
#define INCLUDE_WINXEDXX_H

// winxedxx.h
// (C) 2011 Julián Albo "NotFound"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>

namespace WinxedXX
{

class WxxObjectPtr;
class WxxObjectArray;

std::string wxx_int_to_string(int i);
std::string wxx_num_to_string(double value);

WxxObjectPtr wxx_error(const std::string &message);
WxxObjectPtr wxx_error(const std::string &message, int severity);
WxxObjectPtr wxx_error(const std::string &message, int severity, int type);

class WxxObject
{
public:
    virtual int is_null() const = 0;
    virtual int instanceof(const std::string &type) = 0;
    virtual int get_bool() = 0;
    virtual int get_integer() = 0;
    virtual double get_number() = 0;
    virtual int elements() = 0;
    virtual std::string get_string() = 0;
    virtual WxxObject & set(int value) = 0;
    virtual WxxObject & set(double value) = 0;
    virtual WxxObject & set(const char *s) = 0;
    virtual WxxObject & set(const std::string &s) = 0;
    virtual WxxObjectPtr get_pmc_keyed(int i) = 0;
    virtual WxxObjectPtr get_pmc_keyed(const std::string &s) = 0;
    virtual WxxObjectPtr get_pmc_keyed(const char *s) = 0;
    virtual WxxObjectPtr & set_pmc_keyed(const std::string &s, const WxxObjectPtr &value) = 0;
    virtual WxxObjectPtr & get_attr_str(const std::string &s) = 0;
    virtual void set_attr_str(const std::string &s, const WxxObjectPtr &value) = 0;
    virtual WxxObjectPtr get_iter() = 0;
    virtual WxxObjectPtr shift_pmc() = 0;

    virtual WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args) = 0;
    virtual void print() = 0;
    virtual void print(WxxObjectPtr &obj) = 0;
    void incref() { ++numrefs; }
    void decref()
    {
        --numrefs;
        if (numrefs <= 0)
            delete this;
    }
protected:
    int numrefs;
    WxxObject()
    {
        numrefs = 0;
    }
    virtual ~WxxObject() { }
};


class WxxNull : public WxxObject
{
public:
    int is_null() const;
    int instanceof(const std::string &type);
    int get_bool();
    int get_integer();
    double get_number();
    int elements();
    std::string get_string();
    WxxObject & set(int value);
    WxxObject & set(double value);
    WxxObject & set(const char *s);
    WxxObject & set(const std::string &s);
    WxxObjectPtr get_pmc_keyed(int i);
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    WxxObjectPtr get_pmc_keyed(const char *s);
    WxxObjectPtr & set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr & get_attr_str(const std::string &s);
    void set_attr_str(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr get_iter();
    WxxObjectPtr shift_pmc();
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
    void print();
    void print(WxxObjectPtr &);
private:
    void nullaccess(const std::string &funcname);
};


class WxxDefault : public WxxObject
{
protected:
    WxxDefault(const char *name);
    WxxDefault(const std::string &name);
    ~WxxDefault();
public:
    int is_null() const;
    std::string getname() const;
    int instanceof(const std::string &type);
    int get_bool();
    int get_integer();
    double get_number();
    int elements();
    virtual std::string get_string();
    WxxObject & set(int value);
    WxxObject & set(double value);
    WxxObject & set(const char *s);
    WxxObject & set(const std::string &s);
    WxxObjectPtr get_pmc_keyed(int i);
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    WxxObjectPtr get_pmc_keyed(const char *s);
    WxxObjectPtr & set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr & get_attr_str(const std::string &s);
    void set_attr_str(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr get_iter();
    WxxObjectPtr shift_pmc();
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
    void print();
    void print(WxxObjectPtr &);
private:
    std::string name;
    std::map<std::string, WxxObjectPtr> attributes;
    void notimplemented(const std::string &funcname);
};


class WxxInteger : public WxxDefault
{
public:
    WxxInteger(int value);
    int get_integer();
    double get_number();
    std::string get_string();
    WxxObject & set(int value);
    WxxObject & set(double value);
    void print();
private:
    int i;
};


class WxxFloat : public WxxDefault
{
public:
    WxxFloat(double value);
    int get_integer();
    double get_number();
    std::string get_string();
    WxxObject & set(int value);
    WxxObject & set(double value);
    void print();
private:
    double n;
};


class WxxString : public WxxDefault
{
public:
    WxxString(std::string value);
    std::string get_string();
    WxxObject & set(const char *s);
    WxxObject & set(const std::string &s);
    void print();
private:
    std::string str;
};


class WxxArrayBase : public WxxDefault
{
protected:
    WxxArrayBase(const std::string &name);
public:
    int get_integer();
    WxxObjectPtr get_iter();
};

class WxxObjectArray : public WxxArrayBase
{
public:
    WxxObjectArray();
    ~WxxObjectArray();
    int elements();
    WxxObjectPtr *operator[](int i) const;
    WxxObjectPtr get_pmc_keyed(int i);
    WxxObjectArray& push(WxxObjectPtr obj);
    WxxObjectArray& push(int i);
    WxxObjectArray& push(double value);
    WxxObjectArray& push(const char *str);
    WxxObjectArray& push(const std::string &str);
private:
    std::vector<WxxObjectPtr *> arr;
};

class WxxStringArray : public WxxArrayBase
{
public:
    WxxStringArray();
    ~WxxStringArray();
    int elements();
    std::string operator[](int i) const;
    WxxObjectPtr get_pmc_keyed(int i);
    WxxStringArray& push(WxxObjectPtr obj);
    WxxStringArray& push(int i);
    WxxStringArray& push(double value);
    WxxStringArray& push(const char *str);
    WxxStringArray& push(const std::string &str);
private:
    std::vector<std::string> arr;
};

class WxxArrayIterator : public WxxDefault
{
public:
    WxxArrayIterator(WxxObject *container);
    ~WxxArrayIterator();
    int get_bool();
    WxxObjectPtr shift_pmc();
private:
    WxxObject *cnt;
    int current;
};

class WxxHash : public WxxDefault
{
public:
    WxxHash();
    WxxHash & set(const std::string &key, WxxObjectPtr value);
    WxxObjectPtr & set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    WxxObjectPtr get_pmc_keyed(const char *s);
private:
    std::map<std::string, WxxObjectPtr> hsh;
};

class WxxException : public WxxDefault
{
public:
    WxxException(const std::string &message, int severity = 2, int type = 0);
    std::string get_string();
private:
    std::string msg;
    int sev;
    int typ;
};


class WxxFileHandle : public WxxDefault
{
public:
    WxxFileHandle(int predef = 0);
    ~WxxFileHandle();
    WxxObject *open(WxxObjectPtr name);
    WxxObject *open(WxxObjectPtr name, WxxObjectPtr mode);
    WxxObjectPtr close();
    void print(WxxObjectPtr &obj);
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
private:
    FILE *f;
    WxxObjectPtr read(int n);
    WxxObjectPtr readline();
};

//*************************************************************

class WxxObjectPtr
{
public:
    WxxObjectPtr();
    WxxObjectPtr(int value);
    WxxObjectPtr(double value);
    WxxObjectPtr(const std::string &value);
    WxxObjectPtr(const char *value);
    WxxObjectPtr(const WxxObjectPtr &old);
    WxxObjectPtr(WxxObject * obj);
    ~WxxObjectPtr();
    WxxObjectPtr & set(int value);
    WxxObjectPtr & set(double value);
    WxxObjectPtr & set(const char *s);
    WxxObjectPtr & set(const std::string &s);
    WxxObjectPtr &operator = (const WxxObjectPtr &from);
    WxxObjectPtr & operator = (int i);
    WxxObjectPtr & operator = (double value);
    WxxObjectPtr & operator = (const std::string &s);
    WxxObjectPtr & operator = (const char *s);
    operator int() { return object->get_integer(); }
    operator bool() { return object->get_bool(); }
    operator double() { return object->get_number(); }
    operator std::string() { return object->get_string(); }
    int is_null() const { return object->is_null(); }
    int instanceof(const std::string &type);
    std::string get_string();
    int elements();
    WxxObjectPtr get_pmc_keyed(int i);
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    WxxObjectPtr get_pmc_keyed(const char *s);
    WxxObjectPtr & set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);
    void print();
    WxxObjectPtr & get_attr_str(const std::string &s);
    void set_attr_str(const std::string &s, const WxxObjectPtr &value);
    void set_attr_str(const char *s, const WxxObjectPtr &value);
    WxxObjectPtr get_iter();
    WxxObjectPtr shift_pmc();
    WxxObjectPtr call_method(const std::string &methname);
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
private:
    WxxObject *object;
};

static WxxObjectPtr winxedxxnull;

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

WxxObjectPtr WxxNull::call_method(const std::string &methname, WxxObjectArray &args)
{
    nullaccess("call_method");
    return winxedxxnull;
}

void WxxNull::print()
{
    nullaccess("print");
}

void WxxNull::print(WxxObjectPtr &)
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

WxxObjectPtr & WxxDefault::set_pmc_keyed(const std::string &s, const WxxObjectPtr &value)
{
    notimplemented("set_pmc_keyed");
    return winxedxxnull;
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

void WxxDefault::print(WxxObjectPtr &)
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

int WxxInteger::get_integer() { return i; };

double WxxInteger::get_number() { return i; }

std::string WxxInteger::get_string()
{
    std::ostringstream oss;
    oss << i;
    return oss.str();
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

void WxxInteger::print() { std::cout << i; }

//*************************************************************

WxxFloat::WxxFloat(double value) : WxxDefault("Float")
{
    n = value;
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
    return *(this->operator[](i));
}

WxxObjectPtr *WxxObjectArray::operator[](int i) const
{
    int size = arr.size();
    if (i < 0)
        i += size;
    if (i < 0)
        throw wxx_error(getname() + ": index out of bounds!");
    if (i >= size)
         return &winxedxxnull;
    return arr[i];
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

//*************************************************************

WxxStringArray::WxxStringArray() :
        WxxArrayBase("ResizableStringArray")
{
}

WxxStringArray::~WxxStringArray()
{
}

int WxxStringArray::elements()
{
    return arr.size();
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

//*************************************************************

WxxFileHandle::WxxFileHandle(int predef) : WxxDefault("FileHandle")
{
    switch (predef) {
    case 1:
        f = stdin;
        break;
    case 2:
        f = stdout;
        break;
    case 3:
        f = stderr;
        break;
    default:
        f = 0;
    }
}

WxxFileHandle::~WxxFileHandle()
{
    //std::cerr << "~WxxFileHandle\n";
    if (f && f != stdin && f != stdout && f != stderr)
        fclose(f);
}

WxxObject *WxxFileHandle::open(WxxObjectPtr name)
{
    std::string strname = name.get_string();
    f = fopen(strname.c_str(), "r");
    return this;
}

WxxObject *WxxFileHandle::open(WxxObjectPtr name, WxxObjectPtr mode)
{
    if (f)
        throw wxx_error("FileHandle is already open");
    std::string strname = name.get_string();
    std::string strmode = mode.get_string();
    for (size_t i = 0; i < strmode.length(); ++i) {
        switch (strmode[i]) {
          case 'r':
          case 'w':
          case 'a':
          case 'b':
            break;
          default:
            throw wxx_error("Invalid mode in open");
        }
    }
    f = fopen(strname.c_str(), strmode.c_str());
    return this;
}

WxxObjectPtr WxxFileHandle::close()
{
    int r;
    if (f) {
        r = fclose(f);
        f = 0;
    }
    else
        r = -1;
    return r;
}

void WxxFileHandle::print(WxxObjectPtr &obj)
{
    if (! f)
        throw wxx_error("FileHandle is closed");
    fputs(obj.get_string().c_str(), f);
}

WxxObjectPtr WxxFileHandle::read(int n)
{
    if (! f)
        throw wxx_error("FileHandle is closed");
    char *buf = (char *)malloc(n);
    *buf = '\0';
    size_t r = fread(buf, 1, n, f);
    std::cerr << "\nread " << r << "\n";
    std::string result = r > 0 ? std::string(buf, r) : std::string();
    free(buf);
    return WxxObjectPtr(result);
}

WxxObjectPtr WxxFileHandle::readline()
{
    if (! f)
        throw wxx_error("FileHandle is closed");
    char buffer[1024];
    const char *r = fgets(buffer, 1024, f);
    if (! r)
        r = "";
    return WxxObjectPtr(std::string(r));
}

WxxObjectPtr WxxFileHandle::call_method(const std::string &methname, WxxObjectArray &args)
{
    if (methname == "readline") {
        if (args.elements() > 0)
            throw wxx_error("too many positional arguments in readline");
        return readline();
    }
    if (methname == "read") {
        if (args.elements() != 1)
            throw wxx_error("wrong number of positional arguments in read");
        return read(args.get_pmc_keyed(0));
    }
    if (methname == "open") {
        switch (args.elements()) {
          case 1:
            return open(args.get_pmc_keyed(0));
          case 2:
            return open(args.get_pmc_keyed(0), args.get_pmc_keyed(1));
          default:
            throw wxx_error("too many positional arguments in close");
        }
    }
    if (methname == "close") {
        if (args.elements() > 0)
            throw wxx_error("too many positional arguments in close");
        return close();
    }
    else
        return WxxDefault::call_method(methname, args);
}

//*************************************************************

WxxException::WxxException(const std::string &message, int severity, int type) :
        WxxDefault("Exception"),
        msg(message),
        sev(severity),
        typ(type)
{
    set_attr_str(std::string("message"), WxxObjectPtr(message));
    set_attr_str(std::string("severity"), WxxObjectPtr(severity));
    set_attr_str(std::string("type"), WxxObjectPtr(type));
}

std::string WxxException::get_string()
{ return msg; }

//*************************************************************

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

int WxxObjectPtr::instanceof(const std::string &type)
{
    return object->instanceof(type);
}

std::string WxxObjectPtr::get_string()
{
    return object->get_string();
}

int WxxObjectPtr::elements()
{
return object->elements();
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

WxxObjectPtr & WxxObjectPtr::set_pmc_keyed(const std::string &s, const WxxObjectPtr &value)
{
    return object->set_pmc_keyed(s, value);
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
            object->print(*args[i]);
        return WxxObjectPtr();
    }
    else
        return object->call_method(methname, args);
}

//*************************************************************

class WxxClass : public WxxDefault
{
public:
    typedef WxxObjectPtr (*memberfun)(WxxObjectPtr &, const WxxObjectArray &);

    WxxClass(const std::string &name);
    void addattribute(const std::string &attrname);
    void addfunction(const std::string &fname, memberfun);
    memberfun getfunction(const std::string &fname);
    static WxxClass * getclass(const std::string &name);
private:
    std::string clname;
    std::vector<std::string> attrs;
    static std::map<std::string, WxxClass *> reg;
    std::map<std::string, memberfun> regfun;
};

std::map<std::string, WxxClass *> WxxClass::reg;

WxxClass * WxxClass::getclass(const std::string &name)
{
    return reg[name];
}

WxxClass::WxxClass(const std::string &name) :
        WxxDefault("Class"),
        clname(name)
{
    reg[name] = this;
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


class WxxInstance : public WxxDefault
{
public:
    WxxInstance(const std::string &clname);
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
private:
    WxxClass *cl;
};

WxxInstance::WxxInstance(const std::string &clname) :
        WxxDefault(clname)
{
    cl = WxxClass::getclass(clname);
    if (! cl)
        throw wxx_error("class not found: " + clname);
}

WxxObjectPtr WxxInstance::call_method(const std::string &methname, WxxObjectArray &args)
{
    WxxClass::memberfun fun = cl->getfunction(methname);
    if (fun) {
        WxxObjectPtr obj(this);
        return (*fun)(obj, args);
    }
    return winxedxxnull;
}

//*************************************************************

WxxObjectPtr wxx_getstdin()
{
    return WxxObjectPtr(new WxxFileHandle(1));
}
WxxObjectPtr wxx_getstdout()
{
    return WxxObjectPtr(new WxxFileHandle(2));
}
WxxObjectPtr wxx_getstderr()
{
    return WxxObjectPtr(new WxxFileHandle(3));
}

int wxx_print(int i) { std::cout << i; return 0; }
int wxx_print(const char *s) { std::cout << s; return 0; }
int wxx_print(const std::string &s) { std::cout << s; return 0; }
int wxx_print(double n) { std::cout << n; return 0; }
int wxx_print(WxxObjectPtr obj) { obj.print(); return 0; }

int wxx_eprint(int i) { std::cerr << i; return 0; }
int wxx_eprint(const char *s) { std::cerr << s; return 0; }
int wxx_eprint(const std::string &s) { std::cerr << s; return 0; }
int wxx_eprint(double n) { std::cerr << n; return 0; }
// TODO
int wxx_eprint(WxxObjectPtr obj) { obj.print(); return 0; }

std::string wxx_int_to_string(int i)
{
    std::ostringstream oss;
    oss << i;
    return oss.str();
}

std::string wxx_num_to_string(double value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

int wxx_instanceof(WxxObjectPtr &obj, const std::string &type)
{
    return obj.instanceof(type);
}
int wxx_isnull(WxxObjectPtr obj)
{
    return obj.is_null();
}
int wxx_booland(int li, int ri)
{
    return li ? ri : li;
}
int wxx_boolor(int li, int ri)
{
    return li ? li : ri;
}

WxxObjectPtr wxx_error(const std::string &message)
{
    return WxxObjectPtr((WxxObject *)new WxxException(message));
}
WxxObjectPtr wxx_error(const std::string &message, int severity)
{
    return WxxObjectPtr((WxxObject *)new WxxException(message, severity));
}
WxxObjectPtr wxx_error(const std::string &message, int severity, int type)
{
    return WxxObjectPtr((WxxObject *)new WxxException(message, severity, type));
}

WxxObjectPtr wxx_typeof(WxxObjectPtr &thing)
{
    return winxedxxnull;
}

std::string wxx_join(const std::string &sep, WxxObjectPtr &arr)
{
    std::string result;
    int n = arr.elements();
    for (int i = 0; i < n; ++i)
    {
        if (i > 0)
            result += sep;
        result += std::string(arr.get_pmc_keyed(i));
    }
    return result;
}

std::string operator + (WxxObjectPtr obj, const std::string &s)
{
    return obj.get_string() + s;
}

std::string operator + (WxxObjectPtr obj, const char *s)
{
    return obj.get_string() + s;
}

std::string operator + (const std::string &s, WxxObjectPtr obj)
{
    return s + obj.get_string();
}

std::string operator + (const char *s, WxxObjectPtr obj)
{
    return s + obj.get_string();
}

int operator == (WxxObjectPtr &obj, const std::string &str)
{
    return obj.get_string() == str;
}
int operator == (const std::string &str, WxxObjectPtr &obj)
{
    return obj.get_string() == str;
}
int operator != (WxxObjectPtr &obj, const std::string &str)
{
    return obj.get_string() != str;
}
int operator != (const std::string &str, WxxObjectPtr &obj)
{
    return obj.get_string() != str;
}
int operator == (WxxObjectPtr &obj, int i)
{
    return int(obj) == i;
}
int operator == (int i, WxxObjectPtr &obj)
{
    return int(obj) == i;
}

} // namespace WinxedXX

#endif

// End of winxedxx.h
