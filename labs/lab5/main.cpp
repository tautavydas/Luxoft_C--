#include <iostream>
#include "object.h"


int main() {
  print_buf(get_buffer(), 1024);
  Object const*const o_in = new Object(43);
  print_buf(&get_buffer()[offsets().get(o_in)], sizeof(Object));
  //save_to_file(*o_in, "object.bin");

  Object const*const p_in = new Object(42);
  print_buf(&get_buffer()[offsets().get(p_in)], sizeof(Object));
  save_to_file(*p_in, "object.bin");

  print_buf(get_buffer(), 1024);

  Object *const out = read_from_file("object.bin");
  print_buf(&get_buffer()[offsets().get(out)], sizeof(Object));
  print_buf(get_buffer(), 1024);
}
