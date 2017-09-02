#include <iostream>
#include <queue>
#include <vector>
#include <utility>

#include "pairing_heap.hpp"
#include "graph.hh"

using namespace std;

void print_node(Graph *G) {
    cout << "\n" << "Final path length : " << "\n";
    for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        cout << (*nodeit)->value << " : " << (*nodeit)->d << "\n";
    }
}

void Dijkstra(Graph *G, int source) {
    vector<Node *>::iterator nodeit;

    for (nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        (*nodeit)->d = int_max;
        (*nodeit)->previous = NULL;
    }

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

        cout << u->value << " : " << u->d << endl;

        for (vector<pair<Node*, int> >::iterator neighborsit = u->neighbors.begin(); neighborsit != u->neighbors.end(); neighborsit++) {
            if ((*neighborsit).first->d > u->d + (*neighborsit).second) {
                (*neighborsit).first->d = u->d + (*neighborsit).second;
                (*neighborsit).first->previous = u;
                cout << "  -->" << (*neighborsit).first->value << " : "<< (*neighborsit).first->d << endl;

                if (!(*neighborsit).first->mask) {
                    Q.push((*neighborsit).first);
                    (*neighborsit).first->mask = 1;
                }

            }
        }
    }
}

void Spfa(Graph *G, int source) {
    vector<Node *>::iterator nodeit;

    for (nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        (*nodeit)->d = int_max;
        (*nodeit)->previous = NULL;
    }

    (G->nodes)[source] -> d = 0;
    (G->nodes)[source] -> mask = 1;

    queue<Node *> Q;

    Q.push(G->nodes[source]);

    while (!Q.empty()) {

        Node *u = Q.front();
        Q.pop();
        u->mask = 0;

        cout << u->value << " : " << u->d << endl;

        for (vector<pair<Node*, int> >::iterator neighborsit = u->neighbors.begin(); neighborsit != u->neighbors.end(); neighborsit++) {
            if ((*neighborsit).first->d > u->d + (*neighborsit).second) {
                (*neighborsit).first->d = u->d + (*neighborsit).second;
                (*neighborsit).first->previous = u;
                cout << "  -->" << (*neighborsit).first->value << " : "<< (*neighborsit).first->d << endl;

                if (!(*neighborsit).first->mask) {
                    Q.push((*neighborsit).first);
                    (*neighborsit).first->mask = 1;
                }

            }
        }
    }
}
