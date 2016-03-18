#if 0
LeetCode Premium Subscription
Problems 
Pick One
Mock 
Articles
Discuss
Book
balusoft 
337. House Robber III My Submissions Question
Total Accepted: 2762 Total Submissions: 7534 Difficulty: Medium
The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree". It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:
     3
         / \
            2   3
                \   \ 
                     3   1
                     Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
                     Example 2:
                          3
                              / \
                                 4   5
                                   / \   \ 
                                    1   3   1
                                    Maximum amount of money the thief can rob = 4 + 5 = 9.
                                    Credits:
                                    Special thanks to @dietpepsi for adding this problem and creating all test cases.

                                    Subscribe to see which companies asked this question

                                    Show Tags
                                    Show Similar Problems
                                    Have you met this question in a real interview? Yes  No
                                    Discuss

#endif

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
  int rob(TreeNode *root) {}
};
