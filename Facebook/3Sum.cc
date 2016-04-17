/**
15. 3Sum   My Submissions QuestionEditorial Solution
Total Accepted: 112936 Total Submissions: 603100 Difficulty: Medium
Given an array S of n integers, are there elements a, b, c in S such that a + b
+ c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:
Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
The solution set must not contain duplicate triplets.
For example, given array S = {-1 0 1 2 -1 -4},

A solution set is:
  (-1, 0, 1)
  (-1, -1, 2)
Subscribe to see which companies asked this questio
**/

#include <vector>
#include <cxxtest/TestSuite.h>
#include <algorithm>
class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    std::vector<std::vector<int>> res;
    if (nums.size() < 3) {
      return res;
    }
    std::sort(nums.begin(), nums.end());
    // Now fix one element after that take two pointers such that
    // nums[lo]+nums[hi] = -nums[i]
    for (int i=0; i<nums.size(); ++i) {
      int lo = i+1;
      int hi = nums.size() - 1;
      int sum = -1 * nums[i];
      while (lo < hi) {
        int cs = nums[lo] + nums[hi];
        if (cs > sum) {
          --hi;
        } else if (cs < sum) {
          ++lo;
        } else {
          std::vector<int> s3({nums[i], nums[lo], nums[hi]});
          res.push_back(s3);
          // move ahead and search for duplicates
          while(s3[1] == nums[lo] &&  lo < hi) ++lo;
          while(s3[2] == nums[hi] && lo < hi) --hi;
        }
      }
      while(i+1 < nums.size() && nums[i+1] == nums[i]) ++i;
    }
    return res;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_foo1() {
    std::vector<int> nums{-1, 0, 1, 2, -1, -4};
    Solution s;
    TS_ASSERT_EQUALS(s.threeSum(nums),
                     std::vector<std::vector<int>>({{-1, -1, 2}, {-1, 0, 1}}));
  }
};
