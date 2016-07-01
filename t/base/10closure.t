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

function getfuni()
{
    int n = 43;
    var f = function () { return n; };
    return f;
}

function main[main](var args)
{
    var fun = getfun();
    int i = fun();
    is(i, 42, "closure with a lexical var");
    fun = getfuni();
    i = fun();
    is(i, 43, "closure with a lexical int");

    done_testing();
}

// End
