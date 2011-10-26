#! winxed
// runtests.t
// Compile and execute the tests

function strip_ext(string src)
{
    int pos = indexof(src, '.');
    for (int npos = pos; npos != -1; npos = indexof(src, pos, '.'))
        pos = npos;
    if (pos >= 0)
        return substr(src, 0, pos);
    else
        return src;
}

function runtest(string srcname)
{
    string objname = strip_ext(srcname);
    if (objname == srcname)
        objname += '.exe';

    string cmd[] = [
      "parrot", "winxedxx.pbc",
      "--target=exe",
      "-o", objname,
      srcname
    ];
    int r = spawnw(cmd);
    if (r != 0)
        say("FAILED " + srcname);
    else
        spawnw( [ objname ] );
}

function main [main](args)
{
    args.shift();

    for (string arg in args)
        runtest(arg);
}

// End
