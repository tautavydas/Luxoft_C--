#include <iostream>
#include <memory>

// auto_ptr c++98 deprecated since c++11 and removed in c++17

// unique_pointer
// shared_pointer
//    - weak_pointer

// Non copiebale class

template <typename T>
class SmartPointer {
public:
    SmartPointer(T* ptr) : ptr_(ptr) {}
    ~SmartPointer() { delete ptr_; }
    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;
    SmartPointer(SmartPointer&& other) : ptr_(other.ptr_) {
      std::cout << "Move constructor " << other.ptr_ << std::endl;
        other.ptr_ = nullptr;
    }
    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_; }
private:
    T* ptr_;
};


struct Foo {
    int val_ = 0;
    Foo(int val) : val_(val) {std::cout << "Foo(" << val << ") " <<  this << std::endl;}
    Foo() { std::cout << "Foo() " <<  this << std::endl; }
    ~Foo() { std::cout << "~Foo() " << this << std::endl; }
    void bar() { std::cout << "bar()" << this << std::endl; }
};

std::ostream& operator<<(std::ostream& os, const Foo& foo) {
    os << "Foo[" << foo.val_ << "]";
    return os;
}

SmartPointer<Foo> work_with_foo(SmartPointer<Foo> ptr) {
  // ?? return moving instead of copying
  return ptr; // good style is return std::move(ptr);
}

int main_smart_pointer() {
  SmartPointer<Foo> p1(new Foo());
  auto p2 = work_with_foo(std::move(p1));

  auto* p = new Foo();
  std::cout << "p = " << p << std::endl;
  SmartPointer<Foo> ptr(p);
  SmartPointer<Foo> ptr2 = std::move(ptr);
  // ptr2 ows Foo
  // ptr owns nothing
  ptr->bar();
  (*ptr2).bar();
  return 0;
}

// unique_ptr

void work_with_foo(std::unique_ptr<Foo> ptr) {
  ptr->bar();
}

struct StructWithUniq {
  std::unique_ptr<Foo> foo;
};

int main_uniq_ptr_basics() {
  // auto ptr = std::unique_ptr<Foo>(new Foo());
  // work_with_foo(std::move(ptr));

  // StructWithUniq s1;
  // auto s2 = s1; Not possible because StructWithUniq has non copyibla unuque_ptr

  // swapping  
  // auto f1 = std::unique_ptr<Foo>(new Foo(1));
  // auto f2 = std::unique_ptr<Foo>(new Foo(2));
  // std::cout << "f1 = " << *f1 << " " << "f2 = " << *f2 << std::endl;
  // f1.swap(f2);
  // std::cout << "f1 = " << *f1 << " " << "f2 = " << *f2 << std::endl;

  // release() and get()
  // auto f1 = std::unique_ptr<Foo>(new Foo(1));
  // auto f2 = std::unique_ptr<Foo>(new Foo(2));
  // Foo* f2_raw_ptr = f2.release();
  // delete f2_raw_ptr;
  // Foo* f1_raw_ptr = f1.get();
  // std::unique_ptr<Foo> f3(f1.get()); // double deleteion
  // std::cout << "DELETED" << std::endl;

  // reset()
  // auto f1 = std::unique_ptr<Foo>(new Foo(1));
  // f1.reset();
  // std::cout << "DELETED" << std::endl;

  // ptr->bar();
  // std::cout << "END" << std::endl;
  return 0;
}


// Custom deleters

struct Deleter {
  void operator()(Foo* ptr) {
    std::cout << "Custom deleter " << ptr << std::endl;
    delete ptr;
  }
};

int main_cutom_deleter() {
  // std::unique_ptr<Foo, Deleter> ptr(new Foo(), Deleter());

  // auto deleter_lambda = [](Foo* p ) {
  //             std::cout << "Lambda deleter " << p<<std::endl;
  //              delete p;
  // };
  // std::unique_ptr<Foo, std::function<void(Foo*)>> ptr2(new Foo(),deleter_lambda);


  // std::unique_ptr<Foo, Deleter> ptr(new Foo());

  // int count_of_deletions = 0;
  // auto deleter = [&count_of_deletions](Foo* p) {
  //   delete p;
  //   count_of_deletions++;
  // };
  // for (int i = 0; i < 10; i++) {
  //   std::unique_ptr<Foo, std::function<void(Foo*)>> ptr(new Foo(), deleter);
  // }
  // std::cout << "count_of_deletions = " << count_of_deletions << std::endl;

  std::function<void(FILE*)> close_file = [](FILE* f) {
    std::cout << "Closing file" << std::endl;
    fclose(f);
  };
  auto file = std::unique_ptr<FILE, decltype(close_file)>(fopen("test.txt", "w"), 
                                                          close_file);
  return 0;
}

// Shared Pointer



int main_basic() {
  std::shared_ptr<Foo> ptr(new Foo());
  {
    std::shared_ptr<Foo> ptr2 = ptr;
    {
      auto ptr3 = ptr;
      ptr->bar();
      ptr2->bar();
      ptr3->bar();
    }
  }
  std::cout << "END" << std::endl;
  return 0;
}


class A; class B;
struct A {
  A() { std::cout << "A()" << std::endl; }
  ~A() { std::cout << "~A() " << std::endl; }
  std::shared_ptr<B> b_;
};
struct B {
  B() { std::cout << "B()" << std::endl; }
  ~B() { std::cout << "~B()" << std::endl; }
  std::shared_ptr<A> a_;
};

int main_basic_shared_ptr() {
  auto a = std::shared_ptr<A>(new A());
  auto b = std::shared_ptr<B>(new B());
  a->b_ = b;
  b->a_ = a;
  std::cout << "a use count " << a.use_count() << std::endl;
  std::cout << "b use count " << b.use_count() << std::endl;
  std::cout << "a unique " << std::boolalpha << a.unique() << std::endl;
  std::cout << "b unique" << std::boolalpha << b.unique() << std::endl;
  
  a->b_.reset();
  std::cout << "RESETED" << std::endl;
  std::cout << "a use count " << a.use_count() << std::endl;
  std::cout << "b use count " << b.use_count() << std::endl;
  std::cout << "a use count " << std::boolalpha << a.unique() << std::endl;
  std::cout << "b use count " << std::boolalpha << b.unique() << std::endl;
  return 0;
}



// Weak Pointer

class One; class Two  ;
struct One {
  One() { std::cout << "One()" << std::endl; }
  ~One() { std::cout << "~One() " << std::endl; }
  void act() {
    std::cout << "One::act() " << this << std::endl;
    // std::cout << "one_ exipeed " << std::boolalpha << one_.expired() << std::endl;
  }
  std::shared_ptr<Two> two_;
};

struct Two {
  Two() { std::cout << "Two()" << std::endl; }
  ~Two() { std::cout << "~Two()" << std::endl; }
  void act() {
    std::cout << "Two::act()" << std::endl;
    std::cout << "one_ exipeed " << std::boolalpha << one_.expired() << std::endl;
    if (!one_.expired()) {
      one_.lock()->act();
    }
  }
  std::weak_ptr<One> one_;
};

int main_weak_ptr() {
  auto one = std::shared_ptr<One>(new One());
  auto two = std::shared_ptr<Two>(new Two());
  // weak release
  // std::weak_ptr<One> three = one;
  // three.lock()->act();
  // three.reset();
  // three.lock()->act();

  one->two_ = two;
  two->one_ = one;
  two->act();
  one.reset();
  std::cout << "RESSETED" << std::endl;
  two->act();

  return 0;
}


// shared_ptr is slow

int main_make_shared() {
  auto p = new Foo(); // 0x1000
  auto shared_p = std::shared_ptr<Foo>(p); // creates ref_counter in on 0x9999
  shared_p->bar(); // acess 0x9999 to increment ref_counter and then acess 0x1000 to call bar
  
  auto shared_p2 = std::make_shared<Foo>(); // creates ref_counter in on 0x3330
                                            // creates ref_counter in on 0x3330 + sizeof(ref_counter)
  shared_p2->bar(); // acess 0x3330 to increment ref_counter and
                    // then acess [0x3330 + sizeof(ref_counter)] to call bar                                    
  return 0;
}


void takes_multiple_params(int a, int b, int c) {
  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;
  std::cout << "c = " << c << std::endl;
}

void takes_multiple_pointers(std::unique_ptr<Foo>, std::unique_ptr<Foo>) {
}

// void takes(std::unique_ptr<Foo>) 
// takes(std::unique_ptr<Foo>(new Foo()));// If Foo raise exceptoon - memory for it will be freed


int main() {
  int i = 0;
  takes_multiple_pointers(std::unique_ptr<Foo>(new Foo()),  // order could be
                          std::unique_ptr<Foo>(new Foo())); // p0=new Foo(), p1=new Foo()
                                                            // uniq_ptr(p0), uniq_ptr(p1)
                                                            // if p1=new() throw exception - p0 leakes
  
  takes_multiple_pointers(std::make_unique<Foo>(), std::make_unique<Foo>()); // if second foo wil raise 
                                                                             // uniq_ptr for first will take care about deletion

  // std::unique_ptr<Foo> p0 = std::unique_ptr<Foo>(new Foo); 3 times Foo
  // auto p0 = std::unique_ptr<Foo>(new Foo);  2 times Foo
  // std::unique_ptr<Foo> p0(new Foo);  2 times Foo
  // auto p0 = std::make_unique<Foo>(); // 1 times Foo
}

// T* create() not clear if factory will take cate about deletion of T

// shared_ptr create() // resource is shared, there nto specific owner
// unique_ptr create() // client is now responcible for object lifetime


// void foo(T) - just copy
// void foo(T&) - probably T will be modified
// void foo(const T&) - boorrow resource
// void foo(T*) - probably T will be modified or even deleted
// void foo(shared_ptr<T>) // T could be modified but not deleted
// void foo(unique_ptr<T>) // foo not controlls lifetime of T
// void foo(shared_ptr<T>&) // T could be modified or shared_ptr could be reseted
// void foo(unique_ptr<T>& p) //  T could be modified or unique_ptr could be reseted
                        // {
                        //   p.release()
                        // }



