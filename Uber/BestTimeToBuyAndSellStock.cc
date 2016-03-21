/*
121. Best Time to Buy and Sell Stock My Submissions Question
Total Accepted: 90811 Total Submissions: 254560 Difficulty: Medium

Say you have an array for which the ith element is the price of a given stock on
day i.

If you were only permitted to complete at most one transaction (ie, buy one and
sell one share of the stock), design an algorithm to find the maximum profit.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

cases :
220 : 50 100 45 44 30 250 20
280 : 100 50 45 30 35 250 20 300
0   : 100 90 80 70 60 50 40 30 20 10
90  : 10 20 30 40 50 60 70 80 90 100
*/

#include <vector>
#include <iostream>
#include <algorithm>

#include <cxxtest/TestSuite.h>

class Solution {
public:
  int maxProfit(const std::vector<int>& prices) {
    if (prices.empty()) {
      return 0;
    }
    size_t start=0;
    size_t end=0;
    size_t curStart=0;
    int max=INT_MIN;
    int min=INT_MAX;
    for (size_t idx=0; idx<prices.size(); ++idx) {
      if (min > prices[idx]) {
        min = prices[idx];
        curStart = idx;
      }
      if (max < prices[idx] - min) {
        start = curStart;
        end = idx;
        max = prices[idx] - min;
      }
    }
    std::cout << "range: ( " << start << ", " << end << ")\n";
    return max;
  }
};
class TestSolution : public CxxTest::TestSuite {
public:
  void test_ascending() {
    Solution s;
    TS_ASSERT_EQUALS(s.maxProfit({10, 20, 30}), 20);
  }
  void test_desc() {
    Solution s;
    TS_ASSERT_EQUALS(s.maxProfit({30, 20, 10}), 0);
  }
  void test_zigzag1() {
    Solution s;
    TS_ASSERT_EQUALS(s.maxProfit({100, 50, 45, 30, 35, 250, 20, 30}), 220);
  }
  void test_zigzag() {
    Solution s;
    TS_ASSERT_EQUALS(s.maxProfit({100, 50, 45, 30, 35, 250, 20, 300}), 280);
  }
  void test_null() {
    Solution s;
    TS_ASSERT_EQUALS(s.maxProfit({}), 0);
  }
};
