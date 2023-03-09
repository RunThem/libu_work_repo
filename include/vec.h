/**
 * Created by iccy on 23-3-9.
 */

#ifndef _U_VECTOR_H_
#define _U_VECTOR_H_

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef U_VEC_DEFAULT_LENGTH
#  define U_VEC_DEFAULT_LENGTH 16
#endif /* !U_VEC_DEFAULT_LENGTH */

u_vec_t u_vec_create(size_t size, size_t itsize);
void u_vec_clean(u_vec_t v);
int u_vec_resize(u_vec_t* v, size_t size);

size_t u_vec_len(u_vec_t v);
size_t u_vec_alloc(u_vec_t v);
size_t u_vec_free(u_vec_t v);
size_t u_vec_itsize(u_vec_t v);
u_bool_t u_vec_empty(u_vec_t v);

int _u_vec_push(u_vec_t* v, u_types_type_e type, ...);
#define u_vec_push(v, a) _u_vec_push(v, u_types_of(a), a)

int _u_vec_pop(u_vec_t v, u_types_type_e type, ...);
#define u_vec_pop(v, a) _u_vec_pop(v, u_types_of(a), a)

int _u_vec_insert(u_vec_t* v, size_t idx, u_types_type_e type, ...);
#define u_vec_insert(v, i, a) _u_vec_insert(v, i, u_types_of(a), a)

int _u_vec_at(u_vec_t v, size_t idx, u_types_type_e type, ...);
#define u_vec_at(v, i, a) _u_vec_at(v, i, u_types_of(a), a)

int u_vec_remove(u_vec_t v, size_t idx);

int _u_vec_replace(u_vec_t v, size_t idx, u_types_type_e type, ...);
#define u_vec_replace(v, i, a) _u_vec_replace(v, i, u_types_of(a), a)

u_vec_t u_vec_copy(u_vec_t v);

u_nullptr_t u_vec_at_ptr(u_vec_t v, size_t idx);

#define u_vec_for(v, it)                                                                           \
  for (size_t i = 0, _len = u_vec_len(v); i < _len && !u_vec_at(v, i, &it); i++)

#define u_vec_scan(v, p, type)                                                                     \
  for (size_t i = 0, _len = u_vec_len(v); i < _len && ((p) = (type*)u_vec_at_ptr(v, i)); i++)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_VECTOR_H_ */
