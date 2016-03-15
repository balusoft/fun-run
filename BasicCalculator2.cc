/*
224. Basic Calculator My Submissions Question
Total Accepted: 24326 Total Submissions: 113565 Difficulty: Medium
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus +
or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23
Note: Do not use the eval built-in library function.

Subscribe to see which companies asked this question
*/

/*
This opens door for learning infix, prefix and postfix.

infix:
------
*) Format is <operand><operator><operand>
*) Human readable expression like 1+1 or 2+3, 2*3 etc

prefix:
-------
*) Format is <operator><operand1><operand2>
*) Very efficient in evaluating expressions.
*) Examples a+b can be written as +a,b (, is delimiter)

postfix:
--------
*) Format is <operand1><operand2><operator>
*) Very efficient in evaluating expressions.
*) Examples a+b can be written as a,b+ (, is delimiter)


Operator precedence:
--------------------

1) ( )
2) * /
3) + -

Converting from infix to postfix:
---------------------------------
1) Manual conversion -- understanding purpose:
..............................................
*) Consider expression a+b/c+d*e-f
*) Put parentheses around high priority operators for clarity
*) a+(b/c)+(d*e)-f
*) convert parentheses expressions to post fix
*) a+(bc/)+(de*)-f
*) Now all operators in same priority evaluate left-to-right
*) (a(bc/)+)+((de*)f-)
*) another round
*) ((a(bc/)+)((de*)f-))+
*) Now get rid of parenthesis
*) abc/+de*f-+
*) Hooray that is postfix expression, Hmmm how would machines do this,
   looks complicated Huh

2) Algorithmic approach:
.......................
*) Lets take stack call operator stack, which keeps operators temporarily.
*) Iterate expression from left-to-right
**) if element is operand add to result.
**) else if element is operator:
***)  if stack is empty push into stack
***)  else if top of stack is ( push operator into stack
***)  else if top of stack is ) pop all elements of stack till you get (
      and add those operators to result
***)  else if operator has high-precedence than top of stack push it into stack
***)  else means same priority operatory exists, in this case pop operator add
      add to result and then push operator to stack.
*) Now if there are any operators left add them to result.

Evaluating postfix expression:
-----------------------------
*) Iterate postfix from left-to-right
**) if elem is operand push to stack
**) else if elem is operator:
***) operand2=pop();
***) operand1=pop();
***) push(perform_operation(elem, operand1, operand2));
*) Now stack should be having only one elem, that is expression result.

Note: we can combine those two steps and evaluate directly with two stacks
as well
*/

#include <cassert>
#include <ctype.h>
#include <string>
#include <iostream>
#include <stack>
#include <map>

/*
example expression:
2 * 3 * 31 + 2
assume delim is sapce
*/
class Infix2PostfixItr {
public:
  Infix2PostfixItr(const std::string &infixExpr)
      : infix(infixExpr), operators{{'+',1}, {'-',1}, {'*',2}, {'/',2}},
        oprStack(), idx(0), curInfIdx(0), delim(' '), curValue() {}
  bool next2() {
    if (idx >= infix.length() && oprStack.empty()) {
      return false;
    }
    if (idx == infix.length()) {
      curValue = oprStack.top();
      oprStack.pop();
      return true;
    }
    for (; idx < infix.length(); ++idx) {
      // handle delimiter
      while (idx < infix.length() && infix[idx] == ' ') {
        ++idx;
      }
      if (idx == infix.length()) {
        return next2();
      }
      //infix[i] could be operator or operand.
      // in case of operand return
      std::string oprnd;
      while (idx < infix.length() && isdigit(infix[idx])) {
        oprnd += infix[idx];
        ++idx;
      }
      if (!oprnd.empty()) {
        curValue = oprnd;
        return true;
      }
      // Now check for operator
      if (operators.find(infix[idx]) != operators.end()) {
        // There are three cases here:
        // 1) stack is empty, in that case just push it
        if (oprStack.empty()) {
          oprStack.push(infix[idx]);
          continue;
        }
        // 1.1) another case is top of the stack could be '('
        if (oprStack.top() == '(') {
          oprStack.push(infix[idx]);
          continue;
        }
        // 2) stack top has less priority operator, in this case just push it
        if (operators[oprStack.top()] < operators[infix[idx]]) {
          oprStack.push(infix[idx]);
          continue;
        }
        // 3) stack top has high or equal proirity operator, in this case just
        //    pop it. and then push the operator to stack
        if (operators[oprStack.top()] >= operators[infix[idx]]) {
          curValue = oprStack.top();
          oprStack.pop();
          oprStack.push(infix[idx]);
          ++idx;
          return true;
        }
      }
      // Now check for parenthesis
      // There are two cases here
      // case 1: it is '(', just push it
      if ('(' == infix[idx]) {
        oprStack.push(infix[idx]);
        continue;
      } else if (')' == infix[idx]) {
        // case 2: it is '(', just push it
        // Again here two cases, top could be '(' or operator
        // case '(' just pop it.
        if ('(' == oprStack.top()) {
          oprStack.pop();
          continue;
        } else {
          curValue = oprStack.top();
          oprStack.pop();
          return true;
        }
      }
    }
    return next2();
  }
  std::string operator*() const {
    return curValue;
  }
private:
  const std::string& infix;
  std::map<char, uint32_t> operators;
  std::stack<char> oprStack;
  size_t curInfIdx;
  int idx;
  char delim;
  std::string curValue;
};
int performOp(char op, int oprnd1, int oprnd2) {
  switch (op) {
  case '+':
    return oprnd1 + oprnd2;
  case '-':
    return oprnd1 - oprnd2;
  case '*':
    return oprnd1 * oprnd2;
  case '/':
    return oprnd1 / oprnd2;
  default:
    assert(0 == "never ");
  }
  return 0;
}
int exprEval(const std::string &expr) {
  Infix2PostfixItr itr(expr);
  std::stack<int> oprndStack;
  while(itr.next2()) {
    // Two possible outcomes here, output could be operator or operand.
    // case 1: operand, push it to stack
    if (isdigit((*itr)[0])) {
      oprndStack.push(atoi((*itr).c_str()));
    } else {
      // case 2: operator, pop operands and perform operation
      int oprnd2 = oprndStack.top();
      oprndStack.pop();
      int oprnd1 = oprndStack.top();
      oprndStack.pop();
      assert ((*itr).length() == 1);
      int res = performOp((*itr)[0], oprnd1, oprnd2);
      oprndStack.push(res);
    }
  }
  assert(oprndStack.size() == 1);
  return oprndStack.top();
}
std::string infix2postfix(const std::string &infix) {
  std::string postfix;
  Infix2PostfixItr itr(infix);
  while(itr.next2()) {
    postfix += *itr;
    postfix += ' ';
  }
  return postfix;
}

class Solution {
  public:
    int calculate(std::string s) {
      return exprEval(s);
    }
};

int main() {
  std::cout << "(1+(4+5+2)-3)+(6+8) : " << infix2postfix("(1+(4+5+2)-3)+(6+8)") << "\n";
  std::cout << "(1+(4+5+2)-3)+(6+8)" << exprEval("(1+(4+5+2)-3)+(6+8)") << "\n";
  return 0;
  std::cout << "1+2 = " << exprEval("1+2") << "\n";
  std::cout << "1*2+3 = " << exprEval("1*2+3") << "\n";
  std::cout << "1+2*3 = " << exprEval("1+2*3") << "\n";
  std::cout << "    1 + 2      *      3 = " << exprEval("        1   + 2    * 3  ") << "\n";
  std::cout << "(1+2)*3 = " << exprEval("(1+2)*3") << "\n";
  std::cout << "((1+2))*3 = " << exprEval("(((((1+2))*3)))") << "\n";
  std::cout << "1+2+3 = " << exprEval("1+2+3") << "\n";
  return 0;
}

