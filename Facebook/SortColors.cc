/**
Given an array with n objects colored red, white or blue, sort them so that
objects of the same color are adjacent, with the colors in the order red, white
and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white,
and blue respectively.
*/
#include <vector>
#include <cxxtest/TestSuite.h>

class Solution {
public:
  void sortColors(std::vector<int> &nums) {
    std::vector<size_t> rwb(3, 0);
    for (int e : nums) {
      ++rwb[e];
    }
    size_t j=0;
    for (size_t i = 0; i < rwb.size(); ++i) {
      for (size_t k = 0; k < rwb[i]; ++k) {
        nums[j++] = i;
      }
    }
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    std::vector<int> v{0,1,2,0,1,2,0,1,2};
    Solution s;
    s.sortColors(v);
    TS_ASSERT_EQUALS(v, std::vector<int>({0, 0, 0, 1, 1, 1, 2, 2, 2}));
  }
};
