// winxedxx_namespace.cxx

// (C) 2012 Julián Albo "NotFound"

#include "winxedxx_namespace.h"
#include "winxedxx_integer.h"

namespace WinxedXX
{

typedef std::map<std::string, WxxObjectPtr> symbols_t;
typedef std::map<std::string, WxxNamespace *> childs_t;

WxxNamespace::WxxNamespace() :
        WxxDefault("NameSpace"),
	name("winxedxx"),
        parentns(0)
{
}

WxxNamespace::WxxNamespace(const std::string &nsname, WxxNamespace *parent) :
        WxxDefault("NameSpace"),
	name(nsname),
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

WxxObjectPtr WxxNamespace::find_symbol(const std::string &name)
{
    symbols_t::const_iterator it = symbols.find(name);
    if (it == symbols.end()) {
        if (parentns)
            return parentns->find_symbol(name);
        else
            return winxedxxnull;
    }
    return WxxObjectPtr(it->second);
}

WxxNamespace &WxxNamespace::childNamespace(const std::string &name)
{
    childs_t::const_iterator it = childs.find(name);
    if (it == childs.end()) {
        WxxNamespace *child = new WxxNamespace(name, this);
        childs[name] = child;
        return *child;
    }
    return *it->second;
}

void WxxNamespace::set(const std::string &name, const WxxObjectPtr &value)
{
    symbols[name] = value;
}

void WxxNamespace::setClass(const std::string &name, WxxClass *value)
{
    classes[name] = value;
    symbols[name] = WxxObjectPtr(value);
}

WxxClass * WxxNamespace::getClass(const std::string &name)
{
    WxxClass *cl = classes[name];
    if (!cl)
        throw wxx_error("class not found in namespace: " + name);
    return cl;
}

std::string WxxNamespace::get_string()
{
    return name;
}

WxxObjectPtr WxxNamespace::get_pmc_keyed(const std::string &s)
{
    return get(s);
}

void WxxNamespace::set_pmc_keyed(const std::string &s, const WxxObjectPtr &value)
{
    set(s, value);
}

WxxObjectPtr WxxNamespace::call_method(const std::string &methname, WxxObjectArray &args)
{
    if (methname == "get_parent")
        return parentns ? parentns : winxedxxnull;
    else if (methname == "find_var")
        return get(args.get_string_keyed(0));
    else if (methname == "add_var") {
        set(args.get_string_keyed(0), args.get_pmc_keyed(1));
	return winxedxxnull;
    }
    else
        return WxxDefault::call_method(methname, args);
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
