//
//  binomialCoefficient.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/30/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include "binomialCoefficient.h"

#include <cassert>
#include <iostream>


/**
 Return the number of possiblities to choose "k" from "n" : Old school n C k or C(n,k)
 
 DP formula:
 
 C(0, 0) = 1;
 C(1, 0) = 1;
 C(x, 0) = 1;
 
 C(n, k) = C(n-1, k-1) + C(n-1, k) => See following pascal tree
 
     1
    1 1
   1 2 1
  1 3 3 1
 1 4 6 4 1
 
 The same table left justified:
 
 1
 1 1
 1 2 1
 1 3 3 1
 1 4 6 4 1
 
 */
long pascalTree(long n, long k)
{
    if (k > n)
    {
        assert (0 == "Invalid argumens");
    }
    
    /* C(x, 0) == 1 and C(x, x) == 1*/
    if (k == 0 || n == k)
    {
        return 1;
    }
    
    /* C(n, 1) = C(n, n-1) = n */
    if (k == n-1 || k == 1) {
        return n;
    }
    
    /* Init C(i, 0) = 1 i = {0 ... n} */
    /* Init C(i, i) = 1 i = {0 ... k} */
    
    long pascal[n+1][k+1];
    
    for (long i = 0; i <= n; ++i)
    {
        pascal[i][0] = 1;
        
        if (i <= k) {
            pascal [i][i] = 1;
        }
    }
    
    /* Already covered 0 and n == k cases */
    for (long i = 1; i <= n; ++i)
    {
        for (long j = 1; j <= k; ++j)
        {
            if (i != j) {
                pascal [i][j] = pascal[i-1][j-1] + pascal[i-1][j];
            }
        }
        
    }
    
    return pascal[n][k];
}

void unitTestPascalTree()
{
    
    {
        std::cout << "C(0,0) " << pascalTree(0, 0) << "\n\n";
    }
    
    
    {
        std::cout << "C(1,0) " << pascalTree(1, 0) << "\n\n";
    }
    
    {
        std::cout << "C(999,0) " << pascalTree(999, 0) << "\n\n";
    }

    
    {
        std::cout << "C(999,998) " << pascalTree(999, 998) << "\n\n";
    }
    
    
    {
        std::cout << "C(5,3) " << pascalTree(5, 3) << "\n\n";
    }
    
    
    {
        std::cout << "C(10,5) " << pascalTree(10, 5) << "\n\n";
    }
}
