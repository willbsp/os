#include <stdint.h>

#include "io.h"

#define PIC1 0x20 /* IO base address for master PIC */
#define PIC2 0xA0 /* IO base address for slave PIC */
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define ICW1_ICW4 0x01 /* Indicates that ICW4 will be present */
#define ICW1_INIT 0x10 /* Initialization - required! */

#define ICW4_8086 0x01 /* 8086/88 (MCS-80/85) mode */
#define CASCADE_IRQ 2

#define PIC_EOI 0x20

// small delay
static inline void io_wait(void) { outb(0x80, 0); }

void pic_initialize() {
  // ICW1
  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
  io_wait();
  // ICW2
  // each PIC handles 8 IRQs, start at 32 as reserved CPU
  // exceptions (idt.c) are 0-31
  outb(PIC1_DATA, 0x20); // start at 32
  io_wait();
  outb(PIC2_DATA, 0x28); // start at 40
  io_wait();
  // ICW3
  outb(PIC1_DATA, 1 << CASCADE_IRQ); // start at 32
  io_wait();
  outb(PIC2_DATA, CASCADE_IRQ); // start at 32
  io_wait();
  // ICW4 - should always be set to 8086 on x86
  outb(PIC1_DATA, ICW4_8086);
  io_wait();
  outb(PIC2_DATA, ICW4_8086);
  io_wait();

  // unmask both
  outb(PIC1_DATA, 0x00);
  outb(PIC2_DATA, 0x00);
}

void pic_send_eoi(uint8_t irq) {
  if (irq >= 8) {
    outb(PIC2_COMMAND, PIC_EOI);
  }
  // always call eoi on master
  outb(PIC1_COMMAND, PIC_EOI);
}
