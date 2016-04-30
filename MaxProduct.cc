
/*
152. Maximum Product Subarray   My Submissions QuestionEditorial Solution
Total Accepted: 58125 Total Submissions: 261854 Difficulty: Medium
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        /**
         * The way I looked at this problem is as follows.
        You have three choices to make at any position in array.
1. You can get maximum product by multiplying the current element with 
    maximum product calculated so far.  (might work when current 
    element is positive).
2. You can get maximum product by multiplying the current element with 
    minimum product calculated so far. (might work when current 
    element is negative).
3.  Current element might be a starting position for maximum product sub
     array
     */
     
        int cMax=nums[0];
        int cMin=nums[0];
        int mp = nums[0];
        for (int i=1; i<nums.size(); ++i) {
            int nMax = std::max({nums[i], cMax*nums[i], cMin*nums[i]});
            int nMin = std::min({nums[i], cMax*nums[i], cMin*nums[i]});
            cMax = nMax;
            cMin = nMin;
            mp = std::max(mp, cMax);
        }
        return mp;
    }
};
