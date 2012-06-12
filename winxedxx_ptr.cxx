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

WxxObjectPtr WxxPtr::call_method
        (const std::string &methname, WxxObjectArray &args)
{
    if (methname == "as_string") {
        // Test implementation, don't even check args.
        return WxxObjectPtr(std::string((char *)get_pointer()));
    }
    else
        return WxxDefault::call_method(methname, args);
}

} // namespace WinxedXX

// End of winxedxx_ptr.cxx
