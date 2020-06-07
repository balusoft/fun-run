//
//  LongestCommonPrefix.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 2/25/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include <iostream>
#include "LongestCommonPrefix.hpp"
#include <string>
#include <vector>
class Solution {
public:
  std::string longestCommonPrefix(const std::vector<std::string>& strs) {
    if (strs.size() == 0) { return ""; }
    size_t idx=0;
    while (true) {
      bool fail=false;
      for (size_t sidx=0; sidx<strs.size(); ++sidx) {
        if (strs[sidx].length() < idx) {
          fail=true;
          break;
        }
        if (strs[0][idx] != strs[sidx][idx]) {
          fail=true;
          break;
        }
      }
      if (fail) {
        break;
      }
      ++idx;
    }
    std::string s;
    if (idx > 0) {
      s = strs[0].substr(0, idx);
    }
    return s;
  }
};
namespace LongestCommonPrefix {
void test() {
  Solution s;
  {
    std::vector<std::string> strs;
    strs.push_back("");
    std::cout << "C3: " << s.longestCommonPrefix(strs) << "\n";
  }
  {
    std::vector<std::string> strs;
    strs.push_back("12abc123");
    strs.push_back("12babcabc");
    strs.push_back("12bbabcxyz");
    std::cout << "C2: " << s.longestCommonPrefix(strs) << "\n";
  }

  {
    std::vector<std::string> strs;
    strs.push_back("abc123");
    strs.push_back("abcabc");
    strs.push_back("abcxyz");
    std::cout << "C1: " << s.longestCommonPrefix(strs) << "\n";
  }
}
}

