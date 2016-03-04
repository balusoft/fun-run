/**
Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
*/

#include <vector>
#include <iostream>

/* iterator */
class NextItemsItr {
public:
  NextItemsItr(const std::vector<bool> &inUse)
    : _inUse(inUse), _currIdx(-1) {
  }
  int operator*() const {
    return _currIdx;
  }
  bool next() {
    int tmp = _currIdx + 1;
    while (tmp < _inUse.size() && _inUse[tmp]) {
      ++tmp;
    }
    if (tmp >= _inUse.size()) {
      return false;
    }
    _currIdx = tmp;
    return true;
  }
private:
  const std::vector<bool> &_inUse;
  int _currIdx;
};

/* backtrack */
void backtrack(const std::vector<int>& nums,
               std::vector<std::vector<int>> &perms,
               std::vector<int> &currPerm,
               std::vector<bool>  &inUse,
               int &level) {
  // have reached leaf means solution
  if (currPerm.size()-1 == level) {
    perms.push_back(currPerm);
  } else {
    ++level;
    NextItemsItr itr(inUse);
    while (itr.next()) {
      inUse[*itr] = true;
      currPerm[level] = nums[*itr];
      backtrack(nums, perms, currPerm, inUse, level);
      inUse[*itr] = false;
    }
    --level;
  }
}

/* API */
std::vector<std::vector<int>> getPerm(const std::vector<int>& nums) {
  std::vector<std::vector<int>> perms;
  std::vector<int> currPerm(nums.size());
  std::vector<bool> inUse(nums.size(), false);
  int level=-1;
  backtrack(nums,perms,currPerm,inUse,level);
  return perms;
}

class Solution {
public:
  std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    return getPerm(nums);
  }
};
void testGetPerm(const std::vector<int> &nums) {
  std::vector<std::vector<int>> perms = getPerm(nums);
  for (std::vector<int> curPerm : perms) {
    for (int num : curPerm) {
      std::cout << num << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int main() {
  std::vector<int> nums { 1, 2, 3 };
  testGetPerm(nums);
  std::vector<int> nums2;
  testGetPerm(nums2);
}
