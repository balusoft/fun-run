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


*/
