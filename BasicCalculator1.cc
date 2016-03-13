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
        oprStack(), curInfIdx(0), delim(' '), curValue() {}
  bool next() {
    if (curInfIdx >= infix.length() && oprStack.empty()) {
      return false;
    }
    if (curInfIdx >= infix.length()) {
      if (!oprStack.empty()) {
        curValue = oprStack.top();
        oprStack.pop();
        return true;
      }
    } else {
      // If delimiter
      while (infix[curInfIdx] == ' ') {
        ++curInfIdx;
      }
      if (curInfIdx >= infix.length()) {
        return next();
      }
      // If operand
      std::string oprnd;
      while (isdigit(infix[curInfIdx])) {
        oprnd += infix[curInfIdx];
        ++curInfIdx;
      }
      if (!oprnd.empty()) {
        curValue = oprnd;
        return true;
      }
      // If operator
      if (operators.find(infix[curInfIdx]) != operators.end()) {
        if (oprStack.empty() || oprStack.top() == '(' ||
            operators[oprStack.top()] <= operators[infix[curInfIdx]]) {
          oprStack.push(infix[curInfIdx]);
          ++curInfIdx;
          return next();
        } else {
          curValue = oprStack.top();
          oprStack.pop();
          return true;
        }
      } else if (infix[curInfIdx] == '(') {
        oprStack.push(infix[curInfIdx]);
        ++curInfIdx;
        return next();
      } else if (infix[curInfIdx] == ')') {
        if (oprStack.top() == '(') {
          oprStack.pop();
          ++curInfIdx;
          return next();
        } else {
          curValue = oprStack.top();
          oprStack.pop();
          return true;
        }
      } else {
        assert(0 == "should never reach here");
      }
    }
    return false;
  }
  std::string operator*() const {
    return curValue;
  }
private:
  const std::string& infix;
  std::map<char, uint32_t> operators;
  std::stack<char> oprStack;
  size_t curInfIdx;
  char delim;
  std::string curValue;
};
std::string infix2postfix(const std::string &infix) {
  std::string postfix;
  Infix2PostfixItr itr(infix);
  while(itr.next()) {
    postfix += *itr;
    postfix += ' ';
  }
  return postfix;
}

int main() {
  std::cout << "1+2 = " << infix2postfix("1+2") << "\n";
  std::cout << "1*2+3 = " << infix2postfix("1*2+3") << "\n";
  std::cout << "1+2*3 = " << infix2postfix("1+2*3") << "\n";
  std::cout << "    1 + 2      *      3 = " << infix2postfix("        1   + 2    * 3  ") << "\n";
  std::cout << "(1+2)*3 = " << infix2postfix("(1+2)*3") << "\n";
  std::cout << "((1+2))*3 = " << infix2postfix("(((((1+2))*3)))") << "\n";
  return 0;
}

