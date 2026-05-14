isr_common:
  # save registers, so can resume
  # from where left off when the
  # interrupt was fired
  pusha

  # save data segment, as needs to
  # be set to to 0x10 to access kernel
  # memory. so save to ax then push to eax
  # which keeps the stack 32 bit aligned
  mov %ds, %ax
  push %eax

  # set all data segment registers to 0x10
  # remember: ax is a scratch register
  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs

  # Call the C handler, passing a pointer to the stack frame.
  # At this point, ESP points to a struct that contains:
  #   ds, edi, esi, ebp, esp, ebx, edx, ecx, eax,
  #   int_no, err_code,
  #   eip, cs, eflags  (pushed by CPU)
  push %esp            # Pass the stack pointer as the argument
  call isr_handler    # This is our C function
  add $4, %esp          # Clean up the argument we pushed

  # restore data segment registers
  pop %eax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs

  # restore general purpose registers
  popa

  # clean up interrupt number and error code
  add $8, %esp
  iret

.global isr0
isr0:
  push $0 # dummy error code
  push $0 # interrupt number
  jmp isr_common

.global isr1
isr1:
  push $0
  push $1
  jmp isr_common

.global isr2
isr2:
  push $0
  push $2
  jmp isr_common

.global isr3
isr3:
  push $0
  push $3
  jmp isr_common

.global isr4
isr4:
  push $0
  push $4
  jmp isr_common

.global isr5
isr5:
  push $0
  push $5
  jmp isr_common

.global isr6
isr6:
  push $0
  push $6
  jmp isr_common

.global isr7
isr7:
  push $0
  push $7
  jmp isr_common

.global isr8
isr8:
  push $8
  jmp isr_common

.global isr9
isr9:
  push $0
  push $9
  jmp isr_common

.global isr10
isr10:
  push $10
  jmp isr_common

.global isr11
isr11:
  push $11
  jmp isr_common

.global isr12
isr12:
  push $12
  jmp isr_common

.global isr13
isr13:
  push $13
  jmp isr_common

.global isr14
isr14:
  push $14
  jmp isr_common

.global isr15
isr15:
  push $0
  push $15
  jmp isr_common

.global isr16
isr16:
  push $0
  push $16
  jmp isr_common

.global isr17
isr17:
  push $17
  jmp isr_common

.global isr18
isr18:
  push $0
  push $18
  jmp isr_common

.global isr19
isr19:
  push $0
  push $19
  jmp isr_common

.global isr20
isr20:
  push $0
  push $20
  jmp isr_common

.global isr21
isr21:
  push $21
  jmp isr_common

.global isr22
isr22:
  push $0
  push $22
  jmp isr_common

.global isr23
isr23:
  push $0
  push $23
  jmp isr_common

.global isr24
isr24:
  push $0
  push $24
  jmp isr_common

.global isr25
isr25:
  push $0
  push $25
  jmp isr_common

.global isr26
isr26:
  push $0
  push $26
  jmp isr_common

.global isr27
isr27:
  push $0
  push $27
  jmp isr_common

.global isr28
isr28:
  push $0
  push $28
  jmp isr_common

.global isr29
isr29:
  push $0
  push $29
  jmp isr_common

.global isr30
isr30:
  push $0
  push $30
  jmp isr_common

.global isr31
isr31:
  push $0
  push $31
  jmp isr_common

.global isr32
isr32:
  push $0
  push $32
  jmp isr_common

.global isr33
isr33:
  push $0
  push $33
  jmp isr_common

.global isr34
isr34:
  push $0
  push $34
  jmp isr_common

.global isr35
isr35:
  push $0
  push $35
  jmp isr_common

.global isr36
isr36:
  push $0
  push $36
  jmp isr_common

.global isr37
isr37:
  push $0
  push $37
  jmp isr_common

.global isr38
isr38:
  push $0
  push $38
  jmp isr_common

.global isr39
isr39:
  push $0
  push $39
  jmp isr_common

.global isr40
isr40:
  push $0
  push $40
  jmp isr_common

.global isr41
isr41:
  push $0
  push $41
  jmp isr_common

.global isr42
isr42:
  push $0
  push $42
  jmp isr_common

.global isr43
isr43:
  push $0
  push $43
  jmp isr_common

.global isr44
isr44:
  push $0
  push $44
  jmp isr_common

.global isr45
isr45:
  push $0
  push $45
  jmp isr_common

.global isr46
isr46:
  push $0
  push $46
  jmp isr_common

.global isr47
isr47:
  push $0
  push $47
  jmp isr_common
