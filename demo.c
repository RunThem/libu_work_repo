/**
 * Created by iccy on 23-2-18.
 */

#include <debug.h>
#include <limits.h>
#include <math.h>
// #include <mimalloc.h>
// #include <misc.h>
#include <mut.h>
#include <str.h>
#include <types.h>

int main() {

  u_str_t str = u_str_create_from("hello world");

  u_con("type %d", u_types_of(str));
  u_con("buf[0] = '%c'", str->buf[0]);
  u_con("\"%s\"", str->buf);

  u_con("len is %ld", u_str_len(str));
  u_con("alloc is %ld", u_str_alloc(str));
  u_con("free is %ld", u_str_free(str));

  u_str_resize(&str, 17);

  u_con("len is %ld", u_str_len(str));
  u_con("alloc is %ld", u_str_alloc(str));
  u_con("free is %ld", u_str_free(str));

  u_str_cat(&str, u_byte('v'));

  u_con("\"%s\"", str->buf);
  u_con("len is %ld", u_str_len(str));
  u_con("alloc is %ld", u_str_alloc(str));
  u_con("free is %ld", u_str_free(str));

  u_str_cat(&str, u_c_str("helo aj dfiahg wi"));

  u_con("\"%s\"", str->buf);
  u_con("len is %ld", u_str_len(str));
  u_con("alloc is %ld", u_str_alloc(str));
  u_con("free is %ld", u_str_free(str));

  u_str_clean(str);

  str = u_str_create_from("hello ");

  u_con("\"%s\"", str->buf);
  u_con("len is %ld", u_str_len(str));
  u_con("alloc is %ld", u_str_alloc(str));
  u_con("free is %ld", u_str_free(str));

  u_str_t str1 = u_str_create_from("world");

  u_con("\"%s\"", str1->buf);
  u_con("len is %ld", u_str_len(str1));
  u_con("alloc is %ld", u_str_alloc(str1));
  u_con("free is %ld", u_str_free(str1));

  u_str_cat(&str, str1);

  u_con("\"%s\"", str->buf);
  u_con("len is %ld", u_str_len(str));
  u_con("alloc is %ld", u_str_alloc(str));
  u_con("free is %ld", u_str_free(str));

  u_str_clean(str);
  u_str_clean(str1);

  u_con("hello con");
  u_info("hello info");
  u_warn("hello warn");
  u_dbg("hello dbg");
  u_err("hello err");

  errno = 73;
  u_con("hasidfa %s", "jsdf");
  errno = 0;

  return 0;
err:

  return 0;
}
