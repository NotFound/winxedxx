#! winxed

// winxedxx base tests
// prefix ++ and -- operator

using extern Test.More plan, is;

function main()
{
    plan (10);

    int a = 69;
    int c;

    c = ++a;
    is (c, 70, "pre ++ result");
    is (a, 70, "pre ++ side effect");

    c = --a;
    is (c, 69, "pre -- result");
    is (a, 69, "pre -- side effect");

    c = --(++a);
    is (c, 69, 'pre -- ++ result');
    is (a, 69, 'pre -- ++ side effect');

    var vi1 = 42;
    int i;
    ++vi1;
    is(vi1, 43, "var preincrement");
    i = ++vi1;
    is(i, 44, "var preincrement with assignment");
    --vi1;
    is(vi1, 43, "var peedecrement");
    i = --vi1;
    is(i, 42, "var predecrement with assignment");
}

// End
