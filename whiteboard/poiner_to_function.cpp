#include <iostream>
template <typename> struct DebugType;

// typedef const char* string;

typedef void (*VoidFuncIntParam)(int);

// typedef void (*VoidFuncZeroParams)();

class Foo {
    public:
    Foo(int identifier):identifier_(identifier){}
    double get_double() {
        std::cout << "get_double on " << identifier_ << std::endl;
        return 42.0;
    }

    double get_another_double() {
        std::cout << "get_another_double" << identifier_ << std::endl;
        return 24.0;
    }

    static void static_func() {
        std::cout << "static function" << std::endl;
    }

    int identifier_;
};

class Bar {
    public:
    double get_double() {
        return 0;
    }
};

std::ostream& operator<<(std::ostream& ss, Foo& f) {
    ss << "Foo(" <<f.identifier_ << ")";
    return ss;
}


using FooFunc = double (Foo::*)();

using VoidFuncZeroParams = void(*)();

void foo() {
    std::cout << "foo called" << std::endl;
}

void iterate(int num, VoidFuncIntParam callback) {
    for (int i = 0; i < num; i++) {
        (*callback)(i);
    }
}


void call_me(Foo* pointer, FooFunc func) {
    (pointer->*func)();
}


int main(int argc, const char** argv) {
    Foo* f = new Foo(1);
    Foo* f2 = new Foo(2);


    double (Foo::*foo_func)() = &Foo::get_double;
    double (Foo::*foo_func2)() = &Foo::get_another_double;
    
    call_me(f, foo_func);
    call_me(f, foo_func2);
    call_me(f2, foo_func);
    call_me(f2, foo_func2);
    
    
    
    // std::cout << *f << std::endl;
    // std::cout << *f2 << std::endl;
    
    
    // 
    // (f->*foo_func)();

    // VoidFuncZeroParams pfoo = foo;
    // (*pfoo)();
    // pfoo = Foo::static_func;
    // (*pfoo)();
    // string s = "1234";
    // iterate(5, bar);
    // void (*pointer_to_foo)() = foo;
    // (*pointer_to_foo)();
    // void (*pointer_to_bar)(int) = bar;
    // (*pointer_to_bar)(10);
    // void* p = reinterpret_cast<void*>(&foo); 
    // std::cout << p << std::endl;
    return 0;
}