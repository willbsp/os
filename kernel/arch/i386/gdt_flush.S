.global gdt_flush # makes visible to the linker
gdt_flush:
  mov 4(%esp), %eax
  lgdt (%eax)
  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss
  # reload the cs (code segment register)
  jmp $0x08, $.flush

.flush:
  ret
