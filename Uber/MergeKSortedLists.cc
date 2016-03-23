/*
23. Merge k Sorted Lists My Submissions Question
Total Accepted: 79123 Total Submissions: 343714 Difficulty: Hard
Merge k sorted linked lists and return it as one sorted list. Analyze and
describe its complexity.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

**/

#include <iostream>
#include <queue>
#include <cxxtest/TestSuite.h>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};
class Solution {
public:
  ListNode *mergeKLists(std::vector<ListNode *> &lists) {
    if (lists.empty()) {
      return nullptr;
    }
    if (lists.size() == 1) {
      return lists[0];
    }
    auto cmp = [](const ListNode *n1, const ListNode *n2) {
      return n1->val > n2->val;
    };
    std::priority_queue<ListNode *, std::vector<ListNode *>, decltype(cmp)>
        minHeap(cmp);

    // add all k sorted lists heads into minHeap
    for (auto& l : lists) {
      if (l) {
        //std::cout << "Adding: " << l->val << "\n";
        minHeap.push(l);
      }
    }
    // Now we have all heads in min heap
    ListNode *res = nullptr;
    ListNode *itr = res;

    while(!minHeap.empty()) {
      ListNode *tmp = minHeap.top();
      //std::cout << "top:" << tmp->val << "\n";
      minHeap.pop();
      if (!itr) {
        res = tmp;
        itr = res;
      } else {
        itr->next = tmp;
        itr = itr->next;
      }

      if (itr->next) {
        minHeap.push(itr->next);
        //std::cout << "Adding: " << itr->next->val << "\n";
      }
    }
    return res;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  void test_example() {
    ListNode s10(10);
    ListNode s12(12);
    s10.next = &s12;
    ListNode s14(14);
    s12.next = &s14;

    ListNode s11(11);
    ListNode s13(13);
    s11.next = &s13;
    ListNode s15(15);
    s13.next = &s15;

    std::vector<ListNode*> kLists = {&s10, &s11};
    Solution s;
    ListNode *res = s.mergeKLists(kLists);
    int val=10;
    while (res) {
      TS_ASSERT_EQUALS(res->val, val);
      res = res->next;
      ++val;
    }
    TS_ASSERT_EQUALS(val, 16);
  }

  void test_empty() {
    Solution s;
    std::vector<ListNode *> empty;
    TS_ASSERT_EQUALS(s.mergeKLists(empty), nullptr);
  }

  void test_one() {
    ListNode s10(10);
    ListNode s12(12);
    s10.next = &s12;
    ListNode s14(14);
    s12.next = &s14;

    std::vector<ListNode*> kLists = {&s10};
    Solution s;
    ListNode *res = s.mergeKLists(kLists);
    int val=10;
    while (res) {
      TS_ASSERT_EQUALS(res->val, val);
      res = res->next;
      val += 2;
    }
    TS_ASSERT_EQUALS(val, 16);
  }


};
