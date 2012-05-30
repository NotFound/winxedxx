// winxedxx_namespace.cxx

// (C) 2012 Julián Albo "NotFound"

#include "winxedxx_namespace.h"

namespace WinxedXX
{

typedef std::map<std::string, WxxObjectPtr> symbols_t;

WxxNamespace::WxxNamespace() :
        parentns(0)
{
}

WxxNamespace::WxxNamespace(const std::string &name, WxxNamespace *parent) :
        parentns(parent)
{
}

WxxObjectPtr WxxNamespace::get(const std::string &name)
{
    symbols_t::const_iterator it = symbols.find(name);
    if (it == symbols.end())
        return winxedxxnull;
    return WxxObjectPtr(it->second);
}

void WxxNamespace::set(const std::string &name, const WxxObjectPtr &value)
{
    symbols[name] = value;
}

//**************************************************************

class WxxRootNamespace : WxxNamespace
{
    friend WxxNamespace &getRootNamespace();
};

static WxxRootNamespace *rootnamespace = 0;

WxxNamespace &getRootNamespace()
{
    if (! rootnamespace)
        rootnamespace = new WxxRootNamespace();
    return *rootnamespace;
}

} // namespace WinxedXX

// End of winxedxx_namespace.cxx
