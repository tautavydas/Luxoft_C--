#include <iostream>
#include <exception>
#include <optional>
#include <memory>

void bar() {
    throw 1.5;
}

struct DontNameHisnameException : public std::exception {
    const char* what() const throw() {
        return "Don't name his name!";
    }
};

void foo() {
    std::cout << "foo1" << std::endl;
    bar();
    throw "I'm an exception";
    std::cout << "foo2" << std::endl;
}

int main_basic() {
    try {
      std::cout << "Hello World!" << std::endl;
      foo();
      std::cout << "Hello World 2" << std::endl;
    } catch (int  e) {
        std::cerr << e << std::endl;
    } catch (const char*  e) {
        std::cerr << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }
    std::cout << "Hello World 3" << std::endl;
    return 0;
}

std::string say_my_name(const std::string& name) {
    if (name == "voldemort") {
        throw DontNameHisnameException();
    }
    if (name.size() == 0 ) {
        throw std::runtime_error("Name is empty");
    }
    return "Hello " + name;
}

void logic() {
    try {
        // std::cout << say_my_name("voldemort") << std::endl;
        std::cout << say_my_name("") << std::endl;
    } catch (const DontNameHisnameException& e) {
        std::cerr << "Catched in logic " << e.what() << std::endl;
    } catch (const std::exception& e) {
        throw;
    }
    std::cout << "logic2" << std::endl;
}
int main_nested_exceptions(int argc, const char** argv) {
  try {
    logic();
  } catch (const std::exception& e) {
    std::cerr <<"main:" << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknwon exception" << std::endl;
  }
  return 0;
}


struct A {
    static int counter() {
      static int counter_ = 1;
      return counter_++;
    }
    int value_;
    A() : value_(counter()) {
        std::cout << "A()" << value_ << std::endl;
    }
    A(const A& a) : value_(a.value_) {
        std::cout << "A(const A& a)" << value_ << std::endl;
    }
    ~A() {
        std::cout << "~A()" << value_ << std::endl;
    }
};

void foo2() {
    A a2;
    throw 1;
}

int main_stack_unwind(int argc, const char** argv) {
  try {
    A a1;
    foo2();
    A a3;
  } catch (...) {
    std::cout << "catched" << std::endl;
  }
  return 0;
}


// void* operator new(size_t size) {
//     void* p = malloc(size);
//     std::cout << "new " << size << " " << p << std::endl;
//     return p;
// }

// void operator delete(void* p) noexcept {
//     std::cout << "delete " << p << std::endl;
//     free(p);
// }

struct Server {
    static int counter() {
      static int counter_ = 0;
      return counter_++;
    }
    int value_;
    Server() : value_(counter()) {
        std::cout << "Server() create started" << value_ << std::endl;

        if (value_ == 2) {
            throw 1;
        }
        std::cout << "Server() craated" << value_ << std::endl;
    }
    ~Server() {
        std::cout << "~Server()" << value_ << std::endl;
    }
};

int main_eception_contructor(int argc, const char** argv) {
  try {
    // RAII - Resource Acquisition Is Initialization
    
    auto p1 = new Server();

    // if (!p1->is_ready()) { . BAD practice because breaks RAII
    //   delete p1; 
    //   return;
    // }

    auto p2 = new Server();
    auto p3 = new Server();
    delete p1;
    delete p2;
    delete p3;
  } catch (...) {
    std::cout << "catched" << std::endl;
  }
    return 0;
}



struct Value {
  static int counter() {
    static int counter_ = 0;
    return counter_++;
  };

  Value(): val_(counter()) {
      if (val_ == 1) {
          throw std::runtime_error("Value is 1 is unsupported");
      }
      std::cout << "Value("  << val_ <<  ")" << std::endl;

  }
  ~Value() {
      std::cout << "~Value("  << val_ <<  ")" << std::endl;
  }
  int val_;
};

struct SmartPointer {
  SmartPointer(Value* p) : p_(p) {
  }
  ~SmartPointer() {
      delete p_;
  }
  Value* p_;
};

struct Storage {
  Storage() 
  try:
    value_(new Value()),
    value2_(new Value()),
    value3_(new Value())
  {
    std::cout << "Storage()" << std::endl;
  } catch (...) {
    std::cout << "Storage() catched" << std::endl;
    throw;
  }

  ~Storage() {
  }

  SmartPointer value_;
  SmartPointer value2_;
  SmartPointer value3_;
};

int main_try_in_initializer_list() {
  try {
    Storage storage;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

class DestrutorExcept {
public:
    ~DestrutorExcept() noexcept(false) {
        std::cout << "~DestrutorExcept()" << std::endl;
        throw 1;
    }
};

void noexcept_func() noexcept {
  throw std::runtime_error("foo3");
}

int main() {
  try {
    // DestrutorExcept destrutor_except;
    noexcept_func();
  } catch (...) {
    std::cout << "catched" << std::endl;
  }
  return 0;
}

// Where to use exceptions? 

// Exceptional cases (rare cases)
// Expected error - use other technics to deal with it. 
// Dont use exceptions for unrecheble situations. assert() is better.


// Pros 
// Separate place for handling esxceptional situations
// make code a little bit cleaner
// power OOP for different tyoes of exceptions
// exception may contain many useful information

// Cons
// Not free - performance
// Not free - memory/code size
// If it used wrong - it may be a mess
// Don't base logic(requirenments) on exceptions
// Exceptional cases should be very rare in runtime


