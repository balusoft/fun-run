//
//  Date.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/28/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__Date__
#define __CPP_Test9__Date__

//#include <boost/operators.hpp>

namespace DateLib
{
    class Date //: boost::operators<Date>
    {
    public:
        /**
         Creates to days date
         */
        explicit Date ();
        Date (int day, int week, int month);
        
        int day() const;
        int week() const;
        int month() const;
        
        Date & operator+=(const Date &rhs);
        Date & operator-=(const Date &rhs);
        Date & operator>(const Date &rhs);
        Date & operator<(const Date &rhs);
        Date & operator>=(const Date &rhs);
        Date & operator<=(const Date &rhs);
        
    private:
        int day_;
        int week_;
        int month_;
    };
    
    class DateUtils
    {
    public:
        bool isItNewYear(const Date & date);
        bool isLeapYear(const Date & date);
        
    };
}
#endif /* defined(__CPP_Test9__Date__) */
