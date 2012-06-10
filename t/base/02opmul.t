#! winxed

// winxedxx base tests
// operator *

using extern Test.More plan, ok, nok, is;

function main [main] (var args)
{
    plan(6);

    is(1 * 1, 1, "mul int constants");
    int i1 = 1;
    int i2 = 2;
    is(i1 * i2, 2, "mul int");
    float f1 = 1.3;
    float f2 = 2.4;
    is(f1 * f2, 3.12, "mul float");
    is(i1 * f2, 2.4, "mul int float");
    var o1 = 1;
    is(o1 * i2, 2, "mul var int");
    var o2 = 2;
    is(i1 * o2, 2, "mul int var");
    is(o1 * o2, 2, "mul var var");
}

// End
