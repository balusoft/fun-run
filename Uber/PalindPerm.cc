/* 266 Palindrome Permutation*/
/*
266. Palindrome Permutation My Submissions Question
Total Accepted: 10101 Total Submissions: 20121 Difficulty: Easy
Given a string, determine if a permutation of the string could form a
palindrome.

For example,
"code" -> False, "aab" -> True, "carerac" -> True.

Show Hint
Show Company Tags
Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss


*/
#include <iostream>
#include <string>
#include <unordered_set>

std::ostream &operator<<(std::ostream &ostr,
                         const std::unordered_set<char> &s) {
  ostr << "{";
  for (auto c : s) {
    ostr << c << ", ";
  }
  ostr << "}";
  return ostr;
}
class Solution {
public:
  bool canPermutePalindrome(const std::string &s) {
    if (s.empty()) {
      return true;
    }
    if (s.length() == 1) {
      return true;
    }
    if (s.length() == 2) {
      return s[0] == s[1];
    }
    std::unordered_set<char> uniqueChars;
    for (auto c : s) {
      uniqueChars.insert(c);
    }
    if (s.length() % 2 == 0) {
      return ((s.length() / 2) == uniqueChars.size());
    } else {
      return ((1 + s.length() / 2) == uniqueChars.size());
    }
  }
};

void test(const std::string& s) {
  Solution sol;
  std::cout << "Str: " << s << std::boolalpha
            << " << >> res: " << sol.canPermutePalindrome(s) << "\n";
  return;
}

int main() {
  test("code");
  test("aab");
  test("carerac");
  test("a");
  test("as");
  test("ass");
  test("aabc");
}
