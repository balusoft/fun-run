/**
228. Summary Ranges   My Submissions QuestionEditorial Solution
Total Accepted: 44681 Total Submissions: 184559 Difficulty: Medium
Given a sorted integer array without duplicates, return the summary of its ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].

Credits:
Special thanks to @jianchao.li.fighter for adding this problem and creating all test cases.

Subscribe to see which companies asked this question
**/

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        if (nums.empty()) return res;
        if (nums.size() == 1) { return {std::to_string(nums[0])}; }
        int start=nums[0];
        for (int i=1; i < nums.size(); ++i) {
            if (nums[i-1] + 1 == nums[i]) {
                continue;
            }
            //Make range
            // case 1: start and i-1 are same
            res.push_back(getRange(nums, start, i));
            start = nums[i];
        }
        // do it for last one.
        res.push_back(getRange(nums, start, nums.size()));
        return res;
    }
    std::string getRange(const vector<int> &nums, int start, int i) {
        std::string str;
        str += std::to_string(start);
        if (start != nums[i-1]) {
            str += "->";
            str += std::to_string(nums[i-1]);
        }
        return str;
    }
};
