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
  struct u_buf_t* buf = NULL;

  if (size < U_BUF_DEFAULT_LENGTH) {
    size = U_BUF_DEFAULT_LENGTH;
  }

  dbg_alloc_if(buf = (struct u_buf*)u_zalloc(BUF_HEADER_SIZE + size));

  buf->alloc = size;

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

int u_buf_resize(u_buf_t* b, size_t size) {
  struct u_buf_t* buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(*b == NULL, ~0);
  dbg_return_if(u_buf_alloc(*b) >= size, ~0);

  buf = CONTAINER_BUF(*b);

  dbg_alloc_if(buf = (struct u_buf*)u_realloc(buf, BUF_HEADER_SIZE + size));

  buf->alloc = size;
  *b         = u_buf(buf->buf);

  return 0;
err:
  return ~0;
}

int _u_buf_write(u_buf_t* b, u_types_type_e type, ...) {
  size_t item_size;
  size_t alloc_size;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_buf_t* buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(*b == NULL, ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &item_size));

  if (u_buf_free(*b) < item_size) {
    alloc_size = u_misc_align_2pow(item_size + u_buf_len(*b));
    dbg_err_if(u_buf_resize(b, alloc_size) != 0);
  }

  buf = CONTAINER_BUF(*b);

  memcpy(&buf->buf[buf->len], ptr, item_size);

  buf->len += item_size;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}

int _u_buf_read(u_buf_t b, u_types_type_e type, ...) {
  size_t size;

  va_list ap;
  u_types_arg_t arg = {.type = type};

  u_nullptr_t ptr     = NULL;
  struct u_buf_t* buf = NULL;

  dbg_return_if(b == NULL, ~0);
  dbg_return_if(type == U_TYPES_NONE, ~0);

  va_start(ap, type);
  dbg_alloc_if(ptr = u_types_parse(&arg, ap, &size));

  dbg_err_if(size > u_buf_len(b));

  buf = CONTAINER_BUF(b);

  memcpy((u_u8_t*)ptr, &buf->buf[buf->len - size], size);

  buf->len -= size;

  va_end(ap);

  return 0;
err:
  va_end(ap);

  return ~0;
}
