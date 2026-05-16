#include <stdint.h>

// 1024 * 1024 * 4KB = 4GB
#define PD_ENTRIES 1024
#define PT_ENTRIES 1024
#define PAGE_SIZE  4096 // same as frame size as 1 to 1 mapping

#define PAGE_PRESENT   0x01
#define PAGE_READWRITE 0x02
#define PAGE_USER      0x04

uint32_t flags = PAGE_PRESENT | PAGE_READWRITE;

// looking up an address
// uses top 10 bits of address to pick a page directory entry
// this entry contains the physical address of the page table
// then use the next 10 bits to pick an entry in the page table
// which then contains the physical address of the 4KB frame

// aligning the memory addresses to 4096 ensures that the bottom 12 bits of
// a page address will always be zero. this ensures that those 12 bits can
// be used for the flags and its safe to OR the address with the flags
static uint32_t page_directory[PD_ENTRIES] __attribute__((aligned(4096)));

// 2d array is beside the point here could define like so:
// uint32_t page_table_0[1024]
// uint32_t page_table_1[1024]
// ... etc
// the first index in this case is not actually used for lookup
// since the page directory stores an address to the page
// 1024 * 1024 * 4096 = 4GB address space
static uint32_t page_tables[PD_ENTRIES][PT_ENTRIES]
    __attribute__((aligned(4096)));

void paging_init() {
  // identity paging
  // virtual addresses map to physical addresses 1 to 1
  for (uint32_t pt_index = 0; pt_index < PD_ENTRIES; pt_index++) {
    for (uint32_t pt_offset = 0; pt_offset < PT_ENTRIES; pt_offset++) {
      uint32_t phys_address = (pt_index * PT_ENTRIES + pt_offset) * PAGE_SIZE;
      page_tables[pt_index][pt_offset] = phys_address | flags;
    }
  }

  for (int pd_index = 0; pd_index < PD_ENTRIES; pd_index++) {
    page_directory[pd_index] = ((uint32_t)&page_tables[pd_index]) | flags;
  }

  // load page directory address into CR3 (page directory register)
  asm volatile("mov %0, %%cr3" : : "r"((uint32_t)&page_directory));
  // read the current value of CR0. CR0 is a control register with cpu
  // mode flags
  uint32_t cr0;
  asm volatile("mov %%cr0, %0" : "=r"(cr0));
  // set bit 31 of CR0. this is the paging enable bit
  // also set bit 0, for protected mode (required for paging but
  // in theory should already be set by bootloader)
  cr0 |= 0x80000001;
  // write back to CR0, paging is now enabled
  asm volatile("mov %0, %%cr0" : : "r"(cr0));
}
