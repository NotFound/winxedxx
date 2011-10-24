#ifndef INCLUDE_WINXEDXX_TYPES_H
#define INCLUDE_WINXEDXX_TYPES_H

// winxedxx_types.h
// (C) 2011 Julián Albo

#include <string>
#include <map>

namespace WinxedXX
{

class WxxObject;
class WxxObjectArray;
class WxxLibrary;

class WxxFunctionVars
{
protected:
    WxxFunctionVars() :
        refcount(1)
    {
    }
public:
    void decref()
    {
        if (--refcount == 0)
	    delete this;
    }
private:
    size_t refcount;
};

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
    operator int() const;
    operator bool() const;
    operator double() const;
    operator std::string() const;
    int is_null() const;
    int instanceof(const std::string &type);
    std::string get_string() const;
    int elements() const;
    std::string get_string_keyed(int i);
    WxxObjectPtr get_pmc_keyed(int i);
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    WxxObjectPtr get_pmc_keyed(const char *s);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
    WxxObjectPtr & set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);
    int exists(const std::string &key);
    void print();
    WxxObjectPtr & get_attr_str(const std::string &s);
    void set_attr_str(const std::string &s, const WxxObjectPtr &value);
    void set_attr_str(const char *s, const WxxObjectPtr &value);
    void push(WxxObjectPtr obj);
    void push(int i);
    void push(double value);
    void push(const char *str);
    void push(const std::string &str);
    WxxObjectPtr get_iter();
    WxxObjectPtr shift_pmc();
    WxxObjectPtr operator()(const WxxObjectArray &args);
    WxxObjectPtr call_method(const std::string &methname);
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
    WxxLibrary *getlib();
private:
    WxxObject *object;
};

extern WxxObjectPtr winxedxxnull;

WxxObjectPtr wxx_error(const std::string &message);
WxxObjectPtr wxx_error(const std::string &message, int severity);
WxxObjectPtr wxx_error(const std::string &message, int severity, int type);

} // namespace WinxedXX

#endif

// End of winxedxx_types.h
