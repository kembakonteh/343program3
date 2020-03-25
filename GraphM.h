//
// Created by Kemba Konteh on 2/10/20.
//




#ifndef PROGRAM03_GRAPHM_H
#define PROGRAM03_GRAPHM_H

const int MAXNODES = 101; //101 since index 0 is not used

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <stack>
#include <iomanip>

#include "NodeData.h"

using namespace std;

// this structure represents the data from a src Node to dest Node.
struct TableType {
    bool visited;          // whether node has been visited
    int dist;              // shortest distance from source known so far
    int path;              // previous node in path of min dist
};


class GraphM {
public:

    // constructor
    GraphM();

    //builds up graph node information and adjacency matrix of edges between each node reading from a data file.
    void buildGraph(ifstream &in);

    //find the shortest path between every node to every other node in the graph, i.e., TableType T is updated with
    // shortest path information
    void findShortestPath();

    //uses couts to demonstrate that the algorithm works properly
    void displayAll();

    //uses couts to display the shortest distance with path info between the fromNode to toNode
    void display(int from, int to);

    //insert an edge into graph between two given nodes
    void insertEdge (int from, int to, int weight);

    //remove an edge between two given nodes
    void removeEdge (int from, int to);

private:
    NodeData data[MAXNODES];              // data for graph nodes (names)
    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path
};

#endif //PROGRAM03_GRAPHM_H
