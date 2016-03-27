/*
304. Range Sum Query 2D - Immutable My Submissions Question
Total Accepted: 10240 Total Submissions: 46492 Difficulty: Medium
Given a 2D matrix matrix, find the sum of the elements inside the rectangle
defined by its upper left corner (row1, col1) and lower right corner (row2,
col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1)
and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
[3, 0, 1, 4, 2],
[5, 6, 3, 2, 1],
[1, 2, 0, 1, 5],
[4, 1, 0, 1, 7],
[1, 0, 3, 0, 5]
]

1 2 3  4  5
1 3 6 10 15

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12

Note:
 You may assume that the matrix does not change.
 There are many calls to sumRegion function.
 You may assume that row1 ≤ row2 and col1 ≤ col2.
 Subscribe to see which companies asked this question
*/

#include <vector>
#include <cxxtest/TestSuite.h>
#include <iostream>

using namespace std;
ostream& operator<<(ostream& ostr, const vector<vector<int>> &matrix) {
  ostr << "{";
  bool isFRow=true;
  for (auto &r: matrix) {
    if (isFRow) {
      isFRow = false;
    } else {
      ostr <<",";
    }
    ostr <<"\n";
    bool isFirst=true;
    ostr << "{";
    for (auto &c: r) {
      if (isFirst) {
        isFirst=false;
      } else {
        ostr << ",";
      }
      ostr << c;
    }
    ostr << "}";
  }
  ostr <<"\n}";
  return ostr;
}
class NumMatrix {
public:
  NumMatrix(const vector<vector<int>> &matrix)
      : matrix(matrix), rmax(matrix.size()), cmax(0) {
    if (rmax>0) {
      cmax = matrix[0].size();
    }
    rollingSum=vector<vector<int>>(rmax+1, vector<int>(cmax+1, 0));

    // do rolling sum
    for (size_t i=1; i<rollingSum.size(); ++i) {
      for (size_t j=1; j<rollingSum[i].size(); ++j) {
        rollingSum[i][j] = rollingSum[i - 1][j] + rollingSum[i][j - 1] -
                           rollingSum[i - 1][j - 1] +
                           matrix[i-1][j-1];
      }
    }
    //std::cout << " \n" << matrix << "\n";
    //std::cout << " \n" << rollingSum << "\n";
  }
  int sumRegion(int r1, int c1, int r2, int c2) {
    if (r1 >= rmax || r1 >= rmax || c1 >= cmax || c2 >= cmax) {
      return 0;
    }
    return rollingSum[r2 + 1][c2 + 1] - rollingSum[r1][c2 + 1] -
              rollingSum[r2 + 1][c1] + rollingSum[r1][c1];
  }
private:
  const vector<vector<int>> matrix;
  vector<vector<int>> rollingSum;
  int rmax;
  int cmax;
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_one() {
    vector<vector<int>> matrix{
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
        };
    NumMatrix numMatrix(matrix);
    TS_ASSERT_EQUALS(numMatrix.sumRegion(0, 1, 2, 3), 9);
  }
  void test_example() {
    // Your NumMatrix object will be instantiated and called as such:
    vector<vector<int>> matrix{{3, 0, 1, 4, 2},
                               {5, 6, 3, 2, 1},
                               {1, 2, 0, 1, 5},
                               {4, 1, 0, 1, 7},
                               {1, 0, 3, 0, 5}};
    NumMatrix numMatrix(matrix);
    TS_ASSERT_EQUALS(numMatrix.sumRegion(0, 1, 2, 3), 19);
    TS_ASSERT_EQUALS(numMatrix.sumRegion(1, 2, 3, 4), 20);
    TS_ASSERT_EQUALS(numMatrix.sumRegion(10, 20, 30, 40), 0);
  }
  void test_base() {
    vector<vector<int>> matrix{{}};
    NumMatrix numMatrix(matrix);
    TS_ASSERT_EQUALS(numMatrix.sumRegion(0, 0, 0, 0), 0);
  }
};
