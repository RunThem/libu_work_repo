#include <mut.h>
#include <str.h>
#include <types.h>

void test_types(__mut_result_t* result,
                u_types_type_e _type,
                size_t _size,
                u_types_type_e type,
                ...) {
  va_list ap;
  size_t size       = 0;
  u_types_arg_t arg = {0};

  arg.type = type;
  va_start(ap, type);
  u_types_parse(&arg, ap, &size);

  mut_equal(_type, type);
  mut_equal(_size, size);

  printf("type is %-2d, size is %-4ld, value is ", type, size);
  u_types_print(&arg, stdout);
  printf("\n");
}

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
  u_f32_t t_f32         = 0.1f;
  u_f64_t t_f64         = 0.1;
  u_f128_t t_f128       = 0.1;
  u_nullptr_t t_nullptr = &t_nullptr;
  u_any_t t_any         = (u_any_t)&t_any;
  u_c_str_t t_c_str     = "hello libu";

  /* clang-format off */
  mut_equal(U_TYPES_BYTE,     u_types_of(t_byte));
  mut_equal(U_TYPES_BOOL,     u_types_of(t_bool));
  mut_equal(U_TYPES_I8,       u_types_of(t_i8));
  mut_equal(U_TYPES_U8,       u_types_of(t_u8));
  mut_equal(U_TYPES_I16,      u_types_of(t_i16));
  mut_equal(U_TYPES_U16,      u_types_of(t_u16));
  mut_equal(U_TYPES_I32,      u_types_of(t_i32));
  mut_equal(U_TYPES_U32,      u_types_of(t_u32));
  mut_equal(U_TYPES_I64,      u_types_of(t_i64));
  mut_equal(U_TYPES_U64,      u_types_of(t_u64));
  mut_equal(U_TYPES_F32,      u_types_of(t_f32));
  mut_equal(U_TYPES_F64,      u_types_of(t_f64));
  mut_equal(U_TYPES_F128,     u_types_of(t_f128));

  mut_equal(U_TYPES_BYTE,     u_types_of(u_byte('3')));
  mut_equal(U_TYPES_BOOL,     u_types_of(u_bool(true)));
  mut_equal(U_TYPES_I8,       u_types_of(u_i8(-1)));
  mut_equal(U_TYPES_U8,       u_types_of(u_u8(1)));
  mut_equal(U_TYPES_I16,      u_types_of(u_i16(-2)));
  mut_equal(U_TYPES_U16,      u_types_of(u_u16(2)));
  mut_equal(U_TYPES_I32,      u_types_of(u_i32(-3)));
  mut_equal(U_TYPES_U32,      u_types_of(u_u32(3)));
  mut_equal(U_TYPES_I64,      u_types_of(u_i64(-4)));
  mut_equal(U_TYPES_U64,      u_types_of(u_u64(4)));
  mut_equal(U_TYPES_F32,      u_types_of(u_f32(0.1)));
  mut_equal(U_TYPES_F64,      u_types_of(u_f64(0.2)));
  mut_equal(U_TYPES_F128,     u_types_of(u_f128(0.3)));

  mut_equal(U_TYPES_BYTE_PTR, u_types_of(&t_byte));
  mut_equal(U_TYPES_BOOL_PTR, u_types_of(&t_bool));
  mut_equal(U_TYPES_I8_PTR,   u_types_of(&t_i8));
  mut_equal(U_TYPES_U8_PTR,   u_types_of(&t_u8));
  mut_equal(U_TYPES_I16_PTR,  u_types_of(&t_i16));
  mut_equal(U_TYPES_U16_PTR,  u_types_of(&t_u16));
  mut_equal(U_TYPES_I32_PTR,  u_types_of(&t_i32));
  mut_equal(U_TYPES_U32_PTR,  u_types_of(&t_u32));
  mut_equal(U_TYPES_I64_PTR,  u_types_of(&t_i64));
  mut_equal(U_TYPES_U64_PTR,  u_types_of(&t_u64));
  mut_equal(U_TYPES_F32_PTR,  u_types_of(&t_f32));
  mut_equal(U_TYPES_F64_PTR,  u_types_of(&t_f64));
  mut_equal(U_TYPES_F128_PTR, u_types_of(&t_f128));

  mut_equal(U_TYPES_NULLPTR,  u_types_of(t_nullptr));
  mut_equal(U_TYPES_ANY,      u_types_of(t_any));
  mut_equal(U_TYPES_NULLPTR,  u_types_of(u_nullptr(NULL)));
  mut_equal(U_TYPES_ANY,      u_types_of(u_any(NULL)));

  mut_equal(U_TYPES_C_STR,    u_types_of(t_c_str));
  mut_equal(U_TYPES_C_STR,    u_types_of(u_c_str("hello libu")));

  /* clang-format on */
#define test_types_func(t, s, v, ...)                                                              \
  do {                                                                                             \
    printf("line %d ", __LINE__);                                                                  \
    test_types(result, t, s, u_types_of(v), v, ##__VA_ARGS__);                                     \
  } while (0)

  test_types_func(U_TYPES_BYTE, 1, u_byte('3'));
  test_types_func(U_TYPES_BOOL, 1, u_bool(true));
  test_types_func(U_TYPES_I8, 1, u_i8(-1));
  test_types_func(U_TYPES_U8, 1, u_u8(1));
  test_types_func(U_TYPES_I16, 2, u_i16(-2));
  test_types_func(U_TYPES_U16, 2, u_u16(2));
  test_types_func(U_TYPES_I32, 4, u_i32(-3));
  test_types_func(U_TYPES_U32, 4, u_u32(3));
  test_types_func(U_TYPES_I64, 8, u_i64(-4));
  test_types_func(U_TYPES_U64, 8, u_u64(4));
  test_types_func(U_TYPES_F32, 4, u_f32(0.1));
  test_types_func(U_TYPES_F64, 8, u_f64(0.2));
  test_types_func(U_TYPES_F128, 16, u_f128(0.3));

  test_types_func(U_TYPES_BYTE_PTR, 8, &t_byte);
  test_types_func(U_TYPES_BOOL_PTR, 8, &t_bool);
  test_types_func(U_TYPES_I8_PTR, 8, &t_i8);
  test_types_func(U_TYPES_U8_PTR, 8, &t_u8);
  test_types_func(U_TYPES_I16_PTR, 8, &t_i16);
  test_types_func(U_TYPES_U16_PTR, 8, &t_u16);
  test_types_func(U_TYPES_I32_PTR, 8, &t_i32);
  test_types_func(U_TYPES_U32_PTR, 8, &t_u32);
  test_types_func(U_TYPES_I64_PTR, 8, &t_i64);
  test_types_func(U_TYPES_U64_PTR, 8, &t_u64);
  test_types_func(U_TYPES_F32_PTR, 8, &t_f32);
  test_types_func(U_TYPES_F64_PTR, 8, &t_f64);
  test_types_func(U_TYPES_F128_PTR, 8, &t_f128);

  test_types_func(U_TYPES_NULLPTR, 8, t_nullptr);
  test_types_func(U_TYPES_ANY, 1024, t_any, 1024);

  test_types_func(U_TYPES_C_STR, strlen(t_c_str), t_c_str);

  mut_equal(32, sizeof(u_types_arg_t));
}

mut_test(libu_types_advanced_type) {
  u_str_t t_str = u_str_create_from(u_c_str("hello libu"));

  mut_equal(U_TYPES_STR, u_types_of(t_str));

  u_str_clean(t_str);
}

mut_group(libu_types) {
  mut_add_test(libu_types_base_type, "test libu base type");
  mut_add_test(libu_types_advanced_type, "test libu advanced type");
}
