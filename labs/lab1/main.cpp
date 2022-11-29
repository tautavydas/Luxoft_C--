#include <iostream>
#include "quadratic_equation.h"

int main() {
    double x1, x2 = 0;
    double b = 2;
    double c = 1;
    double a = 1;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    bool solved = quadratic_equation(a, b, c, x1, x2);
    if (solved) {
        std::cout << "x1 = " << x1 << std::endl;
        std::cout << "x2 = " << x2 << std::endl;
    } else {
        std::cout << "No roots" << std::endl;
    }
    return 0;
}