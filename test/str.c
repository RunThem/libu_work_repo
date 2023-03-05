/**
 * Created by iccy on 23-3-5.
 */
#include <mut.h>
#include <str.h>

mut_test(libu_str_create) {
  u_str_t str = NULL;

  struct {
    int n;
    int m;
  } tbl[] = {
      {16,   0   },
      {16,   3   },
      {16,   7   },
      {16,   10  },
      {100,  100 },
      {129,  129 },
      {1025, 1025},
  };
  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    str = u_str_create(tbl[i].m);

    mut_assert(str != NULL);

    mut_equal(0, u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(u_str_alloc(str) - u_str_len(str), u_str_free(str));
    u_str_clean(str);
  }
}

mut_test(libu_str_create_from) {
  u_str_t str = NULL;

  struct {
    int n;
    char* str;
  } tbl[] = {
      {16, "a"                                    },
      {16, "ab"                                   },
      {16, "abc"                                  },
      {16, "0123456789012345"                     },
      {32, "01234567890123456789"                 },
      {32, "01234567890123456789012345678901"     },
      {64, "0123456789012345678901234567890123456"},
  };

  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    str = u_str_create_from(tbl[i].str);

    mut_assert(str != NULL);

    mut_equal(strlen(tbl[i].str), u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(u_str_alloc(str) - strlen(tbl[i].str), u_str_free(str));

    mut_equal(tbl[i].str, str->buf);
    u_str_clean(str);
  }
}

mut_test(libu_str_resize) {
  u_str_t str = NULL;

  struct {
    int n;
    int m;
  } tbl[] = {
      {33,   0   },
      {33,   3   },
      {33,   7   },
      {33,   10  },
      {201,  100 },
      {259,  129 },
      {2051, 1025},
  };

  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    str = u_str_create(tbl[i].m);
    u_str_resize(&str, 1 + 2 * u_str_alloc(str));

    mut_assert(str != NULL);

    mut_equal(0, u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(u_str_alloc(str) - u_str_len(str), u_str_free(str));
    u_str_clean(str);
  }
}

mut_test(libu_str_cat_of_char) {
  u_str_t str = NULL;

  struct {
    char* str;
    char ch;
    int n;
    char* str1;
  } tbl[] = {
      {"hello",             'L', 16, "helloL"            },
      {"hello world",       'L', 16, "hello worldL"      },
      {"hello world worl",  'L', 32, "hello world worlL" },
      {"hello world world", 'L', 32, "hello world worldL"},
  };

  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    str = u_str_create_from(tbl[i].str);
    u_str_cat(&str, tbl[i].ch);

    mut_equal(strlen(tbl[i].str1), u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(tbl[i].str1, str->buf);
    u_str_clean(str);
  }
}

mut_test(libu_str_cat_of_c_str) {
  u_str_t str = NULL;

  struct {
    char* str;
    const char* ch;
    int n;
    char* str1;
  } tbl[] = {
      {"hello",            "L",                 16, "helloL"                           },
      {"hello world",      "LL",                16, "hello worldLL"                    },
      {"hello world wor",  "L",                 16, "hello world worL"                 },
      {"hello world wor",  "LL",                32, "hello world worLL"                },
      {"hello world worl", "hello world worl",  32, "hello world worlhello world worl" },
      {"hello world worl", "hello world world", 64, "hello world worlhello world world"},
  };

  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    str = u_str_create_from(tbl[i].str);
    u_str_cat(&str, tbl[i].ch);

    mut_equal(strlen(tbl[i].str1), u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(tbl[i].str1, str->buf);
    u_str_clean(str);
  }
}

mut_test(libu_str_cat_of_str) {
  u_str_t str = NULL;

  struct {
    char* str;
    char* ch;
    int n;
    char* str1;
  } tbl[] = {
      {"hello",            "L",                 16, "helloL"                           },
      {"hello world",      "LL",                16, "hello worldLL"                    },
      {"hello world wor",  "L",                 16, "hello world worL"                 },
      {"hello world wor",  "LL",                32, "hello world worLL"                },
      {"hello world worl", "hello world worl",  32, "hello world worlhello world worl" },
      {"hello world worl", "hello world world", 64, "hello world worlhello world world"},
  };

  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    str          = u_str_create_from(tbl[i].str);
    u_str_t str1 = u_str_create_from(tbl[i].ch);

    u_str_cat(&str, str1);

    mut_equal(strlen(tbl[i].str1), u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(tbl[i].str1, str->buf);

    u_str_clean(str1);
    u_str_clean(str);
  }
}

mut_test(libu_str_copy) {
  u_str_t str = NULL;

  struct {
    char* str;
  } tbl[] = {
      {"hello"},
      {"hello world"},
      {"hello world wor"},
      {"hello world wor"},
      {"hello world worl"},
      {"hello world worl"},
  };

  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    str = u_str_create_from(tbl[i].str);

    u_str_t str1 = u_str_copy(str);

    mut_equal(u_str_len(str1), u_str_len(str));
    mut_equal(u_str_alloc(str1), u_str_alloc(str));

    mut_equal(str1->buf, str->buf);

    u_str_clean(str1);
    u_str_clean(str);
  }
}
mut_group(libu_str) {

  mut_add_test(libu_str_create, "test libu u_str_create");
  mut_add_test(libu_str_create_from, "test libu u_str_create_from");
  mut_add_test(libu_str_resize, "test libu u_str_resize");
  mut_add_test(libu_str_cat_of_char, "test libu u_str_cat of char");
  mut_add_test(libu_str_cat_of_c_str, "test libu u_str_cat of c string");
  mut_add_test(libu_str_cat_of_str, "test libu u_str_cat of string");
  mut_add_test(libu_str_copy, "test libu u_str_copy");
}