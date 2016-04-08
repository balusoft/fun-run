/*
67. Add Binary My Submissions QuestionEditorial Solution
Total Accepted: 80745 Total Submissions: 296617 Difficulty: Easy
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
#include <cassert>
#include <string>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  string addBinary(string a, string b) {
    int na=0;
    int nb=0;
    int nc=0;
    int ai=a.length()-1;
    int bi=b.length()-1;
    std::string out;
    while (ai >= 0 || bi >= 0) {
      ostringstream ostr;
      na=0;
      nb=0;
      if (ai < a.length()) {
        na = a[ai] - '0';
      }
      if (bi < b.length()) {
        nb = b[bi] - '0';
      }
      int res = 0;
      int tmp = na + nb + nc;
      if (tmp < 2) {
        res = tmp;
        nc = 0;
      } else if (tmp == 2) {
        res = 0;
        nc = 1;
      } else if (tmp == 3) {
        res = 1;
        nc = 1;
      } else {
        assert(0 == "bad path");
      }
      ostr << res;
      out = ostr.str() + out;
      --ai;
      --bi;
    }
    if (nc) {
      ostringstream ostr;
      ostr << nc;
      out = ostr.str() + out;
    }
    return out;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    TS_ASSERT_EQUALS(s.addBinary("11", "1"), "100");
  }
};
