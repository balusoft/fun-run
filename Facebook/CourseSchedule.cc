/**
210. Course Schedule II   My Submissions QuestionEditorial Solution
Total Accepted: 25351 Total Submissions: 121005 Difficulty: Medium
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to
first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the
ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it
is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have
finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have
finished both courses 1 and 2. Both courses 1 and 2 should be taken after you
finished course 0. So one correct course order is [0,1,2,3]. Another correct
ordering is[0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency
matrices. Read more about how a graph is represented.

click to show more hints.

Subscribe to see which companies asked this question
**/

#include <vector>
#include <map>
#include <list>
#include <queue>
#include <cassert>

using Graph=std::vector<std::list<int>>;
class Solution {
public:
  std::vector<int>
  findOrder(const int numCourses,
            const std::vector<std::pair<int, int>> &prerequisites) {
    Graph g(numCourses);
    makeGraph(numCourses, prerequisites, g);
    return topologicalOrder(g);
  }
  void makeGraph(const int numCourses,
                 const std::vector<std::pair<int, int>> &prerequisites,
                 Graph &g) {
    //[1, 0] => 0 to 1 edge
    for (auto &e : prerequisites) {
      g[e.second].push_back(e.first);
    }
  }
  std::vector<int> topologicalOrder(const Graph &g) {
    std::vector<bool> discovered(g.size(), false);
    std::vector<bool> processed(g.size(), false);
    std::list<int> order;
    for (size_t i=0; i<g.size(); ++i) {
      if (discovered[i]) {
        continue;
      }
      if (!dfs(g, i, discovered, processed, order)) {
          return std::vector<int>();
      }
    }
    return std::vector<int>(order.begin(), order.end());
  }

  bool dfs(const Graph &g, const int v,
          std::vector<bool> &discovered,
          std::vector<bool> &processed,
          std::list<int> &order) {
    discovered[v] = true;
    for (auto ev : g[v]) {
      if (discovered[ev]) {
        if (!processed[ev]) {
        // loop detected.
          return false;
        }
      } else {
        if (!dfs(g, ev, discovered, processed, order)) {
          return false;
        }
      }
    }
    order.insert(order.begin(), v);
    processed[v] = true;
    return true;
  }
};

#if 0
  // @return true, acyclic, false cyclic
  bool bfs(const Graph &g, const int v,
           std::vector<bool> &visited,
           std::vector<bool> &processed,
           std::vector<int> &order) {
    if (visited[v]) {
      return true;
    }
    std::queue<int> q;
    q.push(v);
    while (!q.empty()) {
      int cv = q.front();
      if (processed[cv]) {
        return false;//cycle here.
      }
      q.pop();
      order.push_back(cv);
      for (auto n : g[cv]) {
        if (!visited[n]) {
          q.push(n);
        }
        visited[n] = true;
      }
      processed[cv] = true;
    }
    return true;
  }
#endif

class TestSolution : public CxxTest::TestSuite {
public:
  void test_foo() {
    Solution s;
    TS_ASSERT_EQUALS(s.findOrder(2, std::vector<std::pair<int, int>>({{0, 1}})),
                     std::vector<int>({1, 0}));
    TS_ASSERT_EQUALS(s.findOrder(2, std::vector<std::pair<int, int>>({{1, 0}})),
                     std::vector<int>({0, 1}));
    TS_ASSERT_EQUALS(s.findOrder(4, std::vector<std::pair<int, int>>(
                                        {{1, 0}, {2, 0}, {3, 1}, {3, 2}})),
                     std::vector<int>({0, 2, 1, 3}));
  }
};
