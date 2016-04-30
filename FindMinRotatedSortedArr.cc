/**
153. Find Minimum in Rotated Sorted Array   My Submissions QuestionEditorial
Solution
Total Accepted: 89823 Total Submissions: 248015 Difficulty: Medium
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
**/

class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        int j = pivot(nums);
        return j == -1 ? nums[0] : nums[j];
    }
    int pivot(vector<int>& nums) {
        int f=0, r=nums.size()-1;
        while (f < r) {
            int m = f + (r-f)/2;
            if (nums[f] > nums[m]) {
                r = m;
            } else if (nums[f] < nums[m]) {
                f = m;
            } else if (f==m){
                // Which means only two elements are there.
                // If n[f] < n[r]: return -1
                if (nums[f] < nums[r]) return -1;
                return r;
            }
        }
        assert(0);
        return -1;
    }
    /**
     * 4 5 6 [7 8 [[[9] 1] 2 3]]
     * 7 8 [[[9] 1] 2 3]
     */ 
};
