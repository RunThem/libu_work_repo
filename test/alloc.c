#include <alloc.h>
#include <debug.h>
#include <malloc.h>
#include <mimalloc.h>
#include <mut.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <types.h>

mut_test(libu_alloc_malloc) {
  u_i8_t* buf = u_malloc(100);
  mut_assert(NULL != buf);

  u_free(buf);

  mut_bench("benchmark mi_malloc", {
    mut_blank_line();
    u_malloc(sizeof(char) * 1024);
  });

  mut_bench("benchmark mi_calloc", {
    mut_blank_line();
    u_zalloc(sizeof(int) * 1024);
  });
}

mut_group(libu_alloc) {
  mut_add_test(libu_alloc_malloc, "test libu alloc malloc");
}
