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
class WxxNamespace;

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
    WxxObjectPtr(WxxNamespace * obj);
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
    int instanceof(const std::string &type) const;
    std::string get_string() const;
    int get_integer() const;
    double get_number() const;
    void *get_pointer() const;
    void set_pointer(void *p) const;
    int elements() const;
    WxxObjectPtr add(const WxxObjectPtr &value);
    WxxObjectPtr sub(const WxxObjectPtr &value);
    std::string get_string_keyed(int i) const;
    WxxObjectPtr get_pmc_keyed(int i) const;
    WxxObjectPtr get_pmc_keyed(const std::string &s) const;
    WxxObjectPtr get_pmc_keyed(const WxxObjectPtr &key) const;
    void set_pmc_keyed(int i, const WxxObjectPtr &value) const;
    void set_pmc_keyed(const std::string &s, const WxxObjectPtr &value) const;
    void set_pmc_keyed(const WxxObjectPtr &key, const WxxObjectPtr &value) const;
    int exists(const std::string &key) const;
    WxxObjectPtr & get_attr_str(const std::string &s) const;
    void set_attr_str(const std::string &s, const WxxObjectPtr &value) const;
    void push(WxxObjectPtr obj) const;
    void push(int i) const;
    void push(double value) const;
    void push(const std::string &str) const;
    WxxObjectPtr get_iter() const;
    WxxObjectPtr shift_pmc() const;
    WxxObjectPtr get_class() const;
    WxxObjectPtr instantiate() const;
    WxxObjectPtr operator()(const WxxObjectArray &args) const;
    WxxObjectPtr call_method(const std::string &methname) const;
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args) const;
    WxxLibrary *getlib() const;
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

std::string wxx_substr(const std::string &from, int start);
std::string wxx_substr(const std::string &from, int start, int length);

int wxx_indexof(const std::string &from, const std::string &search);
int wxx_indexof(const std::string &from, const std::string &search, int pos);

std::string wxx_chomp(const std::string &src);

std::string wxx_escape(const std::string &src);
std::string wxx_unescape(const std::string &src);

WxxObjectPtr wxx_new(const std::string &name);
WxxObjectPtr wxx_new(const std::string &name, WxxObjectArray args);
WxxObjectPtr wxx_new_string(const std::string &name);
WxxObjectPtr wxx_new_string(const std::string &name, WxxObjectPtr arg);

WxxObjectPtr wxx_open(const std::string &filename);
WxxObjectPtr wxx_open(const std::string &filename, const std::string &mode);

} // namespace WinxedXX

#endif

// End of winxedxx_types.h
