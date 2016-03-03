//
//  Counters.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/29/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include <iostream>

#include "Counters.h"

template <typename T>
int Counter<T>::counter=0;

template <typename T>
pthread_mutex_t Counter<T>::m = PTHREAD_MUTEX_INITIALIZER;
