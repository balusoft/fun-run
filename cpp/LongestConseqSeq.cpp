//
//  LongestConseqSeq.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/5/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include "LongestConseqSeq.h"
#include <unordered_map>
#include <iostream>

struct Cnt{
    int pred;
    int succ;
};

int longestConsecutive(const std::vector<int>& nums)
{
    if (nums.empty()) {
        return 0;
    }
    
    if (nums.size() == 1) {
        return 1;
    }
    
    std::unordered_map<int, Cnt> cache;
    
    for (auto i : nums) {
        if (cache.find(i) != cache.end()) {
            continue;
        }
        
        auto predIdxSet = false;
        auto succIdxSet = false;
        
        auto predIdx = -1;
        auto succIdx = -1;
        if (cache.find(i-1) != cache.end()){
            cache[i].pred = cache[i-1].pred + 1;
            //update successor of i-cache[i].pred successor count
            predIdx =  i-cache[i].pred;
            predIdxSet = true;
        } else {
            cache[i].pred = 0;
        }

        if (cache.find(i+1) != cache.end()) {
            cache[i].succ = cache[i+1].succ + 1;
            //update predecessor of i+cache[i].succ count
            succIdx = i + cache[i].succ;
            succIdxSet = true;
        } else {
            cache[i].succ = 0;
        }
    
        if (predIdxSet) {
            cache[predIdx].succ = cache[i].succ + cache[i].pred;
        }
        
        if (succIdxSet) {
            cache[succIdx].pred = cache[i].succ + cache[i].pred;
        }
//
//        std::cout << "i:["<< i << "]:(" <<  cache[i].pred << "," << cache[i].succ << ") ";
//        if(predIdxSet) {
//            std::cout << "p:["<< predIdx << "]:(" <<  cache[predIdx].pred << "," << cache[predIdx].succ << ") ";
//        }
//        if(succIdxSet) {
//            std::cout << "s:["<< succIdx << "]:(" <<  cache[succIdx].pred << "," << cache[succIdx].succ << ") ";
//        }
//        std::cout << "\n";

    }
    
    
    auto m = std::max_element(cache.begin(), cache.end(),
                              [](const std::pair<int,Cnt> &first, const std::pair<int, Cnt> &second) {
                                  return (first.second.pred + first.second.succ) < (second.second.pred + second.second.succ); });
    
    return m->second.succ + m->second.pred + 1;
}

void unitTestLongestConsecutive()
{
    {
        std::cout << "Length of consequetive: " << longestConsecutive({0, -1}) << "\n";
    }
//
//    {
//        std::cout << "Length of consequetive: " << longestConsecutive({-3,2,8,5,1,7,-8,2,-8,-4,-1,6,-6,9,6,0,-7,4,5,-4,8,2,0,-2,-6,9,-4,-1}) << "\n";
//    }

//    {
//        std::cout << "Length of consequetive: " << longestConsecutive({1,3,5,2,4}) << "\n";
//    }
//    {
//        std::cout << "Length of consequetive: " << longestConsecutive({1,2,0,1}) << "\n";
//    }
//    {
//        std::cout << "Length of consequetive: " << longestConsecutive({100, 4, 200, 1, 3, 2}) << "\n";
//    }
}