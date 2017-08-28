#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <climits>

// #define DIJKSTRA_ALGORITHM
#define SPFA_ALGORITHM

using namespace std;

typedef struct Node {
    // for adjacency list
    char value;
    vector<pair<struct Node *, int> > neighbors;

    // for algorithms
    int d;
    Node *previous;

    // for spfa algorithm, if node in queue, then mask = 1, else mask = 0
    int mask;
} Node;

typedef struct Graph {
    vector<Node *> nodes;
} Graph;

struct compare_min_first{
    bool operator ()(Node *a, Node *b){
        return a->d > b->d; //最小值优先
    }
};

void construct(Graph *G) {
    Node *A = new Node();
    Node *B = new Node();
    Node *C = new Node();
    Node *D = new Node();
    Node *E = new Node();

    A->value = 'A';
    (A->neighbors).push_back(make_pair(B, 7));
    (A->neighbors).push_back(make_pair(C, 1));

    B->value = 'B';
    (B->neighbors).push_back(make_pair(A, 7));
    (B->neighbors).push_back(make_pair(D, 2));

    C->value = 'C';
    (C->neighbors).push_back(make_pair(A, 1));
    (C->neighbors).push_back(make_pair(D, 3));

    D->value = 'D';
    (D->neighbors).push_back(make_pair(B, 2));
    (D->neighbors).push_back(make_pair(C, 3));
    (D->neighbors).push_back(make_pair(E, 2));

    E->value = 'E';
    (E->neighbors).push_back(make_pair(D, 2));

    (G->nodes).push_back(A);
    (G->nodes).push_back(B);
    (G->nodes).push_back(C);
    (G->nodes).push_back(D);
    (G->nodes).push_back(E);
}

void dijkstra(Graph *G, int source) {
    vector<Node *>::iterator nodeit;

    for (nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        (*nodeit)->d = INT_MAX;
        (*nodeit)->previous = NULL;
    }

    (G->nodes)[source] -> d = 0;
    (G->nodes)[source] -> mask = 1;
    for (vector<pair<Node*, int> >::iterator neighborsit = G->nodes[source]->neighbors.begin(); neighborsit != G->nodes[source]->neighbors.end(); neighborsit++) {
        // cout << (*neighborsit).first->value << " " << (*neighborsit).second <<endl;
        (*neighborsit).first->d = (*neighborsit).second;
    }

#ifdef DIJKSTRA_ALGORITHM
    // for Dijkstra algrithm
     priority_queue<Node *, vector<Node *>, compare_min_first> Q;
#endif

#ifdef SPFA_ALGORITHM
    // for SPFA algorithm
     queue<Node *> Q;
#endif

     int size = (G->nodes).size();
     for (int i = 0; i < size; i++) {
         if (i != source) {
             Q.push(G->nodes[i]);
         }
     }

     while (!Q.empty()) {

#ifdef DIJKSTRA_ALGORITHM
         Node *u = Q.top();
#endif

#ifdef SPFA_ALGORITHM
        Node *u = Q.front();
#endif

         Q.pop();
         u->mask = 0;
        //  cout << u->value << endl;

         for (vector<pair<Node*, int> >::iterator neighborsit = u->neighbors.begin(); neighborsit != u->neighbors.end(); neighborsit++) {
             if ((*neighborsit).first->d > u->d + (*neighborsit).second) {
                 (*neighborsit).first->d = u->d + (*neighborsit).second;
                 (*neighborsit).first->previous = u;

                 if (!(*neighborsit).first->mask) {
                     Q.push((*neighborsit).first);
                     (*neighborsit).first->mask = 1;
                 }
             }
         }
     }
}

void print_node(Graph *G) {
    for (vector<Node *>::iterator nodeit = G->nodes.begin(); nodeit != G->nodes.end(); nodeit++) {
        cout << (*nodeit)->value << " : " << (*nodeit)->d << "\n";
    }
}

int main(int argc, char const *argv[]) {
    Graph *G = new Graph();
    construct(G);
    dijkstra(G, 0);
    print_node(G);
    return 0;
}
