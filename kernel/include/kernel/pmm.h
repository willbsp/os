#ifndef _KERNEL_PMM_H
#define _KERNEL_PMM_H

#include <kernel/multiboot.h>
#include <stdint.h>

void pmm_init(struct multiboot_info *info);
uint32_t pmm_alloc();
void pmm_free(uint32_t addr);
void pmm_meminfo(uint32_t *used, uint32_t *free);

#endif // !_KERNEL_PMM_H
