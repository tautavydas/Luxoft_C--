#pragma once
#include "ostream"

class ComplexNumber {
  public:
  ComplexNumber(double re, double im);
  double getRe() const;
  double getIm() const;
  bool operator==(ComplexNumber const& input) const;
  bool operator!=(ComplexNumber const& input) const;
  ComplexNumber operator+(ComplexNumber const& input) const;
  ComplexNumber operator-(ComplexNumber const& input) const;
  ComplexNumber const& operator+=(ComplexNumber const& input);
  private:
    double re_;
    double im_;
};

std::ostream& operator<<(std::ostream& out,ComplexNumber const& number);
