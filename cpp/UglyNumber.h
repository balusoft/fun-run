//
//  UglyNumber.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/19/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__UglyNumber__
#define __CPP_Test9__UglyNumber__

/**
 An ugly number contains only prime factors of 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
 1. Determine if a number is an ugly number.
 https://leetcode.com/problems/ugly-number/
 2. Follow up: Find the nth ugly number. This is the fun part. wink emoticon
 https://leetcode.com/problems/ugly-number-ii/
 */

bool isUglyNumber(int num);

int nthUglyNumber(int n);

void unitTestUgly();

#endif /* defined(__CPP_Test9__UglyNumber__) */
