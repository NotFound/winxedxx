#ifndef INCLUDE_WINXEDXX_NAMESPACE_H
#define INCLUDE_WINXEDXX_NAMESPACE_H

// winxedxx_namespace.h

// (C) 2012 Julián Albo "NotFound"

#include "winxedxx_types.h"

#include <string>
#include <map>

namespace WinxedXX
{

class WxxNamespace
{
protected:
    WxxNamespace();
    WxxNamespace(const std::string &name, WxxNamespace *parent);
public:
    WxxObjectPtr get(const std::string &name);
    void set(const std::string &name, const WxxObjectPtr &value);
private:
    WxxNamespace *parentns;
    std::map<std::string, WxxObjectPtr> symbols;
};

WxxNamespace &getRootNamespace();

} // namespace WinxedXX

#endif

// End of winxedxx_namespace.h
