#include <misc.h>
#include <mut.h>

mut_test(libu_misc_align_2pow) {
  mut_equal(1, u_misc_align_2pow(0));
  mut_equal(1, u_misc_align_2pow(1));
  mut_equal(4, u_misc_align_2pow(3));
  mut_equal(4, u_misc_align_2pow(4));
  mut_equal(8, u_misc_align_2pow(5));
  mut_equal(1024, u_misc_align_2pow(1000));
}

mut_group(libu_misc) {
  mut_add_test(libu_misc_align_2pow, "test libu_misc_align_2pow");
}
