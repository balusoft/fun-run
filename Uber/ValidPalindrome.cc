/*

125. Valid Palindrome My Submissions Question
Total Accepted: 94110 Total Submissions: 399891 Difficulty: Easy
Given a string, determine if it is a palindrome, considering only alphanumeric
characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask
during an interview.

For the purpose of this problem, we define empty string as valid palindrome.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss


*/
#include <string>
#include <cctype>
#include <iostream>

class Solution {
public:
  bool isPalindrome(const std::string& s) {
    if (s.empty()) {
      return true;
    }
    size_t sidx=0;
    size_t eidx=s.length()-1;
    while (sidx < eidx) {
      for (; sidx <= eidx; ++sidx) {
        if (std::isalnum(s[sidx])) {
          break;
        }
      }
      if (sidx >= eidx) { return true; }
      for (; eidx >= sidx; --eidx) {
        if (std::isalnum(s[eidx])) {
          break;
        }
      }
      if (eidx <= sidx) { return true; }
      if (std::tolower(s[sidx]) != std::tolower(s[eidx])) {
        return false;
      }
      ++sidx;
      --eidx;
    }
    return true;
  }
};

