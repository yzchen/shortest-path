#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <fstream>

#include "pairing_heap.hpp"
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

void Dijkstra(Graph *G, int source) {
    clear(G);

    (G->nodes)[source] -> d = 0;
    (G->nodes)[source] -> mask = 1;

    // priority_queue<Node *, vector<Node *>, compare_min_first> Q;

    // using self implement pair heap other than stl priority queue
    // pair heap is a simple implementation of fibonacci heap
    PairingHeap Q;

    Q.push(G->nodes[source]);

    while (!Q.empty()) {

        Node *u = Q.top();
        Q.pop();

        // cout << u->value << " : " << u->d << endl;

        for (vector<pair<Node*, double> >::iterator neighborsit = u->neighbors.begin(); neighborsit != u->neighbors.end(); neighborsit++) {
            if ((*neighborsit).first->d > u->d + (*neighborsit).second) {
                (*neighborsit).first->d = u->d + (*neighborsit).second;
                (*neighborsit).first->previous = u;
                // cout << "  -->" << (*neighborsit).first->value << " : "<< (*neighborsit).first->d << endl;

                if (!(*neighborsit).first->mask) {
                    Q.push((*neighborsit).first);
                    (*neighborsit).first->mask = 1;
                }

            }
        }
    }
}

void Spfa(Graph *G, int source) {
    clear(G);

    (G->nodes)[source] -> d = 0;
    (G->nodes)[source] -> mask = 1;

    queue<Node *> Q;

    Q.push(G->nodes[source]);

    while (!Q.empty()) {

        Node *u = Q.front();
        Q.pop();
        u->mask = 0;

        // cout << u->value << " : " << u->d << endl;

        for (vector<pair<Node*, double> >::iterator neighborsit = u->neighbors.begin(); neighborsit != u->neighbors.end(); neighborsit++) {
            if ((*neighborsit).first->d > u->d + (*neighborsit).second) {
                (*neighborsit).first->d = u->d + (*neighborsit).second;
                (*neighborsit).first->previous = u;
                // cout << "  -->" << (*neighborsit).first->value << " : "<< (*neighborsit).first->d << endl;

                if (!(*neighborsit).first->mask) {
                    Q.push((*neighborsit).first);
                    (*neighborsit).first->mask = 1;
                }

            }
        }
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

        return G;
    }
    else {
        std::cerr << "Unable to open file\n";
        return NULL;
    }
}
