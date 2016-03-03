//
//  InvertBinaryTree.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 2/25/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include "InvertBinaryTree.hpp"
#include <queue>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  TreeNode* invertTree(TreeNode* root) {
    if (NULL == root) return root;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
      TreeNode* node=q.front();
      q.pop();
      TreeNode *right=NULL;
      if (node->right) {
        right=node->right;
        q.push(right);
      }
      TreeNode *left=NULL;
      if (node->left) {
        left=node->left;
        q.push(left);
      }
      node->right = left;
      node->left = right;
    }
    return root;
  }
};

namespace InvertBinaryTree {
void test() {
}
}
