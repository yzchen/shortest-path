#ifndef _GRAGH_H_
#define _GRAGH_H_

#include <vector>
#include <utility>

typedef struct Node {
    // for adjacency list
    std::string value;
    std::vector<std::pair<struct Node *, double> > neighbors;

    // for algorithms
    double d;
    Node *previous;

    // for spfa algorithm, if node in queue, then mask = 1, else mask = 0
    int mask;
} Node;

typedef struct Graph {
    std::vector<Node *> nodes;
    int nNodes;
    int nEdges;
} Graph;

struct compareMinFirst {
    bool operator ()(Node *a, Node *b){
        return a->d > b->d; //最小值优先
    }
};

// tools.cc
void printPath(Graph *G);
void printGraph(Graph *G);
void clear(Graph *G);
Node *findMin(const std::vector<Node *> &v, int &index);
void preSort(Graph *G);
Graph *readFile(std::string fileName);

// shortest-path.cc
void Dijkstra(Graph *G, int source);
void DijkstraHeap(Graph *G, int source);
void Spfa(Graph *G, int source);

#endif
