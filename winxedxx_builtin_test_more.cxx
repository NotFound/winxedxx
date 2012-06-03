// winxedxx_builtin_test_more.h
// (C) 2012 Julián Albo "NotFound"

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"
#include "winxedxx_namespace.h"

#include <iostream>

namespace WinxedXX
{

namespace Builtin
{

namespace Test
{

namespace More
{

static int counter;

WxxObjectPtr diag(const WxxObjectArray &args)
{
    std::string msg;
    for (int i = 0; i < args.elements(); ++i)
         msg += args.get_pmc_keyed(i).get_string();
    size_t pos = msg.find('\n');
    while (pos != std::string::npos) {
        std::string part = msg.substr(0, pos);
        if (part.length() == 0 || part[0] != '#')
            std::cout << "# ";
        std::cout << part << '\n';
        msg.erase(pos + 1);
        pos = msg.find('\n');
    }
    if (msg != "") {
        if (msg[0] != '#')
            std::cout << "# ";
        std::cout << msg << '\n';
    }

    return winxedxxnull;
}

WxxObjectPtr plan(const WxxObjectArray &args)
{
    counter = 0;
    int numtests = args.get_pmc_keyed(0).get_integer();
    std::cout << "1.." << numtests << "\n";
    return winxedxxnull;
}

WxxObjectPtr done_testing(const WxxObjectArray &args)
{
    std::cout << "1.." << counter << "\n";
    return winxedxxnull;
}

static int numNewTest()
{
    return ++counter;
}

WxxObjectPtr ok(const WxxObjectArray &args)
{
    int numargs = args.elements();
    int value = args.get_pmc_keyed(0).get_integer();
    if (! value)
        std::cout << "n";
    std::cout << "ok " << numNewTest();
    if (numargs > 1)
        std::cout << " - " << args.get_pmc_keyed(1).get_string();
    std::cout << "\n";

    return winxedxxnull;
}

WxxObjectPtr nok(const WxxObjectArray &args)
{
    int numargs = args.elements();
    int value = args.get_pmc_keyed(0).get_integer();
    if (value)
        std::cout << "n";
    std::cout << "ok " << numNewTest();
    if (numargs > 1)
        std::cout << " - " << args.get_pmc_keyed(1).get_string();
    std::cout << "\n";

    return winxedxxnull;
}

static bool args_equal(WxxObjectPtr &value, WxxObjectPtr &expected)
{
    bool result;
    // Poor man's "multi" dispatch
    bool is_integer =
            value.instanceof("Integer") && expected.instanceof("Integer");
    bool is_number = is_integer || (
            (value.instanceof("Float") || value.instanceof("Integer")) &&
            (expected.instanceof("Float") ||expected.instanceof("Integer") ));
    bool is_string = (! is_number) &&
            (value.instanceof("String") && expected.instanceof("String"));
    if (is_integer)
        result = value.get_integer() == expected.get_integer();
    else if (is_number)
        result = value.get_number() == expected.get_number();
    else if (is_string)
        result = value.get_string() == expected.get_string();
    else
        result = value.is_equal(expected);
    return result;
}

WxxObjectPtr is(const WxxObjectArray &args)
{
    int numargs = args.elements();
    WxxObjectPtr value = args.get_pmc_keyed(0);
    WxxObjectPtr expected = args.get_pmc_keyed(1);
    std::string msg = numargs > 2 ? args.get_pmc_keyed(2).get_string() : "";

    bool result = args_equal(value, expected);

    if (! result)
        std::cout << "n";
    std::cout << "ok " << numNewTest();
    if (msg != "")
        std::cout << " - " << msg;
    std::cout << "\n";

    return winxedxxnull;
}

WxxObjectPtr isnt(const WxxObjectArray &args)
{
    int numargs = args.elements();
    WxxObjectPtr value = args.get_pmc_keyed(0);
    WxxObjectPtr expected = args.get_pmc_keyed(1);
    std::string msg = numargs > 2 ? args.get_pmc_keyed(2).get_string() : "";

    bool result = args_equal(value, expected);

    if (result)
        std::cout << "n";
    std::cout << "ok " << numNewTest();
    if (msg != "")
        std::cout << " - " << msg;
    std::cout << "\n";

    return winxedxxnull;
}

//******************************************************

void initialize()
{
    counter = 0;
    WxxNamespace &ns = getRootNamespace().
            childNamespace("Test").childNamespace("More");
    ns.set("diag", new WxxSub(&diag));
    ns.set("plan", new WxxSub(&plan));
    ns.set("done_testing", new WxxSub(&done_testing));
    ns.set("ok", new WxxSub(&ok));
    ns.set("nok", new WxxSub(&nok));
    ns.set("is", new WxxSub(&is));
    ns.set("isnt", new WxxSub(&isnt));
}

} // namespace Test
} // namespace More
} // namespace Builtin
} // namespace WinxedXX


// End of winxedxx_builtin_test_more.h
