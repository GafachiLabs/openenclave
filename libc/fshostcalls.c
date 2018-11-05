#include <openenclave/enclave.h>
#include "../fs/hostcalls.h"

static void* _malloc(fs_host_calls_t* host_calls, size_t size)
{
    return oe_host_malloc(size);
}

static void* _calloc(fs_host_calls_t* host_calls, size_t nmemb, size_t size)
{
    return oe_host_calloc(nmemb, size);
}

static void _free(fs_host_calls_t* host_calls, void* ptr)
{
    return oe_host_free(ptr);
}

fs_host_calls_t fs_host_calls =
{
    _malloc,
    _calloc,
    _free
};