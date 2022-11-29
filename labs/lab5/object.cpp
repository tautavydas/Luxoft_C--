#include "object.h"
#include <iostream>
#include <fstream>
#include <cassert>


char* get_buffer() {
  static char buffer[1024];
  return buffer;
}
static unsigned offset = 0;

Table& offsets() {
  static Table table;
  return table;
}



void Table::set(int offset, const void* value) {
  offsets[pos] = offset;
  values[pos] = value;
  ++pos;
}

int Table::get(const void* value) {
  for (size_t i{0}; i<pos; ++i) {
    if (value == values[i])
      return offsets[i];
  }
  return -1;
}

Object::Object(int id): id_(id) {
    std::cout << "created Object(" << id_ << ") on address " << this << std::endl;
}

bool Object::operator==(const Object& other) const {
    return id_ == other.id_;
}

void* Object::operator new(size_t size) {
  // allocate meory for object of current offset on buffer 
  // save offset and pointer to offfsets table
  // increase offset 
  // return pointer to allocated memory
  assert(size == sizeof(Object));
  void *const pointer{&get_buffer()[offset]};
  offsets().set(offset, pointer);
  offset += sizeof(Object);
  return pointer;
}

std::ostream& operator<<(std::ostream& ss, const Object& o) {
  const void* ptr = reinterpret_cast<const void*>(&o);
  ss << "Object(" << o.id_ << ") on " << ptr 
     << " offset " << offsets().get(ptr);
  return ss;
}

void save_to_file(const Object& o, const char* filename) {
  // get offset for 0
  // write to file size of Objet from buffer + offset 
  //get_bufe
  int const buf_beg = offsets().get(reinterpret_cast<void const*>(&o));
  if(buf_beg != -1) {
    std::ofstream file{filename, std::fstream::binary};
    //for (int i{buf_beg}; i < buf_end; ++i) {
    //  file << get_buffer()[i];
    //}
    file.write(&get_buffer()[buf_beg], sizeof(Object));
    file.close();
  } else {
    std::cout << "no such pointer entry in the table" << std::endl;
  }
}

Object* read_from_file(const char* filename) {
  // create objest
  // get offset of created object
  // get char* pointer to buffer where object is allocated
  // read size of object bytes from file to this buffer
  Object* const object = new Object(666);
  int const buf_beg = offsets().get(object);
  if(buf_beg != -1) {
    std::ifstream file{filename, std::fstream::binary};
    //for (size_t i{buf_beg}; i < buf_end; ++i) {
      //file >> get_buffer()[i];
    //}
    file.read(&get_buffer()[buf_beg], sizeof(Object));
    file.close();
  } else {
    std::cout << "no such pointer entry in the table" << std::endl;
  }
  return object;
}

void print_buf(char* buf, size_t size) {
  for (int i = 0; i < size; i++) {
    std::cout << std::hex << (int) (buf[i]) << std::dec;
  }
  std::cout << std::endl;
}
