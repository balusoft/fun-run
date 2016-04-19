/**
286. Walls and Gates   My Submissions QuestionEditorial Solution
Total Accepted: 8338 Total Submissions: 22473 Difficulty: Medium
You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to
represent INF as you may assume that the distance to a gate is less than
2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible
to reach a gate, it should be filled with INF.

For example, given the 2D grid:
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:
3  -1   0   1
2   2   1  -1
1  -1   2  -1
0  -1   3   4

**/
class Solution {
public:
  void wallsAndGates(vector<vector<int>> &rooms) {
    // initialize with zero elements.
    std::queue<std::tuple<int, int>> q;
    for (int i = 0; i < rooms.size(); ++i) {
      for (int j = 0; j < rooms[0].size(); ++j) {
        if (rooms[i][j] == 0) {
          q.push(std::make_tuple(i, j));
        }
      }
    }

    bfs(rooms, q);
  }
  void bfs(vector<vector<int>> &rooms, std::queue<std::tuple<int, int>> &q) {
    while (!q.empty()) {
      // Get the top of the element
      int i, j;
      std::tie(i, j) = q.front();
      q.pop();
      int nextVal = rooms[i][j] + 1;
      int max = std::numeric_limits<int>::max();
      // a b c  i-1,j-1  i-1,j   i-1,j+1
      // x y z  i,  j-1  i,j     i,  j+1
      // l m n  i+1,j-1  i+1,j   i+1,j+1
      // check(i-1, j-1, rooms, q, nextVal);
      check(i - 1, j, rooms, q, nextVal);
      // check(i-1, j+1, rooms, q, nextVal);
      check(i, j - 1, rooms, q, nextVal);
      check(i, j + 1, rooms, q, nextVal);
      // check(i+1, j-1, rooms, q, nextVal);
      check(i + 1, j, rooms, q, nextVal);
      // check(i+1, j+1, rooms, q, nextVal);
    }
  }
  void check(const int i, const int j, vector<vector<int>> &rooms,
             std::queue<std::tuple<int, int>> &q, const int nextVal) {
    if ((i >= 0 && i <= rooms.size() - 1) &&
        (j >= 0 && j <= rooms[0].size() - 1) &&
        rooms[i][j] == std::numeric_limits<int>::max()) {
      rooms[i][j] = nextVal;
      q.push(std::make_tuple(i, j));
    }
  }
};
