/**
1. Two Sum My Submissions QuestionEditorial Solution
Total Accepted: 213400 Total Submissions: 945265 Difficulty: Easy
Given an array of integers, return indices of the two numbers such that they add
up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
UPDATE (2016/2/13):
The return format had been changed to zero-based indices. Please read the above
updated description carefully.
*/

#include <vector>
#include <unordered_map>
#include <cxxtest/TestSuite.h>

using namespace std;
class Solution {
public:
  vector<int> twoSum(const vector<int> &nums, int target) {
    unordered_map<int, int> map;
    for (int idx=0; idx<nums.size(); ++idx) {
      int secondKey = target - nums[idx];
      if (map.find(secondKey) == map.end()) {
        map[nums[idx]] = idx;
      } else {
        int secIdx = map[secondKey];
        if (idx != secIdx) {
          return vector<int>({secIdx, idx});
        }
      }
    }
    return vector<int>();
  }

  vector<int> twoSumOld(const vector<int> &nums, int target) {
    unordered_map<int, size_t> map;
    for (size_t idx=0; idx<nums.size(); ++idx) {
      map[nums[idx]] = idx;
    }
    std::vector<int> res;
    res.reserve(2);
    for (size_t idx=0; idx<nums.size(); ++idx) {
      if (map.find(target-nums[idx]) == map.end()) {
        continue;
      } else {
        size_t idx2 = map[target-nums[idx]];
        if (idx == idx2) {
          continue;
        } else {
          res.push_back(idx);
          res.push_back(map[target - nums[idx]]);
          break;
        }
      }
    }
    return res;
  }
};

class TestSuite : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    std::vector<int> v1{2, 7, 11, 15};
    std::vector<int> v2{3, 2, 4};
    TS_ASSERT_EQUALS(s.twoSum(v1, 9), vector<int>({0, 1}));
    TS_ASSERT_EQUALS(s.twoSum(v1, 18), vector<int>({1, 2}));
    TS_ASSERT_EQUALS(s.twoSum(v2, 6), vector<int>({1, 2}));
  }
};
