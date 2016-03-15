/*
Given an array nums, there is a sliding window of size k which is moving from
the very left of the array to the very right. You can only see the k numbers in
the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
1 [3  -1  -3] 5  3  6  7       3
1  3 [-1  -3  5] 3  6  7       5
1  3  -1 [-3  5  3] 6  7       5
1  3  -1  -3 [5  3  6] 7       6
1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for
non-empty array.

Follow up:
Could you solve it in linear time?

Show Hint

[1  3  -1] -3  5  3  6  7       3
Q: 3
1  [3  -1 -3]  5  3  6  7       3
Q: 3 -1
1  3  [-1 -3  5]  3  6  7       5
Q: 5
1  3  -1 [-3  5  3]  6  7       5
Q: 5
1  3  -1 -3  [5  3  6 ] 7       6
Q: 6
1  3  -1 -3  5  [3  6  7]       7
Q: 7
*/

#include <vector>
#include <deque>
#include <iostream>

class Solution {
public:
  std::vector<int> maxSlidingWindow(const std::vector<int> &nums, int k) {
    std::deque<int> qu;
    std::vector<int> swm;
    if (nums.empty() || k <= 0 || nums.size() < k) {
      return swm;
    }
    swm.reserve(nums.size() - k + 1);
    int i = 0;
    for (; i < k; ++i) {
      while (!qu.empty() && nums[i] >= nums[qu.back()]) {
        qu.pop_back();
      }
      qu.push_back(i);
    }

    for (; i < nums.size(); ++i) {
      // Add front element to swm
      swm.push_back(nums[qu.front()]);

      // Pop front element all element if it is i-k
      if (qu.front() == i - k) {
        qu.pop_front();
      }

      // pop all elements which are less than nums[i]
      while (!qu.empty() && nums[i] >= nums[qu.back()]) {
        qu.pop_back();
      }

      // In two cases we need to add i to qu
      // 1) if qu is empty
      // 2) if qu back is less than nums[i]
      if (qu.empty() || nums[i] < nums[qu.back()]) {
        qu.push_back(i);
      }
    }
    swm.push_back(nums[qu.front()]);
    return swm;
  }
};
void test(const std::vector<int> &nums, int k) {
  for (auto i : nums) {
    std::cout << i << " ";
  }
  std::cout << ": ";
  Solution s;
  std::vector<int> swm = s.maxSlidingWindow(nums, k);
  for (auto i : swm) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}
int main() {
  test({1, 3, -1, -3, 5, 3, 6, 7}, 33);
  test({7, 2, 4}, 2);
  return 0;
}
