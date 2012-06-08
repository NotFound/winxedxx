#ifndef INCLUDE_WINXEDXX_INTEGER_H
#define INCLUDE_WINXEDXX_INTEGER_H

// winxedxx_integer.h

// (C) 2011-2012 Julián Albo "NotFound"

#include <vector>

namespace WinxedXX
{

int wxx_int_cast(int i);
int wxx_int_cast(double n);
int wxx_int_cast(const std::string &str);
int wxx_int_cast(const WxxObjectPtr &obj);

double wxx_num_cast(int i);
double wxx_num_cast(double n);
double wxx_num_cast(const std::string &str);
double wxx_num_cast(const WxxObjectPtr &obj);

std::string www_string_cast(int i);
std::string www_string_cast(double n);
std::string wxx_string_cast(const std::string &str);
std::string wxx_string_cast(const WxxObjectPtr &obj);

std::string wxx_repeat_string(std::string s, int n);

class WxxInteger : public WxxDefault
{
public:
    WxxInteger(int value);
    void init_pmc(const WxxObjectPtr &arg);
    std::string class_name() const;
    int get_integer();
    double get_number();
    std::string get_string();
    int is_equal(const WxxObject &to);
    WxxObject & set(int value);
    WxxObject & set(double value);
    void increment();
    WxxObjectPtr add(const WxxObjectPtr &value);
    WxxObjectPtr sub(const WxxObjectPtr &value);
    void decrement();
private:
    int i;
};

class WxxFloat : public WxxDefault
{
public:
    WxxFloat(double value);
    std::string class_name() const;
    int get_integer();
    double get_number();
    std::string get_string();
    WxxObject & set(int value);
    WxxObject & set(double value);
private:
    double n;
};

class WxxString : public WxxDefault
{
public:
    WxxString(std::string value);
    std::string class_name() const;
    std::string get_string();
    WxxObject & set(const std::string &s);
    WxxObjectPtr get_iter();
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
    virtual WxxArrayBase& push(const std::string &str) = 0;
    virtual void set_pmc_keyed(int i, const WxxObjectPtr &value) = 0;
    WxxObjectPtr get_iter();
};

class WxxIntegerArray : public WxxArrayBase
{
public:
    WxxIntegerArray();
    ~WxxIntegerArray();
    int elements() const;
    WxxObject & set(int value);
    int operator[](int i) const;
    int get_integer_keyed(int i);
    std::string get_string_keyed(int i);
    double get_number_keyed(int i);
    WxxObjectPtr get_pmc_keyed(int i);
    WxxIntegerArray& push(WxxObjectPtr obj);
    WxxIntegerArray& push(int i);
    WxxIntegerArray& push(double value);
    WxxIntegerArray& push(const std::string &str);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
private:
    std::vector<int> arr;
};

class WxxFloatArray : public WxxArrayBase
{
public:
    WxxFloatArray();
    ~WxxFloatArray();
    int elements() const;
    WxxObject & set(int value);
    double operator[](int i) const;
    int get_integer_keyed(int i);
    double get_number_keyed(int i);
    std::string get_string_keyed(int i);
    WxxObjectPtr get_pmc_keyed(int i);
    WxxFloatArray& push(WxxObjectPtr obj);
    WxxFloatArray& push(int i);
    WxxFloatArray& push(double value);
    WxxFloatArray& push(const std::string &str);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
private:
    std::vector<double> arr;
};

class WxxStringArray : public WxxArrayBase
{
public:
    WxxStringArray();
    WxxStringArray(char **argv);
    ~WxxStringArray();
    int elements() const;
    WxxObject & set(int value);
    std::string operator[](int i) const;
    int get_integer_keyed(int i);
    double get_number_keyed(int i);
    std::string get_string_keyed(int i);
    WxxObjectPtr get_pmc_keyed(int i);
    WxxStringArray& push(WxxObjectPtr obj);
    WxxStringArray& push(int i);
    WxxStringArray& push(double value);
    WxxStringArray& push(const std::string &str);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
private:
    std::vector<std::string> arr;
};

class WxxObjectArray : public WxxArrayBase
{
public:
    WxxObjectArray();
    ~WxxObjectArray();
    int elements() const;
    WxxObject & set(int value);
    WxxObjectPtr operator[](int i) const;
    int get_integer_keyed(int i);
    double get_number_keyed(int i);
    std::string get_string_keyed(int i);
    WxxObjectPtr get_pmc_keyed(int i) const;
    WxxObjectPtr get_pmc_keyed(int i);
    WxxObjectArray& push(WxxObjectPtr obj);
    WxxObjectArray& push(int i);
    WxxObjectArray& push(double value);
    WxxObjectArray& push(const std::string &str);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
private:
    std::vector<WxxObjectPtr *> arr;
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

class WxxStringIterator : public WxxDefault
{
public:
    WxxStringIterator(const std::string &container);
    ~WxxStringIterator();
    int get_bool();
    WxxObjectPtr shift_pmc();
private:
    std::string cnt;
    int current;
};

class WxxHash : public WxxDefault
{
public:
    WxxHash();
    WxxHash & set(const std::string &key, WxxObjectPtr value);
    int elements() const;
    using WxxDefault::set_pmc_keyed;
    void set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    int exists(const std::string &key);
private:
    std::map<std::string, WxxObjectPtr> hsh;
};

class WxxSub : public WxxDefault
{
public:
    WxxSub(WxxObjectPtr(*)(const WxxObjectArray &));
    WxxSub(WxxObjectPtr(*)(const WxxObjectArray &), const std::string &subname);
    WxxObjectPtr operator()(WxxObjectArray &args);
    std::string get_string();
    void * get_pointer();
private:
    std::string name;
    WxxObjectPtr(*fn)(const WxxObjectArray &);
};

class WxxClosure : public WxxDefault
{
public:
    WxxClosure(WxxInnerFunction *);
    ~WxxClosure();
    WxxObjectPtr operator()(WxxObjectArray &args);
private:
    WxxInnerFunction *fn;
};

class WxxClass : public WxxDefault
{
public:
    typedef WxxObjectPtr (*memberfun)(WxxObjectPtr &, const WxxObjectArray &);

    WxxClass(const std::string &name);
    std::string get_string();

    std::string class_name() const;
    void addattribute(const std::string &attrname);
    void addfunction(const std::string &fname, memberfun);
    memberfun getfunction(const std::string &fname);
    static WxxClass * getclass(const std::string &name);
    WxxObjectPtr get_class();
    WxxObjectPtr instantiate();
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
private:
    std::string clname;
    std::vector<std::string> attrs;
    std::map<std::string, memberfun> regfun;
};

class WxxInstance : public WxxDefault
{
public:
    WxxInstance(const std::string &clname);
    WxxInstance(WxxClass &cassobjl);
    std::string class_name() const;
    WxxObjectPtr get_class();
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
private:
    WxxClass *cl;
};

class WxxLibrary : public WxxDefault
{
public:
    WxxLibrary(void *dl_handle);
    void * getsym(const std::string &funcname);

    int get_bool();
    int get_integer();
    void * get_pointer();
private:
    void *dl_h;
};

} // namespace WinxedXX

#endif

// End of winxedxx_integer.h
