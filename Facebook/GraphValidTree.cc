/**

261. Graph Valid Tree   My Submissions QuestionEditorial Solution
Total Accepted: 11410 Total Submissions: 35030 Difficulty: Medium
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge
is a pair of nodes), write a function to check whether these edges make up a
valid tree.

For example:

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.

Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.

Hint:

Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return? Is
this case a valid tree?
According to the definition of tree on Wikipedia: “a tree is an undirected graph
in which any two vertices are connected by exactly one path. In other words, any
connected graph without simple cycles is a tree.”
Note: you can assume that no duplicate edges will appear in edges. Since all
edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear
together in edges.

Show Company Tags
Show Tags
Show Similar Problems

*/

using Graph = std::vector<std::list<int>>;
enum class VertexState {
  UNDISCOVERED,
  DISCOVERED,
  PROCESSED,
};
class Solution {
public:
  bool validTree(int n, vector<pair<int, int>> &edges) {
    Graph g(n);
    makeGraph(g, edges);
    std::vector<int> p(n, -1);
    std::vector<VertexState> state(n, VertexState::UNDISCOVERED);
    if (!dfs(g, 0, state, p)) {
      return false;
    }
    for (int i = 1; i < n; ++i) {
      if (state[i] != VertexState::UNDISCOVERED) {
        continue;
      }
      // no need to proceed with forest of trees...
      // we got our answer.. this is not tree..
      return false;
    }
  }
  void makeGraph(Graph &g, const vector<pair<int, int>> &edges) {
    for (auto &e : edges) {
      g[e.first].push_back(e.second);
      g[e.second].push_back(e.first);
    }
  }
  bool dfs(const Graph &g, const int v, std::vector<VertexState> &state,
           std::vector<int> &p) {
    state[v] = VertexState::DISCOVERED;
    for (int u : g[v]) {
      // std::cout << "(u, v) : " << "(" << u << "," << v << ")\n";
      // std::cout << "state[u]: " <<
      // static_cast<std::underlying_type<VertexState>::type>(state[u]) << "\n";
      // std::cout << "p[u]: " << p[u] << "\n";
      switch (state[u]) {
      // if state is undiscovered, this is tree edge.
      case VertexState::UNDISCOVERED:
        p[u] = v;
        if (!dfs(g, u, state, p)) {
          return false;
        }
        break;
      // if state is DISCOVERED, this is back edge.
      case VertexState::DISCOVERED:
        // unless this edge is with your parent it is back edge
        if (p[v] != u) {
          return false;
        }
        break;
      // if vertex is already processed, this is back edge too.
      // but we should have caught this already?
      case VertexState::PROCESSED:
        return false;
        break;
      }
    }
    state[v] = VertexState::PROCESSED;
    // std::cout << "4vertex end v: " << v << std::endl;
    return true;
  }
};
