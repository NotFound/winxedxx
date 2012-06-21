#! winxed

// winxedxx base tests
// multi assign and multi return

using extern Test.More plan, is, ok;

function main()
{
    plan(2);

    int i, j;
    :(i, j) = ret2();
    is(i, 42, "first value of 2");
    is(j, 24, "second value of 2");

}

function ret1()
{
    return 7;
}

function ret2()
{
    return 42, 24;
}

// End
