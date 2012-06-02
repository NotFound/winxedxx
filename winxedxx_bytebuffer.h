#ifndef INCLUDE_WINXEDXX_BYTEBUFFER_H
#define INCLUDE_WINXEDXX_BYTEBUFFER_H

// winxedxx_bytebuffer.h

// (C) 2012 Julián Albo


namespace WinxedXX
{

class WxxByteBuffer : public WxxDefault
{
public:
    WxxByteBuffer();

    int elements() const;
    WxxByteBuffer & set(int i);
    void set_integer_native(int i);
    void set_integer_keyed(int i, int value);
    void set_pmc_keyed(int i, const WxxObjectPtr &value);

    void * get_pointer();
    void set_pointer(void *ptr);
private:
    void *p;
    size_t allocated_size;
    size_t size;
};

} // namespace WinxedXX

#endif

// End of winxedxx_bytebuffer.h
