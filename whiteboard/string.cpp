#include <cstring>
#include <iostream>

class String
{
public:
  String(){}
  String(const char *data);
  String(const String &other);

  String(String&& other) {
    std::cout << "move constructor" << std::endl;
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
  }

  void ones() {
    for (int i = 0; i < size_; i++) {
      data_[i] = '1';
    }
  }

  ~String();

  String& operator=(const String &other);
  String& operator=(const char *data);

  String& operator=(String&& other);

  int size_ = 0;
  char *data_ = nullptr;
};

std::ostream &operator<<(std::ostream &ss, const String &s)
{
  if (s.data_ == nullptr)
  {
    ss <<" nullptr " << " on [" << reinterpret_cast<void *>(s.data_) << "]";
  } else {
  ss << s.data_ << " on [" << reinterpret_cast<void *>(s.data_) << "]";

  }
  return ss;
}

String::String(const char *data) : size_(strlen(data)),
                                   data_(new char[size_ + 1])
{
  strcpy(data_, data);
  std::cout << "String(const char*)" << *this << std::endl;
}

String::String(const String &other) : size_(other.size_),
                                      data_(new char[size_ + 1])
{
  strcpy(data_, other.data_);
  std::cout << "copy constructor String(const String&)" << *this << std::endl;
}

String &String::operator=(const String &other)
{
  if (this != &other)
  {
    delete[] data_;
    size_ = other.size_;
    data_ = new char[size_ + 1];
    strcpy(data_, other.data_);
  }
  std::cout << "operator=(const String&)" << *this << std::endl;
  return *this;
}

String &String::operator=(const char *data)
{
  delete[] data_;
  size_ = strlen(data);
  data_ = new char[size_ + 1];
  strcpy(data_, data);
  std::cout << "operator=(const String&)" << *this << std::endl;
  return *this;
}

String::~String()
{
  std::cout << "~String()" << *this << std::endl;
  delete[] data_;
}

// String::String(String&& other) {
//     data_ = other.data_;
//     size_ = other.size_;
//     other.data_ = nullptr;
//     other.size_ = 0;
//     std::cout << "move constructor for " <<  *this << std::endl;
//   }

String& String::operator=(String&& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  return *this;

  // delete [] data_;
  // data_ = other.data_;
  // size_ = other.size_;
  // other.data_ = nullptr;
  // other.size_ = 0;
  // std::cout << "move operatpr = for " <<  *this << std::endl;
  // return *this;
}

String getrepr(int i)
{
  String zero("zero");
  if (i == 0)
  {
    return std::move(zero);
  }
  return std::move(String("not zero"));
}

// String global("");

void own(String&& s) {
  // global = std::move(s);
  std::cout << "own " << s << std::endl;
}

class Age {
  public:
  Age(){}
  Age(int){};
  // Age(Age&&) = delete;
  Age(const Age&) {};
};

class User {
  public:

  User(String name, String surname, int age)
   : name_(std::move(name)),
    surname_(std::move(surname)),
    age_(age) {
    std::cout << "User constructor" << std::endl;
  }
  User(User&&) = default;
 
  // ~User(){};
  String name_;
  String surname_;
  Age age_;
};

// void foo(String&& s) {
//   std::cout << "foo " << s << std::endl;
//   s.ones();
//   std::cout << "foo " << s << std::endl;
// }

void foo(const String& s) {
  std::cout << "foo " << s << std::endl;
  // String s("foo");
  // return s;
}

int main()
{
  // const String& s = foo();
  // std::cout << s << std::endl;
  // std::cout << "END" << std::endl;
  // String s2("World");

  // s2 = std::move(s);
  
  // std::cout << "s1 = " << s << std::endl;
  // std::cout << "s2 = " << s2 << std::endl;

  // User u1 (String("John"), String("Doe"), 1);
  // std::cout << "=====================" << std::endl;
  // User copy = std::move(u1); // rvalue of User |  User&
  // String one = getrepr(1);
  // std::cout << "one = " << one << std::endl;
  // String s1("Hello");
  // std::cout << "s1 = " << s1 << std::endl;

  // String s2 = std::move(s1);
  // // s2 = std::move(s1);
  // // String s1(getrepr(5));
  // std::cout << "s1 = " << s1 << std::endl;
  // std::cout << "s2 = " << s2 << std::endl;
  // std::cout << a << std::endl;
  // std::cout << b << std::endl;

  return 0;
}