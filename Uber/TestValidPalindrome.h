
#include <cxxtest/TestSuite.h>
#include "ValidPalindrome.cc"

class ValidPalindromeTestSuite : public CxxTest::TestSuite {
public:
  void test_all() {
    Solution s;
    // test("A man, a plan, a canal: Panama");
    TS_ASSERT_EQUALS(s.isPalindrome("race a car"), false);
    TS_ASSERT_EQUALS(s.isPalindrome("a."), true);
    TS_ASSERT_EQUALS(s.isPalindrome(".a."), true);
    TS_ASSERT_EQUALS(s.isPalindrome(".a"), true);
    TS_ASSERT_EQUALS(s.isPalindrome(".a+++++====="), true);
    TS_ASSERT_EQUALS(
        s.isPalindrome(
            "++++++++++++++++++++++++++++++++++++++++++++++++++++++++"),
        true);
  }
};
