/**
 * Created by iccy on 23-2-20.
 */

#include <debug.h>
#include <misc.h>

u_u64_t u_misc_align_2pow(u_u64_t n) {
  dbg_return_if(n <= 0, 1);
  dbg_return_if((n & (n - 1)) == 0, n);

  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  n |= n >> 32;

  return n + 1;
}
