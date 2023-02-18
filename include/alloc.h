/*
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 */

#ifndef _U_MEMORY_H_
#define _U_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

void u_alloc_set_malloc(u_nullptr_t (*f_malloc)(size_t));
void u_alloc_set_calloc(u_nullptr_t (*f_calloc)(size_t, size_t));
void u_alloc_set_realloc(u_nullptr_t (*f_realloc)(u_nullptr_t, size_t));
void u_alloc_set_free(void (*f_free)(u_nullptr_t));

u_nullptr_t u_malloc(size_t sz);
u_nullptr_t u_calloc(size_t cnt, size_t sz);
u_nullptr_t u_zalloc(size_t sz);
u_nullptr_t u_realloc(u_nullptr_t ptr, size_t sz);
void u_free(u_nullptr_t ptr);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_MEMORY_H_ */
