#include <iostream>
#include <vector>
#include <fstream>

#include "graph.hh"

using namespace std;

void print_node(Graph *G) {
    cout << "\n" << "Final path length : " << "\n";
    for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        cout << (*nodeit)->value << " : " << (*nodeit)->d << "\n";
    }
}

void print_pre(Node *node) {
    if (node->previous != NULL) {
        print_pre(node->previous);
        cout << " -> ";
    }
    cout << node->value;
}

void print_path(Graph *G) {
    std::cout << '\n';
    for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        cout << (*nodeit)->value << " ( d : " << (*nodeit)->d << " ) : ";
        print_pre(*nodeit);
        cout<<endl;
    }
}

void print_graph(Graph *G) {
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
        (*nodeit)->d = int_max;
        (*nodeit)->previous = NULL;
    }
}

Node *findMin(const std::vector<Node *> &v, int &index) {
    int minV = int_max;
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

bool less_weight(const pair<Node*, double> &m1, const pair<Node*, double> &m2) {
        return m1.second < m2.second;
}

void pre_sort(Graph *G) {
    for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        sort((*nodeit)->neighbors.begin(), (*nodeit)->neighbors.end(), less_weight);
    }
}

Graph *read_file(string fileName){
    std::cout << fileName << '\n';
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
    }
    else {
        std::cerr << "Unable to open file\n";
        return NULL;
    }
}
