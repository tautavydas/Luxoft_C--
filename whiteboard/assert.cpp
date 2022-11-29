#include <assert.h>
#include <iostream>
#include <stdlib.h>

void ownassert(bool cond) {
    if (!cond) {
        std::cerr << "Assertion failed" << std::endl;
        abort();
    }
}

int binarysearch(int data*, int size, int value) {
  // assert(sorted(data, size));
  ownassert(sorted(data, size));
};

int main() {
    std::cout << "main()" << std::endl;
    try {
      assert(1 == 2);
    } catch (...) {
      std::cout << "catched" << std::endl;
    }

    std::cout << "main()2" << std::endl;
    return 0;
}