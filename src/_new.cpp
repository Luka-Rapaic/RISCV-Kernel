#include "../h/syscall_c.h"

using size_t = decltype(sizeof(0));

void *operator new(size_t n)
{
    //return __mem_alloc(n);
    return mem_alloc(n);
    //return MemoryAllocator::allocate(n/MEM_BLOCK_SIZE+1);
}

void *operator new[](size_t n)
{
    //return __mem_alloc(n);
    return mem_alloc(n);
    //return MemoryAllocator::allocate(n/MEM_BLOCK_SIZE+1);
}

void operator delete(void *p) noexcept
{
    //__mem_free(p);
    mem_free(p);
    //MemoryAllocator::deallocate(p);
}

void operator delete[](void *p) noexcept
{
    //__mem_free(p);
    mem_free(p);
    //MemoryAllocator::deallocate(p);
}