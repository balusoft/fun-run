/*

Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with
the character '.'.


A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the
filled cells need to be validated.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

http://sudoku.com.au/TheRules.aspx

*/
#include <vector>
#include <iostream>
static bool checkVal(char ch, std::vector<int> &check) {
  if ('.' == ch) {
    return true;
  }
  if (!check[ch-'0']) {
    check[ch-'0'] = true;
    return true;
  }
  return false;
}
class Solution {
public:
  bool isValidSudoku(const std::vector<std::vector<char>> &board) {
    int rmax = board.size();
    int cmax = board[0].size();
    //row checks
    for (int r=0; r<rmax; ++r) {
      std::vector<int> check(10, false);
      for (int c=0; c<cmax; ++c) {
        if (!checkVal(board[r][c], check)) {
          return false;
        }
      }
    }
    //col checks
    for (int c=0; c<cmax; ++c) {
      std::vector<int> check(10, false);
      for (int r=0; r<rmax; ++r) {
        if (!checkVal(board[r][c], check)) {
          return false;
        }
      }
    }
    // box checks
    for (int r = 0; r < rmax; r += 3) {
      for (int c = 0; c < cmax; c += 3) {
        std::vector<int> check(10, false);
        for (int rr=r; rr<r+3; ++rr) {
          for (int cc=c; cc<c+3; ++cc) {
            if (!checkVal(board[rr][cc], check)) {
              return false;
            }
          }
        }
      }
    }
    return true;
  }
};

int main() {
  std::vector<std::vector<char>> sudoku {
    {'.', '8', '7', '6', '5', '4', '3', '2', '1'},
    {'2', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'3', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'4', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'5', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'6', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'8', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'9', '.', '.', '.', '.', '.', '.', '.', '.'},
  };
  Solution s;
  std::cout << std::boolalpha << "isvalid >>> " << s.isValidSudoku(sudoku)
            << "\n";
}
