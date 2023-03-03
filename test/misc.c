#include <misc.h>
#include <mut.h>

mut_test(libu_misc_align_2pow) {
  mut_equal(u_misc_align_2pow(3), 4);
  mut_equal(u_misc_align_2pow(4), 4);
  mut_equal(u_misc_align_2pow(5), 8);
  mut_equal(u_misc_align_2pow(1000), 1024);
  mut_equal(u_misc_align_2pow(0), 1);
}

mut_group(libu_misc) {
  mut_add_test(libu_misc_align_2pow, "test libu_misc_align_2pow");
}
