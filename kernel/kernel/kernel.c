#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

void kernel_main(void) {
  init_serial_port();
	terminal_initialize();
	printf("Loading..\n");

  gdt_install();
  printf("GDT loaded.\n");

  idt_install();
  printf("IDT loaded.\n");
}
