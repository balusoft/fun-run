/*
79. Word Search My Submissions QuestionEditorial Solution
Total Accepted: 72034 Total Submissions: 316013 Difficulty: Medium
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where
"adjacent" cells are those horizontally or vertically neighboring. The same
letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/

#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

template <typename T>
std::ostream &operator<<(std::ostream &ostr, const std::vector<T> &v) {
  bool isFirst = false;
  ostr << "\n{";
  for (const auto &e : v) {
    if (isFirst) {
      isFirst = false;
    } else {
      ostr << ",";
    }
    ostr << e;
  }
  ostr << "}";
  return ostr;
}
using PPOI = std::tuple<int,int>;
class Solution {
public:
  struct Context {
    Context(const vector<vector<char>> &board, const string &word)
        : board(board), word(word),
          visited(board.size(), std::vector<bool>(board[0].size(), false)),
          wordFound(false), wordLen(0) {}

    const vector<vector<char>> &board;
    const string &word;
    vector<vector<bool>> visited;
    PPOI curPPOI;
    bool wordFound;
    int wordLen;
  };

  void getAdjacent(const Context &ctx, std::vector<PPOI> &adjPPOIs) {
    //std::cout << "visited: " << ctx.visited << "\n";
    // adjacent points are for i, j
    //  [i-1, j]  [i, j-1]  [i+1, j]   [i, j+1]
    int i = std::get<0>(ctx.curPPOI);
    int j = std::get<1>(ctx.curPPOI);
    //std::cout << "i: " << i << " j: " << j << "\n";
    char c = ctx.word[ctx.wordLen];
    if (i > 0 && !ctx.visited[i - 1][j] && c == ctx.board[i - 1][j]) {
      adjPPOIs.push_back(std::make_tuple(i - 1, j));
    }
    if (j > 0 && !ctx.visited[i][j - 1] && c == ctx.board[i][j - 1]) {
      adjPPOIs.push_back(std::make_tuple(i, j - 1));
    }
    if (i < ctx.board.size() - 1 && !ctx.visited[i + 1][j] &&
        c == ctx.board[i + 1][j]) {
      adjPPOIs.push_back(std::make_tuple(i + 1, j));
    }
    if (j < ctx.board[0].size() - 1 && !ctx.visited[i][j + 1] &&
        c == ctx.board[i][j + 1]) {
      adjPPOIs.push_back(std::make_tuple(i, j+1));
    }
  }
  void backtrack(Context &ctx) {
    if (ctx.wordFound) {
      return;
    }
    int i = std::get<0>(ctx.curPPOI);
    int j = std::get<1>(ctx.curPPOI);
    if (ctx.board[i][j] != ctx.word[ctx.wordLen]) {
      return;
    }
    ++ctx.wordLen; // remember to decrement while returning
    if (ctx.wordLen == ctx.word.length()) {
      ctx.wordFound = true;
      return;
    }
    std::vector<PPOI> adjPPOIs;
    //std::cout << "adj: " << ctx.board[i][j] << " >> ";
    adjPPOIs.reserve(4);
    getAdjacent(ctx, adjPPOIs);
    for (auto p : adjPPOIs) {
      //std::cout << "(" << std::get<0>(p) << "," << std::get<1>(p) << "),";
    }
    //std::cout << "\n";
    for (auto &point : adjPPOIs) {
      ctx.curPPOI = point;
      i = std::get<0>(ctx.curPPOI);
      j = std::get<1>(ctx.curPPOI);
      ctx.visited[i][j] = true;
      backtrack(ctx);
      ctx.visited[i][j] = false;
      if (ctx.wordFound) {
        break;
      }
    }
    --ctx.wordLen;
  }
  bool exist(vector<vector<char>> &board, string word) {
    if (board.empty() || board[0].empty()) {
      return false;
    }
    if (word.empty()) {
      return false;
    }
    // use backtracking
    for (int i = 0; i<board.size(); ++i) {
      for (int j = 0; j < board[i].size(); ++j) {
        if (word[0] != board[i][j]) {
          continue;
        }
        Context ctx(board, word);
        ctx.curPPOI = std::make_tuple(i, j);
        ctx.visited[i][j] = true;
        backtrack(ctx);
        if (ctx.wordFound) {
          return true;
        }
      }
    }
    return false;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_lc2() {
    //["ABCE","SFES","ADEE"]
    //"ABCESEEEFS"
    std::vector<vector<char>> board{
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'E', 'S'},
        {'A', 'D', 'E', 'E'}};
    Solution s;
    TS_ASSERT_EQUALS(s.exist(board, "ABCESEEEFS"), true);
    TS_ASSERT_EQUALS(s.exist(board, "ABCB"), false);
  }
  void test_lc() {
    std::vector<vector<char>> board{{'A', 'B'}} ;
    Solution s;
    TS_ASSERT_EQUALS(s.exist(board, "AB"), true);
    TS_ASSERT_EQUALS(s.exist(board, "ABCB"), false);
  }

  void test_example() {
    std::vector<vector<char>> board{
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}} ;
    Solution s;
    //word = "ABCCED", -> returns true,
    TS_ASSERT_EQUALS(s.exist(board, "ABCCED"), true);
    //word = "SEE", -> returns true,
    TS_ASSERT_EQUALS(s.exist(board, "SEE"), true);
    //word = "ABCB", -> returns false.
    TS_ASSERT_EQUALS(s.exist(board, "ABCB"), false);
  }
};
