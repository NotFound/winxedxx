#ifndef INCLUDE_WINXEDXX_OBJECT_H
#define INCLUDE_WINXEDXX_OBJECT_H

// winxedxx_object.h
// (C) 2011 Julián Albo "NotFound"

namespace WinxedXX
{

class WxxObject : public WxxRefcounted
{
public:
    virtual void init_pmc(const WxxObjectPtr &arg) = 0;
    virtual int is_null() const = 0;
    virtual std::string class_name() const = 0;
    virtual int instanceof(const std::string &type) = 0;
    virtual int get_bool() = 0;
    virtual int get_integer() = 0;
    virtual double get_number() = 0;
    virtual void * get_pointer() = 0;
    virtual void set_pointer(void *p) = 0;
    virtual int elements() const = 0;
    virtual std::string get_string() = 0;
    virtual int is_equal(const WxxObject &to) = 0;
    virtual WxxObject & set(int value) = 0;
    virtual WxxObject & set(double value) = 0;
    virtual WxxObject & set(const std::string &s) = 0;
    virtual void increment() = 0;
    virtual void decrement() = 0;
    virtual WxxObjectPtr add(const WxxObjectPtr &value) = 0;
    virtual WxxObjectPtr sub(const WxxObjectPtr &value) = 0;
    virtual int get_integer_keyed(int i) = 0;
    virtual double get_number_keyed(int i) = 0;
    virtual std::string get_string_keyed(int i) = 0;
    virtual WxxObjectPtr get_pmc_keyed(int i) = 0;
    virtual WxxObjectPtr get_pmc_keyed(const std::string &s) = 0;
    virtual WxxObjectPtr get_pmc_keyed(const WxxObjectPtr &key) = 0;
    virtual void set_pmc_keyed(int i, const WxxObjectPtr &value) = 0;
    virtual void set_pmc_keyed(const std::string &s, const WxxObjectPtr &value) = 0;
    virtual int exists(const std::string &key) = 0;
    virtual WxxObjectPtr & get_attr_str(const std::string &s) = 0;
    virtual void set_attr_str(const std::string &s, const WxxObjectPtr &value) = 0;
    virtual WxxObjectPtr get_iter() = 0;
    virtual WxxObjectPtr shift_pmc() = 0;

    virtual WxxObjectPtr get_class() = 0;
    virtual WxxObjectPtr instantiate() = 0;
    virtual WxxObjectPtr operator()(WxxObjectArray &args) = 0;
    virtual WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args) = 0;
};

WxxObjectPtr wxx_getstdin();
WxxObjectPtr wxx_getstdout();
WxxObjectPtr wxx_getstderr();
WxxObjectPtr wxx_spawnw(WxxObjectPtr obj);

} // namespace WinxedXX

#endif

// End of winxedxx_object.h
