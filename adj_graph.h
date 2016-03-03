//
//  adj_graph.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/8/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__adj_graph__
#define __CPP_Test9__adj_graph__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

struct GraphEdgeNode;
typedef std::shared_ptr<GraphEdgeNode> GraphEdgeNodePtr;

struct GraphEdgeNode
{
    int y;
    int weight;
    GraphEdgeNodePtr next;
};

#define MAXV 100

//http://www.slideshare.net/TraianRebedea/algorithm-design-and-complexity-course-8
//http://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
//http://www.geeksforgeeks.org/bridge-in-a-graph/
//http://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
//https://github.com/rajatIIT/interview_question_practice/tree/master/src/interviewquestions
//https://www.youtube.com/watch?v=_nEaVxFvXO4

enum NodeState
{
    UNDISCOVERED,
    DISCOVERED,
    PROCESSED,
};

enum Color
{
    UNCOLORED,
    WHITE,
    BLACK,
};

struct Graph
{

    Graph(int vertexCount);
    
    void insert(int x, int y, bool directed=false);
    void readFromFile(const std::ifstream& ifs);
    int connectedComponents();
    bool processVertexEarly(int v);
    bool processVertexEnd(int v);
    bool processEdge(int x, int y);
    Color complement(Color x);

    // BFS algos
    
    bool bfs(int startVertex);
    bool bipartite();
    void shortestPath(int x, int y, std::vector<int> &path);
    
    // DFS algos
    
    void dfs(int startVertex);
    void dfsProcessVertexEarly(int x);
    void dfsProcessEdge(int x, int y);
    void dfsProcessVertexLate(int x);

    int vertexCount;
    int edgesCount;
    bool directed;
    GraphEdgeNodePtr vertices[MAXV+1];
    int verticesDegree[MAXV+1];
    std::vector<NodeState> nodeState;
    std::vector<int> nodeParents;
    std::vector<Color> nodeColors;
    std::vector<int>  entry;
    std::vector<int>  exit;
    bool bfsNoReturn;
    bool finished;
    bool cyclic;

    static int time;
};

void unitTestGraphs();


#endif /* defined(__CPP_Test9__adj_graph__) */
