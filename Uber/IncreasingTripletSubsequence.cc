#include <vector>
using namespace std;
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        if (nums.size() < 3) {
            return false;
        }
        int min=INT_MAX;
        int mid=INT_MAX;
        for (auto n : nums) {
            if (n < min) {
                min = n;
            } else if (n > min) {
                if (n > mid) {
                    return true;
                } else {
                    mid = n;
                }
            }
        }
        return false;
    }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    std::vector<int> v1 { 2, 5, 3, -1, 4, 5};
    std::vector<int> v2 { 2, 5, 3, -1, -2};
    Solution s;
    TS_ASSERT_EQUALS(s.increasingTriplet(v1), true);
    TS_ASSERT_EQUALS(s.increasingTriplet(v2), false);
  }
};
