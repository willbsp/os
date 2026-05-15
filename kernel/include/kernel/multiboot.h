#ifndef _KERNEL_MULTIBOOT_H
#define _KERNEL_MULTIBOOT_H

#include <stdint.h>

#define MULTIBOOT_MAGIC 0x2BADB002

#define MULTIBOOT_INFO_MEMORY  0x00000001
#define MULTIBOOT_INFO_MEM_MAP 0x00000040

struct __attribute__((packed)) multiboot_info {
  uint32_t flags;
  uint32_t mem_lower;
  uint32_t mem_upper;
  uint32_t boot_device;
  uint32_t cmdline;
  uint32_t mods_count;
  uint32_t mods_addr;
  uint32_t syms[4];
  uint32_t mmap_length;
  uint32_t mmap_addr;
};

struct __attribute__((packed)) multiboot_mmap_entry {
  uint32_t size;
  uint64_t addr;
  uint64_t len;
  uint32_t type;
};

#endif // !_KERNEL_MULTIBOOT_H
