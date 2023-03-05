/**
 * Created by iccy on 23-2-18.
 */

#include <debug.h>
#include <limits.h>
#include <math.h>
// #include <mimalloc.h>
// #include <misc.h>
#include <buf.h>
#include <mut.h>
#include <str.h>
#include <types.h>

int main() {

  u_buf_t buf = u_buf_create(10);

  u_con("type %d", u_types_of(buf));

  u_buf_write(&buf, u_byte('2'));
  u_buf_write(&buf, 30);
  u_buf_write(&buf, 2304);
  u_buf_write(&buf, u_i128(23));

  u_i16_t a[] = {12, 43, 53, 13};
  u_buf_write(&buf, u_any(a), sizeof(a));

  u_con("len is %ld", u_buf_len(buf));
  u_con("alloc is %ld", u_buf_alloc(buf));
  u_con("free is %ld", u_buf_free(buf));

  u_i16_t n = 0;

  u_buf_read(buf, u_any(&n), sizeof(n));
  u_con("%d", n);

  u_i16_t b[3] = {0};

  u_buf_read(buf, u_any(b), sizeof(b));

  u_con("%d", b[0]);
  u_con("%d", b[1]);
  u_con("%d", b[2]);

  u_buf_clean(buf);

  return 0;
}
