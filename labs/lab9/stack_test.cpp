#include <gtest/gtest.h>
#include "stack.h"


TEST(StackTest, EmptyStack) {
  Stack<int> stack(10);
  EXPECT_TRUE(stack.empty());
  EXPECT_FALSE(stack.pop());  // pop method should return bool
}

TEST(StackTest, Push) {
  Stack<int> stack(10);
  ASSERT_TRUE(stack.empty());
  ASSERT_FALSE(stack.pop());
  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(stack.push(i)); // push should return bool
  }
  EXPECT_FALSE(stack.push(10)); // push should return false if stack is full 
}

TEST(StackTest, HeadAndPop) {
  const size_t stack_size = 5;
  Stack<int> stack(stack_size);
  ASSERT_TRUE(stack.empty());
  ASSERT_FALSE(stack.pop());
  for (int i = 0; i < stack_size; i++) {
    ASSERT_TRUE(stack.push(i));
  }
  ASSERT_FALSE(stack.push(10));
  for (int i = stack_size-1; i >= 0; i--) {
    EXPECT_EQ(i, stack.head()); // stack head should return last element 
    EXPECT_TRUE(stack.pop());  // pop return true if pop successful
  }
  EXPECT_TRUE(stack.empty());
  EXPECT_FALSE(stack.pop());
}

TEST(StackOfPointerTest, EmptyStack) {
  Stack<int*> stack(3);
  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(nullptr, stack.pop()); // pop for stack poointer should return T*  delete stack.pop();
}

struct Foo {
  Foo(int val, 
      size_t& deletions_counter) : val_(val),
                                    deletions_counter_(deletions_counter) {}
  ~Foo() {
    deletions_counter_++;
  }
  int val_;
  size_t& deletions_counter_;
};

TEST(StackOfPointersTest, Push) {
  const size_t stack_size = 5;
  size_t deletions_counter = 0;
  {
    Stack<Foo*> stack(stack_size);
    ASSERT_TRUE(stack.empty());
    ASSERT_EQ(nullptr, stack.pop());
    for (int i = 0; i < stack_size; i++) {
      EXPECT_TRUE(stack.push(new Foo(i, deletions_counter)));
    }
    EXPECT_FALSE(stack.push(nullptr));
  }
  EXPECT_EQ(stack_size, deletions_counter); // stack should take care about deletion of all pointers inside
}

TEST(StackOfPointerTest, Pop) {
  const size_t stack_size = 12;
  size_t deletions_counter = 0;
  Stack<Foo*> stack(stack_size);
  ASSERT_TRUE(stack.empty());
  ASSERT_EQ(nullptr, stack.pop());
  for (int i = 0; i < stack_size; i++) {
    auto val = new Foo(i, deletions_counter);
    ASSERT_EQ(i, val->val_);
    ASSERT_TRUE(stack.push(val));
  }
  ASSERT_FALSE(stack.push(nullptr));
  for (int i = stack_size-1; i >= 0; i--) {
    const Foo& ref = stack.head();
    EXPECT_EQ(i, ref.val_);
    Foo* foo = stack.pop();
    EXPECT_EQ(i, foo->val_);
    delete foo;
  }
  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(nullptr, stack.pop());
}

TEST(StackTest, SizeofStack) {
  EXPECT_EQ(sizeof(int) * 10, SizeOf(Stack<int>(10)));
  EXPECT_EQ(sizeof(double) * 10, SizeOf(Stack<double>(10)));
  EXPECT_EQ(sizeof(Foo) * 10, SizeOf(Stack<Foo*>(10)));
}

TEST(StackTest, Apply) {
  Stack<int> stack(10);
  for (int i = 0; i < 10; i++) {
    stack.push(i);
  }
  auto multiply = [](const int& val) { return val * 2; };
  stack.apply(multiply);
  for (int i = 9; i > 0; i--) {
    EXPECT_EQ(i * 2, stack.head());
    stack.pop();
  }
}

TEST(StackTest, ApplyException) {
  Stack<int> stack(10);
  for (int i = 0; i < 10; i++) {
    stack.push(i);
  }
  auto multiply = [](const int& val) { 
    if (val == 5) {
      struct DummyException : std::exception {
        const char* what() const noexcept override {
          return "5 should not be here";
        }
      };
      throw DummyException();
    }
    return val * 2; 
  };
  stack.apply(multiply);
  for (int i = 9; i > 0; i--) {
    if (i == 5) {
      EXPECT_EQ(5, stack.head());
    } else {
      EXPECT_EQ(i * 2, stack.head());
    }
    stack.pop();
  }
}

TEST(StackTest, Inspect) {
  Stack<int> stack(10);
  for (int i = 0; i < 10; i++) {
    stack.push(i);
  }
  int count = 0;
  auto calculate = [&count](int&) { count++; };
  stack.inspect(calculate);
  EXPECT_EQ(10, count);
}

TEST(StackTest, InspectExceptions) {
  Stack<int> stack(10);
  for (int i = 0; i < 10; i++) {
    stack.push(i);
  }
  std::vector<int> proceed;
  auto calculate = [&proceed](int& val) { 
    struct UnknownException : std::exception {
        const char* what() const noexcept override {
          return "Unknown exception should stop inspecting";
        }
    };
    if (val == 5) throw std::invalid_argument("5 should be skipped");
    if (val == 8) throw UnknownException();
    proceed.push_back(val); 
  };
  stack.inspect(calculate);
  EXPECT_EQ(7, proceed.size());
  for (int i = 0; i < 5; i++) {
    EXPECT_FALSE(proceed.end() == std::find(proceed.begin(), proceed.end(), i));
  }
  EXPECT_EQ(6, proceed[5]);
  EXPECT_EQ(7, proceed[6]);
}


TEST(StackTest, InspectRuntimeExceptin) {
  Stack<int> stack(10);
  for (int i = 0; i < 10; i++) {
    stack.push(i);
  }
  EXPECT_THROW({
    stack.inspect([](int& val){
        throw std::runtime_error("runtime error");
    });
  }, std::runtime_error);
}