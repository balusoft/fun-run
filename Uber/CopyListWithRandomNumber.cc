/*

138. Copy List with Random Pointer My Submissions Question
Total Accepted: 60560 Total Submissions: 232960 Difficulty: Hard
A linked list is given such that each node contains an additional random pointer
which could point to any node in the list or null.

Return a deep copy of the list.
*/

#include <iostream>
#include <unordered_map>

#include <cxxtest/TestSuite.h>

struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
  RandomListNode *copyRandomList(RandomListNode *head) {
    if (!head) {
      return nullptr;
    }
    std::unordered_map<RandomListNode*, RandomListNode*> map;
    RandomListNode *itr = head;
    RandomListNode *copy = nullptr;
    RandomListNode *cItr = copy;

    while (itr) {
      RandomListNode *tmp = new RandomListNode(itr->label);
      map[itr] = tmp;
      if (cItr) {
        cItr->next = tmp;
        cItr = cItr->next;
      } else {
        cItr = tmp;
        copy = cItr;
      }
      itr = itr->next;
    }
    itr = head;
    while (itr) {
      if (itr->random) {
        map[itr]->random = map[itr->random];
      }
      itr = itr->next;
    }
    return copy;
  }
};

class TestSuite : public CxxTest::TestSuite {
public:
  void test_random() {
    RandomListNode r0(0);
    RandomListNode r1(1);
    RandomListNode r2(2);

    r0.next = &r1;
    r1.next = &r2;

    r2.random = &r1;
    r1.random = &r0;

    Solution s;
    RandomListNode *copy = s.copyRandomList(&r0);
    TS_ASSERT_EQUALS(copy->label, 0);
    TS_ASSERT_EQUALS(copy->next->label, 1);
    TS_ASSERT_EQUALS(copy->next->next->label, 2);
    TS_ASSERT_EQUALS(copy->next->next->next, nullptr);

    TS_ASSERT_EQUALS(copy->random, nullptr);
    TS_ASSERT_EQUALS(copy->next->random->label, 0);
    TS_ASSERT_EQUALS(copy->next->next->random->label, 1);
  }
  void test_null() {
    Solution s;
    TS_ASSERT_EQUALS(s.copyRandomList(nullptr), nullptr);
  }
};
