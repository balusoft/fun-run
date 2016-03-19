/*
206. Reverse Linked List My Submissions Question
Total Accepted: 93805 Total Submissions: 241971 Difficulty: Easy
Reverse a singly linked list.

click to show more hints.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

*/

#include <iostream>
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};
std::ostream& operator<<(std::ostream& ostr, ListNode *list) {
  ostr << "[ ";
  ListNode *itr = list;
  while (itr) {
    std::cout << itr->val << ",";
    itr = itr->next;
  }
  ostr << "]";
  return ostr;
}

class Solution {
public:
  ListNode *reverseList(ListNode *head) {
    ListNode *rev = nullptr;
    ListNode *itr = head;
    while (itr) {
      ListNode *tmp = itr;
      itr = itr->next;
      tmp->next = rev;
      rev = tmp;
    }
    return rev;
  }
};

void test(ListNode* list) {
  Solution s;
  std::cout << "List: " <<  list << "\n";
  std::cout << "Rev List: " << s.reverseList(list) << "\n\n";
  return;
}

int main() {
  ListNode l(10);
  ListNode l2(20);
  l.next = &l2;
  ListNode l3(30);
  l2.next = &l3;
  test (&l);
  test (nullptr);
}
