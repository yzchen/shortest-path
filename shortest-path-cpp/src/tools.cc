#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

#include "graph.hh"

using namespace std;

static void printPre(Node *node) {
    if (node->previous != NULL) {
        printPre(node->previous);
        cout << " -> ";
    }
    cout << node->value;
}

// void printNode(Graph *G) {
//     cout << "\n" << "Final path length : " << "\n";
//     for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
//         cout << (*nodeit)->value << " : " << (*nodeit)->d << "\n";
//     }
// }

void printPath(Graph *G) {
    int cntInfinity = 0;
    std::cout << '\n' << "Path from nodes[0] to all other nodes :\n";
    for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        if ((*nodeit)->d == numeric_limits<double>::max()) {
            cntInfinity++;
            continue;
        }
        cout << (*nodeit)->value << " ( d : " << (*nodeit)->d << " ) : ";
        printPre(*nodeit);
        cout<<endl;
    }

    std::cout << "\n" << "unreached nodes : " << cntInfinity << endl;
}

void printGraph(Graph *G) {
    std::cout << "\nGraph showed in adjacency list : " << '\n';
    for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        std::cout << (*nodeit)->value << " : ";
        for (vector<pair<Node*, double> >::iterator neighborsit = (*nodeit)->neighbors.begin(); neighborsit != (*nodeit)->neighbors.end(); neighborsit++) {
            std::cout << (*neighborsit).first->value << ", ";
        }
        std::cout << '\n';
    }
}

void clear(Graph *G) {
    for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        (*nodeit)->d = numeric_limits<double>::max();
        (*nodeit)->previous = NULL;
    }
}

Node *findMin(const std::vector<Node *> &v, int &index) {
    double minV = numeric_limits<double>::max();
    index = -1;
    for (size_t i = 0; i < v.size(); i++) {
        if ((v[i])->d < minV) {
            minV = (v[i])->d;
            index = i;
        }
    }
    if (index != -1) {
        return v[index];
    }
    else {
        return NULL;
    }
}

bool lessWeight(const pair<Node*, double> &m1, const pair<Node*, double> &m2) {
        return m1.second < m2.second;
}

void preSort(Graph *G) {
    for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        sort((*nodeit)->neighbors.begin(), (*nodeit)->neighbors.end(), lessWeight);
    }
}

Graph *readFile(string fileName) {
    std::cout << "fileName : " << fileName << '\n';
    Graph *G = new Graph();

    std::ifstream infile(fileName, std::ios::in);
    if (infile.is_open()) {
        int nNodes, nEdges;
        infile >> nNodes >> nEdges;

        std::cout << "nNodes : " << nNodes << "   nEdges : " << nEdges << endl;

        G->nNodes = nNodes;
        G->nEdges = nEdges;

        for (size_t i = 0; i < nNodes; i++) {
            Node *tmp = new Node();
            tmp->value = to_string(i);
            (G->nodes).push_back(tmp);
        }

        int inNode, outNode;
        double weight;
        for (size_t i = 0; i < nEdges; i++) {
            infile >> inNode >> outNode >> weight;
            (((G->nodes)[inNode])->neighbors).push_back(make_pair((G->nodes)[outNode], weight));
        }

        // print_graph(G);

        // // add a pre_sort for each node's neighbors,
        // // but don't know the results is not good for Spfa
        // pre_sort(G);

        return G;
    } else {
        std::cerr << "Unable to open file " + fileName + "\n";
        return NULL;
    }
}
