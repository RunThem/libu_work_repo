/**
 * Created by iccy on 23-2-19.
 */

#include <alloc.h>
#include <debug.h>
#include <misc.h>
#include <str.h>

struct u_str {
  size_t len;   /* used */
  size_t alloc; /* excluding the header and null terminator */
  char buf[];
};

u_str_t u_str_create(size_t s) {
  struct u_str* str = NULL;

  if (s <= U_STR_DEFAULT_LENGTH) {
    s = U_STR_DEFAULT_LENGTH;
  }

  str = u_zalloc(sizeof(struct u_str) + s);
  dbg_alloc_if(str);

  str->alloc = s;

  return (u_str_t)str->buf;
err:
  return NULL;
}

u_str_t u_str_create_from(u_c_str_t s) {
  size_t size;
  u_str_t str = NULL;

  dbg_return_if(s == NULL, NULL);

  size = strlen(s);
  str  = u_str_create(u_misc_align_2pow(size));
  dbg_err_if(str == NULL);

  strncpy(str, s, size);
  container_of(str, struct u_str, buf)->len = size;

  return str;
err:
  return NULL;
}

int u_str_init(u_str_t* s) {
  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);

  *s = u_str_create(U_STR_DEFAULT_LENGTH);
  dbg_err_if(*s == NULL);

  return 0;
err:
  return ~0;
}

int u_str_init_from(u_str_t* s, u_c_str_t str) {
  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(str == NULL, ~0);

  *s = u_str_create_from(str);
  dbg_err_if(*s == NULL);

  return 0;
err:
  return ~0;
}

void u_str_free(u_str_t s) {
  dbg_err_if(s == NULL);

  u_free(container_of(s, struct u_str, buf));
err:
  return;
}

size_t u_str_len(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  struct u_str* str = container_of(s, struct u_str, buf);

  // return container_of(s, struct u_str, buf)->len;
  return str->len;
}

size_t u_str_alloc(u_str_t s) {
  dbg_return_if(s == NULL, 0);

  return container_of(s, struct u_str, buf)->alloc;
}

int u_str_resize(u_str_t* s, size_t size) {
  struct u_str* str = NULL;

  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);

  dbg_return_if(u_str_alloc(*s) >= size, ~0);

  str = container_of(*s, struct u_str, buf);

  str = u_realloc(str, size);
  dbg_alloc_if(str);

  str->alloc = size;
  *s         = (u_str_t)str->buf;

  return 0;
err:
  return ~0;
}

int u_str_cat(u_str_t* s, u_str_t s1) {
  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(s1 == NULL, ~0);

  if (u_str_alloc(*s) - u_str_len(*s) < u_str_len(s1)) {
    /* TODO: resize */
    u_str_resize(s, u_misc_align_2pow(u_str_alloc(*s) + u_str_len(s1)));
  }

  strncpy(&(*s)[u_str_len(*s)], s1, u_str_len(s1));
  container_of(*s, struct u_str, buf)->len += u_str_len(s1);

  return 0;
err:
  return ~0;
}

int u_str_cat_(u_str_t* s, u_str_t s1) {
  dbg_return_if(s == NULL, ~0);
  dbg_return_if(*s == NULL, ~0);
  dbg_return_if(s1 == NULL, ~0);

  if (u_str_alloc(*s) - u_str_len(*s) < u_str_len(s1)) {
    /* TODO: resize */
    u_str_resize(s, u_misc_align_2pow(u_str_alloc(*s) + u_str_len(s1)));
  }

  strncpy(&(*s)[u_str_len(*s)], s1, u_str_len(s1));
  container_of(*s, struct u_str, buf)->len += u_str_len(s1);

  return 0;
err:
  return ~0;
}
