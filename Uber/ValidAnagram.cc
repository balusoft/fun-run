/*
Valid Anagram My Submissions Question
Total Accepted: 70441 Total Submissions: 170322 Difficulty: Easy
Given two strings s and t, write a function to determine if t is an anagram of
s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution
to such case?
*/

#include <string>
#include <unordered_map>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  bool isAnagram(const string &s, const string &t) {
    unordered_map<char, unsigned> map;
    for (auto &c : s) {
      map[c] += 1;
    }

    for (auto &c : t) {
      if (map.find(c) == map.end()) {
        return false;
      } else {
        if (map[c] == 1) {
          (void) map.erase(c);
        } else {
          map[c] -= 1;
        }
      }
    }

    return map.empty();
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    TS_ASSERT_EQUALS(s.isAnagram("anagram", "nagaram"), true);
    TS_ASSERT_EQUALS(s.isAnagram("rat", "car"), false);
  }
  Solution s;
};
