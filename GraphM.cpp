//
// Created by Kemba Konteh on 2/10/20.
//

#include "GraphM.h"



/*
 * graphm.cpp
 *
 * This class implements Dijkstra's shortest path algorithm.
 * It reads a data file consisting of many lines and will be able
 * to find the lowest cost paths (findShortestPath function) and
 * the displayAll function displays the cost and path from every node to every other node.
 * while the display function will output one path in detail.
 */


// --------------------------------------------------- Default Constructor ---------------------------------------------
// Constructs an empty table and initializes all values
// ---------------------------------------------------------------------------------------------------------------------
GraphM::GraphM() {

    // instance members data, size and cost are iniitalized in buildGraph method.
    //size = 0;

    for(int i=0; i<MAXNODES; i++) {
        for(int j=0; j<MAXNODES; j++) {
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            // We only consider the numbers from 1 to n
            // Hence 0 node determines end of the path.
            T[i][j].path = 0;

            // to represent no path between 2 vertices
            C[i][j] = 0;
        }
    }
}


// --------------------------------------------------- buildGraph() ----------------------------------------------------
// Builds up graph node information and adjacency matrix of edges
// between each node reading from a data file.
// ---------------------------------------------------------------------------------------------------------------------

void GraphM::buildGraph(ifstream &in) {
    string line;

    getline(in, line);
    if(line.empty()) {
        size = 0;
        return;
    }

    size = atoi(line.c_str());

    // Read node names
    for(int i=1; i<=size; i++) {
        data[i].setData(in);
    }

    // Read the cost for adjacency matrix.
    int from, to, cost;
    while(true) {
        getline(in, line);

        stringstream ss(line);
        ss >> from >> to >> cost;

        if(from == 0) {
            break;
        }
        insertEdge(from, to, cost);
    }
}

// ------------------------------------------------- insertEdge() ------------------------------------------------------
// Inserts an edge into a graph between 2 given nodes
// ---------------------------------------------------------------------------------------------------------------------
void GraphM::insertEdge(int from, int to, int weight) {
    C[from][to] = weight;
}

// ------------------------------------------------- removeEdge() ------------------------------------------------------
// Removes an edge between 2 given nodes
// ---------------------------------------------------------------------------------------------------------------------
void GraphM::removeEdge(int from, int to) {
    C[from][to] = 0;
}

// ----------------------------------------------- findShortestPath() --------------------------------------------------
// Finds the shortest path between every node to every other node
// in the graph using Dijkstra's algorithm
// --------------------------------------------------------------------------------------------------------------------
void GraphM::findShortestPath() {
    for(int source = 1; source <= size; source++) {

        T[source][source].dist = 0;

        // Cover n nodes.
        for(int i = 1; i <= size; i++) {

            // find minNode that is not visited and at min distance.
            int minDist = INT_MAX;
            int minNode;

            for(int v=1; v<= size; v++) {
                if(!T[source][v].visited && T[source][v].dist < minDist) {
                    minDist = T[source][v].dist;
                    minNode = v;
                }
            }

            // mark minNode visited
            T[source][minNode].visited = true;

            // for each node adjacent to minNode
            for(int v=1; v<= size; v++) {
                if(!T[source][v].visited
                   && (C[minNode][v] != 0)
                   && (T[source][minNode].dist != INT_MAX)
                   && (T[source][minNode].dist + C[minNode][v] < T[source][v].dist)) {
                    T[source][v].dist = T[source][minNode].dist + C[minNode][v];
                    T[source][v].path = minNode;
                }
            }
        }
    }
}

// ------------------------------------------------------ displayAll() -------------------------------------------------
// Uses couts to demonstrate that the alogorithm works properly
// Uses helper function findPath()
// ---------------------------------------------------------------------------------------------------------------------
void GraphM::displayAll() {
    cout << setw(20) << left << "Description";
    cout << setw(15) << left << "From Node";
    cout << setw(10) << left << "To Node";
    cout << setw(20) << left << "Dijkstra's";
    cout << setw(10) << left << "Path" << endl;

    for(int start=1; start<=size; start++) {
        cout << data[start] << endl;

        for(int node=1; node<=size; node++) {

            if(node != start) {
                cout << setw(25) << " ";
                cout << setw(15) << start;
                cout << setw(10) << node;

                // If start to node is reachable
                if(T[start][node].dist != INT_MAX) {
                    cout << setw(15) << T[start][node].dist;

                    // use stack to store the nodes from start to node.
                    stack<int> pathNodes;
                    pathNodes.push(node);
                    int parent = T[start][node].path;
                    while(parent != 0) {
                        pathNodes.push(parent);
                        parent = T[start][parent].path;
                    }

                    // using the stack, print the path
                    while(!pathNodes.empty()) {
                        cout << pathNodes.top() << " ";
                        pathNodes.pop();
                    }
                    cout << endl;

                } else {
                    cout << "----" << endl;
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}


// ---------------------------------------------------- display() ------------------------------------------------------
// Uses couts to display the shortest distance with path info between the from to the to nodes. Uses helper function
// ---------------------------------------------------------------------------------------------------------------------

void GraphM::display(int from, int to) {

    // if given nodes are invalid or not reachable.
    if(T[from][to].dist == INT_MAX) {
        //cout << "Nodes " << from << " and " << to << " are not connnected." << endl << endl;
        cout << "     " << from << "         " << to << "      ----  " << endl;
        cout << " " << endl;
        return;
    }

    cout << "     " << from << "         " << to << "        "   << T[from][to].dist << "                  ";

    stack<int> pathNodes;
    stack<int> pathNodesCopy;

    pathNodes.push(to);

    int parent = T[from][to].path;
    while(parent != 0) {
        pathNodes.push(parent);
        parent = T[from][parent].path;
    }

    pathNodesCopy = pathNodes;

    while(!pathNodes.empty()) {
        cout << pathNodes.top() << " ";
        pathNodes.pop();
    }
    cout << endl;

    while(!pathNodesCopy.empty()) {
        cout << data[pathNodesCopy.top()] << endl;
        pathNodesCopy.pop();
    }
    cout << endl;
}

