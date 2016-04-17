/**
91. Decode Ways   My Submissions QuestionEditorial Solution
Total Accepted: 67032 Total Submissions: 383683 Difficulty: Medium
A message containing letters from A-Z is being encoded to numbers using the
following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways
to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.
*/

#include <cxxtest/TestSuite.h>
#include <string>

class Solution{
public:
  int numDecodings(const std::string &s) {
    if (s.empty()) {
      return 0;
    }
    if (s[0] == '0') {
      return 0;
    }
    int p=s[0]-'0';
    int sc = 1;
    int nsc=0;
    //std::cout << "p:" << p << " sc:" << sc << " nsc:" << nsc << "\n";
    for (int i=1; i<s.length(); ++i) {
      int c = s[i] -'0';
      int osc = sc;
      if (c != 0) {
        sc = sc + nsc;
      } else {
        sc = 0;
      }
      int pre = p*10 + c;
      //if ((p == 1 && c >= 0 && c <= 9) || (p == 2 && c >= 0 && c <= 6)) {
      if (pre < 27) {
        nsc = osc;
      } else {
        nsc = 0;
      }
      p = c;
      //std::cout << "p:" << p << " sc:" << sc << " nsc:" << nsc << "\n";
    }
    return sc + nsc;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    TS_ASSERT_EQUALS(s.numDecodings("12"), 2);
    TS_ASSERT_EQUALS(s.numDecodings("123123"), 9);
    TS_ASSERT_EQUALS(s.numDecodings("456789"), 1);
  }
};
