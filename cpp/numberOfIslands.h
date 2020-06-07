//
//  numberOfIslands.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/23/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__numberOfIslands__
#define __CPP_Test9__numberOfIslands__

#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>


namespace islands {
    template<typename T>
    void printBoard(const std::vector<std::vector<T>>& board) {
        for (auto i : board) {
            for (auto j : i) {
                std::cout << std::setw(2) << j << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        
    }

    bool handleSurr(const std::pair<int, int>& c, std::vector<std::vector<char>>& islandMap, std::queue<std::pair<int, int>>& lQ, std::queue<std::pair<int, int>>& wQ, bool early=false){
        int i = c.first;
        int j = c.second;
        
        if (i > 0) {
            if (islandMap[i-1][j] == '1') {
                lQ.push(std::pair<int, int>(i-1, j));
                islandMap[i-1][j] = 'l';
                if (early) {
                    return true;
                }
            } else if(islandMap[i-1][j] == '0') {
                wQ.push(std::pair<int, int>(i-1, j));
                islandMap[i-1][j] = 'w';
            }
        }
        
        if (i < islandMap.size()-1) {
            if (islandMap[i+1][j] == '1') {
                lQ.push(std::pair<int, int>(i+1, j));
                islandMap[i+1][j] = 'l';
                if (early) {
                    return true;
                }
            } else if(islandMap[i+1][j] == '0') {
                wQ.push(std::pair<int, int>(i+1, j));
                islandMap[i+1][j] = 'w';
            }
        }
        
        
        if (j > 0) {
            if (islandMap[i][j-1] == '1') {
                lQ.push(std::pair<int, int>(i, j-1));
                islandMap[i][j-1] = 'l';
                if (early) {
                    return true;
                }
            } else if (islandMap[i][j-1] == '0') {
                wQ.push(std::pair<int, int>(i, j-1));
                islandMap[i][j-1] = 'w';
            }
        }
        
        if (j < islandMap[i].size()-1) {
            if (islandMap[i][j+1] == '1') {
                lQ.push(std::pair<int, int>(i, j+1));
                islandMap[i][j+1] = 'l';
            } else if (islandMap[i][j+1] == '0') {
                wQ.push(std::pair<int, int>(i, j+1));
                islandMap[i][j+1] = 'w';
            }
        }
        printBoard(islandMap);
        return false;
    }
    
    int numIslands(std::vector<std::vector<char>>& islandMap) {
        int ic = 0;
        
        if (islandMap.size() == 0) return 0;
        
        
        std::queue<std::pair<int, int>> lQ;
        std::queue<std::pair<int, int>> wQ;
        
        if (islandMap[0][0] == '0') {
            wQ.push(std::pair<int, int>(0, 0));
            islandMap[0][0] = 'w';
        } else {
            lQ.push(std::pair<int, int>(0, 0));
            islandMap[0][0] = 'l';
        }
        
        while (!lQ.empty() || !wQ.empty()){
            bool foundLand = false;
            while (!lQ.empty()) {
                foundLand = true;
                std::pair<int, int> c = lQ.front();
                lQ.pop();
                handleSurr(c, islandMap, lQ, wQ);
            }
            
            while (lQ.empty() && !wQ.empty()) {
                std::pair<int, int> c = wQ.front();
                if (!handleSurr(c, islandMap, lQ, wQ, true)) {
                    wQ.pop();
                }
            }
            
            if (foundLand) {
                ic++;
            }
        }
        
        for (int i = 0; i < islandMap.size(); i++) {
            for (int j = 0; j < islandMap[i].size(); j++) {
                if (islandMap[i][j] == 'l') {
                    islandMap[i][j] = '1';
                } else if (islandMap[i][j] == 'w') {
                    islandMap[i][j] = '0';
                }
            }
        }
        printBoard(islandMap);
        return ic;
    }
    
    void unitTest()
    {
//        {
//            
//            std::vector<std::string> rawMap =
//{"11111011111111101011","01111111111110111110","10111001101111111111","11110111111111111111","10011111111111111111","10111111011101110111","01111111111101101111","11111111111101111011","11111111110111111111","11111111111111111111","01111111011111111111","11111111111111111111","11111111111111111111","11111011111110111111","10111110111011110111","11111111111101111110","11111111111110111100","11111111111111111111","11111111111111111111","11111111111111111111"};
//            
//            std::vector<std::vector<char>> islandMap(rawMap.size());
//            
//            for (int i = 0; i < rawMap.size(); i++) {
//                islandMap[i] = (std::vector<char>(rawMap[i].begin(), rawMap[i].end()));
//            }
//            
//            std::cout << "Total islands are: " << numIslands(islandMap) << "\n";
//
//            
//        }
        {
            std::vector<std::vector<char>> islandMap =
            {
                {'1', '0', '1', '1', '0', '1', '1'},
//                {'0', '1', '0', '0'},
//                {'1', '0', '1', '0'},
//                {'1', '0', '1', '0'},
            };
            
            printBoard(islandMap);

            
            std::cout << "Total islands are: " << numIslands(islandMap) << "\n";
        }
    }
}
#endif /* defined(__CPP_Test9__numberOfIslands__) */
