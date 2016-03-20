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
#include <unordered_map>

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
    std::unordered_map<char, size_t> uniqueChars;
    for (auto c : s) {
      if (uniqueChars.find(c) == uniqueChars.end()) {
        uniqueChars[c] = 1;
      } else {
        uniqueChars[c] += 1;
      }
    }

    size_t evenC=0;
    size_t oddC=0;

    for (auto &kv : uniqueChars) {
      if (kv.second % 2 == 0) {
        ++evenC;
      } else {
        ++oddC;
      }
    }
    return oddC <= 1;
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
  test("aaaa");
  test("aaa");
}
