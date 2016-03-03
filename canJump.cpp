//
//  canJump.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 1/4/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include "canJump.hpp"
#include <vector>
#include <iostream>

static
bool canJump(std::vector<int>& nums) {
    if (nums.size() == 1) {
        return true;
    }
    size_t maxReach = 0;
    for (size_t s = 0; s < nums.size() && maxReach >= s; ++s) {
        if (maxReach == 0) {
            maxReach = nums[s] + s;
        } else {
            maxReach = std::max(nums[s] + s, maxReach);
        }
        
        if (maxReach == 0) {
            return false;
        } else if (maxReach >= nums.size() - 1) {
            return true;
        }
    }
    
    return false;
}

void jump::unitTest() {
    {
    const int arr[] = {2,3,1,1,4};
    std::vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]));
        std::cout << std::boolalpha << "canJump: " << canJump(vec) << "\n";
    }
    {
        const int arr[] = {3,2,1,0,4};
        std::vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]));
        std::cout << std::boolalpha << "canJump: " << canJump(vec) << "\n";
    }
    {
        const int arr[] = {1,1,2,2,0,1,1};
        std::vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]));
        std::cout << std::boolalpha << "canJump: " << canJump(vec) << "\n";
    }
}