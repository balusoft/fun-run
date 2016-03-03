//
//  MyStrStr.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/29/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__MyStrStr__
#define __CPP_Test9__MyStrStr__

#include <vector>

int kmpSearch(const std::string & haystack, const std::string &needle);

void kmpPreParseString(const std::string& needle, std::vector<int>& preparsedData);

// UNIT TEST //

void unitTestKmpPreParseString();
void unitTestkmpSearch();

#endif /* defined(__CPP_Test9__MyStrStr__) */
