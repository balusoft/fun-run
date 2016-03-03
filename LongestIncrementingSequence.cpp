//
//  LongestIncrementingSequence.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/2/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include "LongestIncrementingSequence.h"

#include <set>
#include <iostream>

void printv(std::vector<int> &v) {
    for (int i : v ) {
        std:: cout << i << " ";
    }
    std:: cout << "\n";
}


void lis(const std::vector<int> & sequence, std::vector<int> & subSeq)
{
    if (sequence.empty()) {
        return;
    }
    
    if (sequence.size() == 1) {
        subSeq.push_back(sequence[0]);
        return;
    }
    
    std::vector<int> length(sequence.size());
    std::vector<std::set<int>> prev(sequence.size());
    
    auto curMaxLength = 0;
    auto curMaxIndex = -1;
    
    for (auto i = 0; i < sequence.size(); ++i) {
        if (0 == i) {
            length[0] = 1;
            prev[0].insert(-1);
            curMaxLength = 1;
            curMaxLength = 0;
        } else {
            auto increasedSubset = false;
            length[i] = 1;
            for (auto j = i-1 ; j >= (curMaxLength <= 2 ? 0 : curMaxLength - 2) ; --j) {
                if (sequence[i] > sequence[j]) {
                    if (length[i] <= length[j]){
                        length[i] = length[j] + 1;
                        prev[i].clear();
                        prev[i].insert(j);
                        if (length[i] >= curMaxLength) {
                            curMaxLength = length[i];
                            curMaxIndex = i;
                        }
                    } else if (length[i] - 1 == length[j]) {
                        prev[i].insert(j);
                    }
                    increasedSubset = true;
                }
            }
            
            if (prev[i].empty()) {
                prev[i].insert(-1);
            }
        }
        
    }
    
    // fill subset
    
    auto idx = curMaxIndex;
        std::cout << "idx = ";
    std::vector<int> tmp;
    tmp.reserve(curMaxLength);
    do {
        std::cout << idx << " ,, " ;
        tmp.push_back(idx);
        idx = *prev[idx].begin(); // Ignoring all others for now
    } while (idx != -1);
    std::cout << "\n" ;

    printv(tmp);
    
    for (auto it = tmp.rbegin(); it != tmp.rend(); ++it)
    {
        subSeq.push_back(*it);
    }
    
    std::cout << "curMaxLength = "  << curMaxLength << "\n" ;
    std::cout << "curMaxIndex = "   << curMaxIndex  << "\n" ;
    std::cout << "length array = [ " ;
    for (auto l : length) {
        std::cout << l << " ";
    }
    std::cout << "]\n";
    std::cout << "prev array list = [ " ;
    for (auto l : prev) {
        std::cout <<  "[ ";
        for (auto i : l) {
            std::cout << i << " ";
        }
        std::cout <<  "] ";
    }
    std::cout << "]\n";
}

void unitTestLis()
{
    {
        std::vector<int> subset;
        subset.reserve(10);
        std::vector<int> set({20, 9, 21, 10, 22, 11});
        printv(set);
        lis(set, subset );
        printv(subset);
    }
}
