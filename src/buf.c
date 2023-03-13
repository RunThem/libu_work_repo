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

u_buf_t _u_buf_create(size_t size) {
  u_buf_t buf = NULL;

  if (size < U_BUF_DEFAULT_LENGTH) {
    size = U_BUF_DEFAULT_LENGTH;
  }

  size = u_misc_align_2pow(size);
  dbg_alloc_if(buf = (u_buf_t)u_zalloc(BUF_HEADER_SIZE + size));

  buf->alloc = size;

  return u_buf(buf->buf);
err:

  return NULL;
}

void _u_buf_clean(u_buf_t b) {
  dbg_return_if(b == NULL, );

  u_free(CONTAINER_BUF(b));
}

size_t _u_buf_len(u_buf_t b) {
  dbg_return_if(b == NULL, 0);

  return CONTAINER_BUF(b)->len;
}

size_t _u_buf_alloc(u_buf_t b) {
  dbg_return_if(b == NULL, 0);

  return CONTAINER_BUF(b)->alloc;
}

size_t _u_buf_free(u_buf_t b) {
  dbg_return_if(b == NULL, 0);

  return CONTAINER_BUF(b)->alloc - CONTAINER_BUF(b)->len;
}

u_bool_t _u_buf_empty(u_buf_t b) {
  dbg_return_if(b == NULL, true);

  return !CONTAINER_BUF(b)->len;
}

int _u_buf_resize(u_buf_t* b, size_t size) {
  u_buf_t buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(*b == NULL, ~0);
  dbg_return_if(u_buf_alloc(*b) >= size, ~0);

  size = u_misc_align_2pow(size);

  buf = CONTAINER_BUF(*b);

  dbg_alloc_if(buf = (u_buf_t)u_realloc(buf, BUF_HEADER_SIZE + size));

  buf->alloc = size;
  *b         = u_buf(buf->buf);

  return 0;
err:

  return ~0;
}

int _u_buf_push(u_buf_t* b, u_types_type_e type, ...) {
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_buf_t buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(*b == NULL, ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  if (u_buf_free(*b) < itsize) {
    dbg_err_if(u_buf_resize(*b, itsize + u_buf_alloc(*b)) != 0);
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
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_buf_t buf = NULL;

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
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_buf_t buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(*b == NULL, ~0);
  dbg_return_if(idx >= u_buf_len(*b), ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  if (u_buf_free(*b) < itsize) {
    dbg_err_if(u_buf_resize(*b, itsize + u_buf_alloc(*b)) != 0);
  }

  buf = CONTAINER_BUF(*b);

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
  va_list ap;
  size_t itsize;
  u_nullptr_t ptr   = NULL;
  u_types_arg_t arg = {.type = type};

  u_buf_t buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(idx >= u_buf_len(b), ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &itsize));

  dbg_err_if((idx + itsize) > u_buf_len(b));

  buf = CONTAINER_BUF(b);

  memcpy((void*)ptr, &buf->buf[idx], itsize);

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_buf_remove(u_buf_t b, size_t idx, size_t itsize) {
  u_buf_t buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(idx >= u_buf_len(b), ~0);
  dbg_return_if((idx + itsize) > u_buf_len(b), ~0);

  buf = CONTAINER_BUF(b);

  memmove(&buf->buf[idx], &buf->buf[idx + itsize], buf->len - idx - itsize);

  buf->len -= itsize;

  return 0;
}

u_buf_t _u_buf_copy(u_buf_t b) {
  u_buf_t buf_1 = NULL;
  u_buf_t buf_2 = NULL;

  dbg_return_if(b == NULL, NULL);

  buf_2 = CONTAINER_BUF(b);

  dbg_alloc_if(buf_1 = (u_buf_t)u_zalloc(BUF_HEADER_SIZE + buf_2->alloc));

  memcpy(buf_1, buf_2, BUF_HEADER_SIZE + buf_2->alloc);

  return u_buf(buf_1->buf);
err:

  return NULL;
}
