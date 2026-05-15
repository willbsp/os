#include <kernel/multiboot.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define FRAME_SIZE   4096
#define TOTAL_FRAMES (0xFFFFFFFF / FRAME_SIZE + 1) // 1,048,576 frames for 4GB
#define BITMAP_SIZE  (TOTAL_FRAMES / 8)

extern uint32_t _kernel_start;
extern uint32_t _kernel_end;

uint8_t mem_bitmap[BITMAP_SIZE];
uint32_t last_alloc_byte_index;

void bitmap_clear(uint32_t frame_no) {
  int32_t byte_index = frame_no / 8;
  int32_t bit_index = frame_no % 8;
  mem_bitmap[byte_index] &= ~(0x01 << bit_index);
}

void bitmap_set(uint32_t frame_no) {
  int32_t byte_index = frame_no / 8;
  int32_t bit_index = frame_no % 8;
  mem_bitmap[byte_index] |= (0x01 << bit_index);
}

void pmm_init(struct multiboot_info *info) {
  // memory bitmap, mark everything as used
  // 0xFF since 1 would set each byte to 1
  memset(mem_bitmap, 0xFF, sizeof(mem_bitmap));

  uint32_t total_usable = 0;
  printf("Detected memory map:\n");
  for (uint32_t i = 0; i < info->mmap_length;
       i += sizeof(struct multiboot_mmap_entry)) {
    struct multiboot_mmap_entry *entry =
        (struct multiboot_mmap_entry *)(info->mmap_addr + i);
    printf("Start: %u | Size: %uKB | Type: %u",
           (uint32_t)entry->addr,
           (uint32_t)entry->len / 1024,
           entry->type);
    // skip first 1M of usable RAM
    if (entry->type == 1 && (uint32_t)entry->addr >= 0x100000) {
      printf(" | Mapped");
      uint32_t start_frame =
          (uint32_t)entry->addr / FRAME_SIZE; // 4kb per frame
      uint32_t no_frames = (uint32_t)entry->len / FRAME_SIZE;
      for (uint32_t frame = start_frame; frame < start_frame + no_frames;
           frame++) {
        bitmap_clear(frame);
      }
      total_usable += (uint32_t)entry->len;
    }
    printf("\n");
  }

  uint32_t kstart = (uint32_t)&_kernel_start;
  uint32_t kend = (uint32_t)&_kernel_end;
  uint32_t start_frame = (uint32_t)kstart / FRAME_SIZE;
  uint32_t end_frame = (uint32_t)kend / FRAME_SIZE;
  for (uint32_t frame = start_frame; frame < end_frame; frame++) {
    bitmap_set(frame);
  }

  printf("Detected %uMB of memory\n\n", total_usable / 1024 / 1024);
}

uint32_t pmm_alloc() {
  for (uint32_t i = 0; i < BITMAP_SIZE; i++) {
    // start at last allocatd, % handles the wraparound at the end of the bitmap
    uint32_t byte_index = (last_alloc_byte_index + i) % BITMAP_SIZE;
    uint8_t byte = mem_bitmap[byte_index];
    if (byte == 0xFF) {
      // the byte is 11111111 so no free bits
      continue;
    }
    for (int8_t bit_index = 7; bit_index >= 0; bit_index--) {
      uint8_t used = (byte >> bit_index) & 0x01;
      if (!used) {
        uint32_t frame_no = (byte_index * 8) + bit_index;
        bitmap_set(frame_no);
        last_alloc_byte_index = byte_index;
        return frame_no * FRAME_SIZE;
      }
    }
  }

  return 0; // could not find free memory
}

void pmm_free(uint32_t addr) {
  uint32_t frame_no = addr / FRAME_SIZE;
  bitmap_clear(frame_no);
}
