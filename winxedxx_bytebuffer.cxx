// winxedxx_bytebuffer.cxx

// (C) 2012 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_ptr.h"
#include "winxedxx_bytebuffer.h"

#include <stdlib.h>

namespace WinxedXX
{

WxxByteBuffer::WxxByteBuffer() : WxxDefault("ByteBuffer"),
        p(0),
        allocated_size(0),
        size(0)
{
}

int WxxByteBuffer::elements() const
{
    return size;
}

WxxByteBuffer & WxxByteBuffer::set(int i)
{
    set_integer_native(i);
    return *this;
}

void WxxByteBuffer::set_integer_native(int i)
{
    if (allocated_size) {
        void *ptr = get_pointer();
        if (i <= 0) {
            free(ptr);
            set_pointer(0);
            allocated_size = 0;
            size = 0;
        }
        else {
            if ((size_t)i > allocated_size) {
                void *newptr = realloc(ptr, i);
                if (! newptr)
                    return;
                set_pointer(newptr);
                allocated_size = i;
                size = i;
            }
            size = i;
        }
    }
    else {
        if (i > 0) {
            void *newptr = malloc(i);
            if (newptr) {
                set_pointer(newptr);
                allocated_size = i;
                size = i;
            }
        }
    }
}

int WxxByteBuffer::get_integer_keyed(int i)
{
    if (i < 0 || (size_t)i >= size)
        return 0;
    else {
        return ((unsigned char *)get_pointer())[i];
    }
}

WxxObjectPtr WxxByteBuffer::get_pmc_keyed(int i)
{
    return get_integer_keyed(i);
}

void WxxByteBuffer::set_integer_keyed(int i, int value)
{
    if (i >= 0 && (size_t)i < size)
        ((char *)get_pointer())[i] = value;
}

void WxxByteBuffer::set_pmc_keyed(int i, const WxxObjectPtr &value)
{
    set_integer_keyed(i, value.get_integer());
}

void * WxxByteBuffer::get_pointer()
{
    return p;
}

void WxxByteBuffer::set_pointer(void *ptr)
{
    p = ptr;
}

} // namespace WinxedXX

// End of winxedxx_bytebuffer.cxx
