#include <kernel/heap.h>
#include <kernel/pmm.h>
#include <stdint.h>
#include <stdio.h>
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

static void split_block_if_required(struct block_header *block, uint32_t size) {
  // ensure subtraction will not underflow
  if (block->size > size + sizeof(struct block_header)) {
    // if the size remaining after allocating this block is greater than
    // the size of a block header, split the block into two one of which
    // we allocate now and the other is free for later allocation
    uint32_t remaining = block->size - size - sizeof(struct block_header);
    if (remaining > sizeof(struct block_header)) {
      struct block_header *new_block =
          (struct block_header *)((uint32_t)block +
                                  sizeof(struct block_header) + size);
      new_block->size = remaining;
      new_block->free = 1;

      new_block->next = block->next;
      block->next = new_block;
      block->size = size;
    }
  }
}

void *kmalloc(uint32_t size) {
  printf("Heap: Allocating %u\n", size);
  struct block_header *ptr = head;
  struct block_header *last = NULL;
  while (ptr != NULL) {
    if (ptr->free && ptr->size >= size) {
      split_block_if_required(ptr, size);
      ptr->free = 0;
      return (void *)((uint32_t)ptr + sizeof(struct block_header));
    }
    last = ptr;
    ptr = ptr->next;
  }

  uint32_t frame = pmm_alloc();
  ptr = (struct block_header *)frame;
  ptr->size = PAGE_SIZE - sizeof(struct block_header);
  ptr->next = NULL;
  last->next = ptr;
  split_block_if_required(ptr, size);

  ptr->free = 0;
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
    printf("\nHeap: Size %u Header %u Total %u\n",
           ptr->size,
           sizeof(struct block_header),
           ptr->size + sizeof(struct block_header));
    *total += ptr->size + sizeof(struct block_header);
    if (ptr->free) {
      printf("Heap: Free %u\n", ptr->size);
      *free += ptr->size;
    } else {
      printf("Heap: Used %u\n", ptr->size);
      *used += ptr->size;
    }
    ptr = ptr->next;
    printf("Heap: next\n\n");
  }
}
