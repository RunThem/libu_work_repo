/*
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 */

#include <memory.h>
#include <stdlib.h>

typedef struct u_memory_funcs_s {
  u_nullptr_t (*f_malloc)(size_t);
  u_nullptr_t (*f_calloc)(size_t, size_t);
  u_nullptr_t (*f_realloc)(u_nullptr_t, size_t);
  void (*f_free)(u_nullptr_t);
} u_memory_fns_t;

/* defaults to LibC memory allocator */
static u_memory_fns_t u_memory_fns = {malloc, calloc, realloc, free};

void u_memory_set_malloc(u_nullptr_t (*f_malloc)(size_t)) {
  u_memory_fns.f_malloc = f_malloc;
}

void u_memory_set_calloc(u_nullptr_t (*f_calloc)(size_t, size_t)) {
  u_memory_fns.f_calloc = f_calloc;
}

void u_memory_set_realloc(u_nullptr_t (*f_realloc)(u_nullptr_t, size_t)) {
  u_memory_fns.f_realloc = f_realloc;
}

void u_memory_set_free(void (*f_free)(u_nullptr_t)) {
  u_memory_fns.f_free = f_free;
}

u_nullptr_t u_malloc(size_t sz) {
  return u_memory_fns.f_malloc(sz);
}

u_nullptr_t u_calloc(size_t cnt, size_t sz) {
  return u_memory_fns.f_calloc(cnt, sz);
}

u_nullptr_t u_zalloc(size_t sz) {
  return u_memory_fns.f_calloc(1, sz);
}

u_nullptr_t u_realloc(u_nullptr_t ptr, size_t sz) {
  return u_memory_fns.f_realloc(ptr, sz);
}

void u_free(u_nullptr_t ptr) {
  if (ptr) {
    u_memory_fns.f_free(ptr);
  }
}
