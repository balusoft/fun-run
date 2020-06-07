//
//  OddEvenLinkedList.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 2/15/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include "OddEvenLinkedList.hpp"
#include <iostream>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(const int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    ListNode* removeNext(ListNode *evenPtr) {
      if (NULL == evenPtr || NULL == evenPtr->next) {
        return NULL;
      }
      ListNode* nextOfEven = evenPtr->next;
      evenPtr->next = nextOfEven->next;
      return nextOfEven;
    }

    void pushBack(ListNode *oddPtr, ListNode *n) {
      if (NULL == oddPtr || NULL == n) {
        return;
      }
      ListNode *oddNext = oddPtr->next;
      oddPtr->next = n;
      n->next = oddNext;
    }
    /**
     * Algorithm:
     * odd ptr -> insert point
     * even ptr-> forward point
     */
    ListNode* oddEvenList(ListNode* head) {
      //Step 1: oddPtr = first element in list
      // evenPtr = second element in list
      //Step 2: Move element next-to even element to element next-to odd.
      if (NULL == head || NULL == head->next) {
        return head;
      }
      ListNode *oddPtr=head;
      ListNode *evenPtr=head->next;
      while (NULL != evenPtr->next) {
        //Now move element from next-to-even to next-to-odd
        //Take a backup of next-to-even
        pushBack(oddPtr, removeNext(evenPtr));
        oddPtr = oddPtr->next;
        if (NULL != evenPtr->next) {
          evenPtr = evenPtr->next;
        }
      }
      return head;
    }
};

namespace OddEvenLinkedList {
void test(const int max) {
  ListNode *head = new ListNode(1);
  ListNode *itr = head;
  if (max > 1) {
    for (int i=2; i<=max; ++i) {
      itr->next = new ListNode(i);
      itr=itr->next;
    }
  }
  itr->next = NULL;
  Solution s;
  s.oddEvenList(head);
  itr = head;
  while (NULL != itr) {
    std::cout << " " << itr->val;
    itr=itr->next;
  }
  std::cout << "\n";
}
void test() {
  test(1);
  test(2);
  test(3);
  test(4);
  test(5);
  test(6);
  test(7);
  test(8);
}
}
