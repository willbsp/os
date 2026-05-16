#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

#include <stdint.h>

struct __attribute__((__packed__)) idt_entry {
  uint16_t offset_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t type_attributes;
  uint16_t offset_high;
};

struct __attribute__((__packed__)) idt_table {
  uint16_t limit;
  uint32_t base;
};

void idt_install(void);

#endif // !_KERNEL_IDT_H
