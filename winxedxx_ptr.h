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

    void * get_pointer();
    void set_pointer(void *ptr);
private:
    void *p;
};

} // namespace WinxedXX

#endif

// End of winxedxx_ptr.h
