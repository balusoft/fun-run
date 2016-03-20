/*
78. Subsets My Submissions Question
Total Accepted: 88982 Total Submissions: 287885 Difficulty: Medium
Given a set of distinct integers, nums, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,3], a solution is:

[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]
Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

          []            [1]
      []     [2]    []      [2]
  []    [3] []  [3] [] [3] [] [3]

  [
  []
  [3]
  [2]
  [2, 3]
  [1, 3]
  [1, 2]
  [1, 2, 3]
  ]
*/

#include <iostream>
#include <vector>
#include <algorithm>

std::ostream& operator<<(std::ostream& ostr, std::vector<int> v) {
  ostr << "[";
  for (auto &i : v) {
    ostr << i << ", ";
  }
  ostr << "]";
  return ostr;
}
std::ostream& operator<<(std::ostream& ostr, std::vector<std::vector<int>> vv) {
  ostr << "[";
  for (auto &v : vv) {
    ostr << v << ",\n";
  }
  ostr << "]";
  return ostr;
}
struct Context {
  Context(std::vector<int> &nnums)
      : nums(nnums), inOut(nums.size(), false), level(-1) {}
  std::vector<int> &nums;
  std::vector<bool> inOut;
  std::vector<std::vector<int>> out;
  int level;
  void addResult() {
    std::vector<int> res;
    res.reserve(nums.size());
    for (size_t idx=0; idx<nums.size(); ++idx) {
      if (inOut[idx]) {
        res.push_back(nums[idx]);
      }
    }
    out.push_back(res);
  }
};
void backtrack(Context &ctx) {
  ++ctx.level;
  if (ctx.level == ctx.nums.size()) {
    ctx.addResult();
    --ctx.level;
    return;
  }
  // case: consider
  ctx.inOut[ctx.level] = false;
  backtrack(ctx);
  // case: do not consider
  ctx.inOut[ctx.level] = true;
  backtrack(ctx);
  --ctx.level;
}
class Solution {
public:
  std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
    std::sort(nums.begin(), nums.end());
    Context ctx(nums);
    backtrack(ctx);
    return ctx.out;
  }
};

void test(std::vector<int> &nums) {
  Solution s;
  std::cout << "Nums: " << nums << " ::: \n" << s.subsets(nums) << "\n";
}

int main() {
  std::vector<int> tv{1, 2, 3};
  test(tv);
}
