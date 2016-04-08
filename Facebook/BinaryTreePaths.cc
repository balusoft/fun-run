/*
257. Binary Tree Paths My Submissions QuestionEditorial Solution
Total Accepted: 42363 Total Submissions: 150585 Difficulty: Easy
Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]
*/

#include <cxxtest/TestSuite.h>
#include <string>
#include <vector>
using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  string v2path(const std::vector<int>& path) {
    ostringstream ostr;
    bool isFirst = true;
    for (auto e : path) {
      if (isFirst) {
        isFirst = false;
      } else {
        ostr << "->";
      }
      ostr << e;
    }
    return ostr.str();
  }
  void backtrack(TreeNode *node, std::vector<int> &path,
                 std::vector<std::string> &res) {
    if (!node) {
      return;
    }
    //std::cout << "Pushing : " << node->val << "\n";
    path.push_back(node->val);
    if (!node->left && !node->right) {
      res.push_back(v2path(path));
      //std::cout << "res: " << res.back() << "\n";
    } else {
      backtrack(node->left, path, res);
      backtrack(node->right, path, res);
    }
    //std::cout << "Popping : " << path.back() << "\n";
    (void) path.pop_back();
  }
  vector<string> binaryTreePaths(TreeNode *root) {
    std::vector<string> res;
    std::vector<int> path;
    backtrack(root, path, res);
    return res;
  }
};
/*
   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]

*/

class TestSolution1 : public CxxTest::TestSuite {
public:
  void test_example() {
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    TreeNode n1(1);
    TreeNode n2(2);
    TreeNode n3(3);
    TreeNode n5(5);
    n1.left = &n2;
    n1.right = &n3;

    n2.right = &n5;
    Solution s;
    std::vector<string> vS{"1->2->5", "1->3"};
    TS_ASSERT_EQUALS(s.binaryTreePaths(&n1), vS);
  }
};
