#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/multiboot.h>
#include <kernel/pic.h>
#include <kernel/pmm.h>
#include <kernel/serial.h>
#include <kernel/tty.h>
#include <stdint.h>
#include <stdio.h>

void kernel_main(uint32_t magic, struct multiboot_info *info) {
  init_serial_port();

  if (magic != MULTIBOOT_MAGIC) {
    printf("Magic number does not match!\n");
  } else {
    printf("The magic number matches!\n");
  }

  if (!(info->flags & MULTIBOOT_INFO_MEM_MAP)) {
    printf("Invalid memory map!\n");
  } else {
    printf("Detected a valid multiboot memory map!\n");
  }

  pmm_init(info);

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
