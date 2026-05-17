#ifndef _KERNEL_SCHEDULER_H
#define _KERNEL_SCHEDULER_H

#include <kernel/thread.h>

void schedule(void);
void schedule_thread(struct tcb *thread);

#endif // !_KERNEL_SCHEDULER_H
