#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stdint.h>

struct __attribute__((__packed__)) gdt_entry {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
};

struct __attribute__((__packed__)) gdt_table {
  uint16_t limit;
  uint32_t base;
};

void gdt_set_gate(uint8_t entry_no, uint32_t base, uint32_t limit,
                  uint8_t access, uint8_t granularity);

void gdt_install();

#endif // ! _KERNEL_GDT_H
