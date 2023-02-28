#include <alloc.h>
#include <debug.h>
#include <malloc.h>
#include <mimalloc.h>
#include <mut.h>
#include <string.h>
#include <types.h>

mut_test(libu_alloc_malloc) {
  u_i8_t* buf = u_malloc(100);
  mut_assert(NULL != buf);

  u_free(buf);

  int* data[100000];
  bzero(data, 100000 * sizeof(int*));

  for (size_t i = 0; i < 100000; i++) {
    data[i] = u_malloc(i * sizeof(int));
  }

  for (size_t i = 0; i < 100000; i++) {
    u_free(data[i]);
  }
}

mut_group(libu_alloc) {
  mut_add_test(libu_alloc_malloc, "test libu alloc malloc");
}
