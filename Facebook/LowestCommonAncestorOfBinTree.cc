/*
Given a binary tree,
find the lowest common ancestor(LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia
: “The lowest common ancestor is defined between two nodes v and w as
  the lowest node in T that has both v and w as
  descendants(where we allow a node to be a descendant of itself) .”

        _______3______
       /              \
    ___5__         ___1__
   /      \       /      \
   6      _2     0        8
         /  \
        7    4
For example,
the lowest common ancestor(LCA) of nodes 5 and 1 is 3.
Another example is LCA of nodes 5 and 4 is 5,
since a node can be a descendant of itself according to the LCA definition.
*/

#include <stack>
#include <tuple>
#include <cxxtest/TestSuite.h>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

using NodeStack = std::stack<std::tuple<TreeNode*, int>>;
class Solution {
public:
  void findNode(TreeNode *root, TreeNode *s, NodeStack &bt) {
    // Find in DFS way, maintain stack of parents.
    // If node found return with* node in stack
    if (!root) {
      return;
    }
    TreeNode *itr = root;
    bt.push(std::make_tuple(itr, 0));
    while (!bt.empty() && itr) {
      if (itr == s) {
        break;
      }
      if (itr->left && std::get<1>(bt.top()) <= 0) {
        ++std::get<1>(bt.top());
        itr = itr->left;
        bt.push(std::make_tuple(itr, 0));
      } else if (itr->right && std::get<1>(bt.top()) <= 1) {
        // Make current node visited flag true, means no need
        // revisit its right
        // top is pass by reference, you can do following
        ++std::get<1>(bt.top());
        itr = itr->right;
        bt.push(std::make_tuple(itr, 0));
      } else {
        bt.pop();
        itr = nullptr;
        if (!bt.empty()) {
          itr = std::get<0>(bt.top());
        }
      }
    }
  }
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    NodeStack pSt;
    findNode(root, p, pSt);
    NodeStack qSt;
    findNode(root, q, qSt);
    while (pSt.size() > qSt.size()) {
      pSt.pop();
    }
    while (qSt.size() > pSt.size()) {
      qSt.pop();
    }
    if (pSt.empty() || qSt.empty()) {
      return nullptr;
    }
    while (std::get<0>(qSt.top()) != std::get<0>(pSt.top())) {
      qSt.pop();
      pSt.pop();
    }
    if (pSt.empty() || qSt.empty()) {
      return nullptr;
    }
    return std::get<0>(pSt.top());
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    TreeNode n3(3);
    TreeNode n5(5);
    TreeNode n6(6);
    TreeNode n2(2);
    TreeNode n7(7);
    TreeNode n4(4);
    TreeNode n1(1);
    TreeNode n0(0);
    TreeNode n8(8);

    n3.left = &n5;
    n3.right = &n1;
    n5.left = &n6;
    n5.right = &n2;
    n2.left = &n7;
    n2.right = &n4;
    n1.left = &n0;
    n1.right = &n8;

    Solution s;
    NodeStack st;
    s.findNode(&n3, &n7, st);
    TS_ASSERT_EQUALS(&n7, std::get<0>(st.top()));
    TS_ASSERT_EQUALS(4, st.size());
    TS_ASSERT_EQUALS(&n5, s.lowestCommonAncestor(&n3, &n5, &n2));
    TS_ASSERT_EQUALS(&n3, s.lowestCommonAncestor(&n3, &n5, &n8));
    TS_ASSERT_EQUALS(&n5, s.lowestCommonAncestor(&n3, &n6, &n4));
  }
};
