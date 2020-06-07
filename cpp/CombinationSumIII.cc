/**
216. Combination Sum III   My Submissions QuestionEditorial Solution
Total Accepted: 30907 Total Submissions: 86384 Difficulty: Medium
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Ensure that numbers within the set are sorted in ascending order.


Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]

Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]
Credits:
Special thanks to @mithmatt for adding this problem and creating all test cases.


**/

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        /**
         * 0) n =0 || k = 0 return empty set
         * 1) if sig(k) < sig(n) return empty set
         * 
         * Use DFS...
         * DFS(k, n, res)
         * 
         * (1, {})
         */
         std::unordered_map<std::string, vector<vector<int>>> memo;
         return dfs(k, n, 1, memo);
    }
    
    vector<vector<int>> dfs(int k, int n, int start, std::unordered_map<std::string, vector<vector<int>>> &memo) {
        if (k <1 || k > 9 ||
            n < start ||
            start <1 || start >9) {
            return vector<vector<int>>();
        }
        // Termination conditions: k==1
        if (k==1) {
            if (n < 10) return {{ n }};
            else return vector<vector<int>>();
        }

        std::string key= to_string(k) + ":" + to_string(n) + ":" + to_string(start);
        if (memo.count(key) > 0) {
            return memo[key];
        }
        vector<vector<int>> res;
        for (int i=start; i<=(n-start); ++i) {
            std::vector<vector<int>> sr = dfs(k-1, n-i, i+1, memo);
            merge(res, i, sr);
        }
        memo[key] = res;
        return memo[key];
    }
    void merge(vector<vector<int>> &out, const int i, const vector<vector<int>> &sr) {
        for (const auto &r : sr) {
            std::vector<int> res;
            res.push_back(i);
            res.insert(res.end(), r.begin(), r.end());
            out.push_back(res);
        }
    }
};
