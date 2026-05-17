#include <kernel/gdt.h>
#include <kernel/heap.h>
#include <kernel/idt.h>
#include <kernel/multiboot.h>
#include <kernel/paging.h>
#include <kernel/pic.h>
#include <kernel/pmm.h>
#include <kernel/scheduler.h>
#include <kernel/serial.h>
#include <kernel/timer.h>
#include <kernel/tty.h>
#include <stdint.h>
#include <stdio.h>

#include "kernel/thread.h"

#define TIMER_INTERRUPT_HZ 100

void thread_a() {
  uint32_t last_tick = 0;
  uint32_t tick_counter = 0;
  for (;;) {
    tick_counter += timer_get_ticks() - last_tick;
    if (tick_counter > 100) {
      printf("Thread A: A\n");
      tick_counter = 0;
    }
    last_tick = timer_get_ticks();
    schedule(); // yield
  }
}

void thread_b() {
  uint32_t last_tick = 0;
  uint32_t tick_counter = 0;
  for (;;) {
    tick_counter += timer_get_ticks() - last_tick;
    if (tick_counter > 250) {
      printf("Thread B: B\n");
      tick_counter = 0;
    }
    last_tick = timer_get_ticks();
    schedule(); // yield
  }
}

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

  timer_init(100);
  printf("Initialized timer.\n");

  gdt_install();
  printf("GDT loaded.\n");

  idt_install();
  printf("IDT loaded.\n");

  pic_initialize();
  printf("PIC initialized.\n");

  paging_init();
  printf("Paging enabled.\n");

  heap_init();
  printf("Heap initialized.\n");

  threading_init();
  struct tcb *a = thread_create(thread_a);
  schedule_thread(a);

  struct tcb *b = thread_create(thread_b);
  schedule_thread(b);

  // enable interrupts
  asm volatile("sti");
  printf("Interrupts enabled.\n");

  printf("\n---Welcome!---\n");

  for (;;) {
    schedule();
  }

  for (;;) {
    asm volatile("hlt");
  }
}
