/*
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 */

#include <str.h>
#include <string.h>
#include <types.h>

u_nullptr_t u_types_parse(u_types_arg_t* arg, va_list ap, size_t* size) {
  switch (arg->type) {
    case U_TYPES_BYTE:
      arg->i = (u_byte_t)va_arg(ap, u_i32_t);
      *size  = sizeof(u_byte_t);
      return &arg->i;
    case U_TYPES_BOOL:
      arg->i = (u_bool_t)va_arg(ap, u_i32_t);
      *size  = sizeof(u_bool_t);
      return &arg->i;
    case U_TYPES_I8:
      arg->i = (u_i8_t)va_arg(ap, u_i32_t);
      *size  = sizeof(u_i8_t);
      return &arg->i;
    case U_TYPES_U8:
      arg->i = (u_u8_t)va_arg(ap, u_u32_t);
      *size  = sizeof(u_u8_t);
      return &arg->i;
    case U_TYPES_I16:
      arg->i = (u_i16_t)va_arg(ap, u_i32_t);
      *size  = sizeof(u_i16_t);
      return &arg->i;
    case U_TYPES_U16:
      arg->i = (u_u16_t)va_arg(ap, u_u32_t);
      *size  = sizeof(u_u16_t);
      return &arg->i;
    case U_TYPES_I32:
      arg->i = (u_i32_t)va_arg(ap, u_i32_t);
      *size  = sizeof(u_i32_t);
      return &arg->i;
    case U_TYPES_U32:
      arg->i = (u_u32_t)va_arg(ap, u_u32_t);
      *size  = sizeof(u_u32_t);
      return &arg->i;
    case U_TYPES_I64:
      arg->i = (u_i64_t)va_arg(ap, u_i64_t);
      *size  = sizeof(u_i64_t);
      return &arg->i;
    case U_TYPES_U64:
      arg->i = (u_u64_t)va_arg(ap, u_u64_t);
      *size  = sizeof(u_u64_t);
      return &arg->i;
    case U_TYPES_F32:
      arg->f = (u_f32_t)va_arg(ap, u_f64_t);
      *size  = sizeof(u_f32_t);
      return &arg->f;
    case U_TYPES_F64:
      arg->f = (u_f64_t)va_arg(ap, u_f64_t);
      *size  = sizeof(u_f64_t);
      return &arg->f;
    case U_TYPES_F128:
      arg->f = (u_f128_t)va_arg(ap, u_f128_t);
      *size  = sizeof(u_f128_t);
      return &arg->f;

    case U_TYPES_BYTE_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_byte_t);
      return arg->p;
    case U_TYPES_BOOL_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_bool_t);
      return arg->p;
    case U_TYPES_I8_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_i8_t);
      return arg->p;
    case U_TYPES_U8_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_u8_t);
      return arg->p;
    case U_TYPES_I16_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_i16_t);
      return arg->p;
    case U_TYPES_U16_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_u16_t);
      return arg->p;
    case U_TYPES_I32_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_i32_t);
      return arg->p;
    case U_TYPES_U32_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_u32_t);
      return arg->p;
    case U_TYPES_I64_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_i64_t);
      return arg->p;
    case U_TYPES_U64_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_u64_t);
      return arg->p;
    case U_TYPES_F32_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_f32_t);
      return arg->p;
    case U_TYPES_F64_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_f64_t);
      return arg->p;
    case U_TYPES_F128_PTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_f128_t);
      return arg->p;
    case U_TYPES_NULLPTR:
      arg->p = (u_nullptr_t)va_arg(ap, u_nullptr_t);
      *size  = sizeof(u_nullptr_t);
      return arg->p;

    case U_TYPES_ANY:
      arg->p = (u_any_t)va_arg(ap, u_any_t);
      *size  = (size_t)va_arg(ap, size_t);
      return arg->p;

    case U_TYPES_C_STR:
      arg->p = (u_c_str_t)va_arg(ap, u_c_str_t);
      *size  = strlen(arg->p);
      return arg->p;

    case U_TYPES_STR:
      arg->p = (u_str_t)va_arg(ap, u_str_t);
      *size  = u_str_len(u_str(arg->p));
      return arg->p;

    case U_TYPES_NONE:
    default:
      return NULL;
  }
}

void u_types_print(u_types_arg_t* arg, FILE* out) {
  switch (arg->type) {
    case U_TYPES_BYTE:
      fprintf(out, "\'%c\'", u_byte(arg->i));
      break;
    case U_TYPES_BOOL:
      fprintf(out, "%s", arg->i != 0 ? "true" : "false");
      break;
    case U_TYPES_I8:
    case U_TYPES_I16:
    case U_TYPES_I32:
    case U_TYPES_I64:
      fprintf(out, "%ld", u_i64(arg->i));
      break;
    case U_TYPES_U8:
    case U_TYPES_U16:
    case U_TYPES_U32:
    case U_TYPES_U64:
      fprintf(out, "%lu", arg->i);
      break;
    case U_TYPES_F32:
    case U_TYPES_F64:
    case U_TYPES_F128:
      fprintf(out, "%Lf", arg->f);
      break;
    case U_TYPES_BYTE_PTR:
    case U_TYPES_BOOL_PTR:
    case U_TYPES_I8_PTR:
    case U_TYPES_U8_PTR:
    case U_TYPES_I16_PTR:
    case U_TYPES_U16_PTR:
    case U_TYPES_I32_PTR:
    case U_TYPES_U32_PTR:
    case U_TYPES_I64_PTR:
    case U_TYPES_U64_PTR:
    case U_TYPES_F32_PTR:
    case U_TYPES_F64_PTR:
    case U_TYPES_F128_PTR:
    case U_TYPES_NULLPTR:
    case U_TYPES_ANY:
      fprintf(out, "%p", arg->p);
      break;
    case U_TYPES_C_STR:
      fprintf(out, "\"%s\"", u_c_str(arg->p));
      break;
    case U_TYPES_STR:
      fprintf(out, "\"%s\"", u_str(arg->p)->buf);
      break;
    case U_TYPES_NONE:
    default:
      break;
  }
}

u_bool_t u_types_equal(u_types_arg_t* arg, u_types_arg_t* _arg) {
  if (arg->type != _arg->type) {
    return false;
  }

  switch (arg->type) {
    case U_TYPES_BYTE:
    case U_TYPES_BOOL:
    case U_TYPES_I8:
    case U_TYPES_I16:
    case U_TYPES_I32:
    case U_TYPES_I64:
    case U_TYPES_U8:
    case U_TYPES_U16:
    case U_TYPES_U32:
    case U_TYPES_U64:
      return arg->i == _arg->i;
      break;
    case U_TYPES_F32:
    case U_TYPES_F64:
    case U_TYPES_F128:
      /* TODO: float number equal? */
      return false;
    case U_TYPES_BYTE_PTR:
    case U_TYPES_BOOL_PTR:
    case U_TYPES_I8_PTR:
    case U_TYPES_U8_PTR:
    case U_TYPES_I16_PTR:
    case U_TYPES_U16_PTR:
    case U_TYPES_I32_PTR:
    case U_TYPES_U32_PTR:
    case U_TYPES_I64_PTR:
    case U_TYPES_U64_PTR:
    case U_TYPES_F32_PTR:
    case U_TYPES_F64_PTR:
    case U_TYPES_F128_PTR:
    case U_TYPES_NULLPTR:
    case U_TYPES_ANY:
      return arg->p == _arg->p;
    case U_TYPES_C_STR:
      return strcmp(arg->p, _arg->p);
    case U_TYPES_STR:
      return strncmp(arg->p, _arg->p, u_str_len(u_str(arg->p)));
    case U_TYPES_NONE:
    default:
      break;
  }
}
