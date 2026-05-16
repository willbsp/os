#include <stdint.h>

#include "io.h"

#define PIT_CHANNEL_0                 0x40
#define PIT_COMMAND                   0x43
#define PIT_OSCILLATOR_HZ             1193182
#define PIT_MODE_2                    0x06
#define PIT_ACCESS_MODE_LOBYTE_HIBYTE 0x30

static uint32_t ticks = 0;

void timer_init(uint32_t frequency) {
  uint16_t divisor = PIT_OSCILLATOR_HZ / frequency;
  outb(PIT_COMMAND, PIT_MODE_2 | PIT_ACCESS_MODE_LOBYTE_HIBYTE);
  outb(PIT_CHANNEL_0, divisor & 0xFF);        // low byte
  outb(PIT_CHANNEL_0, (divisor >> 8) & 0xFF); // high byte
}

void timer_handler() {
  ticks++;
}

uint32_t timer_get_ticks() {
  return ticks;
}
