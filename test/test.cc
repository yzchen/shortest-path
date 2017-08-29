#include "graph.hh"
#include <utility>

using namespace std;

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

int main(int argc, char const *argv[]) {
    Graph *G = new Graph();
    construct(G);
    Dijkstra(G, 0);
    print_node(G);
    return 0;
}
