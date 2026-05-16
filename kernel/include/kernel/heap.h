#ifndef _KERNEL_HEAP_H
#define _KERNEL_HEAP_H

#include <stdint.h>

void heap_init(void);
void *kmalloc(uint32_t size);
void kfree(void *ptr);

#endif // _KERNEL_HEAP_H
