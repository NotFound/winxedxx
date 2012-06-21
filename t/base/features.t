#! winxed
// Test file for winxedxx supported features
// All features used here should at least compile

using extern Test.More ok, nok, is, done_testing;

//**********************************************************************

function test_string_misc()
{
    var arr = [ "a", "b", "c" ];
    string s = join("-", arr);
    is(s, "a-b-c", "join with literal string");
    string sep = "<<";
    s = join(sep, arr);
    is(s, "a<<b<<c", "join with string var");
    var arr2 = split("<<", s);
    is(elements(arr2), 3, "split");

    s = chr(0x30);
    is(s, "0", "chr literal int");
    int i = 0x31;
    s = chr(i);
    is(s, "1", "chr int");
    var code = 0x32;
    s = chr(code);
    is(s, "2", "chr var");

    s = "012012";
    is(ord(s), 0x30, "ord 1 arg");
    is(ord(s, 1), 0x31, "ord 2 args");

    int pos = indexof(s, "2");
    is(pos, 2, "indexof 2 args");
    pos = indexof(s, "2", pos + 1);
    is(pos, 5, "indexof 3 args");

    is(substr(s, 2), "2012", "substr 2 args");
    is(substr(s, 2, 3), "201", "substr 3 args");

    s = "a\t\nb\\c";
    is(escape(s), 'a\t\nb\\c', "escape");
}

function test_string_iter()
{
    string s = "hello";
    string r = '';
    int count = 0;
    for (string c in s) {
        ++count;
        r = c + r;
    }
    is(count, length(s), "string iterator - length");
    is(r, "olleh", "string iterator gives chars");
}

function aux0()
{
    return "aux0";
}

function aux1()
{
    return "aux1";
}

function aux2()
{
    return "aux2";
}

function test_array()
{
    var arr = [ "a", "b", "c", "d" ];
    ok(arr instanceof "ResizablePMCArray", "array literal has expected type");
    is(elements(arr), 4, "array literal has expected size");
    is(arr[2], "c", "array element initialized");

    string sarr[] = [ "foo", "bar" ];
    ok(sarr instanceof "ResizableStringArray", "string array has expected type");
    int iarr[] = [ 42 ];
    ok(iarr instanceof "ResizableIntegerArray", "int array has expected type");
}

function test_hash()
{
    var hash = { "a" : 1, "b" : "x" };
    is(hash["b"], "x", "hash element initialized");
    var key = "b";
    hash[key] = "y";
    is(hash["b"], "y", "hash kayed with String var - set");
    hash["b"] = "z";
    is(hash[key], "z", "hash kayed with String var - get");

    nok(exists hash["none"], "hash exists false case");
    ok(exists hash["a"], "hash exists true case");
}

function test_func()
{
    var f = aux1;
    string s = f();
    is(s, "aux1", "assign function to var");

    var h = { "a" : aux1, "b" : aux2 };
    f = h["b"];
    is(f(), "aux2", "initialize hash value with function");

    var a = [ aux0, aux1, aux2 ];
    f = a[0];
    is(f(), "aux0", "initialize array value with function");
}

namespace Foo
{

function bar()
{
    return "Foo.bar";
}

// This is to avoid a C++ compiler warning.
class Unused { }

} // namespace Foo

function bar()
{
    return "bar";
}

class SomeClass
{
}

function test_switchcase()
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
    is(result, 1, "switchcase");
}

function test_try()
{
    int result = 1;
    try {
        throw Error("whatever");
        result = 0;
    }
    catch () {
        result = 42;
    }
    is(result, 42, "try - catch");

    result = 1;
    try {
        throw Error("whatever", 2, 42);
        result = 0;
    }
    catch (e) {
        result = e.type;
    }
    is(result, 42, "try - catch, use exception");
}

//**********************************************************************

class Cl
{
    var foo;
}

class Bar
{
    var msg;
    function Bar()
    {
        self.msg = "class Bar";
    }
    function get() { return self.msg; }
}

//**********************************************************************

function miscellaneous(int runit)
{
    // Just do a full syntax check, do not execute.
    // The variable condition is used to avoid being optimized out.
    if (runit) {
        exit(0);
        die("message");
    }

    string s = "abc\n";
    string sc = chomp(s);
    ok(length(s) == 4 && length(sc) == 3, "chomp - yes \\n");
    s = "abc\t";
    sc = chomp(s);
    ok(length(s) == 4 && length(sc) == 4, "chomp - no \\t");
    s = "abc\r";
    sc = chomp(s);
    ok(length(s) == 4 && length(sc) == 4, "chomp - no \\r");

    int t = time();
    float ft1 = floattime();
    sleep(0.1);
    float ft2 = floattime();
    float diff = ft2 - ft1;

    // Should work except unless system exceptionally slow.
    ok(diff >= 0.1 && diff < 0.5 && t <= ft2 + 1.0,
        "time and floattime with sleep results looks reasonable");

    ok(1, "some syntax checks");
}

//**********************************************************************

function main [main] (args)
{
    ok(1, "compiled and started");

    // No debug mode yet, just ensure this can be compiled
    __ASSERT__(1 == 1);

    int i = 1;
    ok(i == 1, "int initialization");

    string str = "hi";
    is(str, "hi", "string initialization");
    str = "hello";
    is(str, "hello", "string assign");
    str = i;
    is(str, "1", "string assign from int");
    str = 42;
    i = str;
    is(i, 42, "int assign from string");
    i = "44";
    is(i, 44, "int assign from string literal");

    float n = 4.5;
    str = n;
    is(str, "4.5", "string assign from float");
    str = "2.5";
    n = str;
    is(n, 2.5, "float assign from string");

    string stri = 42;
    is(stri, "42", "string initialization from int");

    string strn = 4.5;
    is(strn, "4.5", "string initialization from float");

    var nothing = null;
    ok(nothing == null, "var null initialization");

    var vi1 = 42;
    is(vi1, 42, "var initialized with int");
    ok(vi1 != null, "var initialized with int is not null");

    var vn1 = 8.5;
    is(vn1, 8.5, "var initialized with float");

    is(int(vi1), 42, "int cast from string");
    is(int(n), 2, "int cast from float");
    is(string(i), "44", "string cast from int");

    i = 42;
    ok(i == vi1, "operator == int var - true");
    ok(vi1 == i, "operator == var int - true");
    i = 44;
    nok(i == vi1, "operator == int var - false");
    nok(vi1 == i, "operator == var int - false");

    ok(i != vi1, "operator != int var - true");
    ok(vi1 != i, "operator != var int - true");
    i = 42;
    nok(i != vi1, "operator != int var - false");
    nok(vi1 != i, "operator != var int - false");

    i = 1;
    is(i == 1 ? vi1 : 44, 42, "conditional operator var - int");
    is(i != 1 ? 44 : vi1, 42, "conditional operator int - var");

    i = -i;
    is(i, -1, "unary minus");

    var vi2 = 42;
    var vi3 = 7;
    ok(vi1 == vi2, "operator == : x == same class, same value");
    nok(vi1 == vi3, "operator == : x == same class, not same value");
    nok(vi1 != vi2, "operator != : x != same class, same value");

    ok(vi1 === vi1, "operator === : x === x");
    nok(vi1 !== vi1, "operator !== : x !== x");
    nok(vi1 === vi2, "operator === : x === same class");
    ok(vi1 !== vi2, "operator !== : x !== same class");
    nok(vi1 === vn1, "operator === : x === other class");
    ok(vi1 !== vn1, "operator !== : x !== other class");

    ++vi1;
    is(vi1, 43, "var preincrement");
    i = ++vi1;
    is(i, 44, "var preincrement with assignment");
    --vi1;
    is(vi1, 43, "var peedecrement");
    i = --vi1;
    is(i, 42, "var predecrement with assignment");

    is(str + i, "2.542", "string + int");
    is(i + str, "422.5", "int + string");
    is(str + vi1, "2.542", "string + var");
    is(vi1 + str, "422.5", "var + string");

    string s = "abc";
    is(s * 3, "abcabcabc", "repeat string");

    vi1 = 7;
    vi2 = vi1;
    vi2 =: 1;
    ok(vi1 === vi2, "var =: int does not create a new object");
    vi2 = 1;
    ok(vi1 !== vi2, "var = int create a new object");

    i = 1;

    is(~i, -2, "bitwise not");

    is(i | 2, 3, "bitwise or");

    is(i ^ 3, 2, "bitwise xor");

    is(i << 2, 4, "shift left");
    i = 8;
    is(i >> 2, 2, "shift right");

    is(s[1], "b", "string indexing");

    int j = 12;
    for (i = 0; i < 10; ++i)
        --j;
    is(j, 2, "for loop, inc and dec operators");

    j = 0;
    for (i in [ 1, 3, 5, 7 ])
        j += i;
    is(j, 16, "for in");

    test_string_misc();
    test_string_iter();
    test_array();
    test_hash();
    test_func();

    is(Foo.bar(), "Foo.bar", "call function in namespace");
    is(bar(), "bar", "call function out of namespace with same name");

    test_switchcase();
    test_try();

    var obj = new SomeClass;
    ok(obj instanceof SomeClass, "new and instanceof by identifier");

    var cl = new Cl;
    cl.foo = "Cl_foo";
    s = "foo";
    s = cl.*s;
    is(s, "Cl_foo", "indirect get attribute");

    var fbar = new Bar();
    is(fbar.get(), "class Bar", "constructor");

    miscellaneous(false);

    done_testing();
}

// End
