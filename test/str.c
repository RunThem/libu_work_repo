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
      {128,  100 },
      {256,  129 },
      {2048, 1025},
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
    str = u_str_create_from(u_c_str(tbl[i].str));

    mut_assert(str != NULL);

    mut_equal(strlen(tbl[i].str), u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(u_str_alloc(str) - strlen(tbl[i].str), u_str_free(str));

    mut_equal(tbl[i].str, (char*)u_str_cstr(str));
    u_str_clean(str);
  }
}

mut_test(libu_str_resize) {
  u_str_t str = NULL;

  struct {
    int n;
    int m;
  } tbl[] = {
      {64,   0   },
      {64,   3   },
      {64,   7   },
      {64,   10  },
      {512,  100 },
      {1024, 129 },
      {8192, 1025},
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

mut_test(libu_str_push_of_char) {
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
    u_str_push(&str, tbl[i].ch);

    mut_equal(strlen(tbl[i].str1), u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(tbl[i].str1, (char*)u_str_cstr(str));
    u_str_clean(str);
  }
}

mut_test(libu_str_push_of_c_str) {
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
    u_str_push(&str, tbl[i].ch);

    mut_equal(strlen(tbl[i].str1), u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(tbl[i].str1, (char*)u_str_cstr(str));
    u_str_clean(str);
  }
}

mut_test(libu_str_push_of_str) {
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

    u_str_push(&str, str1);

    mut_equal(strlen(tbl[i].str1), u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(tbl[i].str1, (char*)u_str_cstr(str));

    u_str_clean(str1);
    u_str_clean(str);
  }
}

mut_test(libu_str_push_of_array) {
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
    str = u_str_create_from(tbl[i].str);

    u_str_push(&str, u_any(tbl[i].ch), strlen(tbl[i].ch));

    mut_equal(strlen(tbl[i].str1), u_str_len(str));
    mut_equal(tbl[i].n, u_str_alloc(str));

    mut_equal(tbl[i].str1, (char*)u_str_cstr(str));

    u_str_clean(str);
  }
}

mut_test(libu_str_pop_of_char) {
  u_str_t str = NULL;

  struct {
    char* str;
    char ch;
  } tbl[] = {
      {"hello",                           'o'},
      {"hello world",                     'd'},
      {"hello world wor",                 'r'},
      {"hello world wor",                 'r'},
      {"hello world worl",                'l'},
      {"hello world worliehgiqwhgalskdf", 'f'},
  };

  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    str = u_str_create_from(tbl[i].str);
    char ch;

    u_str_pop(str, &ch);

    mut_equal(tbl[i].ch, ch);

    mut_equal(strlen(tbl[i].str) - 1, u_str_len(str));

    u_str_clean(str);
  }
}

mut_test(libu_str_pop_of_str) {
  u_str_t str = NULL;

  struct {
    char* str;
    int n;
    char* ch;

  } tbl[] = {
      {"hello",                           3,  "llo"       },
      {"hello world",                     8,  "lo world"  },
      {"hello world wor",                 1,  "r"         },
      {"hello world wor",                 2,  "or"        },
      {"hello world worl",                5,  " worl"     },
      {"hello world worliehgiqwhgalskdf", 10, "qwhgalskdf"},
  };

  for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
    str          = u_str_create_from(tbl[i].str);
    u_str_t str1 = u_str_create(tbl[i].n);

    u_str_pop(str, str1, tbl[i].n);

    mut_equal(tbl[i].ch, (char*)u_str_cstr(str1));
    mut_equal(tbl[i].n, u_str_len(str1));

    mut_equal(strlen(tbl[i].str) - tbl[i].n, u_str_len(str));

    u_str_clean(str);
    u_str_clean(str1);
  }

  str = u_str_create_from(tbl[5].str);

  u_str_t str1 = u_str_create(16);
  mut_equal(~0, u_str_pop(str, str1, 17));
  u_str_clean(str1);

  str1 = u_str_create(100);
  mut_equal(~0, u_str_pop(str, str1, 100));
  u_str_clean(str1);

  u_str_clean(str);
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
    str          = u_str_create_from(tbl[i].str);
    u_str_t str1 = u_str_copy(str);

    mut_equal(u_str_len(str1), u_str_len(str));
    mut_equal(u_str_alloc(str1), u_str_alloc(str));

    mut_equal((char*)u_str_cstr(str1), (char*)u_str_cstr(str));

    u_str_clean(str1);
    u_str_clean(str);
  }
}
mut_group(libu_str) {

  mut_add_test(libu_str_create, "test libu u_str_create");
  mut_add_test(libu_str_create_from, "test libu u_str_create_from");

  mut_add_test(libu_str_resize, "test libu u_str_resize");

  mut_add_test(libu_str_push_of_char, "test libu u_str_push of char");
  mut_add_test(libu_str_push_of_c_str, "test libu u_str_push of c string");
  mut_add_test(libu_str_push_of_str, "test libu u_str_push of string");
  mut_add_test(libu_str_push_of_array, "test libu u_str_push of array");

  mut_add_test(libu_str_pop_of_char, "test libu u_str_pop of char");
  mut_add_test(libu_str_pop_of_str, "test libu u_str_pop of string");

  mut_add_test(libu_str_copy, "test libu u_str_copy");
}
