//
//  MyStrStr.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/29/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include <string>
#include <vector>
#include <iostream>

#include "MyStrStr.h"

/**
 Example 1:
 
 abcabcdeabcxyab
 000123001230012
 
 Example 2:
 
 abcabcd
 abcd
 */
void kmpPreParseString(const std::string& needle, std::vector<int>& preparsedData)
{
    int pi = 0;
    preparsedData[0] = 0;
    for (int i = 1; i < needle.length(); ++i) {
        if (needle[pi] == needle[i]) {
            preparsedData[i] = pi++;
        } else {
            preparsedData[i] = pi;
            pi = 0;
        }
    }
    return;
}

int kmpSearch(const std::string & haystack, const std::string &needle)
{
    if (needle.empty()) {
        return 0;
    }
    
    std::vector<int> preparse;
    preparse.reserve(needle.length());
    kmpPreParseString(needle, preparse);
    
    auto np = 0;
    auto nl = needle.length();
    for (auto hay=0; hay < haystack.length(); ++hay) {
        if (haystack[hay] == needle[np]) {
            if (np == nl-1) {
                return hay - np;
            }
            
            np++;
        } else {
            if (np != 0) {
                --hay;
            }
            np = preparse[np];
        }
    }
    return -1;
}

// Unit Testing
void printPreparseVector(const std::vector<int>& preparse)
{
    std::cout << "[";
    for (auto itr = preparse.begin(); itr != preparse.end(); ++itr)
    {
        std::cout << *itr << ",";
    }
    std::cout << "]\n";

}

void unitTestKmpPreParseString()
{
    
    {
        std::string needle("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
        std::vector<int> preparse(needle.length());
        //preparse.reserve(needle.length());
        
        kmpPreParseString(needle, preparse);
        
        std::cout << "Needle: " << needle << "\n";
        printPreparseVector(preparse);
        std::cout << "\n";
    }
    {
        std::string needle("abcdefghijklmnopqrstuvwxyz");
        std::vector<int> preparse(needle.length());

        
        kmpPreParseString(needle, preparse);
        
        std::cout << "Needle: " << needle << "\n";
        printPreparseVector(preparse);
        std::cout << "\n";
    }
    
    {
        std::string needle("aaaaaaaaaaaaaa");
        std::vector<int> preparse(needle.length());
        
        kmpPreParseString(needle, preparse);
        
        std::cout << "Needle: " << needle << "\n";
        printPreparseVector(preparse);
        std::cout << "\n";
    }
    
    {
        std::string needle("abcabcdeabcxyab");
        std::vector<int> preparse(needle.length());
        
        kmpPreParseString(needle, preparse);
        
        std::cout << "Needle: " << needle << "\n";
        printPreparseVector(preparse);
        std::cout << "\n";
    }
    
}

void unitTestkmpSearch()
{
    {
        std::string haystack("abcabcyabcabcx");
        std::string needle("abcabcx");
        int pos = kmpSearch(haystack, needle);
        
        std::cout << "Haystack: " << haystack << "\n";
        std::cout << "Needle: " << needle << "\n";
        std::cout << "Pos: " << pos << "\n";
        std::cout << "\n";
    }
    
    {
        std::string haystack("abababababcabcabcabcx");
        std::string needle("abcabcx");
        int pos = kmpSearch(haystack, needle);
        
        std::cout << "Haystack: " << haystack << "\n";
        std::cout << "Needle: " << needle << "\n";
        std::cout << "Pos: " << pos << "\n";
        std::cout << "\n";
    }
    
    
    {
        std::string haystack("mississippppi");
        std::string needle("pi");
        int pos = kmpSearch(haystack, needle);
        
        std::cout << "Haystack: " << haystack << "\n";
        std::cout << "Needle: " << needle << "\n";
        std::cout << "Pos: " << pos << "\n";
        std::cout << "\n";
    }
}

