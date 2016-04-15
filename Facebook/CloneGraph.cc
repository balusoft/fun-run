/*
Clone an undirected graph. Each node in the graph contains a label and a list of
its neighbors.
OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and
each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as
separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a
self-cycle.
Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/
*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <cxxtest/TestSuite.h>
struct UndirectedGraphNode {
  int label;
  std::vector<UndirectedGraphNode *> neighbors;
  UndirectedGraphNode(int x) : label(x){};
};

class Solution {
public:
  /*
    1) add current node in queue
    2) while q.isnotempty
          // pop: ignore if it is visited
    3)    createNewNode(q.front())
    4)    map[label] = newnode; //adj list
    5)    if (!newRoot) newRoot = newNode
    6)    for adj in neighbors:
    7)       q.push(adj)
  */
  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (!node) {
      return node;
    }
    std::unordered_set<int> visited;
    std::unordered_map<int, UndirectedGraphNode*> map;
    UndirectedGraphNode *newRoot = nullptr;
    std::queue<UndirectedGraphNode*> q;
    q.push(node);
    while (!q.empty()) {
      UndirectedGraphNode *cur = q.front();
      q.pop();
      if (visited.count(cur->label) > 0) {
        continue;
      }
      UndirectedGraphNode *newNode = getNode(cur->label, map);
      if (!newRoot) {
        newRoot = newNode;
      }
      for (auto n : cur->neighbors) {
        newNode->neighbors.push_back(getNode(n->label, map));
        q.push(n);
      }
      visited.insert(cur->label);
    }
    return newRoot;
  }
  UndirectedGraphNode *
  getNode(int label, std::unordered_map<int, UndirectedGraphNode *> &map) {
    if (map.count(label) == 0) {
      map[label] = new UndirectedGraphNode(label);
    }
    return map[label];
  }
};
class TestSolution : public CxxTest::TestSuite {
public:
/*
       1
      / \
     /   \
    0 --- 2
         / \
         \_/
*/
  void test_ex1() {
    UndirectedGraphNode n1(1);
    UndirectedGraphNode n2(2);
    UndirectedGraphNode n0(0);

    n1.neighbors.push_back(&n0);
    n1.neighbors.push_back(&n2);

    n2.neighbors.push_back(&n0);
    n2.neighbors.push_back(&n1);
    n2.neighbors.push_back(&n2);

    n0.neighbors.push_back(&n1);
    n0.neighbors.push_back(&n2);
    Solution s;
    UndirectedGraphNode *nr = s.cloneGraph(&n1);
    TS_ASSERT_DIFFERS(nr, &n1);
    TS_ASSERT_EQUALS(nr->label, 1);
    TS_ASSERT_EQUALS(nr->neighbors.size(), 2);
    TS_ASSERT_EQUALS(nr->neighbors[0]->label, 0);
    TS_ASSERT_EQUALS(nr->neighbors[0]->neighbors.size(), 2);
    TS_ASSERT_EQUALS(nr->neighbors[1]->label, 2);
    TS_ASSERT_EQUALS(nr->neighbors[1]->neighbors.size(), 3);
  }
};
