/*
 * Copyright (c) 2005-2012 by KoanLogic s.r.l. - All rights reserved.
 */

#ifndef _U_DEBUG_H_
#define _U_DEBUG_H_

#include <alloc.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef U_DBG_MAX_LENGTH
#  define U_DBG_MAX_LENGTH 1024
#endif

typedef int (*u_dbg_hook_t)(u_cstr_t msg);

#ifdef NDEBUG

#  define u_con(...)
#  define u_err(...)
#  define u_warn(...)
#  define u_info(...)
#  define u_dbg(...)

#else /* disable debugging */

#  define msg(lev, ...) u_dbg_write_ex(lev, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

#  define u_con(...)  msg(LOG_CONS, __VA_ARGS__)
#  define u_err(...)  msg(LOG_ERR, __VA_ARGS__)
#  define u_warn(...) msg(LOG_WARNING, __VA_ARGS__)
#  define u_info(...) msg(LOG_INFO, __VA_ARGS__)
#  define u_dbg(...)  msg(LOG_DEBUG, __VA_ARGS__)

#endif /* !NDEBUG */

#define dbg_err(...)                                                                               \
  do {                                                                                             \
    u_dbg(__VA_ARGS__);                                                                            \
    goto err;                                                                                      \
  } while (false)

#define dbg_die(ecode, ...)                                                                        \
  do {                                                                                             \
    u_dbg(__VA_ARGS__);                                                                            \
    exit(ecode);                                                                                   \
  } while (false)

#define dbg_die_if(expr)                                                                           \
  do {                                                                                             \
    if (expr) {                                                                                    \
      dbg_die(EXIT_FAILURE, #expr);                                                                \
    }                                                                                              \
  } while (false)

#define dbg_if(expr)                                                                               \
  do {                                                                                             \
    if (expr) {                                                                                    \
      u_dbg(#expr);                                                                                \
    }                                                                                              \
  } while (false)
#define dbg_ifm(expr, ...)                                                                         \
  do {                                                                                             \
    if (expr) {                                                                                    \
      u_dbg(__VA_ARGS__);                                                                          \
    }                                                                                              \
  } while (false)

#define dbg_return_if(expr, err)                                                                   \
  do {                                                                                             \
    if (expr) {                                                                                    \
      u_dbg(#expr);                                                                                \
      return err;                                                                                  \
    }                                                                                              \
  } while (false)
#define dbg_return_ifm(expr, err, ...)                                                             \
  do {                                                                                             \
    if (expr) {                                                                                    \
      u_dbg(__VA_ARGS__);                                                                          \
      return err;                                                                                  \
    }                                                                                              \
  } while (false)

#define dbg_err_if(expr)                                                                           \
  do {                                                                                             \
    if (expr) {                                                                                    \
      u_dbg(#expr);                                                                                \
      goto err;                                                                                    \
    }                                                                                              \
  } while (false)
#define dbg_err_ifm(expr, ...)                                                                     \
  do {                                                                                             \
    if (expr) {                                                                                    \
      u_dbg(__VA_ARGS__);                                                                          \
      goto err;                                                                                    \
    }                                                                                              \
  } while (false)

#define dbg_goto_if(expr, gt)                                                                      \
  do {                                                                                             \
    if (expr) {                                                                                    \
      u_dbg(#expr);                                                                                \
      goto gt;                                                                                     \
    }                                                                                              \
  } while (false)

#define dbg_alloc_if(mem) dbg_err_if((mem) == NULL)

#define dbg_free_if(mem)                                                                           \
  do {                                                                                             \
    if ((mem) != NULL) {                                                                           \
      u_free(mem);                                                                                 \
      mem = NULL;                                                                                  \
    }                                                                                              \
  } while (false)

void u_dbg_set_hook(u_dbg_hook_t f);
int u_dbg_write_ex(int lev, const char* file, int line, const char* func, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* !_U_DEBUG_H_ */
