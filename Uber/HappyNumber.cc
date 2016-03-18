/*
202. Happy Number My Submissions Question
Total Accepted: 59940 Total Submissions: 166529 Difficulty: Easy
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any
positive integer, replace the number by the sum of the squares of its digits,
and repeat the process until the number equals 1 (where it will stay), or it
loops endlessly in a cycle which does not include 1. Those numbers for which
this process ends in 1 are happy numbers.

Example: 19 is a happy number

1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1
Credits:
Special thanks to @mithmatt and @ts for adding this problem and creating all
test cases.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

Assumption: xyz => repetitive x^2 + y^2 + z^2 will converge to single digit

*/

#include <set>
#include <iostream>

class Solution {
public:
  bool isHappy(int n) {
    if (n == 0) { return false; }
    int nn = 0;
    std::set<int> knownValues;
    knownValues.insert(n);
    while (n != 0) {
      //std::cout << "*>>> " << n << "\n";
      nn += (n%10) * (n%10);
      n /= 10;
      if (n == 0) {
        std::cout << ">>> " << nn << "\n";
        if (nn == 1) {
          return true;
        }
        if (knownValues.find(nn) != knownValues.end()) {
          return false;
        }
        n = nn;
        knownValues.insert(n);
        nn = 0;
      }
    }
    //std::cout << ">>> " << n << "\n";
    return true;
  }
};

void test(int n) {
  Solution s;
  std::cout << std::boolalpha << "isHappy: " << n << " >> " << s.isHappy(n)
            << "\n";
}
int main() {
  test(17);
  test(19);
  test(7);
  //test(36);
}
