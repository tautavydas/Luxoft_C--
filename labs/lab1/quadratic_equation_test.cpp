#include "quadratic_equation.h"

#include <gtest/gtest.h>

TEST(QuadraticEquationTest, OneRoot) {
  double x1, x2;
  EXPECT_TRUE(quadratic_equation(1, 2, 1, x1, x2));
  EXPECT_DOUBLE_EQ(x1, -1);
  EXPECT_DOUBLE_EQ(x2, -1);
}

TEST(QuadraticEquationTest, TwoRoots) {
  double x1, x2;
  EXPECT_TRUE(quadratic_equation(1, -5, 6, x1, x2));
  EXPECT_DOUBLE_EQ(x1, 2);
  EXPECT_DOUBLE_EQ(x2, 3);
}

TEST (QuadraticEquationTest, NoRoots) {
  double x1, x2;
  EXPECT_FALSE(quadratic_equation(1, 2, 3, x1, x2));
}

TEST(QuadraticEquationTest, DoubleRoots)
{
	int a = 2;
	int b = 8;
	int c = 4;

	double expectedX1 = -3.4142;
	double expectedX2 = -0.5857;
	double x1;
	double x2;

	ASSERT_TRUE(quadratic_equation(a,b,c,x1,x2));

	EXPECT_NEAR(x1, expectedX1, 0.0001);
	EXPECT_NEAR(x2, expectedX2, 0.0001);
}
