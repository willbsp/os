#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/serial.h>
#include <kernel/tty.h>
#include <stdio.h>

void kernel_main(void) {
  init_serial_port();
  terminal_initialize();
  printf("Loading..\n");

  gdt_install();
  printf("GDT loaded.\n");

  idt_install();
  printf("IDT loaded.\n");

  pic_initialize();
  printf("PIC initialized.\n");

  // enable interrupts
  asm volatile("sti");
  printf("Enabled interrupts\n");

  for (;;) {
    asm volatile("hlt");
  }
}
