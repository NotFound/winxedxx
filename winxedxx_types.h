#ifndef INCLUDE_WINXEDXX_TYPES_H
#define INCLUDE_WINXEDXX_TYPES_H

// winxedxx_types.h
// (C) 2011 Julián Albo

#include <string>
#include <map>

namespace WinxedXX
{

class WxxRefcounted
{
protected:
    WxxRefcounted();
    WxxRefcounted(size_t initial);
    virtual ~WxxRefcounted();
public:
    void incref();
    void decref();
private:
    size_t refcount;
};

class WxxObject;
class WxxObjectArray;
class WxxLibrary;
class WxxInnerFunction;

class WxxFunctionVars : public WxxRefcounted
{
protected:
    WxxFunctionVars() : WxxRefcounted(1)
    {
    }
};

class WxxDataHolder
{
public:
    WxxDataHolder(WxxFunctionVars *newdata) : data(newdata) { data->incref(); }
    ~WxxDataHolder() { data->decref(); }
private:
    WxxFunctionVars *data;
};

class WxxObjectPtr
{
public:
    WxxObjectPtr();
    WxxObjectPtr(int value);
    WxxObjectPtr(double value);
    WxxObjectPtr(const std::string &value);
    WxxObjectPtr(const WxxObjectPtr &old);
    WxxObjectPtr(WxxObject * obj);
    WxxObjectPtr(WxxObjectPtr (*)(const WxxObjectArray&));
    WxxObjectPtr(WxxInnerFunction * obj);
    ~WxxObjectPtr();
    std::string class_name() const;
    WxxObjectPtr & set(int value);
    WxxObjectPtr & set(double value);
    WxxObjectPtr & set(const std::string &s);
    WxxObjectPtr &operator = (const WxxObjectPtr &from);
    WxxObjectPtr & operator = (int i);
    WxxObjectPtr & operator = (double value);
    WxxObjectPtr & operator = (const std::string &s);
    int is_equal(const WxxObjectPtr &from) const;
    int is_same(const WxxObjectPtr &from) const;
    operator int() const;
    operator bool() const;
    operator double() const;
    operator std::string() const;
    WxxObjectPtr & operator++();
    WxxObjectPtr & operator--();
    int is_null() const;
    int instanceof(const std::string &type);
    std::string get_string() const;
    int get_integer() const;
    double get_number() const;
    int elements() const;
    WxxObjectPtr add(const WxxObjectPtr &value);
    WxxObjectPtr sub(const WxxObjectPtr &value);
    std::string get_string_keyed(int i) const;
    WxxObjectPtr get_pmc_keyed(int i);
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    WxxObjectPtr get_pmc_keyed(const WxxObjectPtr &key);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
    WxxObjectPtr & set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr & set_pmc_keyed(const WxxObjectPtr &key, const WxxObjectPtr &value);
    int exists(const std::string &key);
    WxxObjectPtr & get_attr_str(const std::string &s);
    void set_attr_str(const std::string &s, const WxxObjectPtr &value);
    void push(WxxObjectPtr obj);
    void push(int i);
    void push(double value);
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

class WxxInnerFunction : public WxxRefcounted
{
public:
    virtual WxxObjectPtr operator()(const WxxObjectArray &args) = 0;
};


WxxObjectPtr wxx_error(const std::string &message);
WxxObjectPtr wxx_error(const std::string &message, int severity);
WxxObjectPtr wxx_error(const std::string &message, int severity, int type);

WxxObjectPtr wxx_die(const std::string &message);

int wxx_time();
double wxx_floattime();
int wxx_sleep(int t);
int wxx_sleep(double t);

int wxx_length(const std::string &str);
int wxx_length(const WxxObjectPtr &obj);

std::string wxx_chr(int code);
int wxx_ord(std::string src);
int wxx_ord(std::string src, int pos);

std::string wxx_chomp(const std::string &src);
std::string wxx_escape(const std::string &src);

} // namespace WinxedXX

#endif

// End of winxedxx_types.h
