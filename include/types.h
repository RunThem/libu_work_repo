/*
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 */

#ifndef _U_TYPES_H_
#define _U_TYPES_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef char u_byte_t;
#define u_byte(v) ((u_byte_t)(v))

typedef _Bool u_bool_t;
#define u_bool(v) ((u_bool_t)(v))

typedef signed char u_i8_t;
typedef signed short u_i16_t;
typedef signed int u_i32_t;
typedef signed long int u_i64_t;
#define u_i8(v)  ((u_i8_t)(v))
#define u_i16(v) ((u_i16_t)(v))
#define u_i32(v) ((u_i32_t)(v))
#define u_i64(v) ((u_i64_t)(v))

typedef unsigned char u_u8_t;
typedef unsigned short u_u16_t;
typedef unsigned int u_u32_t;
typedef unsigned long int u_u64_t;
#define u_u8(v)  ((u_u8_t)(v))
#define u_u16(v) ((u_u16_t)(v))
#define u_u32(v) ((u_u32_t)(v))
#define u_u64(v) ((u_u64_t)(v))

typedef float u_f32_t;
typedef double u_f64_t;
typedef long double u_f128_t;
#define u_f32(v)  ((u_f32_t)(v))
#define u_f64(v)  ((u_f64_t)(v))
#define u_f128(v) ((u_f128_t)(v))

typedef const void* u_nullptr_t;
#define u_nullptr(v) ((u_nullptr_t)(v))

typedef struct {
}* u_any_t;
#define u_any(v) ((u_any_t)(v))

typedef const char* u_c_str_t;
#define u_c_str(v) ((u_c_str_t)(v))

typedef struct {
  char buf[0];
}* u_str_t;
#define u_str(v) ((u_str_t)(v))

typedef struct u_buf* u_buf_t;
#define u_buf(v) ((u_buf_t)(v))

typedef enum {
  U_TYPES_BYTE = 1,
  U_TYPES_BYTE_PTR,
  U_TYPES_BOOL,
  U_TYPES_BOOL_PTR,
  U_TYPES_I8,
  U_TYPES_I8_PTR,
  U_TYPES_U8,
  U_TYPES_U8_PTR,
  U_TYPES_I16,
  U_TYPES_I16_PTR,
  U_TYPES_U16,
  U_TYPES_U16_PTR,
  U_TYPES_I32,
  U_TYPES_I32_PTR,
  U_TYPES_U32,
  U_TYPES_U32_PTR,
  U_TYPES_I64,
  U_TYPES_I64_PTR,
  U_TYPES_U64,
  U_TYPES_U64_PTR,
  U_TYPES_F32,
  U_TYPES_F32_PTR,
  U_TYPES_F64,
  U_TYPES_F64_PTR,
  U_TYPES_F128,
  U_TYPES_F128_PTR,

  U_TYPES_NULLPTR,
  U_TYPES_ANY,

  U_TYPES_C_STR,

  U_TYPES_STR,
  U_TYPES_BUF,

  U_TYPES_NONE = 127,
} u_types_type_e;

typedef struct {
  u_types_type_e type;

  union {
    u_u64_t i;
    u_f128_t f;
    u_nullptr_t p;
  };
} u_types_arg_t;

/* clang-format off */
#define u_types_of(expr) _Generic((expr),                                                          \
u_byte_t      : U_TYPES_BYTE,                                                                      \
u_byte_t*     : U_TYPES_BYTE_PTR,                                                                  \
u_bool_t      : U_TYPES_BOOL,                                                                      \
u_bool_t*     : U_TYPES_BOOL_PTR,                                                                  \
u_i8_t        : U_TYPES_I8,                                                                        \
u_i8_t*       : U_TYPES_I8_PTR,                                                                    \
u_u8_t        : U_TYPES_U8,                                                                        \
u_u8_t*       : U_TYPES_U8_PTR,                                                                    \
u_i16_t       : U_TYPES_I16,                                                                       \
u_i16_t*      : U_TYPES_I16_PTR,                                                                   \
u_u16_t       : U_TYPES_U16,                                                                       \
u_u16_t*      : U_TYPES_U16_PTR,                                                                   \
u_i32_t       : U_TYPES_I32,                                                                       \
u_i32_t*      : U_TYPES_I32_PTR,                                                                   \
u_u32_t       : U_TYPES_U32,                                                                       \
u_u32_t*      : U_TYPES_U32_PTR,                                                                   \
u_i64_t       : U_TYPES_I64,                                                                       \
u_i64_t*      : U_TYPES_I64_PTR,                                                                   \
u_u64_t       : U_TYPES_U64,                                                                       \
u_u64_t*      : U_TYPES_U64_PTR,                                                                   \
u_f32_t       : U_TYPES_F32,                                                                       \
u_f32_t*      : U_TYPES_F32_PTR,                                                                   \
u_f64_t       : U_TYPES_F64,                                                                       \
u_f64_t*      : U_TYPES_F64_PTR,                                                                   \
u_f128_t      : U_TYPES_F128,                                                                      \
u_f128_t*     : U_TYPES_F128_PTR,                                                                  \
                                                                                                   \
u_nullptr_t  : U_TYPES_NULLPTR,                                                                    \
u_any_t      : U_TYPES_ANY,                                                                        \
                                                                                                   \
u_c_str_t    : U_TYPES_C_STR,                                                                      \
                                                                                                   \
u_str_t      : U_TYPES_STR,                                                                        \
u_buf_t      : U_TYPES_BUF,                                                                        \
                                                                                                   \
default      : U_TYPES_NONE)
/* clang-format on */

u_nullptr_t u_types_parse(u_types_arg_t* arg, va_list ap, size_t* size);
void u_types_print(u_types_arg_t* arg, FILE* out);
u_bool_t u_types_equal(u_types_arg_t* arg, u_types_arg_t* _arg);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _U_TYPES_H_ */
