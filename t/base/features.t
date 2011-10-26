#! winxed
// Test file for winxedxx supported features
// All features used here should at least compile

//**********************************************************************

// Minimalistic TAP functions

class Test
{
    var count;
    function Test()
    {
        self.count = 0;
    }
    function inc_count()
    {
        int count = self.count;
        ++count;
        self.count =: count;
        return count;
    }

    function ok(int check, string message)
    {
        if (! check)
            print("not ");
        print("ok ");
        print(self.inc_count());
        say(" - ", message);
    }
    function nok(int check, string message)
    {
        if (check)
            print("not ");
        print("ok ");
        print(self.inc_count());
        say(" - ", message);
    }
    function todo(int check, string message)
    {
        if (! check)
            print("not ");
        print("ok ");
        print(self.inc_count());
        say(" - ", message, " # TODO");
    }
    function ntodo(int check, string message)
    {
        self.todo(! check, message);
    }

    function is(int value, int check, string message)
    {
        if (value != check)
            print("not ");
        print("ok ");
        print(self.inc_count());
        say(" - ", message);
        if (value != check)
            say("# got: ", value, ", excpected: ", check);
    }
    function is_string(string value, string check, string message)
    {
        if (value != check)
            print("not ");
        print("ok ");
        print(self.inc_count());
        say(" - ", message);
        if (value != check)
            say("# got: '", value, "', expected: '", check, "'");
    }

    function done_testing()
    {
        say("1..", self.count);
    }
}

//**********************************************************************

function test_array(test)
{
    var arr = [ "a", "b", "c", "d" ];
    test.is(elements(arr), 4, "array literal");
    test.is_string(arr[2], "c", "array element initialized");
}

function test_hash(test)
{
    var hash = { "a" : 1, "b" : "x" };
    test.is_string(hash["b"], "x", "hash element initialized");
    var key = "b";
    hash[key] = "y";
    test.is_string(hash["b"], "y", "hash kayed with String var - set");
    hash["b"] = "z";
    test.is_string(hash[key], "z", "hash kayed with String var - get");

    test.nok(exists hash["none"], "hash exists false case");
    test.ok(exists hash["a"], "hash exists true case");
}

namespace Foo
{

function bar()
{
    return "Foo.bar";
}

} // namespace Foo

function bar()
{
    return "bar";
}

class SomeClass
{
}

function test_switchcase(test)
{
    int i = 42;
    int result = 0;
    switch {
      case i == 42:
        result = 1;
        break;
      default:
        // Make sure the previous break skip this
        result = 0;
    }
    test.is(result, 1, "switchcase");
}

function test_try(test)
{
    int result = 1;
    try {
        throw Error("whatever");
        result = 0;
    }
    catch () {
        result = 42;
    }
    test.is(result, 42, "try - catch");

    result = 1;
    try {
        throw Error("whatever", 2, 42);
        result = 0;
    }
    catch (e) {
        result = e.type;
    }
    test.is(result, 42, "try - catch, use exception");
}

//**********************************************************************

class Cl
{
    var foo;
}

//**********************************************************************

function miscellaneous(test, int runit)
{
    // Just do a full syntax check, do not execute.
    // The variable condition is used to avoid being optimized out.
    if (runit) {
        exit(0);
    }
    test.ok(1, "some syntax checks");
}

//**********************************************************************

function main [main] (args)
{
    var test = new Test();

    test.ok(1, "compiled and started");

    // No debug mode yet, just ensure this can be compiled
    __ASSERT__(1 == 1);

    int i = 1;
    test.ok(i == 1, "int initialization");

    string str = "hi";
    test.is_string(str, "hi", "string initialization");
    str = "hello";
    test.is_string(str, "hello", "string assign");
    str = i;
    test.is_string(str, "1", "string assign from int");
    str = 42;
    i = str;
    test.is(i, 42, "int assign from string");
    i = "44";
    test.is(i, 44, "int assign from string literal");

    var n = null;
    test.ok(n == null, "var null initialization");

    var vi1 = 42;
    test.is(vi1, 42, "var initialized with int");
    test.ok(vi1 != null, "var initialized with int is not null");

    i = 1;
    test.is(i == 1 ? vi1 : 44, 42, "conditional operator var - int");
    test.is(i != 1 ? 44 : vi1, 42, "conditional operator int - var");

    i = -i;
    test.is(i, -1, "unary minus");

    var vi2 = 42;
    var vi3 = 7;
    test.todo(vi1 == vi2, "operator == : x == same class, same value");
    test.nok(vi1 == vi3, "operator == : x == same class, not same value");
    test.ntodo(vi1 != vi2, "operator != : x != same class, same value");

    test.ok(test === test, "operator === : x === x");
    test.nok(test !== test, "operator !== : x !== x");
    test.nok(vi1 === vi2, "operator === : x === same class");
    test.ok(vi1 !== vi2, "operator !== : x !== same class");
    test.nok(vi1 === test, "operator === : x === other class");
    test.ok(vi1 !== test, "operator !== : x !== other class");

    string s = "abc";
    test.is_string(s * 3, "abcabcabc", "repeat string");

    i = 1;

    test.is(~i, -2, "bitwise not");

    test.is(i | 2, 3, "bitwise or");

    test.is(i ^ 3, 2, "bitwise xor");

    test.is(i << 2, 4, "shift left");
    i = 8;
    test.is(i >> 2, 2, "shift right");

    test.is_string(s[1], "b", "string indexing");

    int j = 12;
    for (i = 0; i < 10; ++i)
        --j;
    test.is(j, 2, "for loop, inc and dec operators");

    j = 0;
    for (i in [ 1, 3, 5, 7 ])
        j += i;
    test.is(j, 16, "for in");

    test_array(test);
    test_hash(test);

    test.is_string(Foo.bar(), "Foo.bar", "call function in namespace");
    test.is_string(bar(), "bar", "call function out of namespace with same name");

    test_switchcase(test);
    test_try(test);

    var obj = new SomeClass;
    test.ok(obj instanceof SomeClass, "new and instanceof by identifier");

    var cl = new Cl;
    cl.foo = "Cl_foo";
    s = "foo";
    s = cl.*s;
    test.is_string(s, "Cl_foo", "indirect get attribute");

    miscellaneous(test, false);

    test.done_testing();
}

// End