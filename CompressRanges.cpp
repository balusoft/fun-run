//
//  CompressRanges.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 7/27/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include <cassert>
#include "CompressRanges.h"
#include <iostream>

//Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
//
//You may assume that the intervals were initially sorted according to their start times.
//
//Example 1:
//Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
//
//Example 2:
//Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
//
//This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
//
IntervalCmpVal compareTwoIntervals(const Interval &intVal1, int val)
{
    if (val < intVal1.start) {
        return LESS;
    } else if (val > intVal1.end) {
        return GREATER;
    } else {
        return WITHIN;
    }
}

int find(std::vector<Interval>& intervals, int start, int low, int high, IntervalCmpVal &res)
{
    int mid = -1;
    //figuring out start position
    while (low <= high) {
        //std::cout << "Debug1: [" << low << "," << high << "]\n";
        mid = (low + high)/2;
        //std::cout << "Debug2: [" << low << "," << high << "," << mid << "]\n";
        
        res =  compareTwoIntervals(intervals[mid], start);
        
        if (LESS == res) {
            low = low;
            high = mid -1;
        } else if (WITHIN == res) {
            // Hooray we found it
            break;
        } else {
            low = mid + 1; // This does not change
            high = high;
        }
        
    }
    return mid;
    
}
std::vector<Interval> insert(std::vector<Interval>& intervals, Interval newInterval)
{
    if (intervals.empty()) {
        intervals.push_back(newInterval);
        return intervals;
    }
    
    int low = 0;
    int high = intervals.size() - 1;
    
    IntervalCmpVal startRes;
    int nStart = find(intervals, newInterval.start, low, high, startRes);
    
    
    low = nStart;
    high = intervals.size() - 1;
    
    IntervalCmpVal endRes;
    int nEnd = find(intervals, newInterval.end, low, high, endRes);
    
    std::cout << "Debug1: [" << nStart << "," << nEnd << "]\n";
    int distance = nEnd - nStart;
    if (distance > 1) {
        switch (startRes) {
            case LESS:
                intervals[nStart].start = newInterval.start;
                break;
            case WITHIN:
                break;
            case GREATER:
                nStart = nStart + 1;
                intervals[nStart].start = newInterval.start;
                break;
                
        }
        
        switch (endRes) {
            case LESS:
                intervals[nStart].end = newInterval.end;
                break;
                
            case WITHIN:
                intervals[nStart].end = intervals[nEnd].end;
                nEnd = nEnd + 1;
                break;
            case GREATER:
                intervals[nStart].end = newInterval.end;
                nEnd = nEnd + 1;
                break;
        }
    } else if (distance == 1) {
        switch (startRes) {
            case LESS:
                intervals[nStart].start = newInterval.start;
                break;
            case WITHIN:
                break;
            case GREATER:
                if (endRes != LESS) {
                    nStart = nStart + 1;
                    intervals[nStart].start = newInterval.start;
                }
                break;
                
        }
        
        switch (endRes) {
            case LESS:
                if (startRes == GREATER) {
                    intervals.insert(intervals.begin() + nStart + 1, newInterval);
                    return intervals;
                }
                intervals[nStart].end = newInterval.end;
                break;
            case WITHIN:
                intervals[nStart].end = intervals[nEnd].end;
                nEnd = nEnd + 1;
                break;
            case GREATER:
                intervals[nStart].end = newInterval.end;
                nEnd = nEnd + 1;
                break;
        }
        
        
    } else if (distance == 0) {
        switch (startRes) {
            case LESS:
                if (endRes == LESS) {
                    intervals.insert(intervals.begin() + nStart, newInterval);
                    return intervals;
                } else if (endRes == GREATER) {
                    intervals[nStart].start = newInterval.start;
                    intervals[nStart].end = newInterval.end;
                } else {
                    intervals[nStart].start = newInterval.start;
                }
                
                break;
            case WITHIN:
                if (endRes == LESS) {
                    assert( 0 == "Cannot happer");
                } else if (endRes == GREATER) {
                    intervals[nStart].end = newInterval.end;
                }
                
                break;
            case GREATER:
                if (endRes == GREATER) {
                    intervals.insert(intervals.begin() + nStart + 1, newInterval);
                }
                break;
                
        }
    }
    
    
    
    if (nStart != nEnd) {
        intervals.erase(intervals.begin()+nStart+1, intervals.begin()+nEnd);
    }
    
    return intervals;
}

void printv(const Interval &i) {
    std::cout << "[" << i.start << "," << i.end << "]";
}
void printIntervals(const std::vector<Interval> &intervals) {
    std::for_each(intervals.begin(), intervals.end(), printv);
    std::cout << "\n";
}

void unitTest()
{
    

/// UNIT TESTING ///

//[[0,4],[7,12]], [0,5]

//[[0,0],[2,4],[9,9]], [0,7]

//[[1,5]], [0,6]

//[[2,5],[6,7],[8,9]], [0,1]

// [[1,5],[6,8]], [0,9]

//[[2,4],[5,7],[8,10],[11,13]], [3,8]

// [[1,5],[6,8]], [5,6]

// [[0,5],[9,12]], [7,16]

// [[0,0],[2,4],[9,9]], [0,7]

#if 0
{
    std::vector<Interval> intervals;
    
    // [[0,10],[14,14],[15,20]], [11,11]
    
    intervals.push_back(Interval(0,10));
    intervals.push_back(Interval(14,14));
    intervals.push_back(Interval(15,20));
    //intervals.push_back(Interval(11,13));
    
    //intervals.push_back(Interval(8,9));
    printIntervals(intervals);
    
    Interval n(11, 11);
    printv(n);
    std::cout << "\n";
    
    printIntervals(insert(intervals, n));
    std::cout << "\n";
    
    }
#endif
    {
        std::vector<Interval> intervals;
        
        //[[2,7],[8,8],[10,10],[12,13],[16,19]], [9,17]
        intervals.push_back(Interval(2,7));
        intervals.push_back(Interval(8,8));
        intervals.push_back(Interval(10,10));
        intervals.push_back(Interval(12,13));
        intervals.push_back(Interval(16,19));
        
        //intervals.push_back(Interval(8,9));
        printIntervals(intervals);
        
        
        IntervalCmpVal res;
        std::cout << "Res find: " << find(intervals, 9, 0, intervals.size()-1, res) << "\n";
        Interval n(9, 17);
        printv(n);
        std::cout << "\n";
        
        printIntervals(insert(intervals, n));
        std::cout << "\n";
        
    }
    
    {
        std::vector<Interval> intervals;
        
        //[[1,5],[6,8]], [0,9]
        intervals.push_back(Interval(1,5));
        intervals.push_back(Interval(6,8));
        //intervals.push_back(Interval(10,10));
        //intervals.push_back(Interval(12,13));
        //intervals.push_back(Interval(16,19));
        
        //intervals.push_back(Interval(8,9));
        printIntervals(intervals);
        
        //
        //        IntervalCmpVal res;
        //        std::cout << "Res find: " << find(intervals, 9, 0, intervals.size()-1, res) << "\n";
        Interval n(0, 9);
        printv(n);
        std::cout << "\n";
        
        printIntervals(insert(intervals, n));
        std::cout << "\n";
        
    }
    
    
    {
        std::vector<Interval> intervals;
        
        //[[1,5],[6,8]], [5,6]
        intervals.push_back(Interval(1,5));
        intervals.push_back(Interval(6,8));
        //intervals.push_back(Interval(10,10));
        //intervals.push_back(Interval(12,13));
        //intervals.push_back(Interval(16,19));
        
        //intervals.push_back(Interval(8,9));
        printIntervals(intervals);
        
        //
        //        IntervalCmpVal res;
        //        std::cout << "Res find: " << find(intervals, 9, 0, intervals.size()-1, res) << "\n";
        Interval n(5, 6);
        printv(n);
        std::cout << "\n";
        
        printIntervals(insert(intervals, n));
        std::cout << "\n";
        
    }
    
    {
        std::vector<Interval> intervals;
        
        //[[2,5],[6,7],[8,9]], [0,10]
        intervals.push_back(Interval(2,5));
        intervals.push_back(Interval(6,7));
        intervals.push_back(Interval(8,9));
        //intervals.push_back(Interval(10,10));
        //intervals.push_back(Interval(12,13));
        //intervals.push_back(Interval(16,19));
        
        //intervals.push_back(Interval(8,9));
        printIntervals(intervals);
        
        //
        //        IntervalCmpVal res;
        //        std::cout << "Res find: " << find(intervals, 9, 0, intervals.size()-1, res) << "\n";
        Interval n(0, 10);
        printv(n);
        std::cout << "\n";
        
        printIntervals(insert(intervals, n));
        std::cout << "\n";
        
    }
    }
