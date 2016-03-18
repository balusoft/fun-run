/*
102. Binary Tree Level Order Traversal My Submissions Question
Total Accepted: 95255 Total Submissions: 295621 Difficulty: Easy
Given a binary tree, return the level order traversal of its nodes' values. (ie,
from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},
       3
      / \
     9  20
   /  \
  15   7
return its level order traversal as:
[
[3],
[9,20],
[15,7]
]
confused what "{1,#,2,3}" means? > read more on how binary
tree is serialized on OJ.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

*/

#include <vector>
#include <iostream>
#include <queue>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

std::ostream& operator<<(std::ostream &ostr, const TreeNode *tree) {
  if (tree) {
    ostr << "(r:" << tree->val << ", lt:";
    if (tree->left) {
      ostr << tree->left->val;
    } else {
      ostr << "(nullptr)";
    }
    ostr << ", rt:";
    if (tree->right) {
      ostr << tree->right->val;
    } else {
      ostr << "(nullptr)";
    }
    ostr << ")";
  } else {
    ostr << "(tree: nullptr)";
  }
  return ostr;
}
std::ostream &operator<<(std::ostream &ostr,
                        const std::vector<std::vector<int>> &lorder) {
  for (const auto &v : lorder) {
    ostr << "[ ";
    for (const auto &i : v) {
      ostr << i << ", ";
    }
    ostr << "]";
  }
  return ostr;
}

class Solution {
  public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
      std::vector<std::vector<int>> res;
      if (!root) {
        return res;
      }
      std::vector<std::queue<TreeNode*>> levelQs(2);
      levelQs[0].push(root);
      res.push_back({});
      size_t q=0;
      size_t nq=(q+1)%2;
      while (!levelQs[q].empty()) {
        TreeNode* node = levelQs[q].front();
        levelQs[q].pop();
        res.back().push_back(node->val);
        if (node->left) {
          levelQs[nq].push(node->left);
        }
        if (node->right) {
          levelQs[nq].push(node->right);
        }
        if (levelQs[q].empty()) {
          q = nq;
          nq = (q+1)%2;
          if (!levelQs[q].empty()) {
            res.push_back({});
          }
        }
      }
      std::cout << "res: " << res << "\n";
      return res;
    }
};

int main() {
  TreeNode t(5);
  TreeNode tl(10);
  TreeNode tr(20);
  t.left = &tl;
  t.right = &tr;
  TreeNode tll(101);
  TreeNode tlr(102);
  tl.left = &tll;
  tl.right = &tlr;
  TreeNode trr(202);
  tr.right = &trr;

  Solution s;
  (void)s.levelOrder(&t);
  return 0;
}

