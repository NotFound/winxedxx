#! winxed

// winxedxx base tests
// operator +

using extern Test.More plan, ok, nok, is, isnt;

function main [main] (var args)
{
    plan(12);

    is(1 + 1, 2, "add int constants");
    int i1 = 1;
    int i2 = 2;
    is(i1 + 6, 7, "add int const");
    is(i1 + i2, 3, "add int");
    string s1 = "He";
    string s2 = "llo";
    is(s1 + s2, "Hello", "add string");
    is(s1 + i2, "He2", "add string int");
    float f1 = 1.3;
    float f2 = 2.4;
    is(f1 + 0.2, 1.5, "add float const");
    is(f1 + f2, 3.7, "add float");
    is(i1 + f2, 3.4, "add int float");
    is(f1 + i2, 3.3, "add float int");
    var o1 = 1;
    is(o1 + i2, 3, "add var int");
    var o2 = 2;
    is(i1 + o2, 3, "add int var");
    is(o1 + o2, 3, "add var var");
}

// End
