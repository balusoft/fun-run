//One Edit Distance
/*

Given two strings S and T, determine if they are both one edit distance apart.

Show Company Tags
Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

*/

#include <string>
#include <cassert>
#include <cxxtest/TestSuite.h>
class Solution {
public:
  bool isOneEditDistance(const std::string &s, const std::string &t) {
    size_t slen = s.length();
    size_t tlen = t.length();
    int diff = slen - tlen;

    if (diff > 1 || diff < -1) {
      return false;
    }

    // if diff is -ve s should be expecting one new char
    // if diff is +ve s should be expecting one less char
    // if diff is 0 s should expect one char to replace
    bool oneEditReached = false;
    for (size_t sidx = 0, tidx = 0; sidx < slen && tidx < tlen;
         ++sidx, ++tidx) {
      if (s[sidx] == t[tidx]) {
        continue;
      }
      if (oneEditReached) {
        return false;
      }
      oneEditReached = true;
      switch (diff) {
      case -1:
        // In this case s[idx] must be equal to t[idx+1]
        if (s[sidx] != t[tidx + 1]) {
          return false;
        }
        ++tidx;
        break;
      case 1:
        // In this case  t[idx] must be equal to s[idx+1]
        if (s[sidx + 1] != t[tidx + 1]) {
          return false;
          break;
        case 0:
          // One diff is allowed
          break;
        default:
          assert(0 == "boom");
        }
      }
    }
    return true;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_0() {
    Solution s;
    TS_ASSERT_EQUALS(s.isOneEditDistance("one","onn"), true);
  }
  void test_p1() {
    Solution s;
    TS_ASSERT_EQUALS(s.isOneEditDistance("one","onen"), true);
  }
  void test_pm1() {
    Solution s;
    TS_ASSERT_EQUALS(s.isOneEditDistance("one","on"), true);
  }
  void test_3() {
    Solution s;
    TS_ASSERT_EQUALS(s.isOneEditDistance("one","abc"), false);
  }
  void test_3m() {
    Solution s;
    TS_ASSERT_EQUALS(s.isOneEditDistance("one","oneabc"), false);
  }
  void test_3m() {
    Solution s;
    TS_ASSERT_EQUALS(s.isOneEditDistance("aone","one"), false);
  }
};
