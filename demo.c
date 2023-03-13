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
  u_str_t str_itor = NULL;
  u_vec_t vec_itor, v1 = NULL;
  u_vec_t vec_vec = u_vec_create(4, sizeof(u_vec_t));
  u_con("%p", vec_vec);

  v1 = u_vec_create(4, sizeof(u_c_str_t));
  u_vec_push(vec_vec, v1);
  u_vec_push(vec_vec, u_vec_create(4, sizeof(u_c_str_t)));

  u_con("%p", v1);

  // u_con("%d", u_vec_len(vec_vec));

  // vec_itor = u_vec_quote(vec_vec, 0, u_vec_t);
  // u_vec_push(vec_itor, u_nullptr("hello work space"));
  // u_vec_push(vec_itor, u_nullptr("hello iccy"));

  // u_con("%p", vec_itor);

  // u_con("%d", u_vec_len(vec_itor));

  // vec_itor = u_vec_quote(vec_vec, 0, u_vec_t);
  // u_con("%p", vec_itor);

  u_vec_at(vec_vec, 0, &vec_itor);
  u_con("%p", vec_itor);

  u_vec_push(u_vec_quote(vec_vec, 0, u_vec_t), u_nullptr("hello runthem.org"));
  u_vec_push(u_vec_quote(vec_vec, 0, u_vec_t), u_nullptr("hello runthem.org"));

  u_vec_push(vec_itor, u_nullptr("hello iccy.fun"));
  u_con("%d", u_vec_len(vec_itor));

  u_vec_for(vec_vec, vec_itor) {
    u_vec_for(vec_itor, str_itor) {
      printf("%s\n", u_str_cstr(str_itor));
    }
  }

  // u_vec_for(vec_vec, vec_itor) {
  //   u_vec_clean(vec_itor);
  // }

  u_vec_clean(vec_vec);

  return 0;
}
