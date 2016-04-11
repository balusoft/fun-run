/*
209. Minimum Size Subarray Sum My Submissions QuestionEditorial Solution
Total Accepted: 36153 Total Submissions: 135419 Difficulty: Medium
Given an array of n positive integers and a positive integer s, find the minimal
length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.
*/
#include <vector>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  int minSubArrayLen(const int s, const vector<int> &nums) {
    if (nums.empty()) {
      return 0;
    }
    int start=0;
    int sum=nums[start];
    if (sum >=s) {
      return 1;
    }
    if (nums.size() == 1) {
      return 0;
    }
    int length=INT_MAX;
    int end=0;
    while (++end < nums.size()) {
      sum += nums[end];
      while (sum >= s && start <=end) {
        int curLen = end-start+1;
        if (curLen < length) {
          length = curLen;
        }
        sum -= nums[start++];
      }
    }
    return (length == INT_MAX) ? 0 : length;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    std::vector<int> v{2, 3, 1, 2, 4, 3};
    Solution s;
    TS_ASSERT_EQUALS(s.minSubArrayLen(7, v), 2);
  }
};
