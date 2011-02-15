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

WxxObjectPtr wxx_error(const std::string &message);
WxxObjectPtr wxx_error(const std::string &message, int severity);
WxxObjectPtr wxx_error(const std::string &message, int severity, int type);

class WxxObject
{
public:
    virtual int is_null() = 0;
    virtual int instanceof(const std::string &type) = 0;
    virtual int get_integer() = 0;
    virtual double get_number() = 0;
    virtual int elements() = 0;
    virtual std::string get_string() = 0;
    virtual WxxObjectPtr & get_pmc_keyed(int i) = 0;
    virtual WxxObjectPtr & get_attr_str(const std::string &s) = 0;
    virtual void set_attr_str(const std::string &s, const WxxObjectPtr &value) = 0;

    virtual void print() {}
    virtual void print(WxxObjectPtr &obj) = 0;
    virtual WxxObjectPtr readline() = 0;
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

class WxxNullAccess : public std::runtime_error
{
public:
    WxxNullAccess(const std::string &funcname) :
        std::runtime_error("Null WxxObject access in " + funcname)
    { }
};

class WxxNotImplemented : public std::runtime_error
{
public:
    WxxNotImplemented(const std::string &funcname, const std::string &name) :
        std::runtime_error(funcname + " not implemented in " + name)
    { }
};

class WxxNull : public WxxObject
{
public:
    int is_null() { return 1; }
    int instanceof(const std::string &type)
    {
        throw WxxNullAccess("instanceof");
    }
    int get_integer()
    {
        throw WxxNullAccess("get_integer");
    }
    double get_number()
    {
        throw WxxNullAccess("get_number");
    }
    int elements()
    {
        throw WxxNullAccess("elements");
    }
    std::string get_string()
    {
        throw WxxNullAccess("get_string");
    }
    WxxObjectPtr & get_pmc_keyed(int i)
    {
        throw WxxNullAccess("get_pmc_keyed");
    }
    WxxObjectPtr & get_attr_str(const std::string &s)
    {
        throw WxxNullAccess("get_attr_str");
    }
    void set_attr_str(const std::string &s, const WxxObjectPtr &value)
    {
        throw WxxNullAccess("set_attr_str");
    }
    void print(WxxObjectPtr &)
    {
        throw WxxNullAccess("print");
    }
    WxxObjectPtr readline();
};

class WxxDefault : public WxxObject
{
protected:
    WxxDefault(const char *name) { this->name = name; }
    ~WxxDefault()
    {
        //std::cerr << "~WxxDefault " << name << "\n";
    }
public:
    int is_null() { return 0; }
    int instanceof(const std::string &type)
    {
        return type == name;
    }
    int get_integer()
    {
        throw WxxNotImplemented("get_integer", name);
    }
    double get_number()
    {
        throw WxxNotImplemented("get_number", name);
    }
    int elements()
    {
        throw WxxNotImplemented("elements", name);
    }
    virtual std::string get_string()
    {
        throw WxxNotImplemented("get_string", name);
    }
    WxxObjectPtr & get_pmc_keyed(int i)
    {
        throw WxxNotImplemented("get_pmc_keyed", name);
    }
    WxxObjectPtr & get_attr_str(const std::string &s);
    void set_attr_str(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr readline();
    void print(WxxObjectPtr &)
    {
        throw WxxNotImplemented("print", name);
    }
private:
    std::string name;
    std::map<std::string, WxxObjectPtr> attributes;
};

class WxxInteger : public WxxDefault
{
public:
    WxxInteger(int value) : WxxDefault("Integer")
    {
        i = value;
    }
    int get_integer() { return i; };
    double get_number()
    {
        return i;
    }
    std::string get_string()
    {
        std::ostringstream oss;
        oss << i;
        return oss.str();
    }
    void print() { std::cout << i; }
private:
    int i;
};

class WxxFloat : public WxxDefault
{
public:
    WxxFloat(double value) : WxxDefault("Float")
    {
        n = value;
    }
    int get_integer() { return n; };
    double get_number()
    {
        return n;
    }
    std::string get_string()
    {
        std::ostringstream oss;
        oss << n;
        return oss.str();
    }
    void print() { std::cout << n; }
private:
    double n;
};

class WxxString : public WxxDefault
{
public:
    WxxString(std::string value) : WxxDefault("String")
    {
        str = value;
    }
    std::string get_string() { return str; }
    void print() { std::cout << str; }
private:
    std::string str;
};

class WxxObjectArray : public WxxDefault
{
public:
    WxxObjectArray() : WxxDefault("ResizablePMCArray")
    {
    }
    ~WxxObjectArray();
    int elements()
    {
        return arr.size();
    }
    WxxObjectPtr *operator[](int i) const;
    WxxObjectPtr & get_pmc_keyed(int i);
    WxxObjectArray& push(WxxObjectPtr &obj);
    WxxObjectArray& push(int i);
    WxxObjectArray& push(double n);
    WxxObjectArray& push(const char *str);
    WxxObjectArray& push(const std::string &str);
private:
    std::vector<WxxObjectPtr *> arr;
};

class WxxException : public WxxDefault
{
public:
    WxxException(const std::string &message, int severity = 2, int type = 0);
    std::string get_string() { return msg; }
private:
    std::string msg;
    int sev;
    int typ;
};

class WxxFileHandle : public WxxDefault
{
public:
    WxxFileHandle(int predef = 0) : WxxDefault("FileHandle")
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
    ~WxxFileHandle()
    {
        //std::cerr << "~WxxFileHandle\n";
        if (f && f != stdin && f != stdout && f != stderr)
            fclose(f);
    }
    WxxObjectPtr readline();
    WxxObject *open(WxxObjectPtr & name);
    void print(WxxObjectPtr &obj);
private:
    FILE *f;
};

//*************************************************************

class WxxObjectPtr
{
public:
    WxxObjectPtr() : object(new WxxNull())
    {
        object->incref();
    }
    WxxObjectPtr(int value) : object(new WxxInteger(value))
    {
        object->incref();
    }
    WxxObjectPtr(double value) : object(new WxxFloat(value))
    {
        object->incref();
    }
    WxxObjectPtr(const std::string &value) : object(new WxxString(value))
    {
        object->incref();
    }
    WxxObjectPtr(const WxxObjectPtr &old) :
        object(old.object)
    {
        object->incref();
    }
    WxxObjectPtr(WxxObject * obj) : object(obj)
    {
        object->incref();
    }
    ~WxxObjectPtr()
    {
        if (object)
            object->decref();
    }
    WxxObjectPtr &operator = (const WxxObjectPtr &from)
    {
        from.object->incref();
        object->decref();
        object = from.object;
        return *this;
    }
    WxxObjectPtr & operator = (int i)
    {
        object->decref();
        object = new WxxInteger(i);
        object->incref();
        return *this;
    }
    WxxObjectPtr & operator = (double n)
    {
        object->decref();
        object = new WxxFloat(n);
        object->incref();
        return *this;
    }
    WxxObjectPtr & operator = (const std::string &s)
    {
        object->decref();
        object = new WxxString(s);
        object->incref();
        return *this;
    }
    operator int() { return object->get_integer(); }
    operator double() { return object->get_number(); }
    operator std::string() { return object->get_string(); }
    int is_null() { return object->is_null(); }
    int instanceof(const std::string &type)
    {
        return object->instanceof(type);
    }
    std::string get_string()
    {
        return object->get_string();
    }
    int elements()
    {
        return object->elements();
    }
    WxxObjectPtr & get_pmc_keyed(int i)
    {
        return object->get_pmc_keyed(i);
    }
    void print()
    {
        object->print();
    }
    WxxObjectPtr & get_attr_str(const std::string &s)
    {
        return object->get_attr_str(s);
    }
    void set_attr_str(const std::string &s, const WxxObjectPtr &value)
    {
        object->set_attr_str(s, value);
    }
    WxxObjectPtr call_method(const std::string &methname)
    {
        if (methname == "readline")
            return object->readline();
        return WxxObjectPtr();
    }
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args)
    {
        if (methname == "print") {
            int n = args.elements();
            for (int i = 0; i < n; ++i)
                object->print(*args[i]);
        }
        return WxxObjectPtr();
    }
private:
    WxxObject *object;
};

static WxxObjectPtr winxedxxnull;

//*************************************************************

WxxObjectArray::~WxxObjectArray()
{
    for (unsigned int i = 0; i < arr.size(); ++i)
        delete arr[i];
}

WxxObjectPtr & WxxObjectArray::get_pmc_keyed(int i)
{
    if (i < 0 || i >= int(arr.size()))
        throw wxx_error("Out of bounds");
    return *arr[i];
}

WxxObjectPtr *WxxObjectArray::operator[](int i) const
{
     if (i < 0 || i >= int(arr.size()))
         throw wxx_error("Out of bounds");
     return arr[i];
}

WxxObjectArray& WxxObjectArray::push(WxxObjectPtr &obj)
{
    arr.push_back(new WxxObjectPtr(obj));
    return *this;
}
WxxObjectArray& WxxObjectArray::push(int i)
{
    arr.push_back(new WxxObjectPtr(i));
    return *this;
}
WxxObjectArray& WxxObjectArray::push(double n)
{
    arr.push_back(new WxxObjectPtr(n));
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

WxxObjectPtr WxxNull::readline()
{
    throw WxxNullAccess("readline");
}

WxxObjectPtr WxxDefault::readline()
{
    throw WxxNotImplemented("readline", name);
}

WxxObject *WxxFileHandle::open(WxxObjectPtr & name)
{
    std::string strname = name.get_string();
    f = fopen(strname.c_str(), "r");
    return this;
}

void WxxFileHandle::print(WxxObjectPtr &obj)
{
    fputs(obj.get_string().c_str(), f);
}

WxxObjectPtr WxxFileHandle::readline()
{
    char buffer[1024];
    const char *r = fgets(buffer, 1024, f);
    if (! r)
        r = "";
    return WxxObjectPtr(std::string(r));
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
    attributes[s] = WxxObjectPtr(value);
}

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
int wxx_print(WxxObjectPtr &obj) { obj.print(); return 0; }
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

} // namespace WinxedXX

#endif

// End of winxedxx.h
