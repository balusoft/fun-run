/*
53. Maximum Subarray My Submissions Question
Total Accepted: 102841 Total Submissions: 283598 Difficulty: Medium
Find the contiguous subarray within an array (containing at least one number)
which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

click to show more practice.

Subscribe to see which companies asked this question

Hide Tags Divide and Conquer Array Dynamic Programming
Show Similar Problems

My algorithm:
------------
1) Maintain candidate list of maxSubSets.
2) Maintain curMaxSubArray
3) on new element:
  1) if new element is greater than max element add it as a candidate set.
  2) if new element can extend(*) add to candidate set.
     New element can extend iff last element in subset is predecessor in main array.
  3) Now eleminate ineligible(*) subsets.
     subset is ineligible if its sum value is less than current-max and endIndex
     is not predecessor.
4) now elementate candidates which sum is less than cur-max.
5) return the sum of 0'th element

[−2, 1,−3,4,−1,2,1,−5,4]
-2: {-2}
 1: {-2}, {1}, {-2, 1} => {1}
-3: {1}, {-3}, {1, -3} => {1}, {1, -3}
 4: {4}, {1}, {1, -3}, {1, -3, 4} => {4} Note: reason is {1} is no more needed
-1: {-1}, {4}, {4, -1} => {4}, {4, -1}
 2: {2}, {4}, {4, -1}, {4, -1, 2} => {4, -1, 2}
 1: {1}, {4, -1, 2}, {4, -1, 2, 1} => {4, -1, 2, 1}
-5: {-5}, {4, -1, 2, 1}, {4, -1, 2, 1, -5} => {4, -1, 2, 1}, {4, -1, 2, 1, -5}
 4: {4}, {4, -1, 2, 1}, {4, -1, 2, 1, -5}, {4, -1, 2, 1, -5, 4} => {4, -1, 2, 1}, {4, -1, 2, 1, -5, 4}

 Now cleanup:
 remove elements which are less than cur_max

 {4, -1, 2, 1}: 6

Data structures:

candidate: (startIdx, endIdx, sum)

Complexity: O(n)
*/

#include <vector>
#include <iostream>
#include <list>
#include <algorithm>

struct Candidate {
  Candidate(size_t s, size_t e, int su) : sIdx(s), eIdx(e), sum(su) {}
  size_t sIdx;
  size_t eIdx;
  int sum;
};

std::ostream &operator<<(std::ostream &ostr, const std::vector<int> &v) {
  ostr << "{ ";
  for (const auto& i : v) {
    ostr << i << ", ";
  }
  ostr << "} ";
  return ostr;
}
std::ostream &operator<<(std::ostream &ostr, const Candidate &cand) {
  ostr << "(sIdx: " << cand.sIdx << ", eIdx: " << cand.eIdx
       << ", sum: " << cand.sum << ")";
  return ostr;
}

std::ostream &operator<<(std::ostream &ostr,
                         const std::list<Candidate> &cands) {
  ostr << "{ ";
  for (const auto &cand : cands) {
    ostr << cand << ", ";
  }
  ostr << " }";
  return ostr;
}

class Solution {
public:
  int maxSubArray(const std::vector<int> &nums) {
    if (nums.size() == 0) {
      return 0;
    }
    if (nums.size() == 1) {
      return nums[0];
    }
    std::list<Candidate> candidateList;
    int curMaxSubArray = 0;
    Candidate tmp(idx, idx, nums[idx]);
    //std::cout << "Adding ... " << tmp << "\n";
    newCandidates.push_back(tmp);
    curMaxSubArray = nums[idx];
    for (size_t idx = 1; idx < nums.size(); ++idx) {
      std::list<Candidate> newCandidates;
      if (0 == idx) 
      for (auto &cand : candidateList) {
        // Two cases to worry:
        // 1) nums[idx] is greater than current cand sum and cand sum is -ve
        //    1) candidate sum is -ve: Start from current idx
        //    2) candidate sum is >=0: add current idx to the candidate's eIdx
        if (cand.eIdx + 1 == idx) {
          int sum = 0;
          if (nums[idx] > cand.sum && cand.sum < 0) {
            cand.sIdx = idx;
            cand.eIdx = idx;
            cand.sum = nums[idx];
            sum = cand.sum;
          } else {
            sum = cand.sum + nums[idx];
            cand.eIdx = idx;
            cand.sum += sum;
            Candidate tmp(cand.sIdx, idx, sum);
            newCandidates.push_back(tmp);
          }
          // std::cout << "Adding ... " << tmp << "\n";
          if (sum > curMaxSubArray) {
            curMaxSubArray = sum;
          }
        }
      }
      std::cout << "nums[idx] = " << nums[idx] << "\n";
      std::cout << "curMaxSubArray: " << curMaxSubArray << "\n";
      // eliminate elements from candidateList
      candidateList.erase(std::remove_if(candidateList.begin(),
                                         candidateList.end(),
                                         [=](const Candidate &cand) {
                                           return cand.sum < curMaxSubArray &&
                                                  cand.eIdx != idx;
                                         }),
                          candidateList.end());
      std::cout << "newCandidates: " << newCandidates << "\n";
      candidateList.splice(candidateList.end(), newCandidates);
      std::cout << "candidateList: " <<  candidateList << "\n";
    }
    // remove all elements which are less than curMaxSubArray
    candidateList.erase(std::remove_if(candidateList.begin(),
                                       candidateList.end(),
                                       [=](const Candidate &cand) {
                                         return cand.sum < curMaxSubArray;
                                       }),
                        candidateList.end());
    std::cout << "2candidateList: " << candidateList << "\n";
    return candidateList.begin()->sum;
  }
};

void test(const std::vector<int> &nums) {
  std::cout << nums << ": ";
  Solution s;
  std::cout << s.maxSubArray(nums) << "\n";
}
int main() {
  test ( {8,-19,5,-4,20});
  test( { -2, 1, -3, 4, -1, 2, 1, -5, 4 } );
  //test( { -2 } );
  //test( { 1, 2, 3 } );
  //test( { 1, 2 } );
  return 0;
}
