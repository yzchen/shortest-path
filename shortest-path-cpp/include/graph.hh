#ifndef _GRAGH_H_
#define _GRAGH_H_

#include <vector>
#include <utility>

const int int_max = 2147483647;

typedef struct Node {
    // for adjacency list
    char value;
    std::vector<std::pair<struct Node *, int> > neighbors;

    // for algorithms
    int d;
    Node *previous;

    // for spfa algorithm, if node in queue, then mask = 1, else mask = 0
    int mask;
} Node;

typedef struct Graph {
    std::vector<Node *> nodes;
} Graph;

struct compare_min_first{
    bool operator ()(Node *a, Node *b){
        return a->d > b->d; //最小值优先
    }
};

void print_node(Graph *G);

void Dijkstra(Graph *G, int source);
void Spfa(Graph *G, int source);

#endif
