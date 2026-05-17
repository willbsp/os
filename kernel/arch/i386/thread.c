#include <kernel/heap.h>
#include <kernel/scheduler.h>
#include <kernel/thread.h>
#include <stddef.h>
#include <stdint.h>

#define THREAD_STACK_SIZE 2048 // 16 KiB

void threading_init() {
  struct tcb *kernel_thread = kmalloc(sizeof(struct tcb));
  kernel_thread->stack = NULL;
  kernel_thread->next = NULL;
  kernel_thread->esp = 0;
  schedule_thread(kernel_thread);
}

struct tcb *thread_create(void (*function)(void)) {
  struct tcb *thread = kmalloc(sizeof(struct tcb));
  thread->stack = kmalloc(THREAD_STACK_SIZE);
  thread->next = NULL;

  // start at end of the stack, stack grows downward
  uint32_t *sp = (uint32_t *)((uint32_t)thread->stack + THREAD_STACK_SIZE);

  // entry point to the thread, what 'ret' will pop
  *(--sp) = (uint32_t)function;

  // registers ebx, esi, edi, ebp
  *(--sp) = 0;
  *(--sp) = 0;
  *(--sp) = 0;
  *(--sp) = 0;

  thread->esp = (uint32_t)sp;

  return thread;
}
