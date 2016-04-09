/*
Implement int sqrt(int x).

Compute and return the square root of x.

Subscribe to see which companies asked this question
*/

#include <cxxtest/TestSuite.h>
#include <cassert>
#include <cmath>
class Solution {
public:
  int mySqrt(int x) {
    if (x < 0) {
      x *= -1;
      assert(0 == "undef");
    }
    if (x < 1) {
      return 0;
    }

    if (x < 4) {
      return 1;
    }

    int low = 0;
    int high = x;
    int mid=0;
    while (high-low > 1) {
      mid = low + ((high-low)/2);
      if (mid > x/mid) {
        high = mid;
      } else {
        low = mid;
      }
      //std::cout << low << "," << high << "\n";
    }
    return low;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    TS_ASSERT_EQUALS(s.mySqrt(0), 0);
    TS_ASSERT_EQUALS(s.mySqrt(1), 1);
    TS_ASSERT_EQUALS(s.mySqrt(2), 1);
    TS_ASSERT_EQUALS(s.mySqrt(3), 1);
    TS_ASSERT_EQUALS(s.mySqrt(4), 2);
    TS_ASSERT_EQUALS(s.mySqrt(5), 2);
    TS_ASSERT_EQUALS(s.mySqrt(8), 2);
    TS_ASSERT_EQUALS(s.mySqrt(50), 7);
    TS_ASSERT_EQUALS(s.mySqrt(49), 7);
    TS_ASSERT_EQUALS(s.mySqrt(48), 6);
    TS_ASSERT_EQUALS(s.mySqrt(40), 6);
    TS_ASSERT_EQUALS(s.mySqrt(399), 19);
    TS_ASSERT_EQUALS(s.mySqrt(10000), 100);
  }
};
