#include <mut.h>

mut_extern_group(libu_types);
mut_extern_group(libu_alloc);

int main(void) {
  mut_init("hello libu");

  mut_add_group(libu_types, "test libu types");
  mut_add_group(libu_alloc, "test libu alloc");

  mut_all_results();

  return 0;
}
