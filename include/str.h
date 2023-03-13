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

u_str_t _u_str_create(size_t size);
#define u_str_create(s) _u_str_create(s)

u_str_t _u_str_create_from(u_c_str_t c_str);
#define u_str_create_from(s) _u_str_create_from(s)

int _u_str_resize(u_str_t* s, size_t size);
#define u_str_resize(s, ss) _u_str_resize(&s, ss)

void _u_str_clean(u_str_t s);
#define u_str_clean(s) _u_str_clean(s)

size_t _u_str_len(u_str_t s);
#define u_str_len(s) _u_str_len(s)

size_t _u_str_alloc(u_str_t s);
#define u_str_alloc(s) _u_str_alloc(s)

size_t _u_str_free(u_str_t s);
#define u_str_free(s) _u_str_free(s)

u_bool_t _u_str_empty(u_str_t s);
#define u_str_empty(s) _u_str_empty(s)

int _u_str_cat(u_str_t* s, u_types_type_e type, ...);
#define u_str_cat(s, v) _u_str_cat(s, u_types_of(v), v)

int _u_str_insert(u_str_t* s, size_t idx, u_types_type_e type, ...);
#define u_str_insert(s, i, v) _u_str_insert(s, i, u_types_of(v), v)

char _u_str_at(u_str_t s, size_t idx);
#define u_str_at(s, i) _u_str_at(s, i)

int _u_str_remove(u_str_t s, size_t idx, size_t itsize);
#define u_str_remove(s, i, is) _u_str_remove(s, i, is)

u_c_str_t _u_str_cstr(u_str_t s);
#define u_str_cstr(s) _u_str_cstr(s)

u_str_t _u_str_copy(u_str_t s);
#define u_str_copy(s) _u_str_copy(s)

u_bool_t _u_str_compare(u_str_t s, u_types_type_e type, ...);
#define u_str_compare(s, v) _u_str_compare(s, u_types_of(v), v)

u_bool_t _u_str_contains(u_str_t s, u_types_type_e type, ...);
#define u_str_contains(s, v) _u_str_contains(s, u_types_of(v), v)

u_bool_t _u_str_prefix(u_str_t s, u_types_type_e type, ...);
#define u_str_prefix(s, v) _u_str_prefix(s, u_types_of(v), v)

u_bool_t _u_str_suffix(u_str_t s, u_types_type_e type, ...);
#define u_str_suffix(s, v) _u_str_suffix(s, u_types_of(v), v)

ssize_t _u_str_index(u_str_t s, u_types_type_e type, ...);
#define u_str_index(s, v) _u_str_index(s, u_types_of(v), v)

int _u_str_replace(u_str_t* s, u_types_type_e type_1, u_types_type_e type_2, ...);
#define u_str_replace(s, o, n) _u_str_replace(s, u_types_of(o), u_types_of(n), o, n)

#define u_str_for(s, ch)                                                                           \
  for (size_t i = 0, _len = u_str_len(s); i < _len && (ch = u_str_at(s, i)); i++)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_STRING_H_ */
