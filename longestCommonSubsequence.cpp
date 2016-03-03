//
//  longestCommonSubsequence.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/1/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include "longestCommonSubsequence.h"

#include <vector>
#include <iostream>

std::string lcs(const std::string &s1, const std::string &s2)
{
    std::string lcs;
    size_t s1Len = s1.length();
    size_t s2Len = s2.length();
    
    if (s1Len == 0 || s2Len == 0) {
        return lcs;
    }
    
    //This is hughe needs to be optimized.
    std::vector<std::vector<std::string>> cache(s1Len+1, std::vector<std::string>(s2Len+1));
    {
        //
        // What we know?
        // lcs("", s) = ""
        // lcs(s, "") = ""
        // lcs("", "") = ""
        // Initialize this to cache first
        //
        
        int i = 0;
        for (; i <= s1Len; ++i ) {
            cache[i][0] = "";
            if (i <= s2Len)
            {
                cache[0][i] = "";
            }
        }
        
        if (i <= s2Len) {
            for (;i < s2Len ; i++) {
                cache[0][i] = "";
            }
        }
    }
    
    for (int i = 1; i <= s1Len; ++i)
    {
        for (int j = 1; j <= s2Len; ++j)
        {
            //i-1,j-1
            std::string i1j1 = cache[i-1][j-1];
            if(s1[i-1] == s2[j-1])
            {
                char c = s1[i-1];
                i1j1 += c;
            };
            std::string i1j = cache[i-1][j];
            std::string ij1 = cache[i][j-1];
            
            auto stCmp = [=](const std::string &st1, const std::string &st2) {
                return (st1.length() < st2.length());
            };
            
            cache[i][j] = std::max({i1j1, i1j, ij1}, stCmp);
            
        }
    }
    
    std::cout << "\n";
    for (auto v : cache) {
        for (auto s : v) {
            std::cout << s << " , ";
        }
        std::cout << "\n";
    }
    return cache[s1Len][s2Len];
}

void unitTestLcs()
{
    {
        std::string st1("a1b2c3d4");
        std::string st2("abd1b2d34");
        std::cout << "LCS("<< st1 << "," << st2 << ") = " << lcs(st1, st2) << "\n\n";
    }
}