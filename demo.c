/**
 * Created by iccy on 23-2-18.
 */

#include <buf.h>
#include <debug.h>
#include <types.h>
#include <vec.h>

int main() {
  u_vec_t vec = u_vec_create(10, sizeof(u_i32_t));

  u_con("itsize is %ld", u_vec_itsize(vec));

  u_con("len is %ld", u_vec_len(vec));
  u_con("alloc is %ld", u_vec_alloc(vec));
  u_con("free is %ld", u_vec_free(vec));

  u_vec_push(&vec, 32);

  u_con("len is %ld", u_vec_len(vec));
  u_con("alloc is %ld", u_vec_alloc(vec));
  u_con("free is %ld", u_vec_free(vec));

  u_con("%d", ((u_i32_t*)vec)[0]);

  u_vec_push(&vec, 123);

  u_con("len is %ld", u_vec_len(vec));
  u_con("alloc is %ld", u_vec_alloc(vec));
  u_con("free is %ld", u_vec_free(vec));

  for (size_t i = 0; i < u_vec_len(vec); i++) {
    u_con("%d", ((u_i32_t*)vec)[i]);
  }

  u_vec_push(&vec, 238923);

  u_con("len is %ld", u_vec_len(vec));
  u_con("alloc is %ld", u_vec_alloc(vec));
  u_con("free is %ld", u_vec_free(vec));

  for (size_t i = 0; i < u_vec_len(vec); i++) {
    u_con("%d", ((u_i32_t*)vec)[i]);
  }

  u_vec_insert(&vec, 0, 233);

  u_con("len is %ld", u_vec_len(vec));
  u_con("alloc is %ld", u_vec_alloc(vec));
  u_con("free is %ld", u_vec_free(vec));

  for (size_t i = 0; i < u_vec_len(vec); i++) {
    u_con("%d", ((u_i32_t*)vec)[i]);
  }

  u_con("");

  int m = 0;

  u_vec_at(vec, 2, &m);
  u_con("%d", m);

  u_vec_for(vec, m) {
    u_con("%d", m);
  }

  u_vec_replace(vec, 1, 100);

  u_con("");
  u_vec_for(vec, m) {
    u_con("%d", m);
  }

  u_con("%d", u_vec_empty(vec));

  u_vec_t vec1 = u_vec_copy(vec);

  u_con("len is %ld", u_vec_len(vec1));
  u_con("alloc is %ld", u_vec_alloc(vec1));
  u_con("free is %ld", u_vec_free(vec1));
  u_con("itsize is %ld", u_vec_itsize(vec1));

  u_vec_for(vec1, m) {
    u_con("%d", m);
  }

  int* ptr = NULL;

  u_vec_scan(vec1, ptr, int) {
    u_con("%p, %d", ptr, *ptr);
    *ptr = *ptr * 2;
  }

  u_vec_for(vec1, m) {
    u_con("%d", m);
  }

  u_vec_clean(vec);

  return 0;
}
