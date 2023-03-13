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

u_vec_t _u_vec_create(size_t size, size_t itsize);
#define u_vec_create(s, is) _u_vec_create(s, is)

void _u_vec_clean(u_vec_t v);
#define u_vec_clean(v) _u_vec_clean(v)

int _u_vec_resize(u_vec_t* v, size_t size);
#define u_vec_resize(v, s) _u_vec_resize(v, s)

size_t _u_vec_len(u_vec_t v);
#define u_vec_len(v) _u_vec_len(v)

size_t _u_vec_alloc(u_vec_t v);
#define u_vec_alloc(v) _u_vec_alloc(v)

size_t _u_vec_free(u_vec_t v);
#define u_vec_free(v) _u_vec_free(v)

size_t _u_vec_itsize(u_vec_t v);
#define u_vec_itsize(v) _u_vec_itsize(v)

u_bool_t _u_vec_empty(u_vec_t v);
#define u_vec_empty(v) _u_vec_empty(v)

int _u_vec_push(u_vec_t* v, u_types_type_e type, ...);
#define u_vec_push(v, a, ...) _u_vec_push(v, u_types_of(a), a, ##__VA_ARGS__)

int _u_vec_pop(u_vec_t v, u_types_type_e type, ...);
#define u_vec_pop(v, a, ...) _u_vec_pop(v, u_types_of(a), a, ##__VA_ARGS__)

int _u_vec_insert(u_vec_t* v, size_t idx, u_types_type_e type, ...);
#define u_vec_insert(v, i, a, ...) _u_vec_insert(v, i, u_types_of(a), a, ##__VA_ARGS__)

int _u_vec_at(u_vec_t v, size_t idx, u_types_type_e type, ...);
#define u_vec_at(v, i, a, ...) _u_vec_at(v, i, u_types_of(a), a, ##__VA_ARGS__)

int _u_vec_remove(u_vec_t v, size_t idx);
#define u_vec_remove(v, i) _u_vec_remove(v, i)

int _u_vec_replace(u_vec_t v, size_t idx, u_types_type_e type, ...);
#define u_vec_replace(v, i, a, ...) _u_vec_replace(v, i, u_types_of(a), a, ##__VA_ARGS__)

u_vec_t _u_vec_copy(u_vec_t v);
#define u_vec_copy(v) _u_vec_copy(v)

u_nullptr_t _u_vec_quote(u_vec_t v, size_t idx);
#define u_vec_quote(v, i, t) ((t)_u_vec_quote(v, i))

#define _CAT(a, b)  _CAT_(a, b)
#define _CAT_(a, b) a##b

#define u_vec_for(v, it, ...)                                                                      \
  for (size_t _CAT(_count_, __LINE__) = 0, _CAT(_len_, __LINE__) = u_vec_len(v);                   \
       _CAT(_count_, __LINE__) < _CAT(_len_, __LINE__) &&                                          \
       !u_vec_at(v, _CAT(_count_, __LINE__), it, ##__VA_ARGS__);                                   \
       _CAT(_count_, __LINE__)++)

#define u_vec_scan(v, p, type)                                                                     \
  for (size_t _CAT(_count_, __LINE__) = 0, _CAT(_len_, __LINE__) = u_vec_len(v);                   \
       _CAT(_count_, __LINE__) < _CAT(_len_, __LINE__) &&                                          \
       ((p) = u_vec_quote(v, _CAT(_count_, __LINE__), type));                                      \
       _CAT(_count_, __LINE__)++)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_VECTOR_H_ */
