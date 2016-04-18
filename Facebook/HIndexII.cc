/**
Given an array of citations (each citation is a non-negative integer) of a
researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if
h of his/her N papers have at least h citations each, and the other N − h papers
have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5
papers in total and each of them had received 3, 0, 6, 1, 5 citations
respectively. Since the researcher has 3 papers with at least 3 citations each
and the remaining two with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as
the h-index.
*/

#include <vector>
#include <algorithm>
#include <cxxtest/TestSuite.h>
class Solution {
public:
  // 0 1 2 3 4
  // 5 4 3 2 1
  // 0 1 3 5 6
  int hIndex(const std::vector<int> &citations) {
    if (citations.empty()) {
      return 0;
    }
    int c = 0;
    int lo = 0;
    int hi = citations.size()-1;
    while (lo <= hi) {
      int mid = lo + (hi -lo)/2;
      // revIdx = size-idx
      int ri = citations.size()-mid;
      if (ri == citations[mid]) {
        return ri;
      } else if (ri < citations[mid]) {
        if (c > ri) {
          break;
        } else {
          c = ri;
        }
        // move left
        hi = mid-1; //TODO: should we ignore mid?
                    //      This could be best.
      } else {
        // move right;
        lo = mid+1;
      }
    }
    return c;
  }

  int hIndex2(const std::vector<int> &citations) {
    std::vector<int> cnt(citations.size() + 1, 0);
    for (auto e : citations) {
      if (e > citations.size()) {
        ++cnt[citations.size()];
      } else {
        ++cnt[e];
      }
    }

    int c=0;
    for (size_t i=citations.size(); i >=1; --i) {
      c+=cnt[i];
      if (c >= i) {
        return i;
      }
    }
    return 0;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    //std::vector<int> cit{3, 0, 6, 1, 5};
    std::vector<int> cit{0, 1, 4, 5, 6};
    Solution s;
    TS_ASSERT_EQUALS(s.hIndex(cit), 3);
  }
};
