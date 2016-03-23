/*
33. Search in Rotated Sorted Array My Submissions Question
Total Accepted: 94986 Total Submissions: 315951 Difficulty: Hard
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index,
otherwise return -1.

You may assume no duplicate exists in the array.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
4 5 6 0 1 2 3
2 3 4 5 6 0 1

search for 2:

mid = 0, low=4, high=3
*/

#include <vector>
#include <cxxtest/TestSuite.h>

class Solution {
public:
  int search(const std::vector<int> &nums, int target) {
    int low=0;
    int high=nums.size()-1;
    //if (nums[low] < nums[high]) {
    //  return bin_search(nums, low, high, target);
    //}
    while (low <= high) {
      int mid = (low + high) / 2;
      if (nums[mid] == target) {
        return mid;
      }
      // key is right hand side :-)
      // case : if rt in order (nums[mid+1] < nums[high])
      if (mid+1 == high || nums[mid+1] < nums[high]) {
        // if target in rt range move right
        if (target >= nums[mid+1] && target <= nums[high]) {
          low = mid+1;
        // else move left
        } else {
          high = mid-1;
        }
      } else {
        // Now left is inorder
        // check wither target in range of left
        // if low == mid break, means no more chance
        if (low == mid) {
          break;
        }
        if (target >= nums[low] && target <= nums[mid-1]) {
          high = mid-1;
        } else {
          low = mid + 1;
        }
      }
    }
    return -1;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    TS_ASSERT_EQUALS(s.search({5, 6, 7, 0, 1, 2, 3, 4}, 3), 6);
    TS_ASSERT_EQUALS(s.search({5, 6, 7, 0, 1, 2, 3, 4}, 0), 3);
    TS_ASSERT_EQUALS(s.search({5, 6, 7, 0, 1, 2, 3, 4}, 0), 3);
    TS_ASSERT_EQUALS(s.search({0, 1, 2, 3, 4}, 0), 0);
    TS_ASSERT_EQUALS(s.search({5, 6, 7, 8, 0, 1, 2, 3, 4}, 0), 4);
    TS_ASSERT_EQUALS(s.search({0, 1, 2, 3, 4}, 2), 2);
    TS_ASSERT_EQUALS(s.search({0, 1, 2, 3, 4}, 3), 3);
    TS_ASSERT_EQUALS(s.search({0, 1, 2, 3, 4}, 4), 4);
  }
};
