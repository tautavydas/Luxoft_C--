#include "object.h"
#include <gtest/gtest.h>


TEST(ObjectTest, SimilarObjects) {
  auto o = new Object(42);
  auto o2 = new Object(42);
  ASSERT_EQ(*o, *o2);
}

TEST(ObjectTest, DifferentObjects) {
  auto o = new Object(42);
  auto o2 = new Object(12);
  ASSERT_FALSE(*o == *o2);
}

TEST(ObjectTest, ObjectTest) {
  auto o = new Object(42);
  save_to_file(*o, "object.bin");
  auto o2 = read_from_file("object.bin");
  ASSERT_FALSE(o2 == nullptr);
  ASSERT_EQ(*o, *o2);
}