#ifndef _KERNEL_ISR_H
#define _KERNEL_ISR_H

#include <stdint.h>

struct registers {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags;
};

#endif // !_KERNEL_ISR_H
