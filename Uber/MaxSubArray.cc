/*
53. Maximum Subarray My Submissions Question
Total Accepted: 103858 Total Submissions: 285953 Difficulty: Medium
Find the contiguous subarray within an array (containing at least one number)
which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

click to show more practice.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss
*/

#include <vector>
#include <cxxtest/TestSuite.h>

class Solution {
public:
  int maxSubArray(const std::vector<int> &nums) {
    if (nums.empty()) {
      return 0;
    }
    int cSum=nums[0];
    int maxSum=cSum;

    for (int idx=1; idx<nums.size(); ++idx) {
      //std::cout << "cSum:" << cSum << " max:" << maxSum << "\n";
      if (cSum > 0) {
        int tSum = cSum + nums[idx];
        if (tSum > 0 || tSum > cSum) {
          cSum = tSum;
        } else {
          cSum = nums[idx];
        }
      } else {
        cSum = nums[idx];
      }
      if (cSum > maxSum) {
        maxSum = cSum;
      }
    }
    return maxSum;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    TS_ASSERT_EQUALS(s.maxSubArray({-2,1,-3,4,-1,2,1,-5,4}), 6);
    TS_ASSERT_EQUALS(s.maxSubArray({1,2,1}), 4);
    TS_ASSERT_EQUALS(s.maxSubArray({1,-2,1}), 1);
    TS_ASSERT_EQUALS(s.maxSubArray({-1,-2, -3, 10, -5, 10}), 15);
  }
};
