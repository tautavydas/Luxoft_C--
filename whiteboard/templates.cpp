#include <iostream>
#include <string.h>
#include <vector>
#include <cstring>
#include <exception>

// int min(int a, int b) {
//   return a < b ? a : b;
// }


// Function templates
// Class templates
// member function emplates
// using templates 
// variable tamplates

struct Storage {
  int data;
  bool operator<(const Storage& other) const {
    return data < other.data;
  }
};

std::ostream& operator<<(std::ostream& os, const Storage& s) {
  os << "Storage{" << s.data << "}";
  return os;
}

template <typename T>
void show_type();

template<class T, class U>
U min(T a, U b) {
  std::cout << "comparing min generic" << std::endl;
  return a < b ? a : b;
}

template<>
const char* min(const char* a, const char* b) {
  std::cout << "comparing min strings" << std::endl;
  return strcmp(a, b) < 0 ? a : b;
}

template<class T>
void foo(T t, T u) {
  std::cout << "foo <T,T> generic" << std::endl;
}

template<class T, class U>
void foo(T t, U u) {
  std::cout << "foo <T,U> generic" << std::endl;
}

template<>
void foo(int t, int u) {
  std::cout << "foo <int,int> generic" << std::endl;
}


// Class templates

// template<class T>
// class Array {
//   public:
//     Array(int size) : size_(size) {
//       data_ = new T[size];
//     }
//     ~Array() {
//       delete[] data_;
//     }
//     T& operator[](int index) {
//       return data_[index];
//     }
//     int size() const {
//       return size_;
//     }
//   T* data_;
//   size_t size_;
// };

// template<class T>
// class Array<T*> {
//   public:
//     Array(int size) : size_(size) {
//       data_ = new T[size];
//     }
//     ~Array() {
//       delete[] data_;
//     }
//     T& operator[](int index) {
//       return data_[index];
//     }

//     T& operator[](int index) const {
//       return data_[index];
//     }

//     int size() const {
//       return size_;
//     }
//   T* data_;
//   size_t size_;
// };


template<class T>
class Foo {
  public:
  void foo(T t) {
    std::cout << "Foo::foo<T> generic" << std::endl;
    std::cout << t << std::endl;
  }
};



template<class T>
class Foo<T*> {
  public:
  void foo(T* t) {
    std::cout << "Foo::foo for pointers" << std::endl;
    std::cout << *t << std::endl;
  }
};

template<>
class Foo<int*> {
  public:
  void foo(int* t) {
    std::cout << "int pointer " << t << " dereferences " << *t << std::endl;
  }
};



int class_template_main() {
  Foo <Storage*> f;
  Storage s{1};
  f.foo(&s);
  Foo<int*> f2;
  int i = 1;
  f2.foo(&i);
  double d = 1.0;
  Foo<double*> f3;
  // f3.foo(d);
  // Array<Storage*> a(3);
  // a[0] = new Storage{1};
  // a[1] = new Storage{2};
  // a[2] = new Storage{3};

  // for (int i = 0; i < a.size(); ++i) {
  //   std::cout << a[i] << std::endl;
  // }

  // foo(1, 5);
  // foo(1.0,5);
  
  // Storage a {1};
  // Storage b {2};
  // std::cout << min(a, b) << std::endl;
  // std::cout << min(1, 5) << std::endl;
  // std::cout << min(1.2, 5.4) << std::endl;
  // const char* a = "Bob";
  // const char* b = "Alice";
  // std::cout << min(a, b) << std::endl;
  // std::cout << min(1, 5) << std::endl;
  // std::cout << min(1.2, 5.4) << std::endl;
    return 0;
}



template<class T>
std::string toString(const T& t) {
  return "value(" + std::to_string(t) + ")";
}

template<typename T> 
std::vector<std::string> toString(const std::vector<T>& input) {
  std::vector<std::string> result;
  for (const auto& element : input) {
    result.push_back(toString(element));
  }
  return result;
}



int to_string_func_main() {
  int i = 1;
  std::cout << toString(i) << std::endl;
  std::cout << toString(4.5) << std::endl;
  
  std::vector<int> v{1,2,3,4,5};
  std::vector<std::string> s = toString(v);
  for (const auto& element : s) {
    std::cout << element << std::endl;
  }
  return 0;
}



template<class T>
class Array {
  public:
    Array(int size) : size_(size) {
      data_ = new T[size];
    }
    ~Array() {
      delete[] data_;
    }
    T& operator[](int index) {
      return data_[index];
    }
    int size() const {
      return size_;
    }
  T* data_;
  size_t size_;
};


// tempalte argument can be:
// - class
// - literal
// pointer or reference to global object (static variable, global variable)
template<class T, int Size>
struct Vector {

  T data_[Size];

  T& operator[](int index) {
    return data_[index];
  }

  const T& operator[](int index) const {
    return const_cast<Vector<T, Size>*>(this)->operator[](index);
  }

  Vector<T, Size> operator*(const Vector<T, Size>& other) {
    Vector<T, Size> result;
    for (int i = 0; i < Size; ++i) {
      result[i] = data_[i] * other[i];
    }
    return result;
  }
  
    Vector<T, Size> operator*(const Vector<T, 0>& other) {
      Vector<T, Size> result;
      for (int i = 0; i < Size; ++i) {
        result[i] = 0;
      }
      return result;
    }

  int size() const {
    return Size;
  }
};


template<class T>
struct Vector<T, 0> {

  Vector<T, 0> operator*(const Vector<T, 5>& other) {
    std::cout << "vector of zeros multiploes vector of fives" << std::endl;
    return *this;
  }

  int size() const {
    return 0;
  }
};

int values_as_template_argument_main() {
  Vector<int, 5> v = {1,2,3,4,5};
  Vector <int, 0> vzeros;
  Vector<int, 5> v2 = {100,100,100,100, 100};
  auto v3 = v * vzeros;
  for (int i = 0; i < v3.size(); ++i) {
    std::cout << v3[i] << ", ";
  }
  std::cout << std::endl;

  return 0;
}

template<class T, T* var>
class Bar {
  public:
  void foo() {
    *var = 5;
  }
};

int i = 6;
int main() {
  Bar<int, &i> b;
  b.foo();
  std::cout << i << std::endl;
}