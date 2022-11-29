#include "quadratic_equation.h"
#include <math.h>

bool quadratic_equation(double a, double b, double c, double& x1, double& x2) {
  // solve with one line
  // use trenary operator and coma operator.
  // use only ; for whole function body
  double determinant;
  bool condition;
  return ((determinant = b*b - 4*a*c), (condition = determinant >= 0), (x1 = (-b - sqrt(determinant))/(2*a)), (x2 = (-b + sqrt(determinant))/(2*a)), condition) ? true : false;
}
