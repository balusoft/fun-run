/**
283. Move Zeroes My Submissions QuestionEditorial Solution
Total Accepted: 71121 Total Submissions: 161913 Difficulty: Easy
Given an array nums, write a function to move all 0's to the end of it while
maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums
should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.
Credits:
Special thanks to @jianchao.li.fighter for adding this problem and creating all
test cases.

Subscribe to see which companies asked this question
*/
#include <vector>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  void moveZeroes(vector<int> &nums) {
    if (nums.empty()) {
      return;
    }
    size_t zb=nums.size();
    for (size_t i=0; i<nums.size(); ++i) {
      if (nums[i] == 0) {
        if (zb == nums.size()) {
          zb = i;
        }
      } else {
        if (zb != nums.size()) {
          std::swap(nums[i], nums[zb]);
          ++zb;
        }
      }
    }
  }
};
class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    std::vector<int> v {1, 0, 2, 0, 3, 0, 4, 0};
    Solution s;
    s.moveZeroes(v);
    const std::vector<int> res{1, 2, 3, 4, 0, 0, 0, 0};
    TS_ASSERT_EQUALS(v, res);
  }
};
