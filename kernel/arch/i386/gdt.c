#include <kernel/gdt.h>
#include <stdint.h>
#include <stdio.h>

extern void gdt_flush(uint32_t);

struct gdt_entry gdt[3];
struct gdt_table table;

void gdt_set_gate(uint8_t entry_no,
                  uint32_t base,
                  uint32_t limit,
                  uint8_t access,
                  uint8_t granularity) {
  gdt[entry_no].limit_low = limit & (0xFFFF);
  gdt[entry_no].base_low = base & (0xFFFF);
  gdt[entry_no].base_middle = (base >> 16) & (0xFF);
  gdt[entry_no].base_high = (base >> 24) & (0xFF);
  gdt[entry_no].access = access;
  gdt[entry_no].granularity = (granularity & 0xF0) | ((limit >> 16) & (0x0F));
}

void gdt_install() {
  table.limit = (sizeof(struct gdt_entry) * 3) - 1;
  table.base = (uint32_t)&gdt;

  gdt_set_gate(0, 0, 0, 0, 0);
  gdt_set_gate(1, 0x00000000, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_gate(2, 0x00000000, 0xFFFFFFFF, 0x92, 0xCF);

  gdt_flush((uint32_t)&table);
}
