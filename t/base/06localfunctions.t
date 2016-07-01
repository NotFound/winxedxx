#! winxed

// winxedxx base tests
// local functions

using extern Test.More plan, is;

function main [main] (var args)
{
    plan(1);
    var f = function () { return 42; };
    is(f(), 42, "define and call a local function");
}

// End
