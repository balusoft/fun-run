/*
. String to Integer (atoi) My Submissions Question
Total Accepted: 93125 Total Submissions: 694591 Difficulty: Easy
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge,
please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given
input specs). You are responsible to gather all the input requirements up front.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your
function signature accepts a const char * argument, please click the reload
button  to reset your code definition.

spoilers alert... click to show requirements for atoi.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

1) case overflow, return zero
2) case -ve number, return negitive number
3) 0xfff => hex => valid integer
4) alphanum => 1234aaa => return integer 1234
5) whitespaces => ignore begin whietespaces..

*/
#include <string>
#include <cctype>
#include <iomanip>
#include <iostream>

class Solution {
public:
  int myAtoi(const std::string &str) {
    bool firstDigitFound = false;
    bool negative = false;
    int num = 0;
    for (size_t idx = 0; idx < str.length(); ++idx) {
      if (!firstDigitFound && std::isspace(str[idx])) {
        continue;
      }
      if (!firstDigitFound && str[idx] == '-') {
        firstDigitFound = true;
        negative = true;
        continue;
      }
      if (!firstDigitFound && str[idx] == '+') {
        firstDigitFound = true;
        continue;
      }
      if (std::isdigit(str[idx])) {
        firstDigitFound = true;
        int numTmp = num * 10 + str[idx] - '0';
        //std::cout << "(" << num << "," << numTmp << ")\n";
        if (numTmp/10 != num) {
          return negative ? INT_MIN : INT_MAX;
        }
        num = numTmp;
      } else {
        break;
      }
    }
    return negative ? num * -1 : num;
  }
};

void test(const std::string &num) {
  Solution s;
  std::cout << "str: " << num << " >>> " << s.myAtoi(num) << "\n";
}

int main() {
  test("    123");
  test("123");
  test("-123");
  test("+-123");
  test("--123");
  test("-123abc");
  test("-123 000 abc");
  test("- 000 abc");
  test("-999999999999999999999999999999999abc");
  test("999999999999999999999999999999999abc");
  test ("    10522545459");
  //std::cout << 2147483647 * 10 << "\n";
  //std::cout << 1052254545 * 10 << "\n";
  //1932610867
  //1052254545

  return 0;
}
