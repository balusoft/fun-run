/*
58. Length of Last Word My Submissions Question
Total Accepted: 87646 Total Submissions: 301682 Difficulty: Easy
Given a string s consists of upper/lower-case alphabets and empty space
characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters
only.

For example,
Given s = "Hello World",
return 5.

*/
#include <string>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  int lengthOfLastWord(const string &s) {
    // skip all spaces from back
    int i=s.length()-1;
    for (; i >= 0; --i) {
      if(' ' == s[i]) {
        continue;
      } else {
        break;
      }
    }
    // if you go beyond zero there is no word return 0
    if (i < 0) {
      return 0;
    }
    // Now find for space,
    int j=i;
    for (; j>=0; --j) {
      if (' ' == s[j]) {
        break;
      }
    }
    return j>=0 ? i-j : i+1;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_all_spaces() {
    Solution s;
    TS_ASSERT_EQUALS(s.lengthOfLastWord("        "), 0);
    TS_ASSERT_EQUALS(s.lengthOfLastWord("a bcd   "), 3);
    TS_ASSERT_EQUALS(s.lengthOfLastWord("a bcd"), 3);
    TS_ASSERT_EQUALS(s.lengthOfLastWord("abcd"), 4);
    TS_ASSERT_EQUALS(s.lengthOfLastWord("  abcd  "), 4);
    TS_ASSERT_EQUALS(s.lengthOfLastWord("  a  "), 1);
    TS_ASSERT_EQUALS(s.lengthOfLastWord("  a"), 1);
    TS_ASSERT_EQUALS(s.lengthOfLastWord("a  "), 1);
    TS_ASSERT_EQUALS(s.lengthOfLastWord("a"), 1);
    TS_ASSERT_EQUALS(s.lengthOfLastWord(" a"), 1);
  }
};
