#include <iostream>
#include <exception>
#include <optional>

[[nodiscard]] int foo(std::string s) {
  // errro could be ignored 
  // no many information about error
  // if function need to return smth impossible to use
    if (s == "voldemort") {
       return -1;
    }
    std::cout << s << std::endl;
    return 0;
}

int say_hello_global_error = 0;
std::string sayHelloglobal(std::string name) {
    if (name == "voldemort") {
        say_hello_global_error = 1;
        return "";
    }
    say_hello_global_error = 0;
    return "Hello " + name;
}

std::string sayHello(std::string name, int& error) {
  // put attantion of checking errors  GOOD
  // still not enforcing
  // boilerplate code ugly
  // information about error is stil poor 
  if (name == "voldemort") {
    error = -1;
    return "";
  }
  return "Hello " + name;
}


std::optional<std::string> optional_hello(std::string name) {
  // Miss infomaition about error
  // boilerplate code ugly
  if (name == "voldemort") {
    return std::nullopt;
  }
  return "Hello " + name;
}



int main() {
    int res = foo("voldemort");
    if (res == -1) {
        std::cout << "bad foo" << std::endl;
    }

    int error = 0;
    std::string hello_string = sayHello("Haay", error);
    if (error == -1) {
        std::cout << "bad sayHello" << std::endl;
    } else {
      std::cout << hello_string << std::endl;
    }

    auto hello = sayHelloglobal("Haay");
    if (say_hello_global_error == 1) {
        std::cout << "bad sayHelloglobal" << std::endl;
    } else {
      std::cout << hello << std::endl;
    }

    auto hello_string2 = optional_hello("voldemort");
    if (!hello_string2) {
        std::cout << "bad optional_hello" << std::endl;
    } else {
      std::cout << *hello_string2 << std::endl;
    }
    return 0;
}