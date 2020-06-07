//
//  NonToupleElement.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/30/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include "NonToupleElement.h"
#include <iostream>

long findNonToupleElement(const std::vector<long> & nums)
{
    long nt = 0;
    bool first = true;
    for (auto num : nums)
    {
        if (!first){
            nt = nt ^ num;
        } else {
            first = false;
            nt = num;
        }
        
    }
    return nt;
}

// UT NonTouple //
void printVector(const std::vector<long> &nums)
{
    std::cout << "[" ;
    for (auto i : nums)
    {
        std::cout << i << ",";
    }
    std::cout << "]\n" ;
}
void unitTestfindNonToupleElement()
{
    {
        std::vector<long> nums = {1,1,2,2,3,4,4,5,6,6,5};
        printVector(nums);
        std::cout << "nonTouple element: " << findNonToupleElement(nums) << "\n";
        std::cout << "\n";
        
    }
}