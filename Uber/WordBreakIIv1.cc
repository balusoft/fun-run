/*

140. Word Break II My Submissions Question
Total Accepted: 52927 Total Submissions: 271857 Difficulty: Hard
Given a string s and a dictionary of words dict, add spaces in s to construct a
sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",


dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

Subscribe to see which companies asked this question

Show Tags
Have you met this question in a real interview? Yes  No
Discuss

s = "catsanddog",
breakItem; if idx can break the word into two then set bit
     0011001001

itr1 0001001001
["cat sand dog"]
in first iteration 2 idx word found set it to zero
but 2-3 is not a valid word hence 3 idx left alone and rest of them.
However here we found rest of the words and added them to list

itr1 0001001001
itr2 0000000000

["cat sand dog", "cats and dog"]
However in this case we did not found any skips means no more combinations.
*/

#include <vector>
#include <unordered_set>
#include <string>

#include <cxxtest/TestSuite.h>
struct Context {
  Context(const std::string &s, const std::unordered_set<std::string> &dict)
  : s(s), dict(dict), level(-1), word(s.length(), false), start(0), length(0) {}

  const std::string &s;
  const std::unordered_set<std::string> &dict;
  int level;
  std::vector<std::string> out;
  std::vector<bool> word;
  int start;
  int length;
  std::unordered_map<std::string, std::string>

  bool isWord() {
    std::string ss = s.substr(start, length);
    bool res = dict.find(ss) != dict.end();
    //std::cout << std::boolalpha << "isWord: " << ss << ">> " << res << "\n";
    return res;
  }
  void addResult() {
    size_t st=0;
    size_t len = 0;
    std::string res;
    for (size_t idx=0; idx<s.length(); ++idx) {
      ++len;
      if (word[idx]) {
        if (res.empty()) {
          res = s.substr(st, len);
        } else {
          res += " ";
          res += s.substr(st, len);
        }
        st = idx+1;
        len=0;
      }
    }
    if (res.length() >= s.length()) {
      //std::cout << "result :>> " << res << "\n";
      out.push_back(res);
    }
    length = 0;
    start = 0;
  }
};

void backtrack(Context &ctx) {
  ++ctx.level;
  if (ctx.level == ctx.s.length()) {
    ctx.addResult();
    --ctx.level;
    return;
  }
  ++ctx.length;
  if (ctx.isWord()) {
    //std::cout << "found word at:: " <<  ctx.level << "\n";
    //case: make it as a word
    int oldStart = ctx.start;
    int oldLength = ctx.length;
    ctx.start = ctx.level+1;
    ctx.length = 0;
    ctx.word[ctx.level] = true;
    backtrack(ctx);
    ctx.start = oldStart;
    ctx.length = oldLength;
    ctx.word[ctx.level] = false;
  }
  //case: make it as not a word
  backtrack(ctx);
  --ctx.length;
  --ctx.level;
}

class Solution {
public:
  std::vector<std::string>
  wordBreak(const std::string &s,
            const std::unordered_set<std::string> &wordDict) {
    Context ctx(s, wordDict);
    if (s.empty() || wordDict.empty()) {
      return ctx.out;
    }
    backtrack(ctx);
    return ctx.out;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    Solution s;
    std::vector<std::string> out =
        s.wordBreak("catsanddog", {"cat", "cats", "and", "sand", "dog"});
    TS_ASSERT_EQUALS(out.size(), 2);
    TS_ASSERT_EQUALS(out[0], "cat sand dog");
    TS_ASSERT_EQUALS(out[1], "cats and dog");
  }
};
