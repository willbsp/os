#include <kernel/isr.h>
#include <kernel/pic.h>
#include <stdint.h>
#include <stdio.h>

#include "kernel/keyboard.h"

#include "io.h"

void isr_handler(struct registers *regs) {
  if (regs->int_no >= 32) {
    // get irq number
    uint8_t irq = regs->int_no - 32;
    pic_send_eoi(irq);
    if (irq == 0) {
      // timer tick
      // printf("tick");
    } else if (irq == 1) {
      uint8_t scancode = inb(0x60);
      keyboard_handler(scancode);
    }

    return; // do not halt on IRQ
  }

  printf("Exception: %u\n", regs->int_no);
  printf("EIP: %u\n", regs->eip);
  for (;;) {
    asm volatile("hlt");
  }
}
