//
//  adj_graph.cpp
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/8/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#include "adj_graph.h"
#include <queue>
#include <cassert>
#include <stack>

Graph::Graph(int vertexCount)
: vertexCount(vertexCount),
  directed(false),
  nodeState(vertexCount+1, UNDISCOVERED),
  nodeParents(vertexCount+1, -1),
  nodeColors(vertexCount+1, UNCOLORED),
  entry(vertexCount+1, -1),
  exit(vertexCount+1, -1),
  bfsNoReturn(true),
  finished(false),
  cyclic(false)
{
    
}
void Graph::insert(int x, int y, bool directed)
{
    GraphEdgeNodePtr n(new GraphEdgeNode());
    n->y = y;
    n->next = vertices[x];
    vertices[x] = n;
    if (!directed) {
        insert (y, x, true);
    } else {
        this->edgesCount++;
    }
}

bool Graph::processVertexEarly(int v)
{
    std::cout << "Vertex: " << v << "\n";
    if (nodeParents[v] == -1 && nodeColors[v] == UNCOLORED)
    {
        nodeColors[v] = WHITE;
    }
    return true;
}

bool Graph::processVertexEnd(int v)
{
    return true;
}

Color Graph::complement(Color x)
{
    assert(x != UNCOLORED);
    
    if (x == WHITE) {
        return BLACK;
    }
    
    return WHITE;
}

bool Graph::processEdge(int x, int y)
{
    std::cout << "Edge:( " << x << "," << y << ")\n";
    
    if (nodeColors [x] == nodeColors[y]) {
        return false;
    }
    
    nodeColors[y] = complement(nodeColors[x]);
    
    return true;
}

bool Graph::bfs(int startFromVertex)
{
    
    bool ret = true;
    std::queue<int> q;

    q.push(startFromVertex);
    nodeState[startFromVertex] = DISCOVERED;
    
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        processVertexEarly(x);
        
        GraphEdgeNodePtr itr = vertices[x];
        
        while (itr) {
            int y = itr->y;
            std::cout << "y: " << y << "\n";
            if (nodeState[y] == UNDISCOVERED) {
                q.push(y);
                nodeState[y] = DISCOVERED;
                nodeParents[y] = x;
            }
            
            if (nodeState[y] != PROCESSED || directed) {
                if (!processEdge(x, y))
                {
                    if (bfsNoReturn) {
                        ret = false;
                    } else {
                        return false;
                    }
                }
            }
            itr = itr->next;
        }
        
        processVertexEnd(x);
        nodeState[x] = PROCESSED;
    }
    
    return ret;
    
}

int Graph::connectedComponents()
{
    int comps = 0;
    
    for (int i = 1; i <= vertexCount; ++i)
    {
        if (nodeState[i] == UNDISCOVERED) {
            bfs(i);
            ++comps;
        }
    }
    
    return comps;
}

bool Graph::bipartite()
{
    for (int i = 1; i <= vertexCount; ++i)
    {
        if (nodeState[i] == UNDISCOVERED) {
            if (!bfs(i)) {
                return false;
            }
        }
    }
    return true;
}

void Graph::shortestPath(int x, int y, std::vector<int> &path)
{
    bfs(x);
    
    std::stack<int> s;
    
    auto curNode = y;
    while(curNode != -1 )
    {
        s.push(curNode);
        curNode = nodeParents[curNode];
    }
 
    while(!s.empty()) {
        path.push_back(s.top());
        s.pop();
    }
}

void Graph::dfsProcessVertexEarly(int x)
{
    std::cout << "Entering Node: " << x << "\n";
}

void Graph::dfsProcessEdge(int x, int y)
{
    std::cout << "Edge: (" << x << "," << y << ")\n";
    
    if (nodeParents[x] == y) {
        cyclic = true;
        std::cout << "Found cycle, this is cyclic graph\n";
    }
}

void Graph::dfsProcessVertexLate(int x)
{
    std::cout << "Exiting Node: " << x << "\n";
}

int Graph::time = 0;
void Graph::dfs(int startVertex)
{
    time++;
    entry[startVertex] = time;
    std::cout << "enter time of (" << startVertex << "): " << entry[startVertex] << "\n";
    nodeState[startVertex] = DISCOVERED;
    GraphEdgeNodePtr p = vertices[startVertex];

    dfsProcessVertexEarly(startVertex);
    while (p)
    {
        int y = p->y;
        if (nodeState[y] == UNDISCOVERED) {
            nodeState[y] = DISCOVERED;
            nodeParents[y] = startVertex;
            dfsProcessEdge(startVertex, y);
            dfs(y);

        } else if (nodeState[y] == DISCOVERED || directed) {
            dfsProcessEdge(startVertex, y);

        }
        
        if (finished) {
            return;
        }
        p = p->next;
    }
    
    dfsProcessVertexLate(startVertex);
    time++;
    exit[startVertex] = time;
    nodeState[startVertex] = PROCESSED;
        std::cout << "exit time of (" << startVertex << "): " << exit[startVertex] << "\n";
}


void printv(std::vector<int> v)
{
    std::cout << "[";
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << "]\n";
}

void unitTestGraphs()
{
//    {
//        Graph g(8);
//        g.insert(1,2);
//        g.insert(1,4);
//        
//        g.insert(2,3);
//        g.insert(2,4);
//        
//        g.insert(5,1);
//        
//        g.insert(6,7);
//        
//        g.bfs(5);
//        
//        
//    }
//    
//    {
//        Graph g(8);
//        g.insert(1,2);
//        g.insert(1,4);
//        
//        g.insert(2,3);
//        g.insert(2,4);
//        
//        g.insert(5,1);
//        
//        g.insert(6,7);
//        
//      
//        std::cout << "Total connected components in graph are: " << g.connectedComponents() << "\n";
//        
//    }
//    
//    {
//        Graph g(8);
//        g.insert(1,2);
//        g.insert(1,4);
//        
//        g.insert(2,3);
//        g.insert(2,4);
//        
//        g.insert(5,1);
//        
//        g.insert(6,7);
//        
//        std::cout << std::boolalpha << "Is Bipartite: " << g.bipartite() << "\n";
//        
//    }
//
//    {
//        Graph g(6);
//        
//        g.insert(1,4);
//        g.insert(1,5);
//        g.insert(1, 6);
//        g.insert(2, 5);
//        g.insert(2, 6);
//        g.insert(3, 4);
//        std::cout << std::boolalpha << "Is Bipartite: " << g.bipartite() << "\n";
//        
//    }
//    
//    
//    {
//        Graph g(8);
//        g.insert(1,2);
//        g.insert(1,4);
//        
//        g.insert(2,3);
//        g.insert(2,4);
//        
//        g.insert(5,1);
//        
//        g.insert(6,7);
//        
//        std::vector<int> path;
//        path.reserve(g.vertexCount);
//        g.shortestPath(1, 7, path);
//        std::cout << "shortestPath(1, 7): ";
//        printv(path);
//        std::cout << "\n";
//        
//    }
//
//    
//    {
//        Graph g(8);
//        g.insert(1,2);
//        g.insert(1,4);
//        
//        g.insert(2,3);
//        g.insert(2,4);
//        
//        g.insert(5,1);
//        
//        g.insert(6,7);
//        
//        std::vector<int> path;
//        path.reserve(g.vertexCount);
//        g.shortestPath(2, 5, path);
//        std::cout << "parentsVector: ";
//        printv(g.nodeParents);
//
//        std::cout << "shortestPath(2, 5): ";
//        printv(path);
//        std::cout << "\n";
//        
//    }
    
    {
        Graph g(8);
//        g.insert(1,2);
//        g.insert(1,4);
//        
//        g.insert(2,3);
//        g.insert(2,4);
//        
//        g.insert(5,1);
//        
//        g.insert(6,7);
//        g.insert(6, 1);
//        g.insert(8, 1);
        
        g.insert(1, 2);
        
        g.insert(1, 3);
        
        g.insert(1, 4);

        g.insert(2, 3);
        
        g.insert(3, 5);
        
        g.insert(4, 1);
        
        g.insert(5, 2);

        g.nodeParents[2] = -1;
        g.dfs(1);
        
        std::cout << "entry: " << "\n";
        printv(g.entry);

        std::cout << "exit: " << "\n";
        printv(g.exit);
        
        std::cout << "Parents: " << "\n";
        printv(g.nodeParents);
    }

}