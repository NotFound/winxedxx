#ifndef INCLUDE_WINXEDXX_PTR_H
#define INCLUDE_WINXEDXX_PTR_H

// winxedxx_ptr.h

// (C) 2012 Julián Albo


namespace WinxedXX
{

class WxxPtr : public WxxDefault
{
public:
    WxxPtr();
    WxxPtr(void *ptr);

    int get_integer();
    void * get_pointer();
    void set_pointer(void *ptr);
    WxxObjectPtr call_method
        (const std::string &methname, WxxObjectArray &args);
private:
    void *p;
};

} // namespace WinxedXX

#endif

// End of winxedxx_ptr.h
