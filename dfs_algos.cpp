//
//  dfs_algos.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/13/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include "dfs_algos.h"

#include <stack>
#include <iostream>

void Graph::insert(int x, int y)
{
    static bool firstCall = true;
    
    EdgeNodePtr ep(new EdgeNode());
    ep->next = this->eNs[x];
    ep->y = y;
    this->eNs[x] = ep;
    
    if (!directed && firstCall) {
        firstCall = false;
        insert(y, x);
    } else {
        ec++;
    }
    
    return;
}

void print_graph(Graph &g) {
    int x = 0;
    for (auto v : g.eNs) {
        std::cout << x++  << ":";
        EdgeNodePtr p = v;
        while (p) {
            std::cout << p->y  << " ";
            p = p->next;
        }
        std::cout << "\n";
    }
}
void process_vertex_early(int v)
{
    std::cout << "Vertex: " << v << "\n";
}

void process_vertex_late(int v)
{
    
}

void process_edge(int x, int y)
{
    std::cout << "Edge: (" << x << "," << y << ")\n";
}

void dfs(Graph &g, int v)
{
    std::vector<EdgeNodePtr> nextEdge(g.vc+1);
    std::vector<VStatus> vs(g.vc+1);
    std::stack<int> s;
    
    s.push(v);
    vs[v] = DIS;
    process_vertex_early(v);
    nextEdge[v] = g.eNs[v];
    
    while (!s.empty()) {
        int x = s.top();
        
        EdgeNodePtr yp = nextEdge[x];
        
        if (yp) {
            int y = yp->y;
            nextEdge[x] = yp->next;
            
            bool newEdge = false;
            if(vs[y] == UND) {
                nextEdge[y] = g.eNs[y];
                s.push(y);
                vs[y] = DIS;
                process_vertex_early(y);

            }
            
            if (vs[y] != PRO || g.directed) {
                process_edge(x, y);
            }
        } else {
            s.pop();
            process_vertex_late(x);
            vs[x] = PRO;
        }
    }
}


void unitTestDfs() {
    {
        Graph g(5, false);
        print_graph(g);
        g.insert(1, 2);
        print_graph(g);

        g.insert(1, 3);
        print_graph(g);

        g.insert(1, 4);
        print_graph(g);

        
        g.insert(2, 3);
        print_graph(g);

        
        g.insert(3, 5);
        print_graph(g);

        
        g.insert(4, 1);
        print_graph(g);

        
        g.insert(5, 2);
        print_graph(g);

        
        dfs(g, 1);
    }
}