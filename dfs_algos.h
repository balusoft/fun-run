//
//  dfs_algos.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/13/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__dfs_algos__
#define __CPP_Test9__dfs_algos__

#include <memory>
#include <vector>

struct EdgeNode;
typedef std::shared_ptr<EdgeNode> EdgeNodePtr;

struct EdgeNode
{
    EdgeNodePtr next;
    int y; // Assuming Edge:(x, y)
};

struct Graph
{
    Graph(int vc, bool directed) : eNs(vc+1), ec(0), vc(vc), directed(directed)
    {
        
    }
    
    void insert(int x, int y);
    
    std::vector<EdgeNodePtr> eNs;
    int ec;
    int vc;
    bool directed;
};

enum VStatus
{
    UND,
    DIS,
    PRO,
};

void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int x, int y);

void dfs(Graph &g, int v);

void unitTestDfs();

#endif /* defined(__CPP_Test9__dfs_algos__) */
