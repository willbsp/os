#include <kernel/idt.h>
#include <kernel/pic.h>
#include <stdio.h>
#include <string.h>

#include "io.h"

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
extern void isr32(void);
extern void isr33(void);
extern void isr34(void);
extern void isr35(void);
extern void isr36(void);
extern void isr37(void);
extern void isr38(void);
extern void isr39(void);
extern void isr40(void);
extern void isr41(void);
extern void isr42(void);
extern void isr43(void);
extern void isr44(void);
extern void isr45(void);
extern void isr46(void);
extern void isr47(void);

struct idt_entry idt[256];
struct idt_table itable;

void idt_set_gate(uint8_t entry_no,
                  uint32_t offset,
                  uint16_t selector,
                  uint8_t type_attributes) {
  idt[entry_no].offset_low = offset & (0xFFFF);
  idt[entry_no].offset_high = (offset >> 16) & (0xFFFF);
  idt[entry_no].selector = selector;
  idt[entry_no].zero = 0;
  idt[entry_no].type_attributes = type_attributes;
}

void idt_install() {
  itable.limit = (sizeof(struct idt_entry) * 256) - 1;
  itable.base = (uint32_t)&idt;

  // "zero out" idt memory
  memset(&idt, 0, sizeof(struct idt_entry) * 256);

  idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
  idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
  idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
  idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
  idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
  idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
  idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
  idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
  idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
  idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
  idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
  idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
  idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
  idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
  idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
  idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
  idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
  idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
  idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
  idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
  idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
  idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
  idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
  idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
  idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
  idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
  idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
  idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
  idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
  idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
  idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
  idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
  idt_set_gate(32, (uint32_t)isr32, 0x08, 0x8E);
  idt_set_gate(33, (uint32_t)isr33, 0x08, 0x8E);
  idt_set_gate(34, (uint32_t)isr34, 0x08, 0x8E);
  idt_set_gate(35, (uint32_t)isr35, 0x08, 0x8E);
  idt_set_gate(36, (uint32_t)isr36, 0x08, 0x8E);
  idt_set_gate(37, (uint32_t)isr37, 0x08, 0x8E);
  idt_set_gate(38, (uint32_t)isr38, 0x08, 0x8E);
  idt_set_gate(39, (uint32_t)isr39, 0x08, 0x8E);
  idt_set_gate(40, (uint32_t)isr40, 0x08, 0x8E);
  idt_set_gate(41, (uint32_t)isr41, 0x08, 0x8E);
  idt_set_gate(42, (uint32_t)isr42, 0x08, 0x8E);
  idt_set_gate(43, (uint32_t)isr43, 0x08, 0x8E);
  idt_set_gate(44, (uint32_t)isr44, 0x08, 0x8E);
  idt_set_gate(45, (uint32_t)isr45, 0x08, 0x8E);
  idt_set_gate(46, (uint32_t)isr46, 0x08, 0x8E);
  idt_set_gate(47, (uint32_t)isr47, 0x08, 0x8E);

  asm volatile("lidt %0" : : "m"(itable));
}

void isr_handler(struct registers *regs) {
  if (regs->int_no >= 32) {
    // get irq number
    uint8_t irq = regs->int_no - 32;
    pic_send_eoi(irq);
    if (irq == 0) {
      // timer tick
      // printf("tick");
    } else if (irq == 1) {
      // keyboard
      uint8_t scancode = inb(0x60);
      printf("key: %u\n", scancode / 10);
    }

    return; // do not halt on IRQ
  }

  printf("Exception: %u\n", regs->int_no);
  printf("EIP: %u\n", regs->eip);
  for (;;) {
    asm volatile("hlt");
  }
}
