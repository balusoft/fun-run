/*
92. Reverse Linked List II My Submissions Question
Reverse a linked list from position m to n.
Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

1 2 3

m=1
n=2

itr=2
revItr=1
tmp=itr->next=3


Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.

*/
#include <cxxtest/TestSuite.h>
#include <cassert>
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

std::ostream& operator<<(std::ostream& ostr, ListNode *list) {
  ostr << "{";
  bool first=true;
  ListNode *prev = list;
  while(list) {
    if (first) {
      first=false;
    } else {
      ostr << ",";
    }
    ostr << list->val ;
    if (prev == list->next) {
      ostr << "ERR: loop detected";
      break;
    }
    prev = list;
    list=list->next;
  }
  ostr << "}";
  return ostr;
}
class Solution {
public:
  ListNode *reverseBetween(ListNode *head, int m, int n) {
    //std::cout << "Given : << " << head << "\n";
    assert (1 <= m);
    assert (m <= n);
    if (!head) {
      return head;
    }
    if (m == n) {
      return head;
    }

    int len=n-m+1;
    ListNode *mpNode = nullptr;
    ListNode *tail = head;
    // find m-1 node and head of mth node
    while (m > 1) {
      --m;
      mpNode = tail;
      tail = tail->next;
    }
    //std::cout << "len == " << len << "\n";
    //std::cout << "tail >> :" << tail << "\n";
    // reverse linked list from mth node
    ListNode *revHead = tail;
    ListNode *itr = tail->next;
    revHead->next = nullptr;
    //std::cout << "\n\n\n";
    //std::cout << "revHead >> :" << revHead << "\n";
    //std::cout << "itr >> :" << itr << "\n";
    while (itr && len>1) {
      ListNode *tmp = revHead;
      revHead = itr;
      itr = itr->next;
      revHead->next = tmp;
      --len;
      //std::cout << "revHead >> :" << revHead << "\n";
      //std::cout << "itr >> :" << itr << "\n";
      //std::cout << "len == " << len << "\n";
    }
    tail->next = itr;

    //std::cout << "itr >> :" << itr << "\n";
    //std::cout << "revHead >> :" << revHead << "\n";

    // Stitch head
    //Now mpNode -> next is revHead
    if (mpNode) {
      mpNode->next = revHead;
    } else {
      head = revHead;
    }

    return head;
  }
};

class TestSolution : public CxxTest::TestSuite {
public:
  TestSolution() : h(1), n2(2), n3(3), n4(4) {
  }
  void setUp() {
    h.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
  }
  void test_m_eq_n_eq_1() {
    ListNode *res = s.reverseBetween(&h, 1, 1);
    TS_ASSERT_EQUALS(&h, res);
    TS_ASSERT_EQUALS(h.val, res->val);
    TS_ASSERT_EQUALS(h.next, res->next);
    TS_ASSERT_EQUALS(h.next->val, res->next->val);
    TS_ASSERT_EQUALS(h.next->next, res->next->next);
    TS_ASSERT_EQUALS(h.next->next->val, res->next->next->val);
  }
  void test_m_eq_n_eq_2() {
    ListNode *res = s.reverseBetween(&h, 2, 2);
    TS_ASSERT_EQUALS(&h, res);
    TS_ASSERT_EQUALS(h.val, res->val);
    TS_ASSERT_EQUALS(h.next, res->next);
    TS_ASSERT_EQUALS(h.next->val, res->next->val);
    TS_ASSERT_EQUALS(h.next->next, res->next->next);
    TS_ASSERT_EQUALS(h.next->next->val, res->next->next->val);
  }
  void test_m_eq_n_eq_3() {
    ListNode *res = s.reverseBetween(&h, 3, 3);
    TS_ASSERT_EQUALS(&h, res);
    TS_ASSERT_EQUALS(h.val, res->val);
    TS_ASSERT_EQUALS(h.next, res->next);
    TS_ASSERT_EQUALS(h.next->val, res->next->val);
    TS_ASSERT_EQUALS(h.next->next, res->next->next);
    TS_ASSERT_EQUALS(h.next->next->val, res->next->next->val);
  }
  void test_m_eq_1_n_eq_2() {
    //std::cout << "h>>> " << &h << "\n";
    ListNode *res = s.reverseBetween(&h, 1, 2);
    //std::cout << "res>>> " << res << "\n";
    TS_ASSERT_EQUALS(res->val, 2);
    TS_ASSERT_EQUALS(res->next->val, 1);
    TS_ASSERT_EQUALS(res->next->next->val, 3);
    TS_ASSERT_EQUALS(res->next->next->next->val, 4);
    TS_ASSERT_EQUALS(res->next->next->next->next, nullptr);
  }
  void test_m_eq_1_n_eq_2_retest() {
    //std::cout << "h>>> " << &h << "\n";
    ListNode *res = s.reverseBetween(&h, 1, 2);
    //std::cout << "res>>> " << res << "\n";
    TS_ASSERT_EQUALS(res->val, 2);
    TS_ASSERT_EQUALS(res->next->val, 1);
    TS_ASSERT_EQUALS(res->next->next->val, 3);
    TS_ASSERT_EQUALS(res->next->next->next->val, 4);
    TS_ASSERT_EQUALS(res->next->next->next->next, nullptr);
  }
  void test_m_eq_2_n_eq_3() {
    //std::cout << "h>>> " << &h << "\n";
    ListNode *res = s.reverseBetween(&h, 2, 3);
    //std::cout << "res>>> " << res << "\n";
    TS_ASSERT_EQUALS(res->val, 1);
    TS_ASSERT_EQUALS(res->next->val, 3);
    TS_ASSERT_EQUALS(res->next->next->val, 2);
    TS_ASSERT_EQUALS(res->next->next->next->val, 4);
    TS_ASSERT_EQUALS(res->next->next->next->next, nullptr);
  }
  void test_m_eq_3_n_eq_4() {
    //std::cout << "h>>> " << &h << "\n";
    ListNode *res = s.reverseBetween(&h, 3, 4);
    //std::cout << "res>>> " << res << "\n";
    TS_ASSERT_EQUALS(res->val, 1);
    TS_ASSERT_EQUALS(res->next->val, 2);
    TS_ASSERT_EQUALS(res->next->next->val, 4);
    TS_ASSERT_EQUALS(res->next->next->next->val, 3);
    TS_ASSERT_EQUALS(res->next->next->next->next, nullptr);
  }
private:
  ListNode h;
  ListNode n2;
  ListNode n3;
  ListNode n4;
  Solution s;
};
