/*
74. Search a 2D Matrix My Submissions Question
Total Accepted: 72925 Total Submissions: 218338 Difficulty: Medium

Write an efficient algorithm that searches for a value in an m x n matrix.
This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous
row.

For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
      Given target = 3, return true.

      Subscribe to see which companies asked this question
*/
#include <vector>
#include <iostream>
int valueAt(const std::vector<std::vector<int>>& matrix, int idx) {
  int i = idx/matrix[0].size();
  int j = idx%matrix[0].size();
  return matrix[i][j];
}
bool search(const std::vector<std::vector<int>>& matrix, int target) {
  if (matrix.empty()) {
    return false;
  }
  int low=0;
  int high=(matrix.size() * matrix[0].size()) - 1;
  while (low <= high) {
    int mid = (low+high)/2;
    if (valueAt(matrix, mid) == target) {
      return true;
    } else if (valueAt(matrix, mid) < target) {
      low = mid+1;
    } else {
      high = mid-1;
    }
  }
  return false;
}
class Solution {
public:
  bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    return search(matrix, target);
  }
};

int main() {
  std::vector<std::vector<int>> matrix = {
    //{1,   3,  5,  7},
    //{10, 11, 16, 20},
    //{23, 30, 34, 50}
  };

  Solution s;
  std::cout << std::boolalpha << s.searchMatrix(matrix, 3) << "\n";
  std::cout << std::boolalpha << s.searchMatrix(matrix, 10) << "\n";
  std::cout << std::boolalpha << s.searchMatrix(matrix, 101) << "\n";
}
