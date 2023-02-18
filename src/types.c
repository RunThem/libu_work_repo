/*
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 */

#include <types.h>

const void* u_types_parse_(u_types_arg_t* arg, va_list ap) {
  switch (arg->type) {
    case U_TYPES_BYTE:
      arg->t_byte = (char)va_arg(ap, int);
      return &arg->t_byte;
    case U_TYPES_BOOL:
      arg->t_bool = (u_bool_t)va_arg(ap, int);
      return &arg->type;
    case U_TYPES_I8:
      arg->t_i8 = (u_i8_t)va_arg(ap, int);
      return &arg->t_i8;
    case U_TYPES_U8:
      arg->t_u8 = (u_u8_t)va_arg(ap, unsigned int);
      return &arg->t_u8;
    case U_TYPES_I16:
      arg->t_i16 = (u_i16_t)va_arg(ap, signed int);
      return &arg->t_i16;
    case U_TYPES_U16:
      arg->t_u16 = (u_u16_t)va_arg(ap, unsigned int);
      return &arg->t_u16;
    case U_TYPES_I32:
      arg->t_i32 = (u_i32_t)va_arg(ap, signed int);
      return &arg->t_i32;
    case U_TYPES_U32:
      arg->t_u32 = (u_u32_t)va_arg(ap, unsigned int);
      return &arg->t_u32;
    case U_TYPES_I64:
      arg->t_i64 = (u_i64_t)va_arg(ap, signed long int);
      return &arg->t_i64;
    case U_TYPES_U64:
      arg->t_u64 = (u_u64_t)va_arg(ap, unsigned long int);
      return &arg->t_u64;
    case U_TYPES_I128:
      arg->t_i128 = (u_i128_t)va_arg(ap, __int128_t);
      return &arg->t_i128;
    case U_TYPES_U128:
      arg->t_u128 = (u_u128_t)va_arg(ap, __uint128_t);
      return &arg->t_u128;
    case U_TYPES_F32:
      arg->t_f32 = (u_f32_t)va_arg(ap, double);
      return &arg->t_f32;
    case U_TYPES_F64:
      arg->t_f64 = (u_f64_t)va_arg(ap, double);
      return &arg->t_f64;
    case U_TYPES_F128:
      arg->t_f128 = (u_f128_t)va_arg(ap, long double);
      return &arg->t_f128;
    case U_TYPES_CSTR:
      arg->t_cstr = (u_cstr_t)va_arg(ap, char*);
      return &arg->t_cstr;
    case U_TYPES_NULLPTR:
      arg->t_nullptr = (u_nullptr_t)va_arg(ap, void*);
      return &arg->t_nullptr;
    case U_TYPES_ANY:
      arg->t_any = (u_any_t)va_arg(ap, u_any_t);
      return arg->t_any;
    case U_TYPES_NONE:
    default:
      return NULL;
  }
}
