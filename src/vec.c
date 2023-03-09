/**
 * Created by iccy on 23-3-9.
 */

#include <debug.h>
#include <misc.h>
#include <vec.h>

struct u_vec_t {
  size_t len;
  size_t alloc;
  size_t itsize;
  u_i8_t buf[0];
};

#define VEC_HEADER_SIZE  (sizeof(struct u_vec_t))
#define CONTAINER_VEC(v) (container_of(v, struct u_vec_t, buf))

u_vec_t u_vec_create(size_t size, size_t itsize) {
  struct u_vec_t* vec = NULL;

  dbg_return_if(itsize == 0, NULL);

  if (size < U_VEC_DEFAULT_LENGTH) {
    size = U_VEC_DEFAULT_LENGTH;
  }

  dbg_alloc_if(vec = (struct u_vec_t*)u_zalloc(VEC_HEADER_SIZE + size * itsize));

  vec->alloc  = size;
  vec->itsize = itsize;

  return u_vec(vec->buf);
err:

  return NULL;
}

void u_vec_clean(u_vec_t v) {
  dbg_return_if(v == NULL, );

  u_free(CONTAINER_VEC(v));
}

size_t u_vec_len(u_vec_t v) {
  dbg_return_if(v == NULL, 0);

  return CONTAINER_VEC(v)->len;
}

size_t u_vec_alloc(u_vec_t v) {
  dbg_return_if(v == NULL, 0);

  return CONTAINER_VEC(v)->alloc;
}

size_t u_vec_free(u_vec_t v) {
  dbg_return_if(v == NULL, 0);

  return CONTAINER_VEC(v)->alloc - CONTAINER_VEC(v)->len;
}

size_t u_vec_itsize(u_vec_t v) {
  dbg_return_if(v == NULL, 0);

  return CONTAINER_VEC(v)->itsize;
}

u_bool_t u_vec_empty(u_vec_t v) {
  dbg_return_if(v == NULL, true);

  return !CONTAINER_VEC(v)->len;
}

int u_vec_resize(u_vec_t* v, size_t size) {
  struct u_vec_t* vec = NULL;

  dbg_return_if(v == NULL, ~0);
  dbg_return_if(*v == NULL, ~0);
  dbg_return_if(u_vec_alloc(*v) >= size, ~0);

  vec = CONTAINER_VEC(v);

  dbg_alloc_if(vec = (struct u_vec_t*)u_realloc(vec, VEC_HEADER_SIZE + vec->itsize * size));

  vec->alloc = size;
  *v         = u_vec(vec->buf);

  return 0;
err:
  return ~0;
}

int _u_vec_push(u_vec_t* v, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_vec_t* vec = NULL;

  dbg_return_if(v == NULL, ~0);
  dbg_return_if(*v == NULL, ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);
  dbg_return_if(type == U_TYPES_C_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  dbg_err_if(itsize != u_vec_itsize(*v));

  if (u_vec_free(*v) == 0) {
    dbg_err_if(u_vec_resize(v, u_vec_alloc(*v) * 2) != 0);
  }

  vec = CONTAINER_VEC(*v);

  memcpy(&vec->buf[vec->len * vec->itsize], ptr, vec->itsize);

  vec->len++;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_vec_pop(u_vec_t v, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_vec_t* vec = NULL;

  dbg_return_if(v == NULL, ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  dbg_err_if(itsize != u_vec_itsize(v));

  vec = CONTAINER_VEC(v);

  memcpy(ptr, &vec->buf[(vec->len - 1) * vec->itsize], vec->itsize);

  vec->len--;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_vec_insert(u_vec_t* v, size_t idx, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_vec_t* vec = NULL;

  dbg_return_if(v == NULL, ~0);
  dbg_return_if(*v == NULL, ~0);
  dbg_return_if(idx > u_vec_len(*v), ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);
  dbg_return_if(type == U_TYPES_C_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  dbg_err_if(itsize != u_vec_itsize(*v));

  if (u_vec_free(*v) == 0) {
    dbg_err_if(u_vec_resize(v, u_vec_alloc(*v) * 2) != 0);
  }

  vec = CONTAINER_VEC(*v);

  if (idx != vec->len) {
    memmove(&vec->buf[(idx + 1) * vec->itsize],
            &vec->buf[idx * vec->itsize],
            vec->itsize * (vec->len - idx));
  }

  memcpy(&vec->buf[idx * vec->itsize], ptr, vec->itsize);

  vec->len++;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_vec_at(u_vec_t v, size_t idx, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_vec_t* vec = NULL;

  dbg_return_if(v == NULL, ~0);
  dbg_return_if(idx >= u_vec_len(v), ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  dbg_err_if(itsize != u_vec_itsize(v));

  vec = CONTAINER_VEC(v);

  memcpy(ptr, &vec->buf[idx * vec->itsize], vec->itsize);

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int u_vec_remove(u_vec_t v, size_t idx) {
  struct u_vec_t* vec = NULL;

  dbg_return_if(v == NULL, ~0);
  dbg_return_if(idx > u_vec_len(v), ~0);

  vec = CONTAINER_VEC(v);

  memcpy(&vec->buf[idx * vec->itsize], &vec->buf[(idx + 1) * vec->itsize], vec->itsize);

  return 0;
}

int _u_vec_replace(u_vec_t v, size_t idx, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_vec_t* vec = NULL;

  dbg_return_if(v == NULL, ~0);
  dbg_return_if(idx >= u_vec_len(v), ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);
  dbg_return_if(type == U_TYPES_C_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  dbg_err_if(itsize != u_vec_itsize(v));

  vec = CONTAINER_VEC(v);

  memcpy(&vec->buf[idx * vec->itsize], ptr, vec->itsize);

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

u_vec_t u_vec_copy(u_vec_t v) {
  struct u_vec_t* vec  = NULL;
  struct u_vec_t* _vec = NULL;

  dbg_return_if(v == NULL, NULL);

  _vec = CONTAINER_VEC(v);

  dbg_alloc_if(vec = u_zalloc(VEC_HEADER_SIZE + _vec->alloc * _vec->itsize));

  memcpy(vec, _vec, VEC_HEADER_SIZE + _vec->alloc * _vec->itsize);

  return u_vec(vec->buf);
err:
  return NULL;
}

u_nullptr_t u_vec_at_ptr(u_vec_t v, size_t idx) {
  struct u_vec_t* vec = NULL;

  dbg_return_if(v == NULL, NULL);
  dbg_return_if(idx >= u_vec_len(v), NULL);

  vec = CONTAINER_VEC(v);

  return &vec->buf[idx * vec->itsize];
}
