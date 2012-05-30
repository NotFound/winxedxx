#ifndef INCLUDE_WINXEDXX_HANDLE_H
#define INCLUDE_WINXEDXX_HANDLE_H

// winxedxx_handle.h
// (C) 2011 Julián Albo "NotFound"

namespace WinxedXX
{

class WxxFileHandle : public WxxDefault
{
public:
    WxxFileHandle(int predef = 0);
    ~WxxFileHandle();
    WxxObject *open(const std::string &name);
    WxxObject *open(const std::string & name, const std::string &mode);
    WxxObject *open(WxxObjectPtr name);
    WxxObject *open(WxxObjectPtr name, WxxObjectPtr mode);
    WxxObjectPtr close();
    void print(WxxObjectPtr obj);
    WxxObjectPtr call_method(const std::string &methname, WxxObjectArray &args);
private:
    FILE *f;
    WxxObjectPtr read(int n);
    WxxObjectPtr readline();
};

} // namespace WinxedXX

#endif

// End of winxedxx_handle.h
