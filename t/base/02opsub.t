#! winxed

// winxedxx base tests
// operator -

using extern Test.More plan, is;

function main [main] (var args)
{
    plan(3);

    int i = 42;
    var vi1 = i;

    is(i - 2, 40, "int - int");
    is(i - vi1, 0, "int - var");
    is(vi1 - i, 0, "var - int");
}

// End
