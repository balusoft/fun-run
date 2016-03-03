//
//  Counters.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/29/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__Counters__
#define __CPP_Test9__Counters__

#include <pthread.h>

class Foo
{
public:
    Foo()
    {
        std::cout << "In Foo Ctr\n";
    }
};


class Monitor
{
private:
    pthread_mutex_t &_m;
public:
    Monitor (pthread_mutex_t &m) : _m(m)
    {
        pthread_mutex_lock(&_m);
    }
    
    ~Monitor ()
    {
        pthread_mutex_unlock(&_m);
    }
};

template <typename T>
class Counter
{
private:
    static int counter;
    static pthread_mutex_t m;
public:
    Counter()
    {
        
        Monitor mntr(Counter::m);
        counter++;
    }
    
    Counter(Counter const & cntr){
        Monitor mntr(Counter::m);
        counter++;
    }
    
    static int getCounter()
    {
        Monitor mntr(Counter::m);
        return counter;
    }
    
    ~Counter()
    {
        Monitor mntr(Counter::m);
        counter--;
    }
};


//    Counter<int> c1, c2, c3;
//    std::cout << "get_count = "<< Counter<int>::getCounter()<< "\n";
//
//    {
//        Counter<int> c11, c12, c13;
//        Counter<double> d1, d2, d3;
//        std::cout << "get_count = "<< Counter<double>::getCounter()<< "\n";
//        std::cout << "get_coubbbnt = "<< Counter<int>::getCounter()<< "\n";
//
//    }
//    std::cout << "get_count = "<< Counter<int>::getCounter()<< "\n";
//
//    return 0;

#endif /* defined(__CPP_Test9__Counters__) */
