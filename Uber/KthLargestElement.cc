/**
Find the kth largest element in an unsorted array. Note that it is the kth
largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.
*/

#include <vector>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cxxtest/TestSuite.h>

using namespace std;
class Solution {
  void swap(int &i, int &j) {
    int tmp= i;
    i = j;
    j = tmp;
  }
public:
  int partition(vector<int> &nums, int start, int end) {
    //int p = (rand()%(end-start)) + start;
    //swap(nums[end], nums[p]);
    int p = end;
    int wall=start;
    for (int i=start; i<end; ++i) {
      if (nums[i] < nums[p]) {
        swap(nums[i], nums[wall]);
        ++wall;
      }
      //std::cout <<"wall: " << wall << ":";
      //copy(nums.begin() + start, nums.begin() + end + 1,
      //     ostream_iterator<int>(cout, ", "));
      //std::cout << "\n";
    }
    swap(nums[p], nums[wall]);
    //std::cout << "wall: " << wall << ":";
    //copy(nums.begin() + start, nums.begin() + end + 1,
    //     ostream_iterator<int>(cout, ", "));
    //std::cout << "\n";
    return wall;
  }

  int findKthSmallest(vector<int> &nums, int start, int end, int k) {
    assert(start < nums.size());
    assert(end >= 0);
    assert(start <= k-1);
    assert(end >= k-1);
    int p = partition(nums, start, end);
    //std::cout << "s: " << start << " e: " << end << " k: " << k;
    //std::cout << " p: " << p << '\n';
    //copy(nums.begin(), nums.end(), ostream_iterator<int>(cout, ", "));
    //std::cout <<"\n";
    if (p == k-1) {
      return nums[k-1];
    } else if (p > k-1) {
      return findKthSmallest(nums, start, p-1, k);
    } else {
      return findKthSmallest(nums, p+1, end, k);
    }
  }
public:
  int findKthLargest(vector<int> &nums, int k) {
    return findKthSmallest(nums, 0, nums.size()-1, nums.size() - k + 1);
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    std::vector<int> v{ 5, 4, 1, 2, 3, 10};
    Solution s;
    TS_ASSERT_EQUALS(s.partition(v, 0, v.size()-1), 5);
    TS_ASSERT_EQUALS(s.partition(v, 1, v.size()-2), 3);
    TS_ASSERT_EQUALS(s.findKthLargest(v, 3), 4);
    TS_ASSERT_EQUALS(s.findKthLargest(v, 1), 10);
  }
};
