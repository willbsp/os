#ifndef ARCH_I386_SERIAL_H
#define ARCH_I386_SERIAL_H

void init_serial_port(void);
void serial_putchar(char c);
void serial_write(const char * data, size_t len);
void serial_writestring(const char * data);

#endif // !ARCH_I386_SERIAL_H
