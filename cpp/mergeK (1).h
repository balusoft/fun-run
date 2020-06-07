//
//  mergeK.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/23/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__mergeK__
#define __CPP_Test9__mergeK__

#include <vector>
#include <cassert>
#include <climits>
#include <iostream>

namespace mergeK {
    struct Heap {
        std::vector<int> hv;
        
        Heap(int capacity)
        : hv()
        {
            hv.reserve(capacity);
        }
        
        // swap
        void swap (int *p1, int *p2)
        {
            int tmp = *p1;
            *p1 = *p2;
            *p2 = tmp;
        }
        //Tree navigation
        
        int parent(int i) { return (i-1)/2; }
        int left(int i) { return 2*i + 1; }
        int right(int i) { return 2*i + 2; }
        
        // Heap operations
        
        int hs() { return hv.size(); }
        bool empty() { return hv.empty(); }
        int min()
        {
            assert(hs() > 0);
            return hv[0];
        }
        
        void insert(int i)
        {
            hv.push_back(i);
            
            int curIdx = hs() - 1;
            
            while (curIdx != 0 && hv[curIdx] < hv[parent(curIdx)]) {
                swap(&hv[curIdx], &hv[parent(curIdx)]);
                curIdx = parent(curIdx);
            }
        }
        
        void decreaseKey(int i, int newValue)
        {
            assert(i < hs());
            assert(hv[i] >= newValue);
            
            hv[i] = newValue;
            
            int curIdx = i;
            while (curIdx != 0 && hv[curIdx] < hv[parent(curIdx)]) {
                swap(&hv[curIdx], &hv[parent(curIdx)]);
                curIdx = parent(curIdx);
            }
        }
        
        void reheapify(int idx)
        {            
            while (idx < hs())
            {
                int sm = idx;
                int l = left(idx);
                int r = right(idx);
                
                if (l < hs() && hv[sm] > hv[l]) {
                    sm = l;
                }
                
                if (r < hs() && hv[sm] > hv[r]) {
                    sm = r;
                }
                
                if (sm != idx) {
                    swap(&hv[sm], &hv[idx]);
                    idx = sm;
                } else {
                    break;
                }
            }
        }
        
        void removeMin()
        {
            assert(hs() > 0);
            
            hv[0] = *hv.rbegin();
            hv.pop_back();
            
            reheapify(0);
        }
        
    };
    
    void unitTest()
    {
        {
            Heap h(5);
            
            h.insert(99);
            h.insert(97);
            h.insert(98);
            h.insert(2);
            h.insert(10);
            
            while (!h.empty()) {
                std::cout << "Heap Min: " << h.min() << "\n\n";
                h.removeMin();
            }
        }
    }
}
#endif /* defined(__CPP_Test9__mergeK__) */
