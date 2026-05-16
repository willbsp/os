#include <kernel/heap.h>
#include <kernel/pmm.h>
#include <stdint.h>
#include <string.h>

#define PAGE_SIZE 4096

struct block_header {
  uint32_t size;
  uint8_t free;
  struct block_header *next;
};

static struct block_header *head = NULL;

void heap_init() {
  uint32_t frame = pmm_alloc();
  head = (struct block_header *)frame;
  head->size = PAGE_SIZE - sizeof(struct block_header);
  head->free = 1;
  head->next = NULL;
}

void *kmalloc(uint32_t size) {
  struct block_header *ptr = head;
  struct block_header *last = NULL;
  while (ptr != NULL) {
    if (ptr->free && ptr->size >= size) {

      // ensure subtraction will not underflow
      if (ptr->size > size + sizeof(struct block_header)) {

        // if the size remaining after allocating this block is greater than
        // the size of a block header, split the block into two one of which
        // we allocate now and the other is free for later allocation
        uint32_t remaining = ptr->size - size - sizeof(struct block_header);
        if (remaining > sizeof(struct block_header)) {
          struct block_header *new_block =
              (struct block_header *)((uint32_t)ptr +
                                      sizeof(struct block_header) + size);
          new_block->size = remaining;
          new_block->free = 1;

          new_block->next = ptr->next;
          ptr->next = new_block;
          ptr->size = size;
        }
      }

      ptr->free = 0;
      return (void *)((uint32_t)ptr + sizeof(struct block_header));
    }
    last = ptr;
    ptr = ptr->next;
  }

  // no free block found, request more memory from
  // physical memory manager
  uint32_t frame = pmm_alloc();
  ptr = (struct block_header *)frame;
  ptr->size = PAGE_SIZE - sizeof(struct block_header);
  ptr->free = 0;
  ptr->next = NULL;
  last->next = ptr;
  return (void *)((uint32_t)ptr + sizeof(struct block_header));
}

void kfree(void *ptr) {
  struct block_header *header =
      (struct block_header *)(ptr - sizeof(struct block_header));
  header->free = 1;
}

void heap_meminfo(uint32_t *total, uint32_t *used, uint32_t *free) {
  struct block_header *ptr = head;
  while (ptr != NULL) {
    *total += ptr->size + sizeof(struct block_header);
    if (ptr->free) {
      *free += ptr->size;
    } else {
      *used += ptr->size;
    }
    ptr = ptr->next;
  }
}
