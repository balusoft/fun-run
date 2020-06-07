//
//  MergeTwoLists.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 2/26/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include "MergeTwoLists.hpp"
#include <cassert>
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (NULL == l1) { return l2; }
    if (NULL == l2) { return l1; }
    ListNode *res = NULL;
    ListNode *root = NULL;
    while (NULL != l1 && NULL != l2) {
      ListNode *tmp = NULL;
      if (l1->val <= l2->val) {
        tmp = l1;
        l1 = l1->next;
      } else {
        tmp = l2;
        l2 = l2->next;
      }
      if (res) {
        res->next = tmp;
        res = res->next;
      } else {
        res = root = tmp;
      }
    }
    if (NULL != l1) {
      res->next = l1;
    } else if (NULL != l2) {
      res->next = l2;
    } else {
      assert(0 == "should be never the case");
    }
    return root;
  }
};
