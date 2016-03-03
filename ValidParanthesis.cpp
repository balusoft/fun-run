//
//  ValidParanthesis.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 2/26/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include "ValidParanthesis.hpp"
#include <string>
#include <stack>
#include <map>
#include <iostream>
class Solution {
public:
  bool isValid(const std::string& s) {
    std::stack<char> st;
    std::map<char, char> braces;
    braces.insert(std::make_pair('(', ')'));
    braces.insert(std::make_pair('[', ']'));
    braces.insert(std::make_pair('{', '}'));
    for (size_t idx=0; idx<s.length(); ++idx) {
      if (braces.find(s[idx]) != braces.end()) {
        st.push(s[idx]);
      } else {
        if (st.empty()) {
          return false;
        }
        if (braces[st.top()] == s[idx]) {
          st.pop();
        } else {
          return false;
        }
      }
    }
    return st.empty();
  }
};
namespace ValidParanthesis {
  void test() {
    std::string s("{");
    Solution sl;
    std::cout << std::boolalpha << s << ":" << sl.isValid(s) << "\n";
  }
}

int main() {
  ValidParanthesis::test();
  return 0;
}
