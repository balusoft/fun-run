/*
220. Contains Duplicate III My Submissions Question

Given an array of integers, find out whether there are two distinct indices i
and j in the array such that the difference between nums[i] and nums[j] is at
most t and the difference between i and j is at most k.
*/

#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <cxxtest/TestSuite.h>
using namespace std;
ostream& operator<<(ostream &ostr, const multiset<int> &vals) {
  ostr << "{";
  bool isFirst = true;
  for (auto &v : vals) {
    if (isFirst) {
      isFirst=false;
    } else {
      ostr << ",";
    }
    ostr << v;
  }
  ostr << "}";
  return ostr;
}
/*
If you have multiple elements in the range [first, last) whose value equals
the value val you are searching for, then the range [l, u) where

l = std::lower_bound(first, last, val)
u = std::upper_bound(first, last, val)
is precisely the range of elements equal to val within the range [first,
last). So l and u are the "lower bound" and "upper bound" for the equal range.
It makes sense if you're accustomed to thinking in terms of half-open
intervals.

(Note that std::equal_range will return both the lower and upper bound in a
pair, in a single call

Other example:
index: 0,  1,  2,  3,  4,  5,  6
data : 9, 10, 10, 16, 16, 18, 99

lb(10)=> index 1, 10
ub(10)=> index 3, 16

lb(17)=> index 5, 18
ub(17)=> index 5, 18

lb(100)=>end
ub(100)=>end
*/
class Solution {
public:
  bool containsNearbyAlmostDuplicate(const vector<int> &nums, int k, int t) {
    if (nums.empty()) {
      return false;
    }
    if (k == 0) {
      return false;
    }
    multiset<int> kBST;
    for (size_t i = 0; i < nums.size(); ++i) {
      //std::cout << "\nkBST: " << kBST << "\n";
      int lbV = nums[i] - t;     // lb is inclusive [
      set<int>::iterator lb = kBST.lower_bound(lbV);
      //std::cout << "(lbV) : (" << lbV << ")\n";
      // std::cout << std::boolalpha << "(lbB) : (" << (lb != kBST.end()) <<
      // ")\n";
      if (lb != kBST.end() && abs(*lb - nums[i]) <= t) {
        return true;
      }

      kBST.insert(nums[i]);
      if (kBST.size() > k) {
        //std::cout << "(i, k): (" << i << "," << k << ")\n";
        (void)kBST.erase(nums[i - k]);
      }
    }
    return false;
  }
};

class TestSolution : public CxxTest::TestSuite{
public:
  void test_example_desc() {
    vector<int> v{200, 210, 212, 70};
    Solution s;
    TS_ASSERT_EQUALS(s.containsNearbyAlmostDuplicate(v, 3, 70), true);
    TS_ASSERT_EQUALS(s.containsNearbyAlmostDuplicate(v, 1, 70), true);
    TS_ASSERT_EQUALS(s.containsNearbyAlmostDuplicate(v, 1, 1), false);
  }
  void test_example_asc() {
    vector<int> v{10, 20, 30, 40, 90, 200};
    Solution s;
    TS_ASSERT_EQUALS(s.containsNearbyAlmostDuplicate(v, 3, 70), true);
  }
  void test_fail1() {
    vector<int> v{3, 6, 0, 2};
    Solution s;
    TS_ASSERT_EQUALS(s.containsNearbyAlmostDuplicate(v, 2, 2), true);
  }
};
