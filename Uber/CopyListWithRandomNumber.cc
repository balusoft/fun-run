/*

138. Copy List with Random Pointer My Submissions Question
Total Accepted: 60560 Total Submissions: 232960 Difficulty: Hard
A linked list is given such that each node contains an additional random pointer
which could point to any node in the list or null.

Return a deep copy of the list.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss


*/
/**
  Definition for singly-linked list with a random pointer.
  */
struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
class Solution {
public:
  RandomListNode *copyRandomList(RandomListNode *head) {}
};
