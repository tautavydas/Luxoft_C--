#include <iostream>
#include <sstream>
#include <vector>

template<typename T>
void debug(T t);

template<typename T>
struct Complex {
  T re;
  T im;
};

template<typename T>
Complex<T> makeComplex(T re, T im) {
  return {re, im};
}

template<typename T, typename U>
Complex<U> operator+(T re, Complex<U> c) {
  return makeComplex(static_cast<U>(re) + c.re, c.im);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Complex<T>& c) {
  os << c.re << " + " << c.im << "i";
  return os;
}

Complex<long double> operator "" _i(long double im) {
  return makeComplex(0.0l, im);
}

Complex<unsigned long long int> operator "" _i(unsigned long long int im) {
  return makeComplex(0ull, im);
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& vec) {
  os << "[";
  for (const auto &str : vec) {
    os << str << ", ";
  }
  os << "]";
  return os;
}

template<typename T>
std::string toString(T val) {
  std::stringstream ss;
  ss << '"' << val << "\"";
  return ss.str();
}

std::vector<std::string> toStrings() {
    std::cout << "call toStrings  empty "  << std::endl;
  return {};
}

template<typename P1, typename... Params>
std::vector<std::string> toStrings(const P1& first_param, const Params& ... params) {
  std::cout << "call toStrings first param = " << first_param << std::endl;
  std::vector<std::string> vec;
  vec.push_back(toString(first_param));
  auto rest_strings = toStrings(params...);
  std::copy(rest_strings.begin(), rest_strings.end(), std::back_inserter(vec));
  // for (const auto &str : rest_strings) {
  //   vec.push_back(str);
  // }
  return vec;
}

template<typename... Params>
std::vector<std::string> toStrings2(const Params& ... params) {
  std::cout << "call toStrings2 " << parastd::endl;
  std::vector<std::string> vec = {toString(params)...};
  return vec;
}

int main() {
  std::cout << toString(1.0_i) << std::endl;
  std::cout << toString(3 + 1.5_i) << std::endl;
  std::cout << toString(1 + 6_i) << std::endl;
  std::cout << toString(5748) << std::endl;
  std::cout << toString("ekjfvnek") << std::endl;
  std::vector<std::string> vec = {"hello", "world"};
  auto res = toStrings(5 + 3_i, "hello", 1, 1.5, 1.0_i);
  std::cout << res << std::endl;
  std::cout << toStrings2(5 + 3_i, "hello", 1, 1.5, 1.0_i) << std::endl;
}