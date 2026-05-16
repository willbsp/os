#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#include <stdint.h>

void timer_init(uint32_t frequency);
void timer_handler(void);
void timer_get_ticks(void);

#endif // !_KERNEL_TIMER_H
