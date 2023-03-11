/**
 * Created by iccy on 23-3-5.
 */
#include <buf.h>
#include <misc.h>
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
      {128,  100 },
      {256,  129 },
      {2048, 1025},
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

  u_buf_push(&buf, u_byte('2'));
  u_buf_push(&buf, u_i16(32));
  u_buf_push(&buf, u_i32(32));
  u_buf_push(&buf, u_u32(32));
  u_buf_push(&buf, u_i16(32));
  u_buf_push(&buf, u_nullptr(&buf));
  u_buf_push(&buf, u_i16(32));
  u_buf_push(&buf, u_c_str("hello"));

  u_i16_t a[] = {2, 3, 4, 2, 4, 2, 3, 41};

  u_buf_push(&buf, u_any(a), sizeof(a));

  mut_equal(1 + 2 + 4 + 4 + 2 + 8 + 2 + 5 + sizeof(a), u_buf_len(buf));
  mut_equal(u_misc_align_2pow(1 + 2 + 4 + 4 + 2 + 8 + 2 + 5 + sizeof(a)), u_buf_alloc(buf));
}

mut_test(libu_buf_read) {
  u_buf_t buf = u_buf_create(10);

  u_buf_push(&buf, u_byte('2'));
  u_buf_push(&buf, u_i16(32));
  u_buf_push(&buf, u_i32(32));
  u_buf_push(&buf, u_u32(32));
  u_buf_push(&buf, u_i16(32));
  u_buf_push(&buf, u_nullptr(&buf));
  u_buf_push(&buf, u_i16(32));
  u_buf_push(&buf, u_c_str("hello"));

  u_i16_t a[] = {2, 3, 4, 2, 4, 2, 3, 41};

  u_buf_push(&buf, u_any(a), sizeof(a));

  mut_equal(1 + 2 + 4 + 4 + 2 + 8 + 2 + 5 + sizeof(a), u_buf_len(buf));
  mut_equal(u_misc_align_2pow(1 + 2 + 4 + 4 + 2 + 8 + 2 + 5 + sizeof(a)), u_buf_alloc(buf));

  u_i64_t n;

  u_buf_pop(buf, (u_i16_t*)&n);
  mut_equal(1 + 2 + 4 + 4 + 2 + 8 + 2 + 5 + sizeof(a) - 2, u_buf_len(buf));

  u_buf_pop(buf, (u_u16_t*)&n);
  mut_equal(1 + 2 + 4 + 4 + 2 + 8 + 2 + 5 + sizeof(a) - 2 - 2, u_buf_len(buf));

  u_buf_pop(buf, &n);
  mut_equal(1 + 2 + 4 + 4 + 2 + 8 + 2 + 5 + sizeof(a) - 2 - 2 - 8, u_buf_len(buf));

  u_i16_t b[3];

  u_buf_pop(buf, u_any(b), sizeof(b));

  mut_equal(1 + 2 + 4 + 4 + 2 + 8 + 2 + 5 + sizeof(a) - 2 - 2 - 8 - sizeof(b), u_buf_len(buf));
}

mut_group(libu_buf) {
  mut_add_test(libu_buf_create, "test libu u_buf_create");
  mut_add_test(libu_buf_write, "test libu u_buf_write");
  mut_add_test(libu_buf_read, "test libu u_buf_read");
}
