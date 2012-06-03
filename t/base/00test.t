#! winxed

// winxedxx base tests
// Verify the builtin module Test.More

using extern Test.More plan, ok, nok, is, isnt;

function main [main] (var args)
{
    plan(10);

    ok(1, "ok is ok");
    nok(0, "nok is ok");

    is(1, 1, "is is ok");
    isnt(1, 0, "isnt is ok");

    float n = 1.1;
    is(n, 1.1, "is with float");
    isnt(n, 1, "isnt with float - int");

    string s = "hello";
    string hi = "he";
    is(s, "hello", "is with string - string literal");
    isnt(s, "other", "isnt with string - string literal");
    isnt(s, hi, "isnt with string - string");
    hi = hi + "llo";
    is(s, hi, "is with string - string");
}

// End
