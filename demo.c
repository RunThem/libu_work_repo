/**
 * Created by iccy on 23-2-18.
 */

#include <debug.h>
#include <limits.h>
#include <math.h>
#include <misc.h>
#include <types.h>

int main() {

  u_str_t str = u_str_create(32);

  printf("type %d\n", u_types_of(str));

  u_str_free(str);

  // for (size_t i = 0; i < 1000; i++) {
  //   u_con("%d", u_misc_align_2pow(i));
  // }

  u_con("%lu", u_misc_align_2pow(powf128(2, 32) + 1));

  str = u_str_create_from("hello world");
  u_con("%s size is %d", str, u_str_len(str));
  u_str_free(str);
  u_con("");

  u_str_init(&str);
  u_con(str);

  u_str_free(str);

  u_str_init_from(&str, "hello libu str");
  u_con(str);

  u_con("%d", u_str_len(str));
  u_str_cat(&str, u_str_create_from("oo0"));

  u_con(str);
  u_con("%d, %d", u_str_len(str), u_str_alloc(str));

  u_str_free(str);

  u_con("hello con");
  u_info("hello info");
  u_warn("hello warn");
  u_dbg("hello dbg");
  u_err("hello err");

  errno = 73;
  u_con("hasidfa %s", "jsdf");
  errno = 0;

  char* ptr = malloc(2300);
  dbg_alloc_if(ptr);

  u_con("%p", ptr);
  dbg_free_if(ptr);
  u_con("%p", ptr);

  return 0;
err:

  dbg_free_if(ptr);

  return 0;
}
