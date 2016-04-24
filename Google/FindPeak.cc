/*
162. Find Peak Element   My Submissions QuestionEditorial Solution
Total Accepted: 63313 Total Submissions: 192064 Difficulty: Medium
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its
index.

The array may contain multiple peaks, in that case return the index to any one
of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should
return the index number 2.

click to show spoilers.

Credits:
Special thanks to @ts for adding this problem and creating all test cases.

Subscribe to see which companies asked this question

Show Tags

0 1 2 3
1 2 3 1

num[i] != num[i+1] going either in asc or desch

mid1  = 1
mid1+1 = 2
lo = 0;
hi = size-1;
mid1 = (lo+hi)/2
mid2 = mid1+1
if (mid1 < mid2) : move right (lo=mid2, hi=hi)
if (mid1 > mid2) : move left (lo=lo, hi=mid1)
if (hi = lo+1) : return n[hi] > n[lo] ? hi : lo

*/

class Solution {
public:
  int findPeakElement(vector<int> &nums) {
    if (nums.empty()) {
      return -1;
    }
    if (nums.size() == 1) {
      return 0;
    }
    int lo = 0;
    int hi = nums.size() - 1;
    while (lo <= hi) {
      if (lo == hi) {
        return lo;
      } else if (lo + 1 == hi) {
        return nums[lo] > nums[hi] ? lo : hi;
      }

      int mid1 = (lo + hi) / 2;
      int mid2 = mid1 + 1;

      if (nums[mid1] < nums[mid2]) {
        lo = mid2;
      } else {
        hi = mid1;
      }
    }
    assert(0);
    return -1;
  }
};
