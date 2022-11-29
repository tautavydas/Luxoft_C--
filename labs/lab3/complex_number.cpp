#include "complex_number.h"
#include <iostream>

ComplexNumber::ComplexNumber(double re, double im)
  : re_(re), im_(im) {
}

double ComplexNumber::getRe() const {
  return re_;
}

double ComplexNumber::getIm() const {
  return im_;
}

bool ComplexNumber::operator==(ComplexNumber const& input) const {
  return re_ == input.re_ && im_ == input.im_;
}

bool ComplexNumber::operator!=(ComplexNumber const& input) const {
  return re_ != input.re_ || im_ != input.im_;
}

ComplexNumber ComplexNumber::operator+(ComplexNumber const& input) const {
  return ComplexNumber{re_ + input.re_, im_ + input.im_};
}

ComplexNumber ComplexNumber::operator-(ComplexNumber const& input) const {
  return ComplexNumber{re_ - input.re_, im_ - input.im_};
}

ComplexNumber const& ComplexNumber::operator+=(ComplexNumber const& input) {
  re_ += input.re_;
  im_ += input.im_;
  return *this;
}

std::ostream& operator<<(std::ostream& out, ComplexNumber const& input) {
  return out << input.getRe() << ((input.getIm() >= 0) ? " + " : " - ") << abs(input.getIm()) << "i";
}
