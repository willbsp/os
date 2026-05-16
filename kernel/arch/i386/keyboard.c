#include <kernel/keyboard.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static char input_buffer[INPUT_BUFFER_SIZE];
static uint32_t buffer_index = 0;

static void shell_execute(const char *cmd) {
  printf("\n");
  if (!*cmd) {
  } else if (strcmp(cmd, "help") == 0) {
    printf("No help sorry...\n");
  } else {
    printf("Command not recognised.\n");
  }
}

static const char scancode_to_ascii[] = {
    0,   0,   '1',  '2',  '3',  '4', '5', '6',  '7', '8', '9', '0',
    '-', '=', '\b', '\t', 'q',  'w', 'e', 'r',  't', 'y', 'u', 'i',
    'o', 'p', '[',  ']',  '\n', 0,   'a', 's',  'd', 'f', 'g', 'h',
    'j', 'k', 'l',  ';',  '\'', '`', 0,   '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm',  ',',  '.',  '/', 0,   '*',  0,   ' '};

void keyboard_handler(uint8_t scancode) {
  if (scancode >= sizeof(scancode_to_ascii)) {
    return;
  }

  char c = scancode_to_ascii[scancode];
  if (!c) {
    return;
  }

  if (c == '\n') {
    input_buffer[buffer_index] = '\0';
    shell_execute(input_buffer);
    buffer_index = 0;
  } else {
    input_buffer[buffer_index++] = c;
    printf("%c", c);
  }
}
