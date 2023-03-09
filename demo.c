/**
 * Created by iccy on 23-2-18.
 */

#include <buf.h>
#include <debug.h>
#include <str.h>
#include <types.h>
#include <vec.h>

#define u_buf_print(v)                                                                             \
  do {                                                                                             \
    u_con("len is %ld, alloc is %ld, free is %ld", u_buf_len(v), u_buf_alloc(v), u_buf_free(v));   \
  } while (0)

int main() {

  u_byte_t a = '9';
  u_i16_t b  = 1322;
  u_i32_t c  = 9999;
  u_f128_t d = 234.12;

  u_u64_t arr[] = {3, 2, 4, 43};

  /* size: 1 + 2 + 4 + 16 + 32 */

  u_buf_t buf = u_buf_create(10);

  u_buf_push(&buf, a);
  u_buf_print(buf);
  u_buf_push(&buf, b);
  u_buf_print(buf);
  u_buf_push(&buf, c);
  u_buf_print(buf);
  u_buf_push(&buf, d);
  u_buf_print(buf);
  u_buf_push(&buf, u_any(arr), sizeof(arr));
  u_buf_print(buf);

  for (int i = 0; i < u_buf_len(buf); ++i) {
    printf("%03d ", ((u_u8_t*)buf)[i]);
  }
  printf("\n");

  u_buf_insert(&buf, 2, 55);
  u_buf_print(buf);
  for (int i = 0; i < u_buf_len(buf); ++i) {
    printf("%03d ", ((u_u8_t*)buf)[i]);
  }
  printf("\n");

  u_buf_remove(buf, 2, sizeof(int));

  u_buf_print(buf);
  for (int i = 0; i < u_buf_len(buf); ++i) {
    printf("%03d ", ((u_u8_t*)buf)[i]);
  }
  printf("\n");

  u_f128_t f = 0;

  u_buf_at(buf, 7, &f);
  u_con("%Lf", f);

  u_buf_t _buf = u_buf_copy(buf);

  u_buf_print(_buf);
  for (int i = 0; i < u_buf_len(_buf); ++i) {
    printf("%03d ", ((u_u8_t*)_buf)[i]);
  }
  printf("\n");

  return 0;
}
