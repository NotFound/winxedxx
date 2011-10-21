#! winxed
// runtests.t
// Compile and execute the tests

function runtest(string srcname)
{
    const string EXT = ".winxed";
    const int LEXT = length(EXT);

    int l = length(srcname);
    if (l <= LEXT || substr(srcname, -LEXT) != EXT)
        throw "Invalid test file: " + srcname;
    string objname = substr(srcname, 0, l - 7);

    string cmd[] = [ "parrot", "winxedxx.pbc", "--target", "exe", "-o", objname, srcname ];
    int r = spawnw(cmd);
    if (r != 0)
        say("FAILED " + srcname);
    else
        spawnw( [ objname ] );
}

function main [main](args)
{
    args.shift();

    for (string arg in args) {
	runtest(arg);
    }
}

// End
