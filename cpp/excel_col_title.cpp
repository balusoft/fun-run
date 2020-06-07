//
//  excel_col_title.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 1/4/16.
//  Copyright © 2016 FooBar. All rights reserved.
//

#include "excel_col_title.hpp"
#include <sstream>
#include <iostream>

/**
 Given a positive integer, return its corresponding column title
 as appear in an Excel sheet.
 
 For example:
 
 1 -> A
 2 -> B
 3 -> C
 ...
 26 -> Z
 27 -> AA
 28 -> AB
 */

static
std::string getExcelColumn(uint64_t n) {
    std::string strNum;
    const size_t alphaCount = 26;
    //uint64_t n = num;
    while (n > 0) {
        uint64_t m = (n % alphaCount);
        std::ostringstream ostr;
        //char ch = (m == 0) ? 'Z' : 'A' - 1 + m;
        char ch = 'A' - 1 + m;
        if (m == 0) {
            ch = 'Z';
        }
        ostr << ch;
        strNum = ostr.str()+ strNum;
        n /= alphaCount;
        if (m == 0) {
            --n;
        }
    }
    
    return strNum;
}

void excelCol::unitTest() {
    {
        for (int64_t n = 0 ; n < 1000 ; n += 1) {
            //std::cout << n-1 << " excel col is: " << getExcelColumn(n-1) << "\n";
            std::cout << n << " excel col is: " << getExcelColumn(n) << "\n";
            //std::cout << n+1 << " excel col is: " << getExcelColumn(n+1) << "\n";
        }
    }
    {
        for (int64_t n = 26 ; n < 1000 ; n += 26) {
            std::cout << n-1 << " excel col is: " << getExcelColumn(n-1) << "\n";
            std::cout << n << " excel col is: " << getExcelColumn(n) << "\n";
            //std::cout << n+1 << " excel col is: " << getExcelColumn(n+1) << "\n";
        }
    }
}