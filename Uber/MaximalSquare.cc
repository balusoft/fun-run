/**
221. Maximal Square My Submissions QuestionEditorial Solution
Total Accepted: 27107 Total Submissions: 115988 Difficulty: Medium
Given a 2D binary matrix filled with 0's and 1's, find the largest square
containing all 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.
Credits:
Special thanks to @Freezen for adding this problem and creating all test cases.

Subscribe to see which companies asked this question
*/
#include <vector>
#include <algorithm>
#include <cxxtest/TestSuite.h>
std::ostream& operator<<(std::ostream& ostr, const std::vector<int>& v) {
  bool isFirst=true;
  ostr << "{";
  for (auto& e : v) {
    if (isFirst) {
      isFirst=false;
    } else {
      ostr << ",";
    }
    ostr << e;
  }
  ostr << "}";
  return ostr;
}
class Solution {
public:
  int maximalSquare(std::vector<std::vector<char>> &matrix) {
    if (matrix.size() == 0) {
      return 0;
    }
    int curMax=0;
    if (std::find(matrix[0].begin(), matrix[0].end(), '1') != matrix[0].end()) {
       curMax = 1;
    }
    if (matrix.size() == 1) {
       return curMax;
    }
    std::vector<std::vector<int>> dp(2, std::vector<int>(matrix[0].size(), 0));
    for (size_t idx=0; idx<matrix[0].size(); ++idx) {
      dp[0][idx] = matrix[0][idx]-'0';
    }
    // take pointers to rows
    size_t prev = 0;
    //std::cout << "\n" << dp[prev] << "\n";
    for (size_t row=1; row < matrix.size(); ++row) {
      size_t curDpRow = row%2;
      //blind copy first element
      dp[curDpRow][0] = matrix[row][0]-'0';
      // go throw all elements from 1->size-1
      for (size_t col=1; col < matrix[curDpRow].size(); ++col) {
        if (matrix[row][col] == '1') {
          // x  y
          // a  c
          // In this example if x is >0 and a&y are >=x we can extend x to x+1
          int x = dp[prev][col-1];
          int y = dp[prev][col];
          int a = dp[curDpRow][col-1];

          dp[curDpRow][col] = std::min(x, std::min(y, a)) + 1;

          if (dp[curDpRow][col] > curMax) {
            curMax = dp[curDpRow][col];
          }
        } else {
          dp[curDpRow][col] = 0;
        }
      }
      prev = curDpRow;
      //std::cout << dp[prev] << "\n";
    }
    return curMax*curMax;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    std::vector<std::vector<char>> v1 { {'1','0','1','0','0'}, {'1','0','1','1','1'},
                                        {'1','1','1','1','1'}, {'1','0','0','1','0'}};
    std::vector<std::vector<char>> v2 {};
    std::vector<std::vector<char>> v3 { {'1','0','1','0','0'} };
    std::vector<std::vector<char>> v4 { {'1','1','1','1','1'}, {'1','1','1','1','1'},
                                        {'1','1','1','1','1'}, {'1','1','1','1','1'}};
    std::vector<std::vector<char>> v5 {{'1'}};
    std::vector<std::vector<char>> v6 { {'0','0','0'}, {'0','0','0'}, {'1','1','1'}};
    std::vector<std::string> vs {
    "101101",
    "111111",
    "011011",
    "111010",
    "011111",
    "110111"
    };
    std::vector <std::vector<char>> vv;
    for (auto &s : vs) {
       vv.push_back(std::vector<char>(s.begin(), s.end()));
    }
    Solution s;
    //TS_ASSERT_EQUALS(s.maximalSquare(v1), 4);
    //TS_ASSERT_EQUALS(s.maximalSquare(v2), 0);
    //TS_ASSERT_EQUALS(s.maximalSquare(v3), 1);
    //TS_ASSERT_EQUALS(s.maximalSquare(v4), 16);
    //TS_ASSERT_EQUALS(s.maximalSquare(v5), 1);
    //TS_ASSERT_EQUALS(s.maximalSquare(v6), 1);
    TS_ASSERT_EQUALS(s.maximalSquare(vv), 4);
  }
};
