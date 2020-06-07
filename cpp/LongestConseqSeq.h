//
//  LongestConseqSeq.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/5/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__LongestConseqSeq__
#define __CPP_Test9__LongestConseqSeq__

#include <vector>

/*
 Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 
 For example,
 Given [100, 4, 200, 1, 3, 2],
 The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
 
 Your algorithm should run in O(n) complexity.
 */

int longestConsecutive(std::vector<int>& nums);

void unitTestLongestConsecutive();

#endif /* defined(__CPP_Test9__LongestConseqSeq__) */
