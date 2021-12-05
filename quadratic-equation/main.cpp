#include "main.h"
extern const int pow_b = 2;
extern const int mul_a = 4;

int main() {
  float a = 0, b = 0, c = 0, d = 0, x1 = 0, x2 = 0;

  std::cout << "Please input an *a* from ax² + bx + c = 0 equation (any "
               "number exept 0) ... "
            << std::endl;
  while (a == 0) {
    a = input_value();
    if (a == 0) {
      std::cout
          << "You entered an incorrect number, try entering the number again."
          << std::endl;
    }
  };

  std::cout << "Please input a *b* from ax² + bx + c = 0 equation (any "
               "number) ... "
            << std::endl;
  b = input_value();

  std::cout << "Please input a *c* from ax² + bx + c = 0 equation (any "
               "number) ... "
            << std::endl;
  c = input_value();
  d = discriminant(a, b, c);

  if (d < 0) {
    std::cout << "The equation " << a << "x²"
              << " + " << b << "x + " << c
              << " = 0 has no roots because the discriminant D=" << d << "<0."
              << std::endl;
    return 0;
  }

  x1 = (-b + sqrt(d)) / (2 * a);
  x2 = (-b - sqrt(d)) / (2 * a);

  std::cout << "Roots are:" << std::endl
            << "x1 = " << x1 << std::endl << "x2 = " << x2 <<std::endl;
}

float input_value() {
  bool badInput = true;
  std::string input;
  while (badInput) {
    std::cin >> input;
    if (input.find_first_not_of("1234567890.-") != std::string::npos) {
      std::cout
          << "You entered an incorrect number, try entering the number again."
          << std::endl;
    } else {
      badInput = false;
    }
  };
  return std::stof(input);
}

float discriminant(double _a, double _b, double _c) {
  return (pow(_b, pow_b) - (mul_a * _a * _c));
}
