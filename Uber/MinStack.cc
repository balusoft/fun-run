/*
155. Min Stack My Submissions Question
Total Accepted: 65620 Total Submissions: 301782 Difficulty: Easy
Design a stack that supports push, pop, top, and retrieving the minimum element
in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

30 20 19 31 32 4 2 1
stack: 1 2 4 32 31 19 20 30
minStack: 1 2 4 19 20 30
*/

#include <stack>
#include <iostream>
#include <cassert>

class MinStack {
public:
  void push(int x) {
    st.push(x);
    if (minSt.empty() || minSt.top() >= x) {
      minSt.push(x);
    }
  }

  void pop() {
    if (st.top() == minSt.top()) {
      minSt.pop();
    }
    st.pop();
  }

  int top() {
    return st.top();
  }

  int getMin() {
    return minSt.top();
  }

  bool empty() {
    assert(st.empty() == minSt.empty());
    return st.empty() && minSt.empty();
  }
private:
  std::stack<int> st;
  std::stack<int> minSt;
};

int main() {
  MinStack st;
  st.push(30);
  st.push(20);
  st.push(4);
  st.push(19);
  st.push(31);
  st.push(32);
  st.push(4);
  st.push(2);
  st.push(1);

  while(!st.empty()) {
    std::cout << "Top: " << st.top() << " <<< >>> min: " << st.getMin() << "\n";
    st.pop();
  }
  return 0;
}
