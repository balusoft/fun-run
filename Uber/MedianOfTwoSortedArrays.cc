/*
Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively. Find
the median of the two sorted arrays. The overall run time complexity should be
O(log (m+n)).
*/

#include <tuple>
#include <vector>
#include <iostream>
#include <cassert>
#include <cxxtest/TestSuite.h>
using namespace std;
class Solution {
public:
  int findKthSmallestElement(vector<int> &nums1, vector<int> &nums2, int k) {
    int s1=0;
    int s2=0;
    while (true) {
      if (s1 >= nums1.size()) {
        return nums2[s2 + k - 1];
      }
      if (s2 >= nums2.size()) {
        return nums1[s1 + k - 1];
      }
      if (k == 1) {
        return std::min(nums1[s1], nums2[s2]);
      }
      int n1Mid = std::numeric_limits<int>::max();
      int n2Mid = std::numeric_limits<int>::max();
      if (s1 + k / 2 - 1 < nums1.size()) {
        n1Mid = nums1[s1 + k / 2 - 1];
      }
      if (s2 + k / 2 - 1 < nums2.size()) {
        n2Mid = nums2[s2 + k / 2 - 1];
      }

      if (n1Mid < n2Mid) {
        // skip n1 elements till s1+k/2
        s1 = s1 + k / 2;
        // return findKthSmallestElement(nums1, s1 + k/2, nums2, s2, k - k/2);
      } else {
        // skip n2 elements till s2+k/2
        s2 = s2 + k / 2;
        // return findKthSmallestElement(nums1, s1,      nums2, s2 + k/2, k -
        // k/2);
      }
      k -= k/2;
    } // while
  }
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int m = nums1.size();
    int n = nums2.size();
    int s = m+n;
    int med = s/2 + 1;
    double median = findKthSmallestElement(nums1, nums2, med);
    if (s%2 == 0) {
      median = (median + findKthSmallestElement(nums1, nums2, med - 1)) * 0.5;
    }
    return median;
  }
  double findMedianSortedArraysOld(vector<int> &nums1, vector<int> &nums2) {
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
  void test_example_ksme() {
    std::vector<int> n1{1,3,5,7,8,9,10,11,12,13};
    std::vector<int> n2{2,4,6};
    Solution s;
    TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 1), 1);
    TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 2), 2);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 3), 3);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 4), 4);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 5), 5);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 6), 6);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 7), 7);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 8), 8);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 9), 9);
    TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 10), 10);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 11), 11);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 12), 12);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 13), 13);
    //TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 13), 13);
  }
  void test_example2() {
    std::vector<int> n1{1,3,5,7,8,9,10,11,12,13};
    std::vector<int> n2{2,4,6};
    Solution s;
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 7);
  }

  void XXtest_example() {
    std::vector<int> n1{1,3,5,7,8,9,10,11,12,13};
    std::vector<int> n2{2,4,6,14};
    Solution s;
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 7.5000);
  }

  void XXtest_example3() {
    std::vector<int> n1{1,3,5,7};
    std::vector<int> n2{2,4,6,8};
    Solution s;
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 4.5000);
  }

  void XXtest_example4() {
    std::vector<int> n1{};
    std::vector<int> n2{2,4,6,8};
    Solution s;
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 5);
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n2, n1), 5);
  }
  void XXtest_example5() {
    std::vector<int> n1{1, 2};
    std::vector<int> n2{1, 2};
    Solution s;
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 1.5);
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n2, n1), 1.5);
  }
  void XXtest_example6() {
    std::vector<int> n1{1, 1};
    std::vector<int> n2{1, 2};
    Solution s;
    TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 3), 1);
    TS_ASSERT_EQUALS(s.findKthSmallestElement(n1, n2, 2), 1);
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n1, n2), 1.5);
    TS_ASSERT_EQUALS(s.findMedianSortedArrays(n2, n1), 1.5);
  }

};
