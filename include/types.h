/*
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 */

#ifndef _U_TYPES_H_
#define _U_TYPES_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

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
typedef __int128_t u_i128_t;
#define u_i8(v)   ((u_i8_t)(v))
#define u_i16(v)  ((u_i16_t)(v))
#define u_i32(v)  ((u_i32_t)(v))
#define u_i64(v)  ((u_i64_t)(v))
#define u_i128(v) ((u_i128_t)(v))

typedef unsigned char u_u8_t;
typedef unsigned short u_u16_t;
typedef unsigned int u_u32_t;
typedef unsigned long int u_u64_t;
typedef __uint128_t u_u128_t;
#define u_u8(v)   ((u_u8_t)(v))
#define u_u16(v)  ((u_u16_t)(v))
#define u_u32(v)  ((u_u32_t)(v))
#define u_u64(v)  ((u_u64_t)(v))
#define u_u128(v) ((u_u128_t)(v))

typedef float u_f32_t;
typedef double u_f64_t;
typedef long double u_f128_t;
#define u_f32(v)  ((u_f32_t)(v))
#define u_f64(v)  ((u_f64_t)(v))
#define u_f128(v) ((u_f128_t)(v))

typedef void* u_nullptr_t;
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

typedef enum {
  U_TYPES_BYTE = 1,
  U_TYPES_BOOL,
  U_TYPES_I8,
  U_TYPES_U8,
  U_TYPES_I16,
  U_TYPES_U16,
  U_TYPES_I32,
  U_TYPES_U32,
  U_TYPES_I64,
  U_TYPES_U64,
  U_TYPES_I128,
  U_TYPES_U128,
  U_TYPES_F32,
  U_TYPES_F64,
  U_TYPES_F128,
  U_TYPES_NULLPTR,
  U_TYPES_ANY,
  U_TYPES_C_STR,

  U_TYPES_STR,

  U_TYPES_NONE = 127,
} u_types_type_e;

typedef struct {
  u_types_type_e type;

  union {
    u_byte_t t_byte;
    u_bool_t t_bool;
    u_i8_t t_i8;
    u_u8_t t_u8;
    u_i16_t t_i16;
    u_u16_t t_u16;
    u_i32_t t_i32;
    u_u32_t t_u32;
    u_i64_t t_i64;
    u_u64_t t_u64;
    u_i128_t t_i128;
    u_u128_t t_u128;
    u_f32_t t_f32;
    u_f64_t t_f64;
    u_f128_t t_f128;
    u_nullptr_t t_nullptr;
    u_any_t t_any;
    u_c_str_t t_c_str;

    u_str_t t_str;
  };
} u_types_arg_t;

/* clang-format off */
#define u_types_of(expr) _Generic((expr),                                                          \
u_byte_t     : U_TYPES_BYTE,                                                                       \
u_bool_t     : U_TYPES_BOOL,                                                                       \
u_i8_t       : U_TYPES_I8,                                                                         \
u_u8_t       : U_TYPES_U8,                                                                         \
u_i16_t      : U_TYPES_I16,                                                                        \
u_u16_t      : U_TYPES_U16,                                                                        \
u_i32_t      : U_TYPES_I32,                                                                        \
u_u32_t      : U_TYPES_U32,                                                                        \
u_i64_t      : U_TYPES_I64,                                                                        \
u_u64_t      : U_TYPES_U64,                                                                        \
u_i128_t     : U_TYPES_I128,                                                                       \
u_u128_t     : U_TYPES_U128,                                                                       \
u_f32_t      : U_TYPES_F32,                                                                        \
u_f64_t      : U_TYPES_F64,                                                                        \
u_f128_t     : U_TYPES_F128,                                                                       \
u_nullptr_t  : U_TYPES_NULLPTR,                                                                    \
u_any_t      : U_TYPES_ANY,                                                                        \
u_c_str_t    : U_TYPES_C_STR,                                                                      \
                                                                                                   \
u_str_t      : U_TYPES_STR,                                                                        \
                                                                                                   \
default      : U_TYPES_NONE)
/* clang-format on */

const u_nullptr_t u_types_parse(u_types_arg_t* arg, va_list ap);

//#define u_types_parse(p, t, a)                                                                     \
//  do {                                                                                             \
//    va_list _ap;                                                                                   \
//    va_start(_ap, t);                                                                              \
//    (a).type = (t);                                                                                \
//    (p)      = _u_types_parse(&(a), _ap);                                                          \
//    va_end(_ap);                                                                                   \
//  } while (0)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _U_TYPES_H_ */
