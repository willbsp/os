#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "io.h"

#define COM1_PORT 0x3F8
#define SERIAL_DATA          0
#define SERIAL_INTERRUPT_EN  1
#define SERIAL_FIFO_CTRL     2
#define SERIAL_LINE_CTRL     3
#define SERIAL_MODEM_CTRL    4
#define SERIAL_LINE_STATUS   5

void init_serial_port() {
  // disable interrupts
  outb(COM1_PORT + SERIAL_INTERRUPT_EN, 0x00);

  // dlab dance
  outb(COM1_PORT + SERIAL_LINE_CTRL, 0x80);  // access baud divisor
  outb(COM1_PORT + 0, 0x03); // divisor low byte:  115200 / 3 = 38400 baud
  outb(COM1_PORT + 1, 0x00); // divisor high byte
  outb(COM1_PORT + SERIAL_LINE_CTRL, 0x03); // 8 bits, no parity, 1 stop bit
  outb(COM1_PORT + SERIAL_FIFO_CTRL, 0xC7); // fifo
  outb(COM1_PORT + SERIAL_MODEM_CTRL, 0x0C); // DTR, RTS, Out 2
}

void serial_putchar(char c) {
  while (!(inb(COM1_PORT + SERIAL_LINE_STATUS) & 0x20)) {}
  outb(COM1_PORT + SERIAL_DATA, c);
}

void serial_write(const char * data, size_t len) {
  for (size_t i = 0; i < len; i++) {
    serial_putchar(data[i]);
  }
}

void serial_writestring(const char * data) {
  serial_write(data, strlen(data));
}
