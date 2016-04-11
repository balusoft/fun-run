/*
Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively. Find
the median of the two sorted arrays. The overall run time complexity should be
O(log (m+n)).
*/

#include <tuple>
#include <vector>
#include <iostream>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int size = nums1.size() + nums2.size();
    int med = (size/2) - 1;
    if (size%2 != 0) {
      ++med;
    }
    //std::cout << "med> " << med << "\n";
    //std::cout << "size> " << size << "\n";
    int vv=0;
    int vi=0;
    int m=0;
    int i=0;
    int j=0;
    std::vector<std::vector<int>*> v{&nums1, &nums2};
    double medValue=0;
    while (m <= med+1) {
      if (m == med+1 && size%2 !=0) {
        break;
      }
      bool chooseFirst = false;
      if (i >= nums1.size()) {
        chooseFirst = false;
      } else if (j >= nums2.size()) {
        chooseFirst = true;
      } else if (v[0]->at(i) < v[1]->at(j)) {
        chooseFirst = true;
      } else if (v[0]->at(i) >= v[1]->at(j)) {
        chooseFirst = false;
      }
      if (chooseFirst) {
        std::tie(vv, vi) = std::make_tuple(0, i++);
      } else {
        std::tie(vv, vi) = std::make_tuple(1, j++);
      }
      if (m == med) {
        medValue = v[vv]->at(vi);
      } else if (m == med+1) {
        medValue = (medValue + v[vv]->at(vi))/2;
      }
      ++m;
    }
    return medValue;
  }
};
class TestSolution : public CxxTest::TestSuite {
public:
  void test_example2() {
    std::vector<int> n1{1,3,5,7,8,9,10,11,12,13};
    std::vector<int> n2{2,4,6};
    Solution s;
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 7);
  }

  void test_example() {
    std::vector<int> n1{1,3,5,7,8,9,10,11,12,13};
    std::vector<int> n2{2,4,6,14};
    Solution s;
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 7.5000);
  }

  void test_example3() {
    std::vector<int> n1{1,3,5,7};
    std::vector<int> n2{2,4,6,8};
    Solution s;
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 4.5000);
  }

  void test_example4() {
    std::vector<int> n1{};
    std::vector<int> n2{2,4,6,8};
    Solution s;
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 5);
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n2, n1), 5);
  }
};
