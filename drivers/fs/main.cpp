#include "kinc.h"


extern "C" __attribute__((section(".driver"))) void dmain(kernel_handle_t*handle)
{
memset(handle->kdata.screen_handle.fb,255,handle->kdata.screen_handle.w*handle->kdata.screen_handle.h*4);

}
