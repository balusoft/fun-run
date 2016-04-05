/**
26. Remove Duplicates from Sorted Array My Submissions QuestionEditorial
Solution

Given a sorted array, remove the duplicates in place such that each element
appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with
constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums
being 1 and 2 respectively. It doesn't matter what you leave beyond the new
length.

*/
#include <vector>
#include <cxxtest/TestSuite.h>
class Solution {
public:
  int removeDuplicates(std::vector<int> &nums) {
    if (nums.size() < 2) {
      return nums.size();
    }
    size_t i=0;
    size_t j=1;
    while (i<nums.size() && j<nums.size()) {
      if(nums[i] != nums[j]) {
        ++i;
        if (i != j) {
          nums[i] = nums[j];
        }
      }
      ++j;
    }
    return i+1;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    std::vector<int> v{1,1,2};
    TS_ASSERT_EQUALS(2, s.removeDuplicates(v));
  }
  void test_example2() {
    Solution s;
    std::vector<int> v{1,1,2,2,3,3,4,5,5,6};
    TS_ASSERT_EQUALS(6, s.removeDuplicates(v));
    std::vector<int> v2{1,1};
    TS_ASSERT_EQUALS(1, s.removeDuplicates(v2));
    std::vector<int> v3{1};
    TS_ASSERT_EQUALS(1, s.removeDuplicates(v3));
    std::vector<int> v4;
    TS_ASSERT_EQUALS(0, s.removeDuplicates(v4));
  }
};
