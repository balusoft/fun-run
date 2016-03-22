/*
337. House Robber III My Submissions Question
Total Accepted: 2762 Total Submissions: 7534 Difficulty: Medium
The thief has found himself a new place for his thievery again. There is only
one entrance to this area, called the "root." Besides the root, each house has
one and only one parent house. After a tour, the smart thief realized that "all
houses in this place forms a binary tree". It will automatically contact the
police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting
the police.

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

DP:

Consider following tree:
       a
      / \
     b   c
   /  \ / \
  d   d f  g

rob(a) = std::max{ {a+ rob(b) + rob(d) + rob(f) + rob(g)}, {rob(b) + rob(c)}}
 */

#include <iostream>
#include <cxxtest/TestSuite.h>
#include <algorithm>
#include <unordered_map>
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
std::ostream &operator<<(std::ostream &ostr,
                         const std::unordered_map<TreeNode *, int> cache) {
  ostr << "{";
  for (const auto &kv : cache) {
    ostr << "(" << kv.first << "," << kv.second << "),";
  }
  ostr << "}";
  return ostr;
}
class Solution {
public:
  /*
      a
     / \
    b   c

  Consider above case, at leaf
  rob_with_root = root_val+max_left_wo_root + max_right_wo_root
  rob_without_root = max(max_left_with_root, max_left_wo_root) +
                     max(max_right_with_root, max_right_wo_root)
  max_rob = std::max(rob_with_root, rob_without_root);
  */

  void dp(TreeNode* root, int& rob_with_root, int& rob_without_root) {
    if (nullptr == root) {
      rob_with_root = 0;
      rob_without_root = 0;
      return;
    }
    int max_left_wo_root=0;
    int max_right_wo_root=0;

    int max_left_with_root=0;
    int max_right_with_root=0;

    dp(root->left, max_left_with_root, max_left_wo_root);
    dp(root->right, max_right_with_root, max_right_wo_root);

    rob_with_root = root->val + max_left_wo_root + max_right_wo_root;
    rob_without_root = std::max(max_left_with_root, max_left_wo_root) +
                       std::max(max_right_with_root, max_right_wo_root);
  }
  int rob(TreeNode* root) {
    int root_val=0;
    int children_val=0;
    dp(root, root_val, children_val);
    return std::max(root_val, children_val);
  }

  int rob2(TreeNode *root) {
    if (nullptr == root) {
      return 0;
    }
    //std::cout << "\ncache:\n" << cache << "\n";
    if (cache.find(root) != cache.end()) {
      return cache[root];
    }
    TreeNode *l = root->left;
    TreeNode *ll=nullptr;
    TreeNode *lr=nullptr;
    if (l) {
      ll = l->left;
      lr = l->right;
    }
    TreeNode *r = root->right;
    TreeNode *rl = nullptr;
    TreeNode *rr = nullptr;
    if (r) {
      rl = r->left;
      rr = r->right;
    }
    cache[root] = std::max((root->val + rob(ll) + rob(lr) + rob(rr) + rob(rl)),
                    (rob(l) + rob(r)));
    return cache[root];
  }
private:
  std::unordered_map<TreeNode*, int> cache;
};

class TestSolution : public CxxTest::TestSuite {
public:
/*
     3
    / \
   2   3
    \   \
     3   1

*/
  void test_top_bottom() {
    TreeNode root(3);
    TreeNode l(2);
    TreeNode r(3);
    root.left = &l;
    root.right = &r;
    TreeNode lr(3);
    TreeNode rr(1);
    l.right = &lr;
    r.right = &rr;

    Solution s;
    TS_ASSERT_EQUALS(s.rob(&root), 7);
  }
/*
        3
       / \
      4   5
     / \   \
    1   3   1

*/
  void test_middle() {
    TreeNode root(3);
    TreeNode l(4);
    TreeNode r(5);
    root.left = &l;
    root.right = &r;
    TreeNode ll(1);
    TreeNode lr(3);
    l.left = &ll;
    l.right = &lr;
    TreeNode rr(1);
    r.right = &rr;
    Solution s;
    TS_ASSERT_EQUALS(s.rob(&root), 9);
  }

/*
        3
       / \
      1   1
     / \   \
    1   3   101
   /     \   \
  90     34  100

*/
  void test_4_top_bottom() {
    TreeNode root(3);
    TreeNode l(1);
    TreeNode r(1);
    root.left = &l;
    root.right = &r;
    TreeNode ll(1);
    TreeNode lr(3);
    l.left = &ll;
    l.right = &lr;
    TreeNode rr(101);
    r.right = &rr;
    TreeNode lll(90);
    ll.left = &lll;
    TreeNode lrr(34);
    lr.right = &lrr;
    TreeNode rrr(100);
    rr.right = &rrr;
    Solution s;
    TS_ASSERT_EQUALS(s.rob(&root), 228);
  }
};
