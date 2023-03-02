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

#define mut_blank_line()
#define mut_bench(msg, block)                                                                      \
  printf("        bench \"%s\" ", msg);                                                            \
  do {                                                                                             \
    size_t MUT_N  = 1;                                                                             \
    clock_t start = 0, end = 0;                                                                    \
    for (; (end - start) < 100000 /* 0.1s */; end = clock()) {                                     \
      MUT_N *= 10;                                                                                 \
      start = clock();                                                                             \
      for (size_t count; count < MUT_N; count++) {                                                 \
        block                                                                                      \
      }                                                                                            \
    }                                                                                              \
    printf("%ld us, %.2f ns\n", end - start, (double)((end - start) * 1000 / MUT_N));              \
  } while (0)

  mut_bench("u_malloc()", {
    mut_blank_line();
    u_malloc(count * sizeof(int));
  });
}

mut_group(libu_alloc) {
  mut_add_test(libu_alloc_malloc, "test libu alloc malloc");
}
