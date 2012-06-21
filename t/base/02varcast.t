#! winxed

// winxedxx base tests
// var cast

using extern Test.More plan;

namespace Test { namespace More { } }

function main [main] (var args)
{
    plan(1);
    var (Test.More.ok)(1, "cast to var avoid parse as method cal");
}

// End
