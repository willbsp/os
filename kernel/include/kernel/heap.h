#ifndef _KERNEL_HEAP_H
#define _KERNEL_HEAP_H

#include <stdint.h>

void heap_init(void);
void *kmalloc(uint32_t size);
void kfree(void *ptr);
void heap_meminfo(uint32_t *total, uint32_t *used, uint32_t *free);

#endif // _KERNEL_HEAP_H
