#include <mut.h>

mut_extern(libu_types);
mut_extern(libu_alloc);
mut_extern(libu_misc);
mut_extern(libu_str);
mut_extern(libu_buf);

int main(void) {
  mut_init("hello libu");

  mut_add_group(libu_types, "test libu types");
  mut_add_group(libu_alloc, "test libu alloc");
  mut_add_group(libu_misc, "test libu misc");

  mut_add_group(libu_str, "test libu str");
  // mut_add_group(libu_buf, "test libu buf");

  mut_results();

  return 0;
}
