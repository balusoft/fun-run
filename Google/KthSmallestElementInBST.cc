/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//19:05
class Solution {
public:
  int kthSmallest(TreeNode *root, int k) {
    int c = 0;
    TreeNode *n = kthEle(root, k, c);
    return n->val;
  }
  TreeNode *kthEle(TreeNode *root, int k, int &c) {
    if (!root) {
      return nullptr;
    }
    TreeNode *n = nullptr;
    n = kthEle(root->left, k, c);
    if (n) {
      return n;
    }
    ++c;
    if (k == c) {
      return root;
    }
    n = kthEle(root->right, k, c);
    if (n) {
      return n;
    }
    return nullptr;
  }
};
