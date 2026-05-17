#ifndef _KERNEL_THREAD_H
#define _KERNEL_THREAD_H

#include <stdint.h>

// thread control block
struct tcb {
  uint32_t esp;     // saved stack pointer used for context switching
  uint32_t *stack;  // threads stack (to free memory)
  struct tcb *next; // pointer to next thread, essentially a linked list to be
                    // used for round robin scheduling
};

void threading_init(void);
struct tcb *thread_create(void (*function)(void));

#endif // !_KERNEL_THREAD_H
