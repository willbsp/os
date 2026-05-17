// for the registers that need to be saved see:
// https://wiki.osdev.org/Calling_Conventions
// the registers we need to preserve are: ebx, esi, edi, ebp, esp
// the c definition for this:
// void switch_context(struct tcb *current, struct tcb *next)
.global switch_context
switch_context:
  push %ebx
  push %esi
  push %edi
  push %ebp
  // 16 bytes into the stack
  // + 4 for return address
  // at this point, stack looks like so:
  // ESP + 0:  EBP (just pushed)
  // ESP + 4:  EDI
  // ESP + 8:  ESI
  // ESP + 12: EBX
  // ESP + 16: return address
  // ESP + 20: current <-- need this next
  // ESP + 24: next

  mov 20(%esp), %eax; // *current->esp save into eax
  mov %esp, (%eax) // save the stack pointer to the tcb->esp

  mov 24(%esp), %eax; // *next->esp into eax
  mov (%eax), %esp // overwrite stack pointer with next

  pop %ebp
  pop %edi
  pop %esi
  pop %ebx

  ret # pop return address - jumps to function
