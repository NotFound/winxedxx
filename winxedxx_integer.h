#ifndef INCLUDE_WINXEDXX_INTEGER_H
#define INCLUDE_WINXEDXX_INTEGER_H

// winxedxx_integer.h

// (C) 2011 Julián Albo "NotFound"

#include <vector>

namespace WinxedXX
{

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
    virtual WxxArrayBase& push(WxxObjectPtr obj) = 0;
    virtual WxxArrayBase& push(int i) = 0;
    virtual WxxArrayBase& push(double value) = 0;
    virtual WxxArrayBase& push(const char *str) = 0;
    virtual WxxArrayBase& push(const std::string &str) = 0;
    virtual void set_pmc_keyed(int i, const WxxObjectPtr &value) = 0;
    WxxObjectPtr get_iter();
};

class WxxObjectArray : public WxxArrayBase
{
public:
    WxxObjectArray();
    ~WxxObjectArray();
    int elements();
    WxxObjectPtr operator[](int i) const;
    WxxObjectPtr get_pmc_keyed(int i);
    WxxObjectArray& push(WxxObjectPtr obj);
    WxxObjectArray& push(int i);
    WxxObjectArray& push(double value);
    WxxObjectArray& push(const char *str);
    WxxObjectArray& push(const std::string &str);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
private:
    std::vector<WxxObjectPtr *> arr;
};

class WxxLibrary : public WxxDefault
{
public:
    WxxLibrary(void *dl_handle);
    void * getsym(const std::string &funcname);
private:
    void *dl_h;
};

} // namespace WinxedXX

#endif

// End of winxedxx_integer.h
