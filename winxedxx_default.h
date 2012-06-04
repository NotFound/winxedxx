#ifndef INCLUDE_WINXEDXX_DEFAULT_H
#define INCLUDE_WINXEDXX_DEFAULT_H

// winxedxx_default.h

// (C) 2011-2012 Julián Albo "NotFound"

namespace WinxedXX
{

class WxxDefault : public WxxObject
{
protected:
    WxxDefault();
    WxxDefault(const std::string &name);
    ~WxxDefault();
public:
    void init_pmc(const WxxObjectPtr &arg);
    std::string class_name() const;
    int is_null() const;
    std::string getname() const;
    int instanceof(const std::string &type);
    int get_bool();
    int get_integer();
    double get_number();
    void * get_pointer();
    void set_pointer(void *p);
    int elements() const;
    virtual std::string get_string();
    int is_equal(const WxxObject &to);
    WxxObject & set(int value);
    WxxObject & set(double value);
    WxxObject & set(const std::string &s);
    void increment();
    void decrement();
    WxxObjectPtr add(const WxxObjectPtr &value);
    WxxObjectPtr sub(const WxxObjectPtr &value);
    int get_integer_keyed(int i);
    double get_number_keyed(int i);
    std::string get_string_keyed(int i);
    WxxObjectPtr get_pmc_keyed(int i);
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    WxxObjectPtr get_pmc_keyed(const WxxObjectPtr &key);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);
    void set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);
    int exists(const std::string &key);
    WxxObjectPtr & get_attr_str(const std::string &s);
    void set_attr_str(const std::string &s, const WxxObjectPtr &value);
    WxxObjectPtr get_iter();
    WxxObjectPtr shift_pmc();
    WxxObjectPtr get_class();
    WxxObjectPtr instantiate();
    WxxObjectPtr operator()(WxxObjectArray &args);
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
private:
    std::string name;
    std::map<std::string, WxxObjectPtr> attributes;
    void notimplemented(const std::string &funcname) const;
};


} // namespace WinxedXX

#endif

// End of winxedxx_default.h
