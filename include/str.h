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

typedef const char* u_c_str_t;
typedef char* u_str_t;
#define u_c_str(v) ((u_c_str_t)(v))
#define u_str(v)   ((u_str_t)(v))

u_str_t u_str_create(size_t s);
u_str_t u_str_create_from(u_c_str_t s);
int u_str_init(u_str_t* s);
int u_str_init_from(u_str_t* s, u_c_str_t str);

void u_str_free(u_str_t s);

size_t u_str_len(u_str_t s);

size_t u_str_alloc(u_str_t s);

int u_str_resize(u_str_t* s, size_t size);
int u_str_cat(u_str_t* s, u_str_t s1);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_STRING_H_ */
