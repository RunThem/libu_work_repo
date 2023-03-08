/**
 * Created by iccy on 23-2-18.
 */

#include <buf.h>
#include <debug.h>
#include <types.h>

int main() {

  u_buf_t buf = u_buf_create(10);

  u_con("type %d", u_types_of(buf));

  u_buf_write(&buf, u_byte('2'));
  u_buf_write(&buf, 30);
  u_buf_write(&buf, 2304);

  u_i16_t a[] = {12, 43, 53, 13};
  u_buf_write(&buf, u_any(a), sizeof(a));

  u_con("len is %ld", u_buf_len(buf));
  u_con("alloc is %ld", u_buf_alloc(buf));
  u_con("free is %ld", u_buf_free(buf));

  u_i16_t n = 0;

  u_buf_read(buf, &n);
  u_con("%d", n);

  u_con("len is %ld", u_buf_len(buf));
  u_con("alloc is %ld", u_buf_alloc(buf));
  u_con("free is %ld", u_buf_free(buf));
  u_i16_t b[3] = {0};

  u_buf_read(buf, u_any(b), sizeof(b));

  u_con("%d", b[0]);
  u_con("%d", b[1]);
  u_con("%d", b[2]);

  u_con("len is %ld", u_buf_len(buf));
  u_con("alloc is %ld", u_buf_alloc(buf));
  u_con("free is %ld", u_buf_free(buf));

  u_i32_t c = 0;

  u_buf_read(buf, &c);
  u_con("%d", c);

  u_con("len is %ld", u_buf_len(buf));
  u_con("alloc is %ld", u_buf_alloc(buf));
  u_con("free is %ld", u_buf_free(buf));

  c = 0;

  u_buf_read(buf, &c);
  u_con("%d", c);

  u_con("len is %ld", u_buf_len(buf));
  u_con("alloc is %ld", u_buf_alloc(buf));
  u_con("free is %ld", u_buf_free(buf));

  char m = 0;

  u_buf_read(buf, &m);
  u_con("'%c'", m);

  u_con("len is %ld", u_buf_len(buf));
  u_con("alloc is %ld", u_buf_alloc(buf));
  u_con("free is %ld", u_buf_free(buf));
  u_buf_clean(buf);

  return 0;
}
