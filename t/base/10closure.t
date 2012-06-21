#! winxed

// winxedxx base tests
// closures

using extern Test.More is, done_testing;

function getfun()
{
    var _TEST_n = 42;
    var f = function () { return _TEST_n; };
    return f;
}

function main[main](var args)
{
    var fun = getfun();
    int i = fun();
    is(i, 42, "calling a closure");

    done_testing();
}

// End
