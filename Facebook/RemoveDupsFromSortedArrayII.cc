/**
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums
being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.
*/
#include <cxxtest/TestSuite.h>
#include <vector>
#include <iostream>
std::ostream& operator<<(std::ostream& ostr, const std::vector<int> &v) {
  bool isFirst = true;
  ostr << "{ ";
  for (auto e : v) {
    if (isFirst) {
      isFirst = false;
    } else {
      ostr << ", ";
    }
    ostr << e;
  }
  ostr << " }";
  return ostr;
}
class Solution {
public:
  int removeDuplicates(std::vector<int> &nums) {
    if (nums.size() < 3) {
      return nums.size();
    }
    int j=0;
    int d=1;
    for (int i=1; i<nums.size(); ++i) {
      if (nums[i] == nums[j]) {
        if (d < 2) {
          nums[++j] = nums[i];
          ++d;
        }
      } else {
        nums[++j] = nums[i];
        d=1;
      }
      //std::cout << nums << "\n";
    }
    return j+1;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    std::vector<int> v {1, 1, 1, 2, 2, 3, 3, 3, 3, 4};
    TS_ASSERT_EQUALS(s.removeDuplicates(v), 7);;
    TS_ASSERT_EQUALS(v, std::vector<int>({1, 1, 2, 2, 3, 3, 4, 3, 3, 4}));
  }
};
