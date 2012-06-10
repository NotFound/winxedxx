#! winxed

// winxedxx base tests
// PMC-alike types

using extern Test.More plan, ok, is;

function main [main] (var args)
{
    plan(3);

    var sh = new ["StringHandle"];
    sh.open("test", "w");
    sh.print("hello");
    is(sh.close(), 0, "StringHandle open, print and close");

    sh.open("test");
    string s = sh.read(2);
    is(s, "he", "StringHandle open and read");
    sh.read(3);
    ok(sh.eof(), "StringHandle eof");
}

// End
