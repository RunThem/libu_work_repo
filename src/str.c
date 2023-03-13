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

u_str_t _u_str_create(size_t size) {
  u_str_t str = NULL;

  if (size < U_STR_DEFAULT_LENGTH) {
    size = U_STR_DEFAULT_LENGTH;
  }

  size = u_misc_align_2pow(size);
  dbg_alloc_if(str = (u_str_t)u_zalloc(STR_HEADER_SIZE + size + 1));

  str->alloc  = size;
  str->buf[0] = '\0';

  return u_str(str->buf);
err:

  return NULL;
}

u_str_t _u_str_create_from(u_c_str_t c_str) {
  size_t size;
  size_t alloc_size;
  u_str_t str = NULL;

  dbg_return_if(c_str == NULL, NULL);

  alloc_size = size = strlen(c_str);
  if (size < U_STR_DEFAULT_LENGTH) {
    alloc_size = U_STR_DEFAULT_LENGTH;
  }

  alloc_size = u_misc_align_2pow(alloc_size);
  dbg_alloc_if(str = (u_str_t)u_zalloc(STR_HEADER_SIZE + alloc_size + 1));

  strncpy(str->buf, c_str, size);

  str->len       = size;
  str->alloc     = alloc_size;
  str->buf[size] = '\0';

  return u_str(str->buf);
err:

  return NULL;
}

void _u_str_clean(u_str_t s) {
  dbg_return_if(s == NULL, );

  u_free(CONTAINER_STR(s));
}

size_t _u_str_len(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return CONTAINER_STR(s)->len;
}

size_t _u_str_alloc(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return CONTAINER_STR(s)->alloc;
}

size_t _u_str_free(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return CONTAINER_STR(s)->alloc - CONTAINER_STR(s)->len;
}

u_bool_t _u_str_empty(u_str_t s) {
  dbg_return_if(s == NULL, true);

  return !CONTAINER_STR(s)->len;
}

int _u_str_resize(u_str_t* s, size_t size) {
  size_t alloc_size;
  u_str_t str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(u_str_alloc(*s) >= size, ~0);

  alloc_size = u_misc_align_2pow(size);

  str = CONTAINER_STR(*s);

  dbg_alloc_if(str = (u_str_t)u_realloc(str, STR_HEADER_SIZE + alloc_size + 1));

  str->alloc = alloc_size;
  *s         = u_str(str->buf);

  return 0;
err:

  return ~0;
}

int _u_str_cat(u_str_t* s, u_types_type_e type, ...) {
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_str_t str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(type != U_TYPES_BYTE && type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  if (itsize > u_str_free(*s)) {
    dbg_err_if(u_str_resize(*s, itsize + u_str_alloc(*s)) != 0);
  }

  str = CONTAINER_STR(*s);

  strncpy(&str->buf[str->len], ptr, itsize);

  str->len += itsize;
  str->buf[str->len] = '\0';

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_str_insert(u_str_t* s, size_t idx, u_types_type_e type, ...) {
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_str_t str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(idx >= u_str_len(*s), ~0);
  dbg_return_if(type != U_TYPES_BYTE && type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  if (itsize > u_str_free(*s)) {
    dbg_err_if(u_str_resize(*s, itsize + u_str_alloc(*s)) != 0);
  }

  str = CONTAINER_STR(*s);

  memmove(&str->buf[idx + itsize], &str->buf[idx], str->len - idx);
  memcpy(&str->buf[idx], ptr, itsize);

  str->len += itsize;
  str->buf[str->len] = '\0';

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

char _u_str_at(u_str_t s, size_t idx) {
  dbg_return_if(s == NULL, '\0');
  dbg_return_if(idx >= u_str_len(s), '\0');

  return CONTAINER_STR(s)->buf[idx];
}

int _u_str_remove(u_str_t s, size_t idx, size_t itsize) {
  u_str_t str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(idx >= u_str_len(s), ~0);
  dbg_return_if((idx + itsize) > u_str_len(s), ~0);

  str = CONTAINER_STR(s);

  memmove(&str->buf[idx], &str->buf[idx + itsize], str->len - idx - itsize);

  str->len -= itsize;
  str->buf[str->len] = '\0';

  return 0;
}

u_c_str_t _u_str_cstr(u_str_t s) {
  dbg_return_if(s == NULL, NULL);
  dbg_return_if(u_str_len(s) == 0, NULL);

  return u_c_str(CONTAINER_STR(s)->buf);
}

u_str_t _u_str_copy(u_str_t s) {
  u_str_t str_1 = NULL;
  u_str_t str_2 = NULL;

  dbg_return_if(s == NULL, NULL);

  str_2 = CONTAINER_STR(s);

  dbg_alloc_if(str_1 = (u_str_t)u_zalloc(STR_HEADER_SIZE + str_2->alloc));

  memcpy(str_1, str_2, STR_HEADER_SIZE + str_2->alloc);

  return u_str(str_1->buf);
err:

  return NULL;
}

u_bool_t _u_str_compare(u_str_t s, u_types_type_e type, ...) {
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_str_t str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  str = CONTAINER_STR(s);

  dbg_err_if(itsize != str->len);
  dbg_err_if(strncmp(ptr, str->buf, str->len) != 0);

  return true;
err:

  return false;
}

u_bool_t _u_str_contains(u_str_t s, u_types_type_e type, ...) {
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_str_t str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(type != U_TYPES_BYTE && type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  str = CONTAINER_STR(s);

  dbg_err_if(str->len < itsize);

  if (type == U_TYPES_BYTE) {
    dbg_err_if(strchr(str->buf, *(char*)ptr) == NULL);
  } else {
    dbg_err_if(strstr(str->buf, ptr) == NULL);
  }

  return true;
err:

  return false;
}

u_bool_t _u_str_prefix(u_str_t s, u_types_type_e type, ...) {
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_str_t str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(type != U_TYPES_BYTE && type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  str = CONTAINER_STR(s);

  dbg_err_if(str->len < itsize);
  dbg_err_if(strncmp(str->buf, ptr, itsize) != 0);

  return true;
err:

  return false;
}

u_bool_t _u_str_suffix(u_str_t s, u_types_type_e type, ...) {
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_str_t str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(type != U_TYPES_BYTE && type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  str = CONTAINER_STR(s);

  dbg_err_if(str->len < itsize);
  dbg_err_if(strncmp(&str->buf[str->len - itsize], ptr, itsize) != 0);

  return true;
err:

  return false;
}

ssize_t _u_str_index(u_str_t s, u_types_type_e type, ...) {
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_c_str_t idx;
  u_str_t str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(type != U_TYPES_BYTE && type != U_TYPES_C_STR && type != U_TYPES_STR, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  str = CONTAINER_STR(s);

  dbg_err_if(str->len < itsize);

  if (type == U_TYPES_BYTE) {
    dbg_err_if((idx = strchr(str->buf, *(char*)ptr)) == NULL);
  } else {
    dbg_err_if((idx = strstr(str->buf, ptr)) == NULL);
  }

  return idx - str->buf;
err:

  return -1;
}

int _u_str_replace(u_str_t* s, u_types_type_e type_1, u_types_type_e type_2, ...) {
  va_list ap;
  size_t itsize_1;
  size_t itsize_2;
  u_nullptr_t ptr_1   = NULL;
  u_nullptr_t ptr_2   = NULL;
  u_types_arg_t arg_1 = {.type = type_1};
  u_types_arg_t arg_2 = {.type = type_2};

  // struct u_str_t* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(type_1 != U_TYPES_C_STR && type_1 != U_TYPES_STR, ~0);
  dbg_return_if(type_2 != U_TYPES_C_STR && type_2 != U_TYPES_STR, ~0);

  va_start(ap, type_2);
  dbg_alloc_if(ptr_1 = u_types_parse(&arg_1, ap, &itsize_1));
  dbg_alloc_if(ptr_2 = u_types_parse(&arg_2, ap, &itsize_2));

  printf("type is %d, ptr is %p, itsize is %ld\n", type_1, ptr_1, itsize_1);
  printf("type is %d, ptr is %p, itsize is %ld\n", type_2, ptr_2, itsize_2);

err:

  return ~0;
}
