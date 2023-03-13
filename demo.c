/**
 * Created by iccy on 23-2-18.
 */

#include <buf.h>
#include <debug.h>
#include <misc.h>
#include <str.h>
#include <types.h>
#include <vec.h>

int main() {

  char ch     = '\0';
  u_str_t str = u_str_create_from("hello world");

  u_str_for(str, ch) {
    u_con("%c", ch);
  }

  u_str_pop(str, &ch);

  u_con("%c", ch);

  return 0;
}
