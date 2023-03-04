#include <mut.h>

mut_extern(libu_types);
mut_extern(libu_alloc);
mut_extern(libu_misc);

int main(void) {
  mut_init("hello libu");

  mut_add_group(libu_types, "test libu types");
  mut_add_group(libu_alloc, "test libu alloc");
  mut_add_group(libu_misc, "test libu misc");

  mut_results();

  return 0;
}
