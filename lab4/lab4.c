#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(char *str) {
  perror(str);
  exit(1);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  size_t len = snprintf(buf, BUF_SIZE, format,
                        data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main(void) {
  void *heap_ptr = sbrk(256);

  struct header *first = (struct header *)heap_ptr;
  struct header *second = (struct header *)((char *)heap_ptr + 128);

  first->next = NULL;
  second->next = first;
  first->size = 128;
  second->size = 128;

  char *first_data = (char *)(first + 1);
  char *second_data = (char *)(second + 1);

  memset(first_data, 0, 128 - sizeof(struct header));
  memset(second_data, 1, 128 - sizeof(struct header));

  print_out("First block address: %p\n", &first, sizeof(first));
  print_out("Second block address: %p\n", &second, sizeof(second));
  print_out("First block size: %lu\n", &first->size, sizeof(first->size));
  print_out("First block next: %p\n", &first->next, sizeof(first->next));
  print_out("Second block size: %lu\n", &second->size, sizeof(second->size));
  print_out("Second block next: %p\n", &second->next, sizeof(second->next));

  for (int i = 0; i < 128 - sizeof(struct header); i++) {
    uint64_t val = first_data[i];
    print_out("%lu\n", &val, sizeof(val));
  }

  for (int i = 0; i < 128 - sizeof(struct header); i++) {
    uint64_t val = second_data[i];
    print_out("%lu\n", &val, sizeof(val));
  }

  return 0;
}
