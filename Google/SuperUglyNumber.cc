/**
313. Super Ugly Number   My Submissions QuestionEditorial Solution
Total Accepted: 12970 Total Submissions: 38094 Difficulty: Medium
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given
prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26,
28, 32] is the sequence of the first 12 super ugly numbers given primes = [2, 7,
13, 19] of size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.

Credits:
Special thanks to @dietpepsi for adding this problem and creating all test
cases.

Subscribe to see which companies asked this question
**/

using PrI=std::tuple<int, int, int>;
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        /**
         * take memo[] as array, with zero as 1
         * take heap as list of tuples as (p, idx:memo), maintians min
         * in a loop (1->n):
         *  pickup min element, and remove min from heap.
         *  increment tuple index for that prime number and add back to heap.
         * return memo[n-1];
         */
         std::vector<int> memo(n, 0);
         memo[0]=1;
         // Create heap
         auto cmp = [&](const PrI & t1, const PrI & t2) {
            return std::get<2>(t1) > std::get<2>(t2); /** due to priority q **/
         };
         std::priority_queue<PrI, std::vector<PrI>, decltype(cmp)> pq(cmp);
         for (auto p : primes) {
             pq.push(std::make_tuple(p, 0, memo[0]*p));
         }
         for (int i=1; i<n; ++i) {
             int p, idx, val;
             std::tie(p, idx, val) = pq.top();
             pq.pop();
             memo[i] = val;
             ++idx;
             pq.push(std::make_tuple(p, idx, memo[idx]*p));
             while(std::get<2>(pq.top()) == memo[i]) {
                 std::tie(p, idx, val) = pq.top();
                 pq.pop();
                 ++idx;
                 pq.push(std::make_tuple(p, idx, memo[idx]*p));
             }
         }
         //for (int i : memo) {
         //    std:: cout << i << ",";
         //}
         return memo[n-1];
    }
};


