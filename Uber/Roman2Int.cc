/*

13. Roman to Integer My Submissions Question
Total Accepted: 77175 Total Submissions: 199835 Difficulty: Easy
Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss


I   1
IV  4
V   5
IX  9
X   10
XL  40
L   50
XC  90
C   100
CD  400
D   500
CM  900
M   1000

I => V X
X => L C
C => D M
*/

#include <string>
#include <iostream>
#include <map>

class Solution {
public:
  int romanToInt(const std::string& s) {
    const static std::map<std::string, int> roman2int{
        {"I", 1},   {"IV", 4},   {"V", 5},   {"IX", 9},  {"X", 10},
        {"XL", 40}, {"L", 50},   {"XC", 90}, {"C", 100}, {"CD", 400},
        {"D", 500}, {"CM", 900}, {"M", 1000}};
    int num = 0;
    for (size_t idx=0; idx<s.length(); ++idx) {
      if (idx + 1 < s.length() &&
          roman2int.find(s.substr(idx, 2)) != roman2int.end()) {
          num += roman2int.at(s.substr(idx, 2));
          ++idx;
      } else {
        num += roman2int.at(s.substr(idx, 1));
      }
    }
    return num;
  }
};
void test(const std::string& s) {
  Solution sol;
  std::cout << "Roman: " << s << " >>>> Int: " << sol.romanToInt(s) << "\n";
}
int main() {
  test("MMDCCLXV");
}
