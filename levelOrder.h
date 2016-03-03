//
//  levelOrder.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/23/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__levelOrder__
#define __CPP_Test9__levelOrder__

#include <vector>
#include <queue>
#include <iomanip>
#include <iostream>

namespace levelOrder {
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
        
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };
    
    void printVVI(const std::vector<std::vector<int>>& vvi)
    {
        for (auto r : vvi) {
            std::cout << "[ ";
            for (auto c : r) {
                std::cout << std::setw(3) << c;
            }
            std::cout << "]\n";
        }
        
    }
    std::vector<std::vector<int>> levelOrder(TreeNode *t)
    {
        std::vector<std::vector<int>> levels;
        
        if (!t) return levels;
        
        std::queue<TreeNode*> main;
        std::queue<TreeNode*>* qM = &main;
        
        std::queue<TreeNode*> alternate;
        std::queue<TreeNode*>* qA = &alternate;
        
        int curLevel = 0;
        
        levels.push_back(std::vector<int>(1));
        levels[0][0] = t->val;
        qM->push(t);
        
        levels.push_back(std::vector<int>());
        
        while (!qM->empty()) {
            TreeNode *n = qM->front();
            qM->pop();
            
            if (n->left) {
                qA->push(n->left);
                levels[curLevel+1].push_back(n->left->val);
            }
            
            if (n->right) {
                qA->push(n->right);
                levels[curLevel+1].push_back(n->right->val);
            }
            
            //printVVI(levels);
            if (qM->empty()) {
                if (qA->empty()) {
                    levels.erase(levels.begin()+curLevel+1);
                    break;
                }
                
                curLevel++;
                levels.push_back(std::vector<int>());
                
                std::queue<TreeNode*>* tmp = qA;
                qA = qM;
                qM = tmp;
            }
            
        }
        
        return levels;
        
    }
    
    void unitTest()
    {
        {
            TreeNode *r10 = new TreeNode(10);
            
            TreeNode *l5 = new TreeNode(5);
            r10->left = l5;

            TreeNode *r15 = new TreeNode(15);
            r10->right = r15;
            
            TreeNode *l2 = new TreeNode(2);
            l5->left = l2;
            
            
            TreeNode *l1 = new TreeNode(1);
            l2->left = l1;
            
            
            TreeNode *r3 = new TreeNode(3);
            l2->right = r3;
            
            
            std::cout << "Level Order: \n";
            printVVI(levelOrder(r10));
            
        }
    }
}

#endif /* defined(__CPP_Test9__levelOrder__) */
