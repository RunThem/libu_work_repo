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

  if (size < U_STR_DEFAULT_LENGTH) {
    size = U_STR_DEFAULT_LENGTH;
  }

  dbg_alloc_if(str = (struct u_str*)u_zalloc(u_str_size + size + 1));

  str->alloc = size;

  return (u_str_t)str->buf;
err:
  return NULL;
}

u_str_t u_str_create_from(u_c_str_t c_str) {
  size_t str_size;
  size_t alloc_size;
  struct u_str* str = NULL;

  dbg_return_if(c_str == NULL, NULL);

  str_size = strlen(c_str);
  alloc_size =
      (str_size < U_STR_DEFAULT_LENGTH) ? U_STR_DEFAULT_LENGTH : u_misc_align_2pow(str_size);

  dbg_alloc_if(str = (struct u_str*)u_zalloc(u_str_size + alloc_size + 1));

  strncpy(str->buf, c_str, str_size);

  str->len   = str_size;
  str->alloc = alloc_size;

  return (u_str_t)str->buf;
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

  dbg_alloc_if(str = (struct u_str*)u_realloc(str, u_str_size + size + 1));

  str->alloc = size;
  *s         = (u_str_t)str->buf;

  return 0;
err:
  return ~0;
}

u_str_t u_str_copy(u_str_t s) {
  u_str_t str = NULL;

  dbg_return_if(s == NULL, NULL);

  dbg_alloc_if(str = u_str_create(u_str_alloc(s)));

  strncpy(str->buf, s->buf, u_str_len(s));
  container_of(str, struct u_str, buf)->len = u_str_len(s);

  return str;
  err:
  return NULL;
}

int _u_str_cat(u_str_t* s, u_types_type_e type, ...) {
  size_t str_size;
  size_t alloc_size;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr   = NULL;
  struct u_str* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(type != U_TYPES_BYTE && type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &str_size));

  if (str_size > u_str_free(*s)) {
    alloc_size = u_misc_align_2pow(str_size + u_str_len(*s));
    dbg_err_if(u_str_resize(s, alloc_size) != 0);
  }

  str = container_of(*s, struct u_str, buf);

  strncpy(&str->buf[str->len], ptr, str_size);
  str->len += str_size;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}