//
//  ZigZagConversion.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 2/22/16.
//  Copyright © 2016 FooBar. All rights reserved.
//
#include "ZigZagConversion.hpp"
#include <string>
#include <sstream>
#include <iostream>
class Solution {
public:
  std::string convert(const std::string& s, int rc) {
    if (s.length() == 0) return "";
    size_t d1=(rc-1)*2;
    if (d1 == 0) return s;
    std::ostringstream ostr;
    for (size_t idx=0; idx<rc; ++idx) {
      if (idx > s.size()) {
        break;
      }
      size_t d2=d1-2*idx;
      size_t sidx=idx;
      while (sidx<s.size()) {
        ostr << s[sidx];
        if (0 != idx && rc-1 != idx && d2 > 0 && sidx+d2 < s.size()) {
          ostr <<s[sidx+d2];
        }
        sidx+=d1;
      }
    }
    return ostr.str();
  }
};

//PAHNAPLSIIGYIR
//PAHNAPLSIIYIR
namespace ZigZagConversion {
void test() {
  Solution s;
  std::cout << "s.convert(\"ABCD\", 4)\n" <<
               s.convert("ABCD", 4) << " END\n";
  std::cout << "s.convert(\"A\", 2)\n" <<
               s.convert("A", 2) << " END\n";
}
}
