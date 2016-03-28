/*
258. Add Digits My Submissions QuestionEditorial Solution
Total Accepted: 82304 Total Submissions: 170470 Difficulty: Easy
Given a non-negative integer num, repeatedly add all its digits until the result
has only one digit.

For example:

Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one
digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime?

Hint:

A naive implementation of the above process is trivial. Could you come up with
other methods?
What are all the possible results?
How do they occur, periodically or randomly?
You may find this Wikipedia article useful.

*/

#include <cxxtest/TestSuite.h>

class Solution {
public:
  int addDigits(int num) {
    if (num == 0) {
      return 0;
    }

    int val = num%9;
    return val == 0 ? 9 : val;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    TS_ASSERT_EQUALS(s.addDigits(0), 0);
    TS_ASSERT_EQUALS(s.addDigits(9), 9);
    TS_ASSERT_EQUALS(s.addDigits(99), 9);
    TS_ASSERT_EQUALS(s.addDigits(1233), 9);
    TS_ASSERT_EQUALS(s.addDigits(123), 6);
  }
};
