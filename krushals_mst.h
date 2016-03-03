//
//  krushals_mst.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/22/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__krushals_mst__
#define __CPP_Test9__krushals_mst__

#include <vector>
#include <cassert>
#include <iostream>

struct EdgeNode;
typedef std::shared_ptr<EdgeNode> EdgeNodePtr;

struct EdgeNode
{
    EdgeNode(int x, int y, int wt)
        : x(x), y(y), next(), wt(wt)
    {
        
    }
    
    int x;
    int y;
    EdgeNodePtr next;
    int wt;
};

void printMST(const std::vector<EdgeNodePtr>& mst) {
    std::cout << "MST:";
    for (const EdgeNodePtr p : mst) {
        std::cout << "(" << p->x+1 << "," << p->y+1 << "," << p->wt << "),";
    }
    
    std::cout << "\n";
}

struct Graph
{
    Graph(int nv, bool directed)
        : edges(nv), ne(0),  nv(nv), directed(directed)
    {
        
    }
    
    void insert(int x1, int y1, int wt)
    {
        assert(x1 > 0);
        assert(y1 > 0);
        
        int x = x1 - 1;
        int y = y1 - 1;
        {
            EdgeNodePtr n(new EdgeNode(x, y, wt));
            n->next = edges[x];
            edges[x] = n;
        }
        
        if(!directed) {
            EdgeNodePtr n2(new EdgeNode(y, x, wt));
            n2->next = edges[y];
            edges[y] = n2;
        }
        
        ne++;
    }
    
    void print()
    {
        for (int i= 0; i< nv; ++i) {
            EdgeNodePtr p = edges[i];
            std::cout << i << ": [";
            while (p) {
                std::cout << "(" << p->x+1 << "," << p->y+1 << "," << p->wt << "),";
                p = p->next;
            }
            std::cout << "]\n";
        }
    }

    
    std::vector<EdgeNodePtr> edges;
    int ne;
    int nv;
    bool directed;
};

struct UnionFind
{
    UnionFind(const Graph& g)
    : nv(g.nv), parents(nv, -1), sizes(nv, 1)
    {
        for (int i = 0; i < nv ; ++i) {
            parents[i] = i;
        }
    }
    
    int find(int x)
    {
        int x1 = x;
        
        while (parents[x1] != x1) {
            x1 = parents[x1];
        }
        
        return x1;
    }
    
    int union1(int x, int y)
    {
        int x1 = x;
        int y1 = y;
        
        int px1 = find(x1);
        int py1 = find(y1);
        
        if (sizes[px1] > sizes[py1]) {
            parents[py1] = px1;
            sizes[px1] += sizes[py1];
            return px1;
        } else {
            parents[px1] = py1;
            sizes[py1] += sizes[px1];
            return py1;
        }
    }
    
    int nv;
    std::vector<int> parents;
    std::vector<int> sizes;
};

void initEdgeNodePairList(const Graph& g, std::vector<EdgeNodePtr>& enpl)
{
    for (int i= 0; i< g.nv; ++i) {
        EdgeNodePtr tmp = g.edges[i];
        while (tmp) {
            enpl.push_back(tmp);
            tmp = tmp->next;
        }
    }
}

struct EdgeNodePtrCmp
{
    bool operator()(const EdgeNodePtr& p1, const EdgeNodePtr& p2)
    {
        return p1->wt < p2->wt;
    }
};

void krushalsMst(const Graph& g, std::vector<EdgeNodePtr>& mst)
{
    std::vector<EdgeNodePtr> edges;
    edges.reserve(g.ne);
    
    initEdgeNodePairList(g, edges);
    std::sort(edges.begin(), edges.end(), EdgeNodePtrCmp());
    
    printMST(edges);
    
    UnionFind uf(g);
    
    for (int i = 0; i < g.ne; ++i) {
        EdgeNodePtr e = edges[i];
        
        int px = uf.find(e->x);
        int py = uf.find(e->y);
        
        if (px == py) {
            std::cout << "(" << e->x << "," << e->y << "): will make cycle\n";
        } else {
            int parent = uf.union1(px, py);
            std::cout << "(" << e->x << "," << e->y << "): is in MST\n";
            mst.push_back(e);
            if (uf.sizes[parent] == g.nv) {
                std::cout << "MST is complete1\n";
                return;
            }
        }
    }
    
    std::cout << "MST is complete2\n";
    return;
}


void unitTestKrushalsMst() {
    {
        Graph g(5, false);
        
        g.insert(1, 2, 9);
        g.print();

        g.insert(1, 3, 10);
        g.print();

        g.insert(1, 5, 71);
        g.print();

        
        g.insert(2, 4, 2);
        g.print();

        g.insert(2, 3, 20);
        g.print();

        
        g.insert(3, 4, 5);
        g.print();

        g.insert(3, 5, 1);
        g.print();
        
        std::vector<EdgeNodePtr> mst;
        mst.reserve(g.ne);
        krushalsMst(g, mst);
        printMST(mst);
    }
}


#endif /* defined(__CPP_Test9__krushals_mst__) */
