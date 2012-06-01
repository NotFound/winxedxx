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
    WxxNamespace &childNamespace(const std::string &name);
    void set(const std::string &name, const WxxObjectPtr &value);
private:
    // vtable functions
    std::string get_string();
    WxxObjectPtr get_pmc_keyed(const std::string &s);
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);

    const std::string name;
    WxxNamespace * const parentns;
    std::map<std::string, WxxNamespace *> childs;
    std::map<std::string, WxxObjectPtr> symbols;
};

WxxNamespace &getRootNamespace();

} // namespace WinxedXX

#endif

// End of winxedxx_namespace.h
