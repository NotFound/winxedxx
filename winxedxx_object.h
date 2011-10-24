#ifndef INCLUDE_WINXEDXX_OBJECT_H
#define INCLUDE_WINXEDXX_OBJECT_H

// winxedxx_object.h
// (C) 2011 Julián Albo "NotFound"

namespace WinxedXX
{

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
    virtual std::string get_string_keyed(int i) = 0;
    virtual WxxObjectPtr get_pmc_keyed(int i) = 0;
    virtual WxxObjectPtr get_pmc_keyed(const std::string &s) = 0;
    virtual WxxObjectPtr get_pmc_keyed(const char *s) = 0;
    virtual void set_pmc_keyed(int i, const WxxObjectPtr &value) = 0;
    virtual int exists(const std::string &key) = 0;
    virtual WxxObjectPtr & set_pmc_keyed(const std::string &s, const WxxObjectPtr &value) = 0;
    virtual WxxObjectPtr & get_attr_str(const std::string &s) = 0;
    virtual void set_attr_str(const std::string &s, const WxxObjectPtr &value) = 0;
    virtual WxxObjectPtr get_iter() = 0;
    virtual WxxObjectPtr shift_pmc() = 0;

    virtual WxxObjectPtr operator()(WxxObjectArray &args) = 0;
    virtual WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args) = 0;
    virtual void print() = 0;
    virtual void print(WxxObjectPtr obj) = 0;
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

WxxObjectPtr wxx_getstdin();
WxxObjectPtr wxx_getstdout();
WxxObjectPtr wxx_getstderr();

} // namespace WinxedXX

#endif

// End of winxedxx_object.h
