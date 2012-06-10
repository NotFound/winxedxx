#ifndef INCLUDE_WINXEDXX_NAMESPACE_H
#define INCLUDE_WINXEDXX_NAMESPACE_H

// winxedxx_namespace.h

// (C) 2012 Julián Albo "NotFound"

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"

#include <string>
#include <map>

namespace WinxedXX
{

class WxxClass;

class WxxNamespace : public WxxDefault
{
protected:
    WxxNamespace();
    WxxNamespace(const std::string &nsname, WxxNamespace *parent);
private:
    WxxNamespace(const WxxNamespace &);
    void operator = (const WxxNamespace &);
public:
    WxxObjectPtr get(const std::string &name);
    WxxObjectPtr find_symbol(const std::string &name);
    WxxNamespace &childNamespace(const std::string &name);
    void set(const std::string &name, const WxxObjectPtr &value);
    void setClass(const std::string &name, WxxClass *value);
    WxxClass * getClass(const std::string &name);
private:
    // vtable functions
    std::string get_string();
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    void set_pmc_keyed(const std::string &s, const WxxObjectPtr &value);

    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);

    const std::string name;
    WxxNamespace * const parentns;
    std::map<std::string, WxxNamespace *> childs;
    std::map<std::string, WxxClass *> classes;
    std::map<std::string, WxxObjectPtr> symbols;
};

WxxNamespace &getRootNamespace();

} // namespace WinxedXX

#endif

// End of winxedxx_namespace.h
