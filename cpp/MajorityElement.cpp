//
//  MajorityElement.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/29/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include <iostream>
#include "MajorityElement.h"

int majorityElement(std::vector<int>& nums)
{
    size_t halfLength = nums.size()/2;
    size_t counter = 0;
    bool first = true;
    // current majority
    int major = 0;
    
    // current count
    int mCount = 0;
    
    for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
        if (!first) {
            if (major == *itr) {
                ++mCount;
            } else {
                --mCount;
                if (mCount == 0) {
                    major = *itr;
                    mCount = 1;
                }
            }
            if (mCount > halfLength) {
                return major;
            }
            
        } else {
            first = false;
            major = *itr;
            mCount = 1;
        }
        //std::cout << "(" << mCount << ","  << major << "," << *itr <<  ")\n" ;
    }
    //std::cout << "\n";
    
    return major;
}

// UT //

void printVector(const std::vector<int> & v)
{
    std::cout << "[";
    for (auto itr = v.begin(); itr!=v.end(); ++itr) {
        std::cout << *itr <<",";
    }
    std::cout << "]\n";
}

void unitTestMajorityElement()
{
    {
        std::vector<int> nums = { 1, 2, 3, 3, 4, 1, 1, 1};
        printVector(nums);
        std::cout << "Majority Element: " << majorityElement(nums) << "\n";
    }
    
    {
        std::vector<int> nums = { 1, 1, 2, 2, 1, 1, 2, 1, 3};
        printVector(nums);
        std::cout << "Majority Element: " << majorityElement(nums) << "\n";
    }
    
}
