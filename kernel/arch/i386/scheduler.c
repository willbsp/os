#include <kernel/thread.h>
#include <stddef.h>

extern void switch_context(struct tcb *current, struct tcb *next);

// should form a circular linked list for round robin
static struct tcb *current_thread = NULL;

void schedule() {
  // need to update current_thread first before context switch
  // as once it has run, will be on a different thread
  // printf("schedule callledA");
  if (current_thread == NULL || current_thread->next == current_thread) {
    return;
  }
  // printf("switching\n");
  struct tcb *previous_thread = current_thread;
  current_thread = current_thread->next;
  switch_context(previous_thread, current_thread);
}

void schedule_thread(struct tcb *thread) {
  if (current_thread == NULL) {
    current_thread = thread;
    current_thread->next = current_thread;
  } else {
    // insert after current thread
    struct tcb *prev_next = current_thread->next;
    thread->next = prev_next;
    current_thread->next = thread;
  }
}
