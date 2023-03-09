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

u_buf_t u_buf_create(size_t size);
int u_buf_resize(u_buf_t* b, size_t size);
void u_buf_clean(u_buf_t b);

size_t u_buf_len(u_buf_t b);
size_t u_buf_alloc(u_buf_t b);
size_t u_buf_free(u_buf_t b);

int _u_buf_push(u_buf_t* b, u_types_type_e type, ...);
#define u_buf_push(b, v, ...) _u_buf_push(b, u_types_of(v), v, ##__VA_ARGS__)

int _u_buf_pop(u_buf_t b, u_types_type_e type, ...);
#define u_buf_pop(b, v, ...) _u_buf_pop(b, u_types_of(v), v, ##__VA_ARGS__)

int _u_buf_insert(u_buf_t* b, size_t idx, u_types_type_e type, ...);
#define u_buf_insert(b, i, v, ...) _u_buf_insert(b, i, u_types_of(v), v, ##__VA_ARGS__)

int _u_buf_at(u_buf_t b, size_t idx, u_types_type_e type, ...);
#define u_buf_at(b, i, v, ...) _u_buf_at(b, i, u_types_of(v), v, ##__VA_ARGS__)

int u_buf_remove(u_buf_t b, size_t idx, size_t itsize);

u_buf_t u_buf_copy(u_buf_t b);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_BUFFER_H_ */
