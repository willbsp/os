#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#include <stdint.h>

#define INPUT_BUFFER_SIZE 256

void keyboard_handler(uint8_t scancode);

#endif // !_KERNEL_KEYBOARD_H
