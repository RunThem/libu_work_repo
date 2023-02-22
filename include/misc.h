/*
 * Copyright (c) 2005-2012 by KoanLogic s.r.l. - All rights reserved.
 */

#ifndef _U_MISC_H_
#define _U_MISC_H_

#include <stddef.h>
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define container_of(ptr, type, member) ((type*)(((u_u8_t*)(ptr)) - (offsetof(type, member))))
#define align_of(addr, size)            (((addr) + (size)-1) & (~((size)-1)))

u_u64_t u_misc_align_2pow(u_u64_t n);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_U_MISC_H_ */
