/**
88. Merge Sorted Array My Submissions QuestionEditorial Solution
Total Accepted: 95627 Total Submissions: 319070 Difficulty: Easy
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one
sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m +
n) to hold additional elements from nums2. The number of elements initialized in
nums1 and nums2 are m and n respectively.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss
*/
#include <cassert>
#include <vector>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int i1 = m - 1;
    int i2 = n - 1;
    int j = m + n - 1;
    assert(j < nums1.size());
    while (i1 >= 0 && i2 >= 0) {
      if (nums1[i1] > nums2[i2]) {
        nums1[j] = nums1[i1];
        --i1;
      } else {
        nums1[j] = nums2[i2];
        --i2;
      }
      --j;
    }
    while (i1 >= 0) {
      nums1[j] = nums1[i1];
      --i1;
      --j;
    }
    while (i2 >= 0) {
      nums1[j] = nums2[i2];
      --i2;
      --j;
    }
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    std::vector<int> nums1{30, 40, 50, 0, 0, 0};
    std::vector<int> nums2{1, 2, 35};
    Solution s;
    s.merge(nums1, 3, nums2, 3);
    std::vector<int> res{1, 2, 30, 35, 40, 50};
    TS_ASSERT_EQUALS(res, nums1);
  }
};
