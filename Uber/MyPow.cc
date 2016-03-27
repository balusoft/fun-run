/*
50. Pow(x, n) My Submissions Question
Total Accepted: 85960 Total Submissions: 308179 Difficulty: Medium
Implement pow(x, n).

Subscribe to see which companies asked this question
*/

#include <limits>
#include <iostream>
#include <cassert>
#include <cstdint>
#include <cxxtest/TestSuite.h>

class Solution {
public:
  double myPow(double x, int n) {
    if (x == 1.0) {
      return x;
    }
    if (n == 0) {
      assert(x != 0);
      return 1;
    }
    bool isNeg=false;
    if (n<0) {
      isNeg=true;
      n = -1*n;
    }
    bool isOdd = (n%2 != 0);
    double res = 1;
    if (n==1) {
      res = x;
    } else {
      res = myPow(x, n/2);
      res *= res;
      if (isOdd) {
        res *= x;
      }

      // bounds check
      double tx = x;
      double tres = res;
      bool isXNeg=false;
      if (x<0) {
        tx = -1*x;
      }
      if (res<0) {
        isXNeg=true;
        tres = -1*res;
      }
      //std::cout << "tx >>> " << tx << "\n";
      //std::cout << "tres >>> " << tres << "\n";
      if (tx>1) {
        if (tres<tx) {
          res = isXNeg ? std::numeric_limits<double>::min()
                       : std::numeric_limits<double>::max();
        }
      } else {
        if (tres>tx) {
          res=0;
        }
      }
    }
    if (isNeg) {
      res = 1 / res;
    }
    return res;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_blah() {
    Solution s;
    TS_ASSERT_EQUALS(s.myPow(1, 2), 1);
    TS_ASSERT_EQUALS(s.myPow(10.0, 5), 100000.0);
    TS_ASSERT_EQUALS(s.myPow(10.0, -5), 1e-05);
    TS_ASSERT_EQUALS(s.myPow(2, -1), 0.5);
    TS_ASSERT_EQUALS(s.myPow(2, -2), 0.25);
    TS_ASSERT_EQUALS(s.myPow(2, -3), 0.125);
    TS_ASSERT_EQUALS(s.myPow(-2, 0), 1);
    //TS_ASSERT_EQUALS(s.myPow(-3.39758, 5), -452.7395395395);
    //std::cout << "0 = " <<s.myPow(-3.39758, -452.74) << "\n";
    //TS_ASSERT_EQUALS(s.myPow(2.00000, -2147483648), 0.0000);
  }
};
