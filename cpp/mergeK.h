//
//  mergeK.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/23/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__mergeK__
#define __CPP_Test9__mergeK__

#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>

namespace mergeK {
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
        bool operator<(const ListNode* a)
        {
            return this->val < a->val;
        }
    };
    
    
    struct Cmp : public std::binary_function<ListNode *, ListNode *, bool>
    {
        bool operator()(const ListNode* n1, const ListNode* n2) const
        {
            return n1->val > n2->val;
        }
    };
    
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        
        ListNode* rt = nullptr;
        ListNode* cur = nullptr;
        
        std::priority_queue<ListNode*, std::vector<ListNode*>, Cmp> pq;
        
        for (int i = 0; i < lists.size(); ++i) {
            if (lists[i]) {
                pq.push(lists[i]);
            }
        }
        
        while (!pq.empty()) {
            ListNode* t = pq.top();
            
            if (!rt) {
                rt = t;
                cur = rt;
            } else {
                cur->next = t;
                cur = cur->next;
            }
            
            pq.pop();
            
            if (cur->next) {
                pq.push(cur->next);
            }
        }
        
        return rt;
    }
    
    void printKSL(const ListNode *l)
    {
        std::cout << "KSL: ";
        while (l) {
            std::cout << std::setw(5) << l->val << " ";
            l = l->next;
        }
        std::cout << "\n\n";
    }
    void unitTest()
    {
        {
            ListNode *n1 = new ListNode(10);
            ListNode *n2 = new ListNode(20); n1->next = n2;
            ListNode *n3 = new ListNode(30); n2->next = n3;
            ListNode *n4 = new ListNode(40); n3->next = n4;
            
            ListNode *p1 = new ListNode(1);
            ListNode *p2 = new ListNode(25); p1->next = p2;
            
            ListNode *l1 = new ListNode(24);
            ListNode *l2 = new ListNode(1000); l1->next = l2;
            
            std::vector<ListNode*> ksl = {n1, p1, l1};
            
            printKSL(mergeKLists(ksl));
        }
    }
}

#endif /* defined(__CPP_Test9__mergeK__) */
