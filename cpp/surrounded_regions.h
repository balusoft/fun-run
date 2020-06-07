//
//  surrounded_regions.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/22/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__surrounded_regions__
#define __CPP_Test9__surrounded_regions__

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <iomanip>

namespace surrounded_regions {
    
    struct UnionFind
    {
        UnionFind(int totalSize)
            : _totalSize(totalSize+1), _parents(_totalSize), _sizes(_totalSize, 1)
        {
            for (int i = 1; i < _totalSize; ++i) {
                _parents[i] = i;
            }
        }
        
        int find (int x) const
        {
            while (_parents[x] != x)
            {
                x = _parents[x];
            }
            
            return x;
        }
        
        int union1(int x, int y)
        {
            int px = _parents[x];
            int py = _parents[y];
            
            if (_sizes[px] > _sizes[py]) {
                _parents[py] = px;
                _sizes[px] += _sizes[py];
                return px;
            } else {
                _parents[px] = py;
                _sizes[py] += _sizes[px];
                return py;
            }
        }

        int _totalSize;
        std::vector<int> _parents;
        std::vector<int> _sizes;
    };
    
    template<typename T>
    void printBoard(const std::vector<std::vector<T>> board) {
        for (auto i : board) {
            for (auto j : i) {
                std::cout << std::setw(2) << j << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";

    }
    
    void printFlip(UnionFind& uf, std::map<int, bool>& flip) {
        for (int i = 1; i <= flip.size(); ++i) {
            std::cout << std::boolalpha << "K(" << i << "," << std::setw(5) << flip[uf.find(i)] << ")\n";
        }
    }
    bool getSurroundedORegions(const std::vector<std::vector<char>>& board,
                               std::vector<std::vector<int>>& regions,
                               std::set<int>& sregions,
                               std::map<int, bool>& flip,
                               int i, int j, bool cross)
    {
        //printBoard(board);
//        std::cout << "Surr(" << i << "," << j << "): ";
        bool canFlip = true;
        if (i > 0) {
            if (j > 0) {
                if (cross && board[i-1][j-1] == 'O') {
                    sregions.insert(regions[i-1][j-1]);
                    canFlip &= flip[regions[i-1][j-1]];
                }
            }
        }
        
        if (j > 0) {
            if (board[i][j-1] == 'O') {

                sregions.insert(regions[i][j-1]);
                canFlip &= flip[regions[i][j-1]];

            }
        }

        if (i > 0) {
            if (board[i-1][j] == 'O') {
                sregions.insert(regions[i-1][j]);
                canFlip &= flip[regions[i-1][j]];

            }
            
            if (j < regions[i].size() - 1) {
                if (cross && board[i-1][j+1] == 'O') {
                    sregions.insert(regions[i-1][j+1]);
                    canFlip &= flip[regions[i-1][j+1]];
                }
            }
        }

//        std:: cout << "sregions: ";
//        for (auto i : sregions) {
//            std:: cout << i << " ";
//        }
//        
//        std:: cout << "\n";

        return canFlip; //RVO
    }
    
    void solve(std::vector<std::vector<char>>& board) {
        
        if (board.size() < 3 || board[0].size() < 3) {
            return;
        }
        std::vector<std::vector<int>> region(board.size(), std::vector<int>(board.size(), 0));
        std::map<int, bool> flip;
        UnionFind uf(board.size() * board[0].size()/2);
        
        // Assuming m x n board
        int rowMax = board.size();
        int curRegionCount = 1;
        
        for (int i = 0; i < rowMax; i++) {
            int colMax = board[i].size();
            for (int j = 0; j < colMax; j++) {
                //std::cout << "processing :" << board[i][j] << "\n";
                if (board[i][j] == 'O') {
                    std::set<int> sregions;

                    bool sorCanFlip = getSurroundedORegions(board, region, sregions, flip, i, j,false);
                    bool canFlip = (i < rowMax-1)
                        && (j < colMax -1) && (i > 0) && (j > 0)
                        && sorCanFlip;
                    
                    if (sregions.size() == 0) {
                        //First O
                        region[i][j] = curRegionCount++;
//                        parents[region[i][j]] = region[i][j];
                        flip[uf.find(region[i][j])] = canFlip;
                    } else if (sregions.size() == 1) {
                        //Found surronded by same regions
                        region[i][j] = *sregions.begin();
                        
                        if (!canFlip) {
                            flip[uf.find(region[i][j])] = canFlip;
                        }
                        // Parent is already set
                    } else {
                        //Found more than one regions
                        int tmpReg = *sregions.begin();
                        
                        // Set parents for all other regions
                        std::set<int>::iterator it = sregions.begin();
                        ++it;
                        for (; it != sregions.end(); ++it)
                        {
                            tmpReg = uf.union1(tmpReg, *it);
                        }

                        if (!canFlip) {
                            flip[tmpReg] = canFlip;
                        }
                        
                        region[i][j] = tmpReg;
                    }
                }
            }
        }
        printBoard(region);
        printFlip(uf, flip);

        for (int i = 0; i < rowMax; i++) {
            int colMax = board[i].size();
            for (int j = 0; j < colMax; j++) {
                if (board[i][j] == 'O' && flip[uf.find(region[i][j])]) {
                    board[i][j] = 'X';
                }
            }
        }
    }
    
    void unitTest()
    {
//        {
//            std::vector<std::vector<char>> board =
//            {   { 'X', 'X', 'X', 'X'},
//                { 'X', 'O', 'O', 'X'},
//                { 'X', 'X', 'O', 'X'},
//                { 'X', 'O', 'X', 'X'}
//            };
//            
//            printBoard(board);
//            solve(board);
//            printBoard(board);
//        }
//        
//        {
//            std::vector<std::vector<char>> board =
//            {   { 'X', 'O', 'X'},
//                { 'O', 'X', 'O'},
//                { 'X', 'O', 'X'}
//            };
//            
//            printBoard(board);
//            solve(board);
//            printBoard(board);
//        }
//        
//        {
//            std::vector<std::vector<char>> board =
//            {   { 'O', 'X', 'X', 'O', 'X'},
//                { 'X', 'O', 'O', 'X', 'O'},
//                { 'X', 'O', 'X', 'O', 'X'},
//                { 'O', 'X', 'O', 'O', 'O'},
//                { 'X', 'X', 'O', 'X', 'O'},
//            };
//            
//            printBoard(board);
//            solve(board);
//            printBoard(board);
//        }
//
//        {
//            std::vector<std::vector<char>> board =
//            {
//                {'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
//                {'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'X'},
//                {'O', 'X', 'O', 'X', 'O', 'O', 'O', 'O', 'X'},
//                {'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O'},
//                {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X'},
//                {'X', 'X', 'O', 'O', 'X', 'O', 'X', 'O', 'X'},
//                {'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O'},
//                {'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O'},
//                {'O', 'O', 'O', 'O', 'O', 'X', 'X', 'O', 'O'}
//            };
//            
//            printBoard(board);
//            solve(board);
//            printBoard(board);
//        }
//
//        {
//            std::vector<std::vector<char>> board =
//            {
//                {'X', 'O', 'X', 'O', 'O', 'O', 'O'},
//                {'X', 'O', 'O', 'O', 'O', 'O', 'O'},
//                {'X', 'O', 'O', 'O', 'O', 'X', 'O'},
//                {'O', 'O', 'O', 'O', 'X', 'O', 'X'},
//                {'O', 'X', 'O', 'O', 'O', 'O', 'O'},
//                {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
//                {'O', 'X', 'O', 'O', 'O', 'O', 'O'}
//            };
//            
//            printBoard(board);
//            solve(board);
//            printBoard(board);
//        }
        
//        {
//            std::vector<std::vector<char>> board =
//            {
//                {'X', 'X', 'X', 'X', 'O', 'O', 'X', 'X', 'O'},
//                {'O', 'O', 'O', 'O', 'X', 'X', 'O', 'X', 'X'},
//                {'X', 'O', 'X', 'O', 'O', 'X', 'X', 'O', 'X'},
//                {'O', 'O', 'X', 'X', 'X', 'O', 'O', 'O', 'O'},
//                {'X', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'O'},
//                {'O', 'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X'},
//                {'O', 'O', 'O', 'X', 'X', 'O', 'X', 'O', 'X'},
//                {'O', 'O', 'O', 'X', 'O', 'O', 'O', 'X', 'O'},
//                {'O', 'X', 'O', 'O', 'O', 'X', 'O', 'X', 'O'},
//
//            };
//            
//            printBoard(board);
//            solve(board);
//            printBoard(board);
//        }

        {
            std::vector<std::string> board1 =
            {"OOXOOXOOOOOOOOXXOXOO","OXOOOOXXOOOXOOXXOOOO","XOXXOOOOOXOOOXOXXXXO","XXOOOOOOOOXOOXXXXXXX","OOOOOXOOOXXXXOXOOOOO","OXXXOOOXOXOXOOXOXXOO","OOOOOOOOXXXOOXXOOOOO","OXXOOOOOXOXXOXXOOXOO","OOXXXOOXOOOOOOOXXXOX","XXOOOXOXOOOXXOOXOXXO","OOOOOOXOXXOOXOXXXXOX","OOXXOOXOXOOXOOXOOXOX","OXOOOOOXOOOOOOXXXOOO","OOXOXOOXXOXXXOOXXOOX","XOXOXOXOOOOOOOXOOXXO","XOXXXOXOOOOOOXOOOOXX","XOOOOXOOOOOOXOOOOOXX","OOOOOOXOOOXOXOXXOXOX","XOOXOOOOOOXOOOOOXXXX","OOOXXOOOOOOOOXOOOXOO"};
            
            std::vector<std::vector<char>> board(board1.size());
            
            for (int i = 0; i < board1.size(); i++) {
                board[i] = (std::vector<char>(board1[i].begin(), board1[i].end()));
            }
            
            printBoard(board);
            solve(board);
            printBoard(board);

        }

    }
    
}

#endif /* defined(__CPP_Test9__surrounded_regions__) */
