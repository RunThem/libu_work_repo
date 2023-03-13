/**
 * Created by iccy on 23-3-5.
 */

#ifndef _U_BUFFER_H_
#define _U_BUFFER_H_

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef U_BUF_DEFAULT_LENGTH
#  define U_BUF_DEFAULT_LENGTH 16
#endif /* !U_BUF_DEFAULT_LENGTH */

u_buf_t _u_buf_create(size_t size);
#define u_buf_create(s) _u_buf_create(s)

int _u_buf_resize(u_buf_t* b, size_t size);
#define u_buf_resize(b, ss) _u_buf_resize(&b, ss)

void _u_buf_clean(u_buf_t b);
#define u_buf_clean(b) _u_buf_clean(b)

size_t _u_buf_len(u_buf_t b);
#define u_buf_len(b) _u_buf_len(b)

size_t _u_buf_alloc(u_buf_t b);
#define u_buf_alloc(b) _u_buf_alloc(b)

size_t _u_buf_free(u_buf_t b);
#define u_buf_free(b) _u_buf_free(b)

u_bool_t _u_buf_empty(u_buf_t b);
#define u_buf_empty(b) _u_buf_empty(b)

int _u_buf_push(u_buf_t* b, u_types_type_e type, ...);
#define u_buf_push(b, v, ...) _u_buf_push(b, u_types_of(v), v, ##__VA_ARGS__)

int _u_buf_pop(u_buf_t b, u_types_type_e type, ...);
#define u_buf_pop(b, v, ...) _u_buf_pop(b, u_types_of(v), v, ##__VA_ARGS__)

int _u_buf_insert(u_buf_t* b, size_t idx, u_types_type_e type, ...);
#define u_buf_insert(b, i, v, ...) _u_buf_insert(b, i, u_types_of(v), v, ##__VA_ARGS__)

int _u_buf_at(u_buf_t b, size_t idx, u_types_type_e type, ...);
#define u_buf_at(b, i, v, ...) _u_buf_at(b, i, u_types_of(v), v, ##__VA_ARGS__)

int _u_buf_remove(u_buf_t b, size_t idx, size_t itsize);
#define u_buf_remove(b) _u_buf_remove(b)

u_buf_t _u_buf_copy(u_buf_t b);
#define u_buf_copy(b) _u_buf_copy(b)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_BUFFER_H_ */
