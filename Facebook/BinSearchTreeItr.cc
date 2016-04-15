/*
Implement an iterator over a binary search tree (BST). Your iterator will be
initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory,
where h is the height of the tree.
*/

#include <stack>
#include <cxxtest/TestSuite.h>
#include <cassert>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BSTIterator {
public:
  BSTIterator(TreeNode *root) : bt() {
    traverseLeft(root, bt);
  }

  /** @return whether we have a next smallest number */
  bool hasNext() {
    return !bt.empty();
  }

  /** @return the next smallest number */
  int next() {
    assert(hasNext());
    TreeNode *cur = bt.top();
    bt.pop();
    traverseLeft(cur->right, bt);
    return cur->val;
  }
private:
  void traverseLeft(TreeNode *node, std::stack<TreeNode*> &bt) {
    while (node) {
      bt.push(node);
      node = node->left;
    }
  }
  std::stack<TreeNode*> bt;
};

/**
 Your BSTIterator will be called like this:
 BSTIterator i = BSTIterator(root);
 while (i.hasNext()) cout << i.next();
 */
class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    TreeNode n1(1);
    TreeNode n2(2);
    TreeNode n3(3);
    TreeNode n4(4);
    TreeNode n5(5);
    TreeNode n6(6);
    TreeNode n7(7);

    n6.left = &n2;
    n6.right = &n7;

    n2.right = &n5;
    n2.left = &n1;
    n5.left = &n4;
    n4.left = &n3;

    BSTIterator itr(&n6);
    TS_ASSERT_EQUALS(true, itr.hasNext());
    TS_ASSERT_EQUALS(1, itr.next());
    TS_ASSERT_EQUALS(true, itr.hasNext());
    TS_ASSERT_EQUALS(2, itr.next());
    TS_ASSERT_EQUALS(true, itr.hasNext());
    TS_ASSERT_EQUALS(3, itr.next());
    TS_ASSERT_EQUALS(true, itr.hasNext());
    TS_ASSERT_EQUALS(4, itr.next());
    TS_ASSERT_EQUALS(true, itr.hasNext());
    TS_ASSERT_EQUALS(5, itr.next());
    TS_ASSERT_EQUALS(true, itr.hasNext());
    TS_ASSERT_EQUALS(6, itr.next());
    TS_ASSERT_EQUALS(true, itr.hasNext());
    TS_ASSERT_EQUALS(7, itr.next());
    TS_ASSERT_EQUALS(false, itr.hasNext());
  }
};
