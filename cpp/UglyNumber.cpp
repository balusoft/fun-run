//
//  UglyNumber.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/19/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include "UglyNumber.h"

#include <vector>
#include <iostream>

/**
 An ugly number contains only prime factors of 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
 1. Determine if a number is an ugly number.
 https://leetcode.com/problems/ugly-number/
 2. Follow up: Find the nth ugly number. This is the fun part. wink emoticon
 https://leetcode.com/problems/ugly-number-ii/
 */
bool isUglyNumber(int num)
{
    if (num == 1) { return true; }
    if (num == 0) { return false; }

    std::vector<int> factors = {2, 3, 5};
    
    int fi = 0;
    while(num > 1) {
        if (num%factors[fi] == 0) {
            num = num/factors[fi];
        } else {
            ++fi;

            if (fi == factors.size()) {
                return false;
            }
        }
    }
    
    return num == 1;
}

int nthUglyNumber(int n)
{
    if (n<=0) {
        return -1;
    }
    
    if (n==0) {
        return 1;
    }
    
    std::vector<int> c(n, 0);
    int p2 = 0;
    int p3 = 0;
    int p5 = 0;
    
    c[0] = 1;
    
    for (int i = 1; i < n ; i++) {
        c[i] = std::min({c[p2]*2, c[p3]*3, c[p5]*5});
        if (c[p2]*2 == c[i]) { ++p2; }
        if (c[p3]*3 == c[i]) { ++p3; }
        if (c[p5]*5 == c[i]) { ++p5; }
    }
    
    return c[n-1];
}

void unitTestUgly()
{
    {
        auto nums = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
        
        for (auto n : nums) {
            //std::cout << std::boolalpha << "is Number '" << n << "' ugly? " << isUglyNumber(n) << "\n";
            std::cout << n << "th ugly number: " << nthUglyNumber(n) << "\n";
        }
    }
}