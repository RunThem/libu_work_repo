/**
 * Created by iccy on 23-2-18.
 */

#include <buf.h>
#include <debug.h>
#include <misc.h>
#include <str.h>
#include <types.h>
#include <vec.h>

#define u_str_debug(s)                                                                             \
  do {                                                                                             \
    u_info("string len is %ld, alloc is %ld. \"%s\"",                                              \
           u_str_len(s),                                                                           \
           u_str_alloc(s),                                                                         \
           u_str_cstr(s));                                                                         \
  } while (0)

int main() {
  u_str_t str = u_str_create_from(u_c_str(" hello, world"));

  char c;
  u_str_for(str, c) {
    printf("'%c' ", c);
  }
  printf("\n");

  u_str_debug(str);

  size_t idx = 6;

  u_str_remove(str, idx, sizeof(char));
  u_str_insert(&str, idx, u_c_str(" {love}"));

  u_str_debug(str);

  u_str_t _str = u_str_copy(str);

  u_str_debug(_str);

  u_con("%d", u_misc_align_2pow(16));

  u_con("%d", u_str_compare(str, u_c_str(" hello {love} world")));

  u_con("%d", u_str_contains(str, u_byte('a')));

  u_con("%d", u_str_prefix(str, u_c_str(" hell")));

  u_con("%d", u_str_suffix(str, u_c_str(" hello {love} world")));

  u_con("%d", u_str_index(str, u_byte('a')));

  return 0;
}
