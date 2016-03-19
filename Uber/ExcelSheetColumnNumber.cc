/*
171. Excel Sheet Column Number My Submissions Question
Total Accepted: 70561 Total Submissions: 172703 Difficulty: Easy
Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding
column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28
Credits:
Special thanks to @ts for adding this problem and
creating all test cases.
Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes No Discuss
*/

#include <string>
#include <iostream>
#include <cmath>

class Solution {
public:
  int titleToNumber(const std::string& s) {
    size_t slen = s.length();
    int num = 0;
    for (size_t i=0; i<slen; ++i) {
      num += std::pow(26, i) * (1+s[slen-1-i]-'A');
    }
    return num;
  }
};

void test(const std::string& s) {
  Solution sol;
  std::cout << "Col: " << s << "\n";
  std::cout << "Num: " << sol.titleToNumber(s) << "\n\n";
}

int main() {
  test("AA");
  test("A");
  test("B");
  test("AB");
  test("BA");
  test("AAA");
  return 0;
}
