//
//  BullsAndCows.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 2/16/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include "BullsAndCows.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class Solution {
public:
  std::string getHint(const std::string& secret, const std::string& guess) {
    std::vector<int> secNumFreq(10, 0);
    std::vector<int> gueNumFreq(10, 0);
    size_t bull=0;
    for (size_t idx=0; idx<guess.size(); ++idx) {
      if (guess[idx] == secret[idx]) {
        ++bull;
      }
      ++gueNumFreq[guess[idx]-'0'];
      ++secNumFreq[secret[idx]-'0'];
    }
    //std::cout << "\n";
    //for (auto i : secNumFreq) { std::cout << " " << i; }
    //std::cout << "\n";
    //for (auto i : gueNumFreq) { std::cout << " " << i; }
    //std::cout << "\n";
    size_t cow=0;
    for (size_t idx=0; idx<10; ++idx) {
      if (0!=gueNumFreq[idx] && 0!=secNumFreq[idx]) {
        cow += std::min(gueNumFreq[idx], secNumFreq[idx]);
      }
    }
    cow-=bull;
    std::ostringstream ostr;
    ostr << bull << "A" << cow << "B";
    return ostr.str();
  }
};

namespace BullsAndCows {
void test() {
  Solution s;
  std::cout << "hint: " << s.getHint("1807", "7810") << "\n";
  std::cout << "hint: " << s.getHint("1123", "0111") << "\n";
}
};
