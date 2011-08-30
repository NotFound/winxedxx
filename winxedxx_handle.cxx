// winxedxx_handle.cxx
// (C) 2011 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_integer.h"
#include "winxedxx_handle.h"

#include <stdlib.h>

namespace WinxedXX
{

//*************************************************************

WxxFileHandle::WxxFileHandle(int predef) : WxxDefault("FileHandle")
{
    switch (predef) {
    case 1:
        f = stdin;
        break;
    case 2:
        f = stdout;
        break;
    case 3:
        f = stderr;
        break;
    default:
        f = 0;
    }
}

WxxFileHandle::~WxxFileHandle()
{
    //std::cerr << "~WxxFileHandle\n";
    if (f && f != stdin && f != stdout && f != stderr)
        fclose(f);
}

WxxObject *WxxFileHandle::open(WxxObjectPtr name)
{
    std::string strname = name.get_string();
    f = fopen(strname.c_str(), "r");
    return this;
}

WxxObject *WxxFileHandle::open(WxxObjectPtr name, WxxObjectPtr mode)
{
    if (f)
        throw wxx_error("FileHandle is already open");
    std::string strname = name.get_string();
    std::string strmode = mode.get_string();
    for (size_t i = 0; i < strmode.length(); ++i) {
        switch (strmode[i]) {
          case 'r':
          case 'w':
          case 'a':
          case 'b':
            break;
          default:
            throw wxx_error("Invalid mode in open");
        }
    }
    f = fopen(strname.c_str(), strmode.c_str());
    return this;
}

WxxObjectPtr WxxFileHandle::close()
{
    int r;
    if (f) {
        r = fclose(f);
        f = 0;
    }
    else
        r = -1;
    return r;
}

void WxxFileHandle::print(WxxObjectPtr obj)
{
    if (! f)
        throw wxx_error("FileHandle is closed");
    fputs(obj.get_string().c_str(), f);
}

WxxObjectPtr WxxFileHandle::read(int n)
{
    if (! f)
        throw wxx_error("FileHandle is closed");
    char *buf = (char *)malloc(n);
    *buf = '\0';
    size_t r = fread(buf, 1, n, f);
    //std::cerr << "\nread " << r << "\n";
    std::string result = r > 0 ? std::string(buf, r) : std::string();
    free(buf);
    return WxxObjectPtr(result);
}

WxxObjectPtr WxxFileHandle::readline()
{
    if (! f)
        throw wxx_error("FileHandle is closed");
    char buffer[1024];
    const char *r = fgets(buffer, 1024, f);
    if (! r)
        r = "";
    return WxxObjectPtr(std::string(r));
}

WxxObjectPtr WxxFileHandle::call_method(const std::string &methname, WxxObjectArray &args)
{
    if (methname == "readline") {
        if (args.elements() > 0)
            throw wxx_error("too many positional arguments in readline");
        return readline();
    }
    if (methname == "read") {
        if (args.elements() != 1)
            throw wxx_error("wrong number of positional arguments in read");
        return read(args.get_pmc_keyed(0));
    }
    if (methname == "open") {
        switch (args.elements()) {
          case 1:
            return open(args.get_pmc_keyed(0));
          case 2:
            return open(args.get_pmc_keyed(0), args.get_pmc_keyed(1));
          default:
            throw wxx_error("too many positional arguments in close");
        }
    }
    if (methname == "close") {
        if (args.elements() > 0)
            throw wxx_error("too many positional arguments in close");
        return close();
    }
    if (methname == "eof") {
        if (args.elements() > 0)
            throw wxx_error("too many positional arguments in close");
        return feof(f);
    }
    else
        return WxxDefault::call_method(methname, args);
}

//*************************************************************

} // namespace WinxedXX

// End