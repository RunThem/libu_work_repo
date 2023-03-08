/**
 * Created by iccy on 23-3-5.
 */
#include <buf.h>
#include <mut.h>

mut_test(libu_buf_create) {
  u_buf_t buf = NULL;

  struct {
    int n;
    int m;
  } tbl[] = {
      {16,   0   },
      {16,   3   },
      {16,   7   },
      {16,   10  },
      {100,  100 },
      {129,  129 },
      {1025, 1025},
  };
  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    buf = u_buf_create(tbl[i].m);

    mut_assert(buf != NULL);

    mut_equal(0, u_buf_len(buf));
    mut_equal(tbl[i].n, u_buf_alloc(buf));
    mut_equal(u_buf_free(buf), u_buf_alloc(buf));

    u_buf_clean(buf);
  }
}

mut_test(libu_buf_write) {
  u_buf_t buf = u_buf_create(10);


}

mut_group(libu_buf) {
  mut_add_test(libu_buf_create, "test libu u_buf_create");
  mut_add_test(libu_buf_write, "test libu u_buf_write");
}
