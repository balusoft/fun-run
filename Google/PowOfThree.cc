/**
Given an integer, write a function to determine if it is a power of three.

Follow up:
Could you do it without using any loop / recursion?
**/

class Solution {
public:
    bool isPowerOfThree(int n) {
        static int x = (int) log(INT_MAX) / log(3);
        static int m3px = pow(3, x);
        return n > 0 && (n == 1 || m3px%n == 0);
    }
};
