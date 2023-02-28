#include <mut.h>
#include <types.h>

mut_test(libu_types_base_type) {
  char t_byte           = 'a';
  u_bool_t t_bool       = true;
  u_i8_t t_i8           = -1;
  u_u8_t t_u8           = 1;
  u_i16_t t_i16         = -1;
  u_u16_t t_u16         = 1;
  u_i32_t t_i32         = -1;
  u_u32_t t_u32         = 1;
  u_i64_t t_i64         = -1;
  u_u64_t t_u64         = 1;
  u_i128_t t_i128       = -1;
  u_u128_t t_u128       = 1;
  u_f32_t t_f32         = 0.1;
  u_f64_t t_f64         = 0.1;
  u_f128_t t_f128       = 0.1;
  u_nullptr_t t_nullptr = &t_nullptr;
  u_any_t t_any         = (u_any_t)&t_any;
  u_c_str_t t_c_str     = "hello libu";

  /* clang-format off */
  mut_equal(U_TYPES_BYTE,    u_types_of(t_byte));
  mut_equal(U_TYPES_BOOL,    u_types_of(t_bool));
  mut_equal(U_TYPES_I8,      u_types_of(t_i8));
  mut_equal(U_TYPES_U8,      u_types_of(t_u8));
  mut_equal(U_TYPES_I16,     u_types_of(t_i16));
  mut_equal(U_TYPES_U16,     u_types_of(t_u16));
  mut_equal(U_TYPES_I32,     u_types_of(t_i32));
  mut_equal(U_TYPES_U32,     u_types_of(t_u32));
  mut_equal(U_TYPES_I64,     u_types_of(t_i64));
  mut_equal(U_TYPES_U64,     u_types_of(t_u64));
  mut_equal(U_TYPES_I128,    u_types_of(t_i128));
  mut_equal(U_TYPES_U128,    u_types_of(t_u128));
  mut_equal(U_TYPES_F32,     u_types_of(t_f32));
  mut_equal(U_TYPES_F64,     u_types_of(t_f64));
  mut_equal(U_TYPES_F128,    u_types_of(t_f128));
  mut_equal(U_TYPES_NULLPTR, u_types_of(t_nullptr));
  mut_equal(U_TYPES_ANY,     u_types_of(t_any));
  mut_equal(U_TYPES_C_STR,   u_types_of(t_c_str));

  mut_equal(U_TYPES_BYTE,    u_types_of(u_byte('3')));
  mut_equal(U_TYPES_BOOL,    u_types_of(u_bool(true)));
  mut_equal(U_TYPES_I8,      u_types_of(u_i8(-1)));
  mut_equal(U_TYPES_U8,      u_types_of(u_u8(1)));
  mut_equal(U_TYPES_I16,     u_types_of(u_i16(-2)));
  mut_equal(U_TYPES_U16,     u_types_of(u_u16(2)));
  mut_equal(U_TYPES_I32,     u_types_of(u_i32(-3)));
  mut_equal(U_TYPES_U32,     u_types_of(u_u32(3)));
  mut_equal(U_TYPES_I64,     u_types_of(u_i64(-4)));
  mut_equal(U_TYPES_U64,     u_types_of(u_u64(4)));
  mut_equal(U_TYPES_I128,    u_types_of(u_i128(-5)));
  mut_equal(U_TYPES_U128,    u_types_of(u_u128(5)));
  mut_equal(U_TYPES_F32,     u_types_of(u_f32(0.1)));
  mut_equal(U_TYPES_F64,     u_types_of(u_f64(0.2)));
  mut_equal(U_TYPES_F128,    u_types_of(u_f128(0.3)));
  mut_equal(U_TYPES_NULLPTR, u_types_of(u_nullptr(NULL)));
  mut_equal(U_TYPES_ANY,     u_types_of(u_any(NULL)));
  mut_equal(U_TYPES_C_STR,   u_types_of(u_c_str("hello libu")));
  /* clang-format on */
}

mut_test(libu_types_advanced_type) {
  u_str_t t_str = u_str_create_from(u_c_str("hello libu"));

  mut_equal(U_TYPES_STR, u_types_of(t_str));

  u_str_free(t_str);
}

mut_group(libu_types) {
  mut_add_test(libu_types_base_type, "test libu base type");
  mut_add_test(libu_types_advanced_type, "test libu advanced type");
}
