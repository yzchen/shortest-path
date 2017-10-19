#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

#include "pairing_heap.hpp"
#include "graph.hh"

using namespace std;

void DijkstraArray(Graph *G, int source) {
    clear(G);

    (G->nodes)[source] -> d = 0;
    (G->nodes)[source] -> mask = 1;

    std::vector<Node *> v;
    v.push_back(G->nodes[source]);

    while (!v.empty()) {
        int index = -1;
        Node *u = findMin(v, index);
        v.erase(v.begin() + index);

        for (vector<pair<Node*, double> >::iterator neighborsit = u->neighbors.begin(); neighborsit != u->neighbors.end(); neighborsit++) {
            if ((*neighborsit).first->d > u->d + (*neighborsit).second) {
                (*neighborsit).first->d = u->d + (*neighborsit).second;
                (*neighborsit).first->previous = u;

                if (!(*neighborsit).first->mask) {
                    v.push_back((*neighborsit).first);
                    (*neighborsit).first->mask = 1;
                }

            }
        }
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
