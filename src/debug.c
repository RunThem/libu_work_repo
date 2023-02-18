/*
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 */

#include <debug.h>
#include <syslog.h>
#include <unistd.h>

static u_log_hook_t hook = NULL;

void u_log_set_hook(u_log_hook_t f) {
  hook = f;
}

static inline const char* u_log_label(int lev) {
  switch (lev) {
    case LOG_DEBUG:
      return "\033[37;1mdbg\033[0m";
    case LOG_INFO:
      return "\033[34;1minf\033[0m";
    case LOG_WARNING:
      return "\033[33;1mwrn\033[0m";
    case LOG_ERR:
      return "\033[31;1merr\033[0m";
    case LOG_CONS:
      return "\033[32;1mcon\033[0m";
    default:
      syslog(LOG_WARNING, "[wrn][%d:::] unknown log level: %d", getpid(), lev);
      return "unk";
  }
}

static int u_log(const char* fmt, ...) {
  int rc;
  va_list ap;
  char buf[U_LOG_MAX_LENGTH] = {0};

  va_start(ap, fmt);
  rc = vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);

  if (rc >= U_LOG_MAX_LENGTH) {
    goto err; /* message too long */
  }

  if (hook) {
    hook(buf);
  } else {
    fprintf(stderr, "%s", buf);
  }

  return 0;
err:
  return ~0;
}

int u_log_write_ex(int lev, const char* file, int line, const char* func, const char* fmt, ...) {
#define STRERR_BUFSZ 128
  int save_err;
  int rc;
  va_list ap;
  char msg[U_LOG_MAX_LENGTH] = {0};
  char errmsg[STRERR_BUFSZ]  = {0};

  save_err = errno;

  /* build the message to send to the log system */
  va_start(ap, fmt);
  rc = vsnprintf(msg, sizeof(msg), fmt, ap);
  va_end(ap);

  if (rc >= U_LOG_MAX_LENGTH) {
    goto err; /* message too long */
  }

  if (save_err) {
    snprintf(errmsg, sizeof(errmsg), "[errno: %d, %s]", save_err, strerror(save_err));
  }

  /* send the msg to the logger */
  u_log("[%s][%s/%d:%s] %s %s\n", u_log_label(lev), file, line, func, msg, errmsg);

  errno = save_err;
  return 0;
err:
  errno = save_err;
  return ~0;
}
