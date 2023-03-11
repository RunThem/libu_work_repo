/*
 * Copyright (c) 2005-2012 by KoanLogic s.r.l. - All rights reserved.
 */

#ifndef _U_STRING_H_
#define _U_STRING_H_

#include <stddef.h>
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef U_STR_DEFAULT_LENGTH
#  define U_STR_DEFAULT_LENGTH 16
#endif /* !U_STR_DEFAULT_LENGTH */

u_str_t u_str_create(size_t size);
u_str_t u_str_create_from(u_c_str_t c_str);
int u_str_resize(u_str_t* s, size_t size);
void u_str_clean(u_str_t s);

size_t u_str_len(u_str_t s);
size_t u_str_alloc(u_str_t s);
size_t u_str_free(u_str_t s);
u_bool_t u_str_empty(u_str_t s);

int _u_str_cat(u_str_t* s, u_types_type_e type, ...);
#define u_str_cat(s, v) _u_str_cat(s, u_types_of(v), v)

int _u_str_insert(u_str_t* s, size_t idx, u_types_type_e type, ...);
#define u_str_insert(s, i, v) _u_str_insert(s, i, u_types_of(v), v)

char u_str_at(u_str_t s, size_t idx);

int u_str_remove(u_str_t s, size_t idx, size_t itsize);

u_c_str_t u_str_cstr(u_str_t s);

u_str_t u_str_copy(u_str_t s);

u_bool_t _u_str_compare(u_str_t s, u_types_type_e type, ...);
#define u_str_compare(s, v) _u_str_compare(s, u_types_of(v), v)

#define u_str_for(s, ch)                                                                           \
  for (size_t i = 0, _len = u_str_len(s); i < _len && (ch = u_str_at(s, i)); i++)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_STRING_H_ */
