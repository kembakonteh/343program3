//
// Created by Kemba Konteh on 2/10/20.
//

#include "GraphL.h"

//--------------------------------------------------------  class GraphL ----------------------------------------------
// GraphL: This class displays the graph information and implements DFS. It calculates depth-first algorithm, search
// alway starts at node number 1, and reads data from provided data file, and find the depth-firts path.
//----------------------------------------------------------------------------------------------------------------------
#include "GraphL.h"


// ------------------------------------------------------- GraphL() ----------------------------------------------------
// Default constructor
// ---------------------------------------------------------------------------------------------------------------------
GraphL::GraphL() {
    size = 0;
}

// -------------------------------------------------- ~GraphL() --------------------------------------------------------
// Destructor to destroy (or delete) the object.
// ---------------------------------------------------------------------------------------------------------------------
GraphL::~GraphL() {

    for(int i=1; i<=size; i++) {
        GraphNode g = nodes[i];
        if(g.data != nullptr) {
            delete g.data;
        }

        EdgeNode* adjNode = g.edgeHead;
        while(adjNode != nullptr) {
            EdgeNode* del = adjNode;
            adjNode = adjNode->nextEdge;
            delete del;
        }

        g.data = nullptr;
        g.edgeHead = nullptr;
    }

    size = 0;
}

// ------------------------------------------------- buildGraph --------------------------------------------------------
// Builds up graph node information and adjacency list of edges between each node reading from a data file
// ---------------------------------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream &in) {
    string line;

    getline(in, line);
    if(line.empty()) {
        size = 0;
        return;
    }

    size = atoi(line.c_str());

    // Read node names
    for(int i=1; i<=size; i++) {
        nodes[i].data = new NodeData();
        nodes[i].data->setData(in);
        nodes[i].visited = false;
        nodes[i].edgeHead = nullptr;
    }

    // Read the cost for adjacency matrix.
    int from, to;
    while(true) {
        getline(in, line);

        stringstream ss(line);
        ss >> from >> to;

        if(from == 0) {
            break;
        }

        nodes[from].edgeHead = new EdgeNode(to, nodes[from].edgeHead);
    }
}

// ------------------------------------------------------ displayGraph -------------------------------------------------
// Displays each node information and edge in the graph
// ---------------------------------------------------------------------------------------------------------------------
void GraphL::displayGraph() {
    cout << "Graph: " << endl;

    for(int start=1; start<=size; start++) {
        cout << "Node " << setw(10) << left << start << *(nodes[start].data) << endl;

        // Start from first connected node in adjacency list
        EdgeNode* startNode = nodes[start].edgeHead;

        while(startNode != nullptr) {
            cout << setw(4) << "";
            cout << "edge " << start << " " << startNode->adjGraphNode << endl;

            // move to next node inside the list.
            startNode = startNode->nextEdge;
        }
    }
    cout << endl;
}

// --------------------------------------------- depthFirstSearch() ----------------------------------------------------
// Makes a depth-first search and displays each node in depth-first order
// ---------------------------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch() {
    cout << "Depth-first ordering:";

    // always start DFS by visiting the first node
    visitDFSHelper(1);

    cout << endl;
}


// ----------------------------------------------------- visitDFSHelper() ----------------------------------------------
// Helper method to visit a particular node and its children in DFS. Recursively finds the depthFirstSearch
// ---------------------------------------------------------------------------------------------------------------------
void GraphL::visitDFSHelper(int nodeIndex) {
    // if this node is already visited, then its children are
    // also visited.
    if(nodes[nodeIndex].visited) {
        return;
    }

    // mark current node visited and print.
    cout << " " << nodeIndex;
    nodes[nodeIndex].visited = true;

    EdgeNode* start = nodes[nodeIndex].edgeHead;
    while(start != nullptr) {
        visitDFSHelper(start->adjGraphNode);

        // move to next node inside the list.
        start = start->nextEdge;
    }
}
