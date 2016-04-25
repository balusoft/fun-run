#include <cassert>
#include <iostream>
#include <vector>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        /*
        1) need a dfs algorithm.Follow below from dfs.
        2) dfs takes i,j
        3) if i == rmax-1 and j== cmax-1 return.
        4) nextGen = 0;
        5) aliveCount();
        6) if alive and aliveCount is < 2 or aliveCount > 3 nextGen=false
        7) if alive and aliveCount is 2 || 3, nextGen = true;
        8) if dead and aliveCount is 3, nextGen=true.
        9) if i == rmax-1; j++
        10) if j == rmax-1; i++
        11) dfs (i, j, board)
        */
        if (board.empty() || board[0].empty()) {
            return;
        }
        dfs(board, 0, 0);
    }
    void dfs(vector<vector<int>>& board, int i, int j) {
        std::cout << std::boolalpha << "i:" << i << " j:" << j << "\n";
        bool alive=board[i][j];
        int aCount = getAliveCount(board, i, j);
        std::cout << "i:" << i << " j:" << j << " ac:" << aCount << "\n";
        if (alive) {
            if (aCount < 2 || aCount > 3) alive = false;
            else if (aCount == 2 || aCount == 3) alive = true;
            //else assert(0 == "Out of range");
        } else {
            if (aCount == 3) {
                alive = true;
            }
        }
        int ni=i;
        int nj=j;
        if (ni < board.size()-1 || nj < board[0].size()-1) {
            if (nj < board[0].size()-1) {
                ++nj;
            } else if (ni < board.size()-1) {
                ++ni;
                nj=0;
            } else {
                assert(0 == "why why");
            }
            std::cout << std::boolalpha << "i:" << i << " j:" << j << " al:" << alive << "\n";
            dfs (board, ni, nj);
        }
        std::cout << std::boolalpha << "i:" << i << " j:" << j << " al:" << alive << "\n";
        board[i][j] = alive;
    }
    int getAliveCount(const vector<vector<int>>& board, int i, int j) {
        // i-1,j-1  i-1,j  i-1,j+1
        // i,  j-1  i, j   i, j+1
        // i+1,j-1  i+1,j  i+1,j+1
        int count=0;
        if (check(board, i-1, j-1)) ++count;
        if (check(board, i-1, j)) ++count;
        if (check(board, i-1, j+1)) ++count;
        if (check(board, i, j-1)) ++count;
        if (check(board, i, j+1)) ++count;
        if (check(board, i+1, j-1)) ++count;
        if (check(board, i+1, j)) ++count;
        if (check(board, i+1, j+1)) ++count;
        return count;
    }
    bool check(const vector<vector<int>>& board, int i, int j) {
        return (i >=0 && i <board.size()) && (j>=0 && j<board[0].size()) && board[i][j];
    }
};
class TestSolution : public CxxTest::TestSuite {
public:
  void test_foo() {
    std::vector<std::vector<int>> board{{0}, {0}};
    Solution s;
    s.gameOfLife(board);
  }
};
