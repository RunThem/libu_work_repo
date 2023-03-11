/**
 * Created by iccy on 23-3-5.
 */

#include <buf.h>
#include <debug.h>
#include <misc.h>

struct u_buf_t {
  size_t len;   /* used */
  size_t alloc; /* excluding the header and null terminator */
  u_u8_t buf[0];
};

#define BUF_HEADER_SIZE  (sizeof(struct u_buf_t))
#define CONTAINER_BUF(b) (container_of(b, struct u_buf_t, buf))

u_buf_t u_buf_create(size_t size) {
  size_t alloc_size = size;

  struct u_buf_t* buf = NULL;

  if (size < U_BUF_DEFAULT_LENGTH) {
    alloc_size = U_BUF_DEFAULT_LENGTH;
  }

  alloc_size = u_misc_align_2pow(alloc_size);

  dbg_alloc_if(buf = (struct u_buf_t*)u_zalloc(BUF_HEADER_SIZE + alloc_size));

  buf->alloc = alloc_size;

  return u_buf(buf->buf);
err:
  return NULL;
}

void u_buf_clean(u_buf_t b) {
  dbg_return_if(b == NULL, );

  u_free(CONTAINER_BUF(b));
}

size_t u_buf_len(u_buf_t b) {
  dbg_return_if(b == NULL, 0);

  return CONTAINER_BUF(b)->len;
}

size_t u_buf_alloc(u_buf_t b) {
  dbg_return_if(b == NULL, 0);

  return CONTAINER_BUF(b)->alloc;
}

size_t u_buf_free(u_buf_t b) {
  dbg_return_if(b == NULL, 0);

  return CONTAINER_BUF(b)->alloc - CONTAINER_BUF(b)->len;
}

u_bool_t u_buf_empty(u_buf_t b) {
  dbg_return_if(b == NULL, true);

  return !CONTAINER_BUF(b)->len;
}

int u_buf_resize(u_buf_t* b, size_t size) {
  size_t alloc_size;

  struct u_buf_t* buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(*b == NULL, ~0);
  dbg_return_if(u_buf_alloc(*b) >= size, ~0);

  alloc_size = u_misc_align_2pow(size);

  buf = CONTAINER_BUF(*b);

  dbg_alloc_if(buf = (struct u_buf_t*)u_realloc(buf, BUF_HEADER_SIZE + alloc_size));

  buf->alloc = alloc_size;
  *b         = u_buf(buf->buf);

  return 0;
err:
  return ~0;
}

int _u_buf_push(u_buf_t* b, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_buf_t* buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(*b == NULL, ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  if (u_buf_free(*b) < itsize) {
    dbg_err_if(u_buf_resize(b, itsize + u_buf_alloc(*b)) != 0);
  }

  buf = CONTAINER_BUF(*b);

  memcpy(&buf->buf[buf->len], ptr, itsize);

  buf->len += itsize;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_buf_pop(u_buf_t b, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_buf_t* buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  dbg_err_if(itsize > u_buf_len(b));

  buf = CONTAINER_BUF(b);

  memcpy((u_u8_t*)ptr, &buf->buf[buf->len - itsize], itsize);

  buf->len -= itsize;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_buf_insert(u_buf_t* b, size_t idx, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_buf_t* buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(*b == NULL, ~0);
  dbg_return_if(idx >= u_buf_len(*b), ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  if (u_buf_free(*b) < itsize) {
    dbg_err_if(u_buf_resize(b, itsize + u_buf_alloc(*b)) != 0);
  }

  buf = CONTAINER_BUF(*b);

  u_info("%ld %ld", idx, itsize);

  memmove(&buf->buf[idx + itsize], &buf->buf[idx], buf->len - idx);
  memcpy(&buf->buf[idx], ptr, itsize);

  buf->len += itsize;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_buf_at(u_buf_t b, size_t idx, u_types_type_e type, ...) {
  size_t itsize;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_buf_t* buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(idx >= u_buf_len(b), ~0);
  dbg_return_if((idx + itsize) > u_buf_len(b), ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  buf = CONTAINER_BUF(b);

  memcpy((void*)ptr, &buf->buf[idx], itsize);

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int u_buf_remove(u_buf_t b, size_t idx, size_t itsize) {
  struct u_buf_t* buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(idx >= u_buf_len(b), ~0);
  dbg_return_if((idx + itsize) > u_buf_len(b), ~0);

  buf = CONTAINER_BUF(b);

  memmove(&buf->buf[idx], &buf->buf[idx + itsize], buf->len - idx - itsize);

  buf->len -= itsize;

  return 0;
}

u_buf_t u_buf_copy(u_buf_t b) {
  struct u_buf_t* buf  = NULL;
  struct u_buf_t* _buf = NULL;

  dbg_return_if(b == NULL, NULL);

  _buf = CONTAINER_BUF(b);

  dbg_alloc_if(buf = (struct u_buf_t*)u_zalloc(BUF_HEADER_SIZE + _buf->alloc));

  memcpy(buf, _buf, BUF_HEADER_SIZE + _buf->alloc);

  return u_buf(buf->buf);
err:

  return NULL;
}