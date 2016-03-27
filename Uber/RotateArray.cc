/*
189. Rotate Array My Submissions Question
Total Accepted: 66645 Total Submissions: 319620 Difficulty: Easy
Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to
[5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways
to solve this problem.

[show hint]

Related problem: Reverse Words in a String II

1 2 3 4 5 6 7

5 6 7 1 2 3 4

swap (idx, ((size-shift)+idx % size)
*/

#include <vector>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  void rotate(vector<int> &nums, int k) {
    int size = nums.size();
    k = k%size;
    int count=0;
    for (int ki = 0; ki < size && count < size; ++ki) {
      int cIdx = ki;
      int nIdx = ((size - k) + cIdx) % size;
      int tmp = nums[ki];

      while (nIdx != ki) {
        nums[cIdx] = nums[nIdx];
        cIdx = nIdx;
        nIdx = ((size - k) + cIdx) % size;
        ++count;
      }
      nums[cIdx] = tmp;
      ++count;
    }
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_123() {
    std::vector<int> v{0, 1, 2};
    Solution s;
    s.rotate(v, 1);
    vector<int> rv{2, 0, 1};
    TS_ASSERT_EQUALS(v, rv);
    s.rotate(v, 2);
    rv={0, 1, 2};
    TS_ASSERT_EQUALS(v, rv);
    s.rotate(v, 3);
    TS_ASSERT_EQUALS(v, rv);
  }
  void test_1_7_w3() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
    std::vector<int> rv{5, 6, 7, 1, 2, 3, 4};
    Solution s;
    s.rotate(v, 3);
    TS_ASSERT_EQUALS(v, rv);
  }
  void test_max_k() {
    std::vector<int> v{1, 2};
    std::vector<int> rv{2, 1};
    Solution s;
    s.rotate(v, 3);
    TS_ASSERT_EQUALS(v, rv);

  }
  void test_1_6_w2() {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    std::vector<int> rv{5, 6, 1, 2, 3, 4};
    Solution s;
    s.rotate(v, 2);
    TS_ASSERT_EQUALS(v, rv);
  }
};
