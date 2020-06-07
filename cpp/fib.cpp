//
//  fib.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/30/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include "fib.h"

#include <iostream>
#include <vector>

unsigned long nthFib(int n)
{
    unsigned long prev1 = 0;
    unsigned long prev2 = 1;
    
    if (n <= 1) return prev1;
    if (n == 2) return prev2;
    
    unsigned long nthElem = 0;
    
    for (int i = 2; i < n ; ++i )
    {
        nthElem = prev1 + prev2;
        prev1 = prev2;
        prev2 = nthElem;
    }
    
    return nthElem;
}

unsigned long nthFibDP(int n)
{
    std::vector<unsigned long> fib(n);
    fib[0] = 0;
    fib[1] = 1;
    if (n < 1) return 0;
    if (n <= 2) return fib[n-1];
    
    for (int i=2; i < n ; ++i )
    {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    return fib[n-1];
}
// Unit Test //

void unitTestNthFib()
{
    std::cout << nthFib(1) << " "<< nthFib(2) << " "<< nthFib(3) << " "<< nthFib(4) << " "<< nthFib(5) << " "<< nthFib(6) << "\n";
}

void unitTestNthFibDP()
{
    std::cout << nthFibDP(1) << " "<< nthFibDP(2) << " "<< nthFibDP(3) << " "<< nthFibDP(4) << " "<< nthFibDP(5) << " "<< nthFibDP(6) << "\n";
}