/**
 * Created by iccy on 23-2-19.
 */

#include <debug.h>
#include <misc.h>
#include <str.h>

struct u_str {
  size_t len;   /* used */
  size_t alloc; /* excluding the header and null terminator */
  char buf[0];
};

#define u_str_size (sizeof(struct u_str))

u_str_t u_str_create(size_t size) {
  struct u_str* str = NULL;
  u_str_t _str      = NULL;

  if (size < U_STR_DEFAULT_LENGTH) {
    size = U_STR_DEFAULT_LENGTH;
  }

  str = u_zalloc(size);
  dbg_alloc_if(str);

  str->alloc = size;
  _str       = (u_str_t)str->buf;

  return _str;
err:
  return NULL;
}

u_str_t u_str_create_from(u_c_str_t c_str) {
  size_t c_str_size;
  size_t alloc_size;
  struct u_str* str = NULL;
  u_str_t _str      = NULL;

  dbg_return_if(c_str == NULL, NULL);

  c_str_size = strlen(c_str);

  if (c_str_size < U_STR_DEFAULT_LENGTH) {
    alloc_size = U_STR_DEFAULT_LENGTH;
  } else {
    alloc_size = u_misc_align_2pow(c_str_size);
  }

  str = u_zalloc(u_str_size + alloc_size);
  dbg_alloc_if(str);

  strncpy(str->buf, c_str, c_str_size);

  str->len   = c_str_size;
  str->alloc = alloc_size;
  _str       = (u_str_t)str->buf;

  return _str;
err:
  return NULL;
}

void u_str_clean(u_str_t s) {
  dbg_return_if(s == NULL, );

  u_free(container_of(s, struct u_str, buf));
}

size_t u_str_len(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return container_of(s, struct u_str, buf)->len;
}

size_t u_str_alloc(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return container_of(s, struct u_str, buf)->alloc;
}

size_t u_str_free(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return u_str_alloc(s) - u_str_len(s);
}

int u_str_resize(u_str_t* s, size_t size) {
  struct u_str* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(u_str_alloc(*s) >= size, ~0);

  str = container_of(*s, struct u_str, buf);

  str = u_realloc(str, u_str_size + size);
  dbg_alloc_if(str);

  str->alloc = size;

  *s = (u_str_t)str->buf;

  return 0;
err:
  return ~0;
}

int _u_str_cat(u_str_t* s, u_types_type_e type, ...) {
  int ret = 0;
  size_t str_size;
  size_t alloc_size;
  va_list ap;
  u_types_arg_t arg = {.type = type};
  u_nullptr_t ptr   = NULL;
  struct u_str* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  ptr = u_types_parse(&arg, ap);
  dbg_err_if(ptr == NULL);

  switch (arg.type) {
    case U_TYPES_BYTE:
      str = container_of(*s, struct u_str, buf);

      str->buf[str->len] = arg.t_byte;
      str->len++;

      break;
    case U_TYPES_C_STR:
      str_size = strlen(arg.t_c_str);
      if (str_size > u_str_free(*s)) {
        alloc_size = u_misc_align_2pow(str_size + u_str_len(*s));
        ret        = u_str_resize(s, alloc_size);
        dbg_err_if(ret != 0);
      }

      str = container_of(*s, struct u_str, buf);

      strncpy(&str->buf[str->len], arg.t_c_str, str_size);
      str->len += str_size;

      break;
    case U_TYPES_STR:
      str_size = u_str_len(arg.t_str);
      if (str_size > u_str_free(*s)) {
        alloc_size = u_misc_align_2pow(str_size + u_str_len(*s));
        ret        = u_str_resize(s, alloc_size);
        dbg_err_if(ret != 0);
      }

      str = container_of(*s, struct u_str, buf);

      strncpy(&str->buf[str->len], arg.t_str, str_size);
      str->len += str_size;

      break;
    default:
      break;
  }

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}