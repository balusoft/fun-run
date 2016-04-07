/**
235. Lowest Common Ancestor of a Binary Search Tree My Submissions
QuestionEditorial Solution
Total Accepted: 63493 Total Submissions: 167833 Difficulty: Easy
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two
given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes v and w as the lowest node in T that has both v and w
as descendants (where we allow a node to be a descendant of itself).”

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
  0      _4       7       9
 /  \
 3   5

For example, the lowest common
ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is
2, since a node can be a descendant of itself according to the LCA definition.

Subscribe to see which companies
asked this question

Show Tags
Show Similar Problems
Have you met this question in a real
interview? Yes  No
Discuss

*/
#include <cxxtest/TestSuite.h>
#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
  }
};
class Solution {
public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (!root || !p || !q) {
      return nullptr;
    }
    // if p or q is root then curNode is LCA
    // if p and q does not beling to single side of the tree then curNode is LCA
    // In other cases go to left/right sub tree and repeat the tests
    TreeNode *itr=root;
    while (itr) {
      if (p == itr || q == itr) {
        return itr;
      }
      bool moveLeft = (itr->val >= p->val && itr->val >= q->val);
      bool moveRight = (itr->val < p->val && itr->val < q->val);
      // std::cout << "(r, p, q): (" << itr->val << "," << p->val << "," <<
      // q->val
      //          << ")\n";
      // std::cout << "moveLeft: " << moveLeft << " moveRight: " << moveRight
      //          << std::endl;
      if (!moveLeft && !moveRight) {
        return itr;
      }
      if (moveLeft) {
        itr = itr->left;
      } else {
        itr = itr->right;
      }
    }
    return nullptr;
  }
};
class TestSolution : public CxxTest::TestSuite {
public:
/*

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
  0      _4       7       9
        /  \
        3   5


*/
  void XXtest_example() {
    TreeNode n6(6);
    TreeNode n2(2);
    TreeNode n8(8);
    TreeNode n0(0);
    TreeNode n4(4);
    TreeNode n7(7);
    TreeNode n9(9);
    TreeNode n3(3);
    TreeNode n5(5);

    n6.left = &n2;
    n6.right = &n8;

    n2.left = &n0;
    n2.right = &n4;

    n8.left = &n7;
    n8.right = &n9;

    n4.left = &n3;
    n4.right = &n5;
    Solution s;
    TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n6, &n2, &n8), &n6);
    TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n6, &n2, &n8)->val, n6.val);
    TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n6, &n2, &n4), &n2);
    TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n6, &n3, &n9), &n6);
    TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n6, &n3, &n5), &n4);
    TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n6, &n3, &n5)->val, n4.val);
    TS_ASSERT_EQUALS(s.lowestCommonAncestor(nullptr, nullptr, nullptr),
                     nullptr);
 }
 void test_lc_run() {
  TreeNode n2(2);
  TreeNode n1(1);
  TreeNode n3(3);

  n2.left = &n1;
  n2.right = &n3;
  Solution s;
  TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n2, &n1, &n3), &n2);
  TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n2, &n1, &n3)->val, n2.val);
  TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n2, &n3, &n1), &n2);
  TS_ASSERT_EQUALS(s.lowestCommonAncestor(&n2, &n3, &n1)->val, n2.val);
 }
};

