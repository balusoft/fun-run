/*
Given two numbers represented as strings, return multiplication of the numbers
as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/
#include <string>
#include <cassert>
#include <cxxtest/TestSuite.h>
#include <iostream>
#include <sstream>
using namespace std;
class Solution {
public:
  string multiply(string num1, string num2) {
    if (num1.empty() || num2.empty()) {
      return "";
    }
    if (num1 == "0" || num2 == "0") {
      return "0";
    }
    std::vector<int> res(num1.length() + num2.length(), 0);
    for (int i=num1.length()-1; i>=0; --i) {
      for (int j=num2.length()-1; j>=0; --j) {
        int ri = (num1.length() - 1 - i) + (num2.length() - 1 - j);
        res[ri] += (num1[i]-'0')*(num2[j]-'0');
      }
    }
    //Fix the carry's digit should contain max one digit
    int carry=0;
    for (size_t i=0; i<res.size(); ++i) {
      res[i] += carry;
      carry = res[i] / 10;
      res[i] = res[i] % 10;
    }
    // Now convert vector to string
    std::string out;
    for (auto e : res) {
      char c = e + '0';
      out = c + out;
    }
    // Now find first index which is not 0
    size_t i=0;
    for (i=0; i<out.length(); ++i) {
      if (out[i] != '0') {
        break;
      }
    }
    out = out.substr(i);
    return out;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    TS_ASSERT_EQUALS(s.multiply("11", "1111"), "12221");
    TS_ASSERT_EQUALS(s.multiply("1234", "123"), "151782");
    TS_ASSERT_EQUALS(s.multiply("9", "9"), "81");
    TS_ASSERT_EQUALS(s.multiply("", "9"), "");
    TS_ASSERT_EQUALS(s.multiply("0", "9"), "0");
    TS_ASSERT_EQUALS(s.multiply("9999", "999999"), "9998990001");
  }
};
