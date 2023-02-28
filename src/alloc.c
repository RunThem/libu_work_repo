/*
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 */

#include <alloc.h>
#include <mimalloc.h>
#include <stdlib.h>

typedef struct {
  u_nullptr_t (*f_malloc)(size_t);
  u_nullptr_t (*f_calloc)(size_t, size_t);
  u_nullptr_t (*f_realloc)(u_nullptr_t, size_t);
  void (*f_free)(u_nullptr_t);
} u_alloc_fns_t;

/* defaults to LibC memory allocator */
static u_alloc_fns_t u_alloc_fns = {mi_malloc, mi_calloc, mi_realloc, mi_free};

void u_alloc_set_malloc(u_nullptr_t (*f_malloc)(size_t)) {
  u_alloc_fns.f_malloc = f_malloc;
}

void u_alloc_set_calloc(u_nullptr_t (*f_calloc)(size_t, size_t)) {
  u_alloc_fns.f_calloc = f_calloc;
}

void u_alloc_set_realloc(u_nullptr_t (*f_realloc)(u_nullptr_t, size_t)) {
  u_alloc_fns.f_realloc = f_realloc;
}

void u_alloc_set_free(void (*f_free)(u_nullptr_t)) {
  u_alloc_fns.f_free = f_free;
}

u_nullptr_t u_malloc(size_t sz) {
  return u_alloc_fns.f_malloc(sz);
}

u_nullptr_t u_calloc(size_t cnt, size_t sz) {
  return u_alloc_fns.f_calloc(cnt, sz);
}

u_nullptr_t u_zalloc(size_t sz) {
  return u_alloc_fns.f_calloc(1, sz);
}

u_nullptr_t u_realloc(u_nullptr_t ptr, size_t sz) {
  return u_alloc_fns.f_realloc(ptr, sz);
}

void u_free(u_nullptr_t ptr) {
  if (ptr) {
    u_alloc_fns.f_free(ptr);
  }
}
