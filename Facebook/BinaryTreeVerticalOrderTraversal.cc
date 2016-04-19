/**
314. Binary Tree Vertical Order Traversal   My Submissions QuestionEditorial Solution
Total Accepted: 4635 Total Submissions: 15340 Difficulty: Medium
Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Examples:

Given binary tree [3,9,20,null,null,15,7],
   3
  /\
 /  \
 9  20
    /\
   /  \
  15   7
return its vertical order traversal as:
[
  [9],
  [3,15],
  [20],
  [7]
]
Given binary tree [3,9,8,4,0,1,7],
     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
return its vertical order traversal as:
[
  [4],
  [9],
  [3,0,1],
  [8],
  [7]
]
Given binary tree [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5),
     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
    /\
   /  \
   5   2
return its vertical order traversal as:
[
  [4],
  [9,5],
  [3,0,1],
  [8,2],
  [7]
]
**/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
  vector<vector<int>> verticalOrder(TreeNode *root) {
    unordered_map<int, vector<int>> map;
    bfs(root, map, 0);
    std::set<int> keys;
    for (auto &kv : map) {
      keys.insert(kv.first);
    }
    std::vector<std::vector<int>> res(keys.size());
    int i = 0;
    for (auto k : keys) {
      res[i++] = map[k];
    }
    return res;
  }
  void bfs(TreeNode *root, unordered_map<int, vector<int>> &map, const int k) {
    if (!root) {
      return;
    }
    std::queue<std::tuple<TreeNode *, int>> q;
    q.push(std::make_tuple(root, 0));
    while (!q.empty()) {
      TreeNode *cur;
      int k;
      std::tie(cur, k) = q.front();
      q.pop();
      map[k].push_back(cur->val);
      if (cur->left) {
        q.push(std::make_tuple(cur->left, k - 1));
      }
      if (cur->right) {
        q.push(std::make_tuple(cur->right, k + 1));
      }
    }
  }
};
