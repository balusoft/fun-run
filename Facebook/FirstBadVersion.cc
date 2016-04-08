/*
You are a product manager and currently leading a team to develop a new product.
Unfortunately, the latest version of your product fails the quality check. Since
each version is developed based on the previous version, all the versions after
a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first
bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether
version is bad. Implement a function to find the first bad version. You should
minimize the number of calls to the API.

Credits:
Special thanks to @jianchao.li.fighter for adding this problem and creating all
test cases.

Subscribe to see which companies asked this question
*/
// Forward declaration of isBadVersion API.
#include <cxxtest/TestSuite.h>
#include <limits>
int badBegin=4;
bool isBadVersion(int version) {
  return version >= badBegin;
}

class Solution {
public:
  int firstBadVersion(int n) {
    /*
      low = good
          hi = bad
            mid = bad
              low <- low
              high <- mid
            mid = good
              low <- mid + 1
              high <- high
      low = bad
        return low
     */
    int low = 1;
    int high = n;
    while (low <= high) {
      int mid = low + ((high - low)/2);
      //std::cout << "\n*******mid = " << mid;
      if (isBadVersion(low)) {
        return low;
      } else {
        if (isBadVersion(high)) {
          if (isBadVersion(mid)) {
            high = mid;
          } else {
            low = mid + 1;
          }
        } else {
          break;
        }
      }
    }
    return -1;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    badBegin=4;
    Solution s;
    TS_ASSERT_EQUALS(s.firstBadVersion(100), badBegin);
    badBegin=99;
    TS_ASSERT_EQUALS(s.firstBadVersion(999), badBegin);
    TS_ASSERT_EQUALS(s.firstBadVersion(99), badBegin);
    TS_ASSERT_EQUALS(s.firstBadVersion(98), -1);
    /*
    2126753390 versions
    1702766719 is the first bad version.
    */
    //std::cout << "\n\n******Int max: " << std::numeric_limits<int>::max();
    badBegin=1702766719;
    TS_ASSERT_EQUALS(s.firstBadVersion(2126753390), 1702766719);
  }
};
