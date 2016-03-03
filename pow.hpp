//
//  pow.hpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 10/3/15.
//  Copyright © 2015 FooBar. All rights reserved.
//

#ifndef pow_hpp
#define pow_hpp

#include <iostream>
#include <cassert>

namespace pow {

    class Solution {
    private:
        double square(double x)
        {
            return x*x;
        }
    public:
        double myPow1(double x, int n) {
            if (x == 0 && n == 0) {
                assert(0);
            }
            
            if (x == 1.0) {
                return 1.0;
            }
            
            if (n == 0) {
                return 1;
            }
            
            if (n == 1) {
                return x;
            }
            
            if (n == 2) {
                return square(x);
            }
            
            if (n < 0) {
                return 1/myPow1(x, -1*n);
            }
            
            double dtmp1 = myPow1(x, n/2);
            double dtmp2;
            
            if (n%2 == 0) {
                dtmp2 = dtmp1;
            } else {
                dtmp2 = myPow1(x, (n+1)/2);
            }
            
            return dtmp1 * dtmp2;
        }
        
        double myPow(double x, int n)
        {
            if (x == 0 && n == 0) {
                assert(0);
            }
            
            if (x == 1.0) {
                return 1.0;
            }
            
            if (n == 0) {
                return 1;
            }
            
            if (n == 1) {
                return x;
            }
            
            if (n == 2) {
                return square(x);
            }
            return 0;
        }
    };
    
    void unitTest()
    {
        {
            Solution s;
            std::cout << "pow(2, 2) = " << s.myPow(2, 2) << "\n";
        }
        
        {
            Solution s;
            std::cout << "pow(2, 3) = " << s.myPow(2, 3) << "\n";
        }
        
        
        {
            Solution s;
            std::cout << "pow(2, 4) = " << s.myPow(2, 4) << "\n";
        }
        
        
        {
            Solution s;
            std::cout << "pow(2, 5) = " << s.myPow(2, 5) << "\n";
        }
        
        {
            Solution s;
            std::cout << "pow(2, 6) = " << s.myPow(2, 6) << "\n";
        }
        
        {
            Solution s;
            std::cout << "pow(2, -2) = " << s.myPow(2, -2) << "\n";
        }
        
        {
            Solution s;
            std::cout << "pow(2, -3) = " << s.myPow(2, -3) << "\n";
        }
        
        
        {
            Solution s;
            std::cout << "pow(2, -4) = " << s.myPow(2, -4) << "\n";
        }
        
        
        {
            Solution s;
            std::cout << "pow(2, -5) = " << s.myPow(2, -5) << "\n";
        }
        
        {
            Solution s;
            std::cout << "pow(2, -6) = " << s.myPow(2, -6) << "\n";
        }
        
        {
            Solution s;
            std::cout << "pow(1, -2147483648) = " << s.myPow(2, -2147483648) << "\n";
        }
    }
    
}
#endif /* pow_hpp */
