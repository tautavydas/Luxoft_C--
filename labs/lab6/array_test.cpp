#include "array.h"
#include <gtest/gtest.h>

TEST(ArrayTest, DefaultConstructor) {
    Array a;
    EXPECT_EQ(0, a.size());
    EXPECT_EQ(0, Array::allocated_memory());
}

TEST(ArrayTest, Constructor) {
  {
    Array a(10);
    EXPECT_EQ(10, a.size());
    EXPECT_EQ(10 * sizeof(double), Array::allocated_memory());
  }
  EXPECT_EQ(0, Array::allocated_memory());
}

TEST(ArrayTest, ConstructorInitializerList) {
    {
      Array a = {1, 2, 3, 4, 5};
      EXPECT_EQ(5, a.size());
      for (int i = 0; i < 5; ++i) {
          EXPECT_EQ(i + 1, a[i]);
      }
      EXPECT_EQ(5 * sizeof(double), Array::allocated_memory());
    }
    EXPECT_EQ(0, Array::allocated_memory());
}

TEST(ArrayTest, CopyConstructor) {
  {
    Array a = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(7 * sizeof(double), Array::allocated_memory());
    Array b(a);
    EXPECT_EQ(14 * sizeof(double), Array::allocated_memory());
    EXPECT_EQ(7, b.size());
    for (int i = 0; i < 7; ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
  }
  EXPECT_EQ(0, Array::allocated_memory());
}

TEST(ArrayTest, AssignmentOperator) {
  {
    Array a = {1, 2, 3, 4, 5};
    EXPECT_EQ(5 * sizeof(double), Array::allocated_memory());
    Array b = {1,2};
    EXPECT_EQ(7 * sizeof(double), Array::allocated_memory());
    b = a;
    EXPECT_EQ(10 * sizeof(double), Array::allocated_memory());
    EXPECT_EQ(5, b.size());
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
  }
  EXPECT_EQ(0, Array::allocated_memory());
}

TEST(ArrayTest, MoveConstructor) {
  {
    Array a = {1, 2, 3, 4, 5};
    EXPECT_EQ(5 * sizeof(double), Array::allocated_memory());
    Array b(std::move(a));
    EXPECT_EQ(5 * sizeof(double), Array::allocated_memory());
    EXPECT_EQ(5, b.size());
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(i + 1, b[i]);
    }
  }
  EXPECT_EQ(0, Array::allocated_memory());
}

TEST(ArrayTest, MoveAssignmentOperator) {
  {
    Array a = {1, 2, 3, 4, 5};
    EXPECT_EQ(5 * sizeof(double), Array::allocated_memory());
    Array b {3,2,1};
    EXPECT_EQ(8 * sizeof(double), Array::allocated_memory());
    b = std::move(a);
    EXPECT_EQ(5 * sizeof(double), Array::allocated_memory());
    EXPECT_EQ(5, b.size());
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(i + 1, b[i]);
    }
  }
  EXPECT_EQ(0, Array::allocated_memory());
}

TEST (ArrayTest, DealocationMemory) {
  size_t allocated = 0;
  {
    Array a = {1, 2, 3, 4, 5};
    allocated += 5 * sizeof(double);
    EXPECT_EQ(allocated, Array::allocated_memory());
    {
      Array a = {1, 2, 3, 4, 5};
      allocated += 5 * sizeof(double);
      EXPECT_EQ(allocated, Array::allocated_memory());
      {
        Array a = {1, 2, 3, 4, 5};
        allocated += 5 * sizeof(double);
        EXPECT_EQ(allocated, Array::allocated_memory());
        {
          Array a = {1, 2, 3, 4, 5};
          allocated += 5 * sizeof(double);
          EXPECT_EQ(allocated, Array::allocated_memory());
        }
        allocated -= 5 * sizeof(double);
        EXPECT_EQ(allocated, Array::allocated_memory());
      }
      allocated -= 5 * sizeof(double);
      EXPECT_EQ(allocated, Array::allocated_memory());
    }
    allocated -= 5 * sizeof(double);
    EXPECT_EQ(allocated, Array::allocated_memory());
  }
  allocated -= 5 * sizeof(double);
  EXPECT_EQ(allocated, Array::allocated_memory());
}