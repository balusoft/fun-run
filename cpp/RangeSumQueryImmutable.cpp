//
//  RangeSumQueryImmutable.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 2/15/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include "RangeSumQueryImmutable.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cassert>

class NumArray {
public:
  NumArray(std::vector<int> &nums)
    : sums(nums.size(), 0) {
    int sum=0;
    for (size_t idx=0; idx<sums.size(); ++idx) {
      sum = sum + nums[idx];
        sums[idx] = sum;
    }
  }

  int sumRange(int i, int j) {
    assert(i<sums.size());
    assert(j<sums.size());
    assert(i<=j);
    return i == 0 ? sums[j] : sums[j]-sums[i-1];
  }
  void printSums() {
      for (int elem : sums) {
          std::cout << " " << elem;
      }
      std::cout << "\n";
  }
private:
 std::vector<int> sums;
};

namespace RangeSumQueryImmutable {
void test() {
  std::vector<int> nums = {-2, 0, 3, -5, 2, -1};
  NumArray na(nums);
  na.printSums();
  std::cout << "(0,2)" << na.sumRange(0, 2) << "\n";
  std::cout << "(2,5)" << na.sumRange(2, 5) << "\n";
  std::cout << "(0,5)" << na.sumRange(0, 5) << "\n";
  std::cout << "(1,1)" << na.sumRange(0, 5) << "\n";
  std::cout << "(2,2)" << na.sumRange(0, 5) << "\n";
  std::cout << "(0,2)" << na.sumRange(0, 2) << "\n";
  std::cout << "(2,5)" << na.sumRange(2, 5) << "\n";
  std::cout << "(0,5)" << na.sumRange(0, 5) << "\n";
  std::cout << "(0,0)" << na.sumRange(0, 0) << "\n";
  std::cout << "(1,1)" << na.sumRange(1, 1) << "\n";
  std::cout << "(2,2)" << na.sumRange(2, 2) << "\n";
}
}

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);
