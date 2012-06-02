// winxedxx_ptr.cxx

// (C) 2012 Julián Albo

#include "winxedxx_types.h"
#include "winxedxx_object.h"
#include "winxedxx_default.h"
#include "winxedxx_ptr.h"

namespace WinxedXX
{

WxxPtr::WxxPtr() : WxxDefault("Ptr"), p(0)
{
}

WxxPtr::WxxPtr(void *ptr) : WxxDefault("Ptr"), p(ptr)
{
}

void * WxxPtr::get_pointer()
{
    return p;
}

void WxxPtr::set_pointer(void *ptr)
{
    p = ptr;
}

} // namespace WinxedXX

// End of winxedxx_ptr.cxx
