//
//  createMaxNumber.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 1/6/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include "createMaxNumber.hpp"

#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <sstream>
#include <iomanip>

/**
 Given two arrays of length m and n with digits 0-9 representing two numbers. 
 Create the maximum number of length k <= m + n from digits of the two. The 
 relative order of the digits from the same array must be preserved. Return an 
 array of the k digits. You should try to optimize your time and space 
 complexity.
 
 Example 1:
 nums1 = [3, 4, 6, 5]
 nums2 = [9, 1, 2, 5, 8, 3]
 k = 5
 return [9, 8, 6, 5, 3]
 
 Example 2:
 nums1 = [6, 7]
 nums2 = [6, 0, 4]
 k = 5
 return [6, 7, 6, 0, 4]
 
 Example 3:
 nums1 = [3, 9]
 nums2 = [8, 9]
 k = 3
 return [9, 8, 9]
 
 More Details
 
 Input:
 [6,7]
 [6,0,4]
 5
 Output:
 [6,6,7,2,5]
 Expected:
 [6,7,6,0,4]
 
*/

class Solution {
public:
    std::unordered_map<std::string, std::pair<int,size_t>> dpMap;
    size_t getNextIndex(const bool isA, const int k, const size_t kidx, const std::vector<int>& a, const size_t ai, const size_t bsize, const size_t bi) {
        size_t nextIdx = ai;
        for (size_t idx = ai; idx < a.size(); ++idx) {
            if (k-kidx-1 > (a.size()-idx-1) + (bsize-bi)) {
                break;
            }
            if (a[idx] > a[nextIdx]) {
                nextIdx = idx;
            }
        }
        return nextIdx;
    }
    
    void saveResult(const std::string &key, const std::pair<int,size_t> &value) {
        std::cout << key << ": (" << ((value.first==0)?"A":"B") << "," << value.second << ")\n";
        dpMap[key] = value;
    }
    std::pair<int, size_t> dp(const int k, const size_t kidx, const std::vector<int>& a, const size_t ai, const std::vector<int>& b, const size_t bi) {
        std::ostringstream ostr;
        ostr << k << ":" << kidx << ":" << ai << ":" << bi << ":";
        if (dpMap.find(ostr.str()) != dpMap.end()) {
            return dpMap[ostr.str()];
        }

        if (ai >= a.size()) {
            saveResult(ostr.str(), std::make_pair(1, getNextIndex(false, k, kidx, b, bi, a.size(), ai)));
            return dpMap[ostr.str()];
        }
        
        if (bi >= b.size()) {
            saveResult(ostr.str(), std::make_pair(0, getNextIndex(true, k, kidx, a, ai, b.size(), bi)));
            return dpMap[ostr.str()];
        }
        
        if (ai >=a.size() && bi >=a.size()) {
            assert(0 == "should not reach here");
        }
        
        const size_t naidx = getNextIndex(true, k, kidx, a, ai, b.size(), bi);
        const size_t nbidx = getNextIndex(false, k, kidx, b, bi, a.size(), ai);
        
        if (a[naidx] > b[nbidx]) {
            saveResult(ostr.str(), std::make_pair(0, naidx));
            return dpMap[ostr.str()];
        } else if (a[naidx] < b[nbidx]) {
            saveResult(ostr.str(),std::make_pair(1, nbidx));
            return dpMap[ostr.str()];
        } else if (kidx == k-1) {
            saveResult(ostr.str(),std::make_pair(0, naidx));
            return dpMap[ostr.str()];
        } else {
            std::vector<std::vector<int> const*> nums;
            nums.reserve(2);
            nums.push_back(&a);
            nums.push_back(&b);
            std::pair<int, size_t> adp;
            std::pair<int, size_t> bdp;
            
            size_t tnaidx = naidx+1;
            size_t tnbidx = nbidx+1;
            size_t depth = 1;
            do {
                adp = dp(k, kidx+depth, a, tnaidx, b, bi);
                bdp = dp(k, kidx+depth, a, ai, b, tnbidx);
                ++tnaidx;
                ++tnbidx;
                ++depth;
            } while ((*nums[adp.first])[adp.second] == (*nums[bdp.first])[bdp.second] &&
                     nums[adp.first]->size()-1 <= adp.second &&
                     nums[bdp.first]->size()-1 <= bdp.second &&
                     depth < k-kidx);
            if ((*nums[adp.first])[adp.second] > (*nums[bdp.first])[bdp.second]) {
                saveResult(ostr.str(),std::make_pair(0, naidx));
                return dpMap[ostr.str()];
            } else if ((*nums[adp.first])[adp.second] < (*nums[bdp.first])[bdp.second]) {
                saveResult(ostr.str(),std::make_pair(1, nbidx));
                return dpMap[ostr.str()];
            } else if (nums[adp.first]->size()-1 > adp.second) {
                saveResult(ostr.str(), std::make_pair(0, naidx));
                return dpMap[ostr.str()];
            } else if (nums[bdp.first]->size()-1 > bdp.second) {
                saveResult(ostr.str(),std::make_pair(1, nbidx));
                return dpMap[ostr.str()];
            }
        }
        assert(0 == "Should never reach here");
    }
    std::vector<int> maxNumber(std::vector<int>& nums1,
                               std::vector<int>& nums2, int k) {
        std::vector<int> res;
        size_t ai = 0;
        size_t bi = 0;
        std::ostringstream ostr;
        for (size_t kidx=0; kidx<k; ++kidx) {
            std::pair<int, size_t> val = dp(k, kidx, nums1, ai, nums2, bi);
            switch (val.first) {
                case 0:
                    ostr << std::setw(2) << kidx << ":A:" << std::setw(2)<< val.second << ":" << std::setw(2)<< nums1[val.second] << "\n";
                    res.push_back(nums1[val.second]);
                    ai = val.second;
                    ++ai;
                    break;
                case 1:
                    ostr << std::setw(2) << kidx << ":B:" << std::setw(2)<< val.second << ":" << std::setw(2)<< nums2[val.second] << "\n";
                    res.push_back(nums2[val.second]);
                    bi = val.second;
                    ++bi;
                    break;
                default:
                    assert(0 == "should not be here");
                    break;
            }
        }
        
        std::cout << "\nResultant array: \n" << ostr.str() << "\n";

        return res;
    }
};

namespace maxNumber {
void printv(const std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << "\n";

    for (auto i : v) {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << "\n\n";
}
void unitTest() {
    {
        std::vector<int> m = {5,0,2,1,0,1,0,3,9,1,2,8,0,9,8,1,4,7,3};
        std::vector<int> n = {7,6,7,1,0,1,0,5,6,0,5,0};
        int k = 31;
        Solution s;
        printv(m);
        printv(n);
        printv(s.maxNumber(m, n, k));
    }
    return;
    {
        std::vector<int> m = {1,1,1};
        std::vector<int> n = {1,1,1};
        int k = 2;
        Solution s;
        printv(m);
        printv(n);
        printv(s.maxNumber(m, n, k));
    }
    {
        std::vector<int> m = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        std::vector<int> n = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        int k = 100;
        Solution s;
        printv(s.maxNumber(m, n, k));
    }
    {
        
        std::vector<int> m = {8,9};
        std::vector<int> n = {3,9};
        int k = 3;
        Solution s;
        for (auto i : s.maxNumber(m, n, k)) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }

    {
        std::vector<int> m = {8,9,7,3,5,9,1,0,8,5,3,0,9,2,7,4,8,9,8,1,0,2,0,2,7,2,3,5,4,7,4,1,4,0,1,4,2,1,3,1,5,3,9,3,9,0,1,7,0,6,1,8,5,6,6,5,0,4,7,2,9,2,2,7,6,2,9,2,3,5,7,4,7,0,1,8,3,6,6,3,0,8,5,3,0,3,7,3,0,9,8,5,1,9,5,0,7,9,6,8,5,1,9,6,5,8,2,3,7,1,0,1,4,3,4,4,2,4,0,8,4,6,5,5,7,6,9,0,8,4,6,1,6,7,2,0,1,1,8,2,6,4,0,5,5,2,6,1,6,4,7,1,7,2,2,9,8,9,1,0,5,5,9,7,7,8,8,3,3,8,9,3,7,5,3,6,1,0,1,0,9,3,7,8,4,0,3,5,8,1,0,5,7,2,8,4,9,5,6,8,1,1,8,7,3,2,3,4,8,7,9,9,7,8,5,2,2,7,1,9,1,5,5,1,3,5,9,0,5,2,9,4,2,8,7,3,9,4,7,4,8,7,5,0,9,9,7,9,3,8,0,9,5,3,0,0,3,0,4,9,0,9,1,6,0,2,0,5,2,2,6,0,0,9,6,3,4,1,2,0,8,3,6,6,9,0,2,1,6,9,2,4,9,0,8,3,9,0,5,4,5,4,6,1,2,5,2,2,1,7,3,8,1,1,6,8,8,1,8,5,6,1,3,0,1,3,5,6,5,0,6,4,2,8,6,0,3,7,9,5,5,9,8,0,4,8,6,0,8,6,6,1,6,2,7,1,0,2,2,4,0,0,0,4,6,5,5,4,0,1,5,8,3,2,0,9,7,6,2,6,9,9,9,7,1,4,6,2,8,2,5,3,4,5,2,4,4,4,7,2,2,5,3,2,8,2,2,4,9,8,0,9,8,7,6,2,6,7,5,4,7,5,1,0,5,7,8,7,7,8,9,7,0,3,7,7,4,7,2,0,4,1,1,9,1,7,5,0,5,6,6,1,0,6,9,4,2,8,0,5,1,9,8,4,0,3,1,2,4,2,1,8,9,5,9,6,5,3,1,8,9,0,9,8,3,0,9,4,1,1,6,0,5,9,0,8,3,7,8,5};
        std::vector<int> n = {7,8,4,1,9,4,2,6,5,2,1,2,8,9,3,9,9,5,4,4,2,9,2,0,5,9,4,2,1,7,2,5,1,2,0,0,5,3,1,1,7,2,3,3,2,8,2,0,1,4,5,1,0,0,7,7,9,6,3,8,0,1,5,8,3,2,3,6,4,2,6,3,6,7,6,6,9,5,4,3,2,7,6,3,1,8,7,5,7,8,1,6,0,7,3,0,4,4,4,9,6,3,1,0,3,7,3,6,1,0,0,2,5,7,2,9,6,6,2,6,8,1,9,7,8,8,9,5,1,1,4,2,0,1,3,6,7,8,7,0,5,6,0,1,7,9,6,4,8,6,7,0,2,3,2,7,6,0,5,0,9,0,3,3,8,5,0,9,3,8,0,1,3,1,8,1,8,1,1,7,5,7,4,1,0,0,0,8,9,5,7,8,9,2,8,3,0,3,4,9,8,1,7,2,3,8,3,5,3,1,4,7,7,5,4,9,2,6,2,6,4,0,0,2,8,3,3,0,9,1,6,8,3,1,7,0,7,1,5,8,3,2,5,1,1,0,3,1,4,6,3,6,2,8,6,7,2,9,5,9,1,6,0,5,4,8,6,6,9,4,0,5,8,7,0,8,9,7,3,9,0,1,0,6,2,7,3,3,2,3,3,6,3,0,8,0,0,5,2,1,0,7,5,0,3,2,6,0,5,4,9,6,7,1,0,4,0,9,6,8,3,1,2,5,0,1,0,6,8,6,6,8,8,2,4,5,0,0,8,0,5,6,2,2,5,6,3,7,7,8,4,8,4,8,9,1,6,8,9,9,0,4,0,5,5,4,9,6,7,7,9,0,5,0,9,2,5,2,9,8,9,7,6,8,6,9,2,9,1,6,0,2,7,4,4,5,3,4,5,5,5,0,8,1,3,8,3,0,8,5,7,6,8,7,8,9,7,0,8,4,0,7,0,9,5,8,2,0,8,7,0,3,1,8,1,7,1,6,9,7,9,7,2,6,3,0,5,3,6,0,5,9,3,9,1,1,0,0,8,1,4,3,0,4,3,7,7,7,4,6,4,0,0,5,7,3,2,8,5,1,4,5,8,5,6,7,5,7,3,3,9,6,8,1,5,1,1,1,0,3};
        
        int k = 500;
        Solution s;
        for (auto i : s.maxNumber(m, n, k)) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    
    {
        
        std::vector<int> m = {};
        std::vector<int> n = {9};
        int k = 1;
        Solution s;
        for (auto i : s.maxNumber(m, n, k)) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    {

        std::vector<int> m = {3,4,6,5};
        std::vector<int> n = {9,1,2,5,8,3};
        int k = 5;
        Solution s;
        for (auto i : s.maxNumber(m, n, k)) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    {
        /**
         nums1 = [3, 4, 6, 5]
         nums2 = [9, 1, 2, 5, 8, 3]
         k = 5
         */
        std::vector<int> m = {3, 4, 6, 5};
        std::vector<int> n = {9, 1, 2, 5, 8, 3};
        int k = 5;
        Solution s;
        for (auto i : s.maxNumber(m, n, k)) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}
}