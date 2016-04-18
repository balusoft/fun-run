/**
Given an array of n integers where n > 1, nums, return an array output such that
output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does
not count as extra space for the purpose of space complexity analysis.)
*/

#include <vector>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    if (nums.size() <= 1) {
      return nums;
    }
    std::vector<int> fp(nums.size(), 1);
    if (nums.size() == 2) {
      fp[1] = nums[0];
      fp[0] = nums[1];
      return fp;
    }
    fp[1] = nums[0];
    for (int j = 2; j < nums.size(); ++j) {
      fp[j] = fp[j - 1] * nums[j - 1];
    }
    int factor = nums[nums.size() - 1];
    fp[nums.size() - 2] *= factor;
    for (int j = nums.size() - 3; j >= 0; --j) {
      factor *= nums[j+1];
      fp[j] *= factor;
    }
    return fp;
  }
};
class TestSolution : public CxxTest::TestSuite {
public:
  void test_example2() {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    std::vector<int> res{2 * 3 * 4 * 5 * 6, 1 * 3 * 4 * 5 * 6,
                         1 * 2 * 4 * 5 * 6, 1 * 2 * 3 * 5 * 6,
                         1 * 2 * 3 * 4 * 6, 1 * 2 * 3 * 4 * 5};
    Solution s;
    std::vector<int> out = s.productExceptSelf(v);
    TS_ASSERT_EQUALS(res, out);
  }
  void test_example() {
    std::vector<int> v{1, 2, 3, 4};
    std::vector<int> res{24, 12, 8, 6};
    Solution s;
    std::vector<int> out = s.productExceptSelf(v);
    TS_ASSERT_EQUALS(res, out);
  }
};
