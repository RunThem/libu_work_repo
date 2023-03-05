/*
 * Copyright (c) 2005-2012 by KoanLogic s.r.l. - All rights reserved.
 */

#ifndef _U_STRING_H_
#define _U_STRING_H_

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef U_STR_DEFAULT_LENGTH
#  define U_STR_DEFAULT_LENGTH 16
#endif /* !U_STR_DEFAULT_LENGTH */

u_str_t u_str_create(size_t size);
u_str_t u_str_create_from(u_c_str_t c_str);
void u_str_clean(u_str_t s);

size_t u_str_len(u_str_t s);
size_t u_str_alloc(u_str_t s);
size_t u_str_free(u_str_t s);

int u_str_resize(u_str_t* s, size_t size);

int _u_str_cat(u_str_t* s, u_types_type_e type, ...);
#define u_str_cat(s, v) _u_str_cat(s, u_types_of(v), v)

u_str_t u_str_copy(u_str_t s);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_STRING_H_ */
