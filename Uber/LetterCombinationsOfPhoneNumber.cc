/*
17. Letter Combinations of a Phone Number My Submissions Question

Total Accepted: 73547 Total Submissions: 260884 Difficulty: Medium

Given a digit string, return all possible letter combinations that the number
could represent.

A mapping of digit to letters (just like on the telephone buttons) is given
below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in
any order you want.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss


*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct Context {
  Context(const std::string &dg)
      : digits(dg), level(-1), curOut(digits.size(), ' ') {}
  void addResult() {
    output.push_back(curOut);
  }
  const std::string &digits;
  int level;
  std::string curOut;
  std::vector<std::string> output;

};

void backtrack(Context &ctx) {
  static const std::unordered_map<char, std::string> phone {
    {'1', ""},
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"},
    {'0', ""},
  };
  ++ctx.level;
  if (ctx.level == ctx.digits.length()) {
    ctx.addResult();
    --ctx.level;
    return;
  }
  char curChar = ctx.digits[ctx.level];
  for (size_t idx = 0; idx < phone.at(curChar).size(); ++idx) {
    ctx.curOut[ctx.level] = phone.at(curChar)[idx];
    backtrack(ctx);
  }
  --ctx.level;
}

class Solution {
public:
  std::vector<std::string> letterCombinations(const std::string& digits) {
    Context ctx(digits);
    if (!digits.empty()) {
      backtrack(ctx);
    }
    return ctx.output;
  }
};

std::ostream &operator<<(std::ostream &ostr,
                         const std::vector<std::string> &vs) {
  ostr << "{";
  for (auto& s : vs) {
    std::cout << s << ", ";
  }
  ostr << "}";
  return ostr;
}
void test(const std::string& digits) {
  Solution s;
  std::cout << "digits: " << digits << " ::: " << s.letterCombinations(digits)
            << "\n";
}

int main() {
  test("34");
  test("23");
  test("");
}
