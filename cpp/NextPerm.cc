class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() <= 1) {
            return;
        }
        if (nums.size() == 2) {
            std::swap(nums[0], nums[1]);
            return;
        }
        /**
         * From max to zero:
         *  1) check if ith element is > i-1th element, 
         *  2) chek index from max -> i which has > than nums[i-1]
         *  3) swap (nums[i-1], nums[nm]);
         *  4) sort (nums[i->max])
         */
         int l=nums.size();
         int fn=false;
         int i=l-1;
         for (; i>=1; --i) {
             if (nums[i-1] < nums[i]) {
                 fn=true;
                 break;
             }
         }
         if (!fn) {
             std::reverse(nums.begin(), nums.end());
             return;
         }
         int j=l-1;
         for (; j>=i; --j) {
             if (nums[i-1] < nums[j]) {
                 break;
             }
         }
         std::swap(nums[i-1], nums[j]);
         std::sort(nums.begin()+i, nums.end());
         return;
        
    }
};
