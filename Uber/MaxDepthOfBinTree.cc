/*
104. Maximum Depth of Binary Tree My Submissions Question
Total Accepted: 130868 Total Submissions: 276006 Difficulty: Easy
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root
node down to the farthest leaf node.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems

*/

#include <iostream>
#include <algorithm>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
std::ostream& operator<< (std::ostream& ostr, const TreeNode* t) {
  if (t) {
    ostr << "(val: " << t->val << ", l:";
    if (t->left) {
      ostr << t->left->val;
    } else {
      ostr << "nullptr";
    }
    ostr << ", r:";
    if (t->right) {
      ostr << t->right->val;
    } else {
      ostr << "nullptr";
    }
    ostr << ")";
  } else {
    ostr << "(nullptr)";
  }
  return ostr;
}
class Solution {
public:
  int maxDepth(TreeNode *root) {
    if (!root) {
      return 0;
    }
    int height =0;
    height = maxDepth(root->left);
    height = std::max(height, maxDepth(root->right));
    return height + 1;
  }
};

int main() {
  TreeNode t(10);
  TreeNode tl(5);
  TreeNode tr(15);
  t.left=&tl;
  std::cout << "t: " << &t << "\n";
  TreeNode *pt=nullptr;
  std::cout << "pt: " << pt << "\n";
  Solution s;
  std::cout << "depth: " << s.maxDepth(&t) << "\n";
  return 0;
}
