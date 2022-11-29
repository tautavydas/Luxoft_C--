#include <iostream>

class Object;

class Table {
  public:
  int offsets[10] = {0};
  const void* values[10] = {nullptr};
  int pos = 0;
  void set(int offset, const void* value);
  int get(const void* value);
};

char* get_buffer();
Table& offsets();

void print_buf(char* buf, size_t size);

class Object {
  public:
  Object(int id);
  bool operator==(const Object& other) const;
  void* operator new(size_t size);
  int id_;
};

std::ostream& operator<<(std::ostream& ss, const Object& o);

void save_to_file(const Object& o, const char* filename);

Object* read_from_file(const char* filename);
