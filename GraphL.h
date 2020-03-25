//
// Created by Kemba Konteh on 2/10/20.
//

/*
 *
 * The graphl class displays the graph information and implements DFS
 */


#ifndef PROGRAM03_GRAPHL_H
#define PROGRAM03_GRAPHL_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <stack>
#include <iomanip>
#include "GraphM.h"
#include "NodeData.h"

using namespace std;

// forward reference for the compiler
struct EdgeNode;

// structs used for simplicity
struct GraphNode {

    // head of the list of edges
    EdgeNode* edgeHead;

    // data information about each node
    NodeData* data;

    // whether node has been visited or not
    bool visited;
};

// struct declaration
struct EdgeNode {

    // subscript of the adjacent graph node
    int adjGraphNode;

    // next edge
    EdgeNode* nextEdge;
    EdgeNode(int nodeIndex, EdgeNode* next) {
        adjGraphNode = nodeIndex;
        nextEdge = next;
    }
};


class GraphL {

public:
    // constructor
    GraphL();

    //destructor
    ~GraphL();

    // Functions
    void buildGraph(ifstream &in);
    void displayGraph();
    void depthFirstSearch();

    // Graph Nodes for adjacency list
    GraphNode nodes[MAXNODES];

private:
    //GraphNode nodes[MAXNODES];  // Graph Nodes for adjacency list

    // size
    int size;

    // visit DFS helper method
    void visitDFSHelper(int nodeIndex);
};

#endif
