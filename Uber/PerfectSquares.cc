/*
279. Perfect Squares My Submissions Question
Total Accepted: 29398 Total Submissions: 91829 Difficulty: Medium
Given a positive integer n, find the least number of perfect square numbers (for
example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return
2 because 13 = 4 + 9.

Credits:
Special thanks to @jianchao.li.fighter for adding this problem and creating all
test cases.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems

*/
#include <cmath>
#include <unordered_map>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  int numSquares(int n) {
    return dp(n);
  }
private:
  /*
    int rMax=sqrt(n):
    dp(n) = min{r{1 .. rMax} 1 + dp(n-r^2)};
  */
  int dp(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (cache.find(n) != cache.end()) {
      return cache[n];
    }
    int rMax = sqrt(n);
    int min = n;
    for (int i=rMax; i>0; --i) {
      int factor = n/(i*i);
      int tmp = factor + dp(n-(factor*i*i));
      if (tmp < min) {
        min = tmp;
      }
    }
    cache[n] = min;
    return cache[n];
  }
  unordered_map<int, int> cache;
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_perfect_square() {
    Solution s;
    TS_ASSERT_EQUALS(s.numSquares(10), 2);
    TS_ASSERT_EQUALS(s.numSquares(12), 3);
    TS_ASSERT_EQUALS(s.numSquares(13), 2);
    TS_ASSERT_EQUALS(s.numSquares(48), 3);
    TS_ASSERT_EQUALS(s.numSquares(4696), 3);
  }
};
