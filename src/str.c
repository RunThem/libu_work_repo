/**
 * Created by iccy on 23-2-19.
 */

#include <debug.h>
#include <misc.h>
#include <str.h>

struct u_str_t {
  size_t len;   /* used */
  size_t alloc; /* excluding the header and null terminator */
  char buf[0];
};

#define STR_HEADER_SIZE  (sizeof(struct u_str_t))
#define CONTAINER_STR(s) (container_of(s, struct u_str_t, buf))

u_str_t u_str_create(size_t size) {
  struct u_str_t* str = NULL;

  if (size < U_STR_DEFAULT_LENGTH) {
    size = U_STR_DEFAULT_LENGTH;
  }

  size = u_misc_align_2pow(size);

  dbg_alloc_if(str = (struct u_str_t*)u_zalloc(STR_HEADER_SIZE + size + 1));

  str->alloc = size;

  return u_str(str->buf);
err:
  return NULL;
}

u_str_t u_str_create_from(u_c_str_t c_str) {
  size_t size;
  size_t alloc_size;
  struct u_str_t* str = NULL;

  dbg_return_if(c_str == NULL, NULL);

  alloc_size = size = strlen(c_str);

  if (size < U_STR_DEFAULT_LENGTH) {
    alloc_size = U_STR_DEFAULT_LENGTH;
  }

  alloc_size = u_misc_align_2pow(alloc_size);

  dbg_alloc_if(str = (struct u_str_t*)u_zalloc(STR_HEADER_SIZE + alloc_size + 1));

  strncpy(str->buf, c_str, size);

  str->len   = size;
  str->alloc = alloc_size;

  return u_str(str->buf);
err:
  return NULL;
}

void u_str_clean(u_str_t s) {
  dbg_return_if(s == NULL, );

  u_free(CONTAINER_STR(s));
}

size_t u_str_len(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return CONTAINER_STR(s)->len;
}

size_t u_str_alloc(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return CONTAINER_STR(s)->alloc;
}

size_t u_str_free(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return CONTAINER_STR(s)->alloc - CONTAINER_STR(s)->len;
}

u_bool_t u_str_empty(u_str_t s) {
  dbg_return_if(s == NULL, true);

  return !CONTAINER_STR(s)->len;
}

int u_str_resize(u_str_t* s, size_t size) {
  size_t alloc_size;
  struct u_str_t* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(u_str_alloc(*s) >= size, ~0);

  alloc_size = u_misc_align_2pow(size);

  str = CONTAINER_STR(*s);

  dbg_alloc_if(str = (struct u_str_t*)u_realloc(str, STR_HEADER_SIZE + alloc_size + 1));

  str->alloc = alloc_size;
  *s         = u_str(str->buf);

  return 0;
err:
  return ~0;
}

int _u_str_cat(u_str_t* s, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_str_t* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(type != U_TYPES_BYTE && type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  if (itsize > u_str_free(*s)) {
    dbg_err_if(u_str_resize(s, itsize + u_str_alloc(*s)) != 0);
  }

  str = CONTAINER_STR(*s);

  strncpy(&str->buf[str->len], ptr, itsize);
  str->len += itsize;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_str_insert(u_str_t* s, size_t idx, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_str_t* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(idx >= u_str_len(*s), ~0);
  dbg_return_if(type != U_TYPES_BYTE && type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  if (itsize > u_str_free(*s)) {
    dbg_err_if(u_str_resize(s, itsize + u_str_alloc(*s)) != 0);
  }

  str = CONTAINER_STR(*s);

  memmove(&str->buf[idx + itsize], &str->buf[idx], str->len - idx);
  memcpy(&str->buf[idx], ptr, itsize);

  str->len += itsize;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

char u_str_at(u_str_t s, size_t idx) {
  dbg_return_if(s == NULL, '\0');
  dbg_return_if(idx >= u_str_len(s), '\0');

  return CONTAINER_STR(s)->buf[idx];
}

int u_str_remove(u_str_t s, size_t idx, size_t itsize) {
  struct u_str_t* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(idx >= u_str_len(s), ~0);
  dbg_return_if((idx + itsize) > u_str_len(s), ~0);

  str = CONTAINER_STR(s);

  u_dbg("%d, %d", idx, itsize);
  u_dbg("%d", str->len);

  memmove(&str->buf[idx], &str->buf[idx + itsize], str->len - idx - itsize);

  str->len -= itsize;

  return 0;
}

u_c_str_t u_str_cstr(u_str_t s) {
  dbg_return_if(s == NULL, NULL);
  dbg_return_if(u_str_len(s) == 0, NULL);

  return u_c_str(CONTAINER_STR(s)->buf);
}

u_str_t u_str_copy(u_str_t s) {
  struct u_str_t* str  = NULL;
  struct u_str_t* _str = NULL;

  dbg_return_if(s == NULL, NULL);

  _str = CONTAINER_STR(s);

  dbg_alloc_if(str = (struct u_str_t*)u_zalloc(STR_HEADER_SIZE + _str->alloc));

  memcpy(str, _str, STR_HEADER_SIZE + _str->alloc);

  return u_str(str->buf);
err:

  return NULL;
}

u_bool_t _u_str_compare(u_str_t s, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_str_t* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  str = CONTAINER_STR(s);

  dbg_goto_if(itsize != str->len, err);

  dbg_goto_if(strncmp(ptr, str->buf, str->len) != 0, err);

  return true;
err:

  return false;
}