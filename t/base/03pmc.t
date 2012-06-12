#! winxed

// winxedxx base tests
// PMC-alike types

using extern Test.More plan, ok, is;

function main [main] (var args)
{
    plan(5);

    var sh = new ["StringHandle"];
    sh.open("test", "w");
    sh.print("hello");
    is(sh.close(), 0, "StringHandle open, print and close");

    sh.open("test");
    string s = sh.read(2);
    is(s, "he", "StringHandle open and read");
    sh.read(3);
    ok(sh.eof(), "StringHandle eof");

    var bb = new ["ByteBuffer"];
    bb =: "hello";
    is(elements(bb), 5, "ByteBuffer set string");
    bb[5] = ord("!");
    int c = bb[5];
    is(chr(c), "!", "ByteBuffer set and get keyed int");
}

// End
