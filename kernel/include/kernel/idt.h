#ifndef ARCH_I386_IDT_H
#define ARCH_I386_IDT_H

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

struct registers {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags;
};

void idt_set_gate(uint8_t entry_no, uint32_t offset, uint16_t selector, uint8_t type_attributes);
void idt_install(void);
void isr_handler(struct registers *regs);

#endif // !ARCH_I386_IDT_H
