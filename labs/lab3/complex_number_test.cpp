#include <gtest/gtest.h>

#include "complex_number.h"

TEST(ComplexNumber, check_operator_eq) {
	ComplexNumber a{1, 2}, b{3, 4};
	ASSERT_EQ(a, ComplexNumber(1, 2));
	ASSERT_EQ(b, ComplexNumber(3, 4));
}

TEST(ComplexNumber, check_operator_neq) {
	ComplexNumber a{1, 2}, b{3, 4};
  ASSERT_TRUE(a != ComplexNumber(0, 0));
  ASSERT_TRUE(b != ComplexNumber(0, 0));
}

TEST(ComplexNumber, check_operator_plus) {
  ComplexNumber a{1, 2}, b{3, 4};
  ASSERT_EQ(a + ComplexNumber(10, 20), ComplexNumber(11, 22));
  ASSERT_EQ(b + ComplexNumber(5, 3), ComplexNumber(8, 7));

  ASSERT_EQ(a + ComplexNumber(0, 0), ComplexNumber(1, 2));
  ASSERT_EQ(b + ComplexNumber(0, 0), ComplexNumber(3, 4));
}

TEST(ComplexNumber, check_operator_minus) {
  ComplexNumber a{1, 2}, b{3, 4};
  ASSERT_EQ(a - ComplexNumber(10, 20), ComplexNumber(-9, -18));
  ASSERT_EQ(b - ComplexNumber(5, 3), ComplexNumber(-2, 1));

  ASSERT_EQ(a - ComplexNumber(0, 0), ComplexNumber(1, 2));
  ASSERT_EQ(b - ComplexNumber(0, 0), ComplexNumber(3, 4));
}

TEST(ComplexNumber, check_operator_plus_eq) {
  ComplexNumber a{1, 2}, b{3, 4};
  a += ComplexNumber(10, 20);
  b += ComplexNumber(5, 3);
  ASSERT_EQ(a, ComplexNumber(11, 22));
  ASSERT_EQ(b, ComplexNumber(8, 7));

  a += ComplexNumber{0, 0};
  b += ComplexNumber{0, 0};
  ASSERT_EQ(a, ComplexNumber(11, 22));
  ASSERT_EQ(b, ComplexNumber(8, 7));
}


TEST(ComplexNumber, check_operator_stream) {
  ComplexNumber a{1, 2}, b{0, -5};
  {
    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "1 + 2i");
  }
  {
    std::stringstream ss;
    ss << b;
    ASSERT_EQ(ss.str(), "0 - 5i");
  }
}
