#include <iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
  public:
    void deleteNode(ListNode* node) {
      // case 1: node is null
      if (NULL == node) { return; }
      // case 2: node next is null
      if (NULL == node->next) { return; }
      // case 3: node next is not null
      ListNode *tmp = node->next;
      node->val = node->next->val;
      node->next = node->next->next;
      delete tmp;
      tmp = NULL;
    }
};

int main() {
  ListNode *root = new ListNode(1);
  root->next = new ListNode(2);
  root->next->next = new ListNode(3);
  root->next->next->next = new ListNode(4);
  std::cout << "iterm#3: " << root->next->next->val << "\n";
  Solution s;
  s.deleteNode(root->next->next);
  std::cout << "iterm#3: " << root->next->next->val << "\n";
  s.deleteNode(root->next->next);
  std::cout << "iterm#3: " << root->next->next->val << "\n";
  s.deleteNode(root->next);
  std::cout << "iterm#2: " << root->next->val << "\n";
  s.deleteNode(root->next);
  s.deleteNode(NULL);
  std::cout << "iterm#2: " << root->next->val << "\n";
}
