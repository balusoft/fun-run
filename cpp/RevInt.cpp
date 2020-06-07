//
//  RevInt.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 2/25/16.
//  Copyright © 2016 FooBar. All rights reserved.
//
#include <iostream>
#include "RevInt.hpp"
class Solution {
public:
  int reverse(int x) {
    std::cout << "x: " << x << "\n";
    if (0 == x) return x;
    int n=0;
    while (x != 0) {
      int n2 = (n*10 + x%10);
      if (n2/10 != n) {
        return 0;
      }
      n = n2;
      x /= 10;
    }
    return n;
  }
};
namespace RevInt {
void test() {
  Solution s;
  std::cout << "s.reverse(1534236469)" << s.reverse(1534236469) << "\n";
  std::cout << "s.reverse(234567890)" << s.reverse(234567890) << "\n";
  std::cout << "s.reverse(10)" << s.reverse(10) << "\n";
  std::cout << "s.reverse(-10)" << s.reverse(-10) << "\n";
  std::cout << "s.reverse(-1234)" << s.reverse(-1234) << "\n";
  std::cout << "s.reverse(-123)" << s.reverse(-123) << "\n";
  std::cout << "-2%10=" << -2%10 << "\n";
  std::cout << "-12%10=" << -12%10 << "\n";
  std::cout << "-12%10=" << -12%10 << "\n";
}
}
