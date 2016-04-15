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

Read this:
https://leetcode.com/discuss/80266/java-dfs-memoization-dfs-and-pruning-solutions-with-analysis

*/
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  vector<string> wordBreak(string s, unordered_set<string> &wordDict) {
    std::unordered_map<int, std::vector<string>> memo;
    return dfsTwo(s, wordDict);
  }
  int getMaxLength(const unordered_set<string> &dict) {
    size_t max=0;
    for (const auto &w : dict) {
      max = std::max(max, w.length());
    }
    return max;
  }
  std::vector<std::string>
  dfsTwo(const std::string &s, const unordered_set<string> &wordDict) {
    std::unordered_map<int, std::vector<int> > startPos;
    int maxWordLen = getMaxLength(wordDict);
    for (int i=s.length()-1; i>=0; --i) {
      for (int j = i; j >= 0 && j >= i - maxWordLen; --j) {
        if (wordDict.count(s.substr(j, i-j+1)) > 0) {
          startPos[i].push_back(j);
        }
      }
    }
    std::vector<std::string> rslt;
    dfs (s, startPos, s.length()-1, "", rslt);
    return rslt;
  }
  void dfs(const std::string &s,
           const std::unordered_map<int, std::vector<int>> &startPos,
           const int end, const std::string &path,
           std::vector<std::string> &rslt) {
    assert(end >= -1);
    if (end == -1) {
      rslt.push_back(path.substr(1));
    }
    if (startPos.count(end) > 0) {
      for (int st : startPos.at(end)) {
        std::string newPath(path);
        newPath = " " + s.substr(st, end - st + 1) + newPath;
        dfs(s, startPos, st - 1, newPath, rslt);
      }
    }
  }

  std::vector<std::string>
  dfsOne(const std::string &s, const int st,
      const std::unordered_set<std::string> &dict,
      std::unordered_map<int, std::vector<string>> &memo) {
    // check is it already solved
    if (memo.count(st) > 0) {
      return memo[st];
    }
    std::vector<std::string> res;
    // check whether we reached terminal state?
    if (st == s.length()) {
      res.push_back("");
      return res;
    }
    // now for each word in dictionary check whether s:st is having one
    for (const auto &word : dict) {
      if (word.length() <= s.length() - st + 1 &&
          word == s.substr(st, word.length())) {
        std::vector<std::string> subList =
            dfsOne(s, st + word.length(), dict, memo);
        for (auto &subSt : subList) {
          std::string tmp(word);
          tmp += subSt.empty() ? "" : " ";
          tmp += subSt;
          res.push_back(tmp);
        }
      }
    }
    memo[st] = res;
    return res;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    std::string s("catsanddog");
    std::unordered_set<std::string> dict {"cat", "cats", "and", "sand", "dog"};
    Solution sol;
    TS_ASSERT_EQUALS(
        sol.wordBreak(s, dict),
        std::vector<std::string>({"cats and dog", "cat sand dog"}));
  }
};
