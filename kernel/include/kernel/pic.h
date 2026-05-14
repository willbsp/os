#ifndef _KERNEL_PIC_H
#define _KERNEL_PIC_H

void pic_initialize(void);
void pic_send_eoi(uint8_t irq);

#endif // !_KERNEL_PIC_H
