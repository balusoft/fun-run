/*
38. Count and Say My Submissions QuestionEditorial Solution
Total Accepted: 77382 Total Submissions: 269531 Difficulty: Easy
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss
*/
#include <string>
#include <sstream>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  string getNext(const string& cur) {
    char prev=cur[0];
    int count=1;
    std::string res;
    for (size_t i=1; i<cur.length(); ++i) {
      if (cur[i] == prev) {
        ++count;
      } else {
        std::ostringstream ostr;
        ostr << count << prev;
        res += ostr.str();
        prev = cur[i];
        count=1;
      }
    }
    std::ostringstream ostr;
    ostr << count << prev;
    res += ostr.str();
    return res;
  }
  string countAndSay(int n) {
    if (n <= 0) {
      return "";
    }
    std::string res("1");
    for (int i=1; i<n; ++i) {
      // Go through each element here
      // And check count
      res = getNext(res);
    }
    return res;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    //TS_ASSERT_EQUALS(s.countAndSay(1), "1");
    //TS_ASSERT_EQUALS(s.countAndSay(2), "11");
    TS_ASSERT_EQUALS(s.countAndSay(3), "21");
    TS_ASSERT_EQUALS(s.countAndSay(4), "1211");
    TS_ASSERT_EQUALS(s.countAndSay(5), "111221");
    TS_ASSERT_EQUALS(s.countAndSay(6), "312211");
    TS_ASSERT_EQUALS(s.countAndSay(0), "");
  }
};
