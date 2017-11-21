#include <utility>
#include <string>
#include <ctime>
#include <iostream>

#include "graph.hh"

using namespace std;

void replTest(string fileName) {
    clock_t start, end;

    Graph *G = readFile(fileName);
    if (!G) {
        return;
    }
    printGraph(G);

    start = clock();
    Dijkstra(G, 0);
    end = clock();

    printPath(G);
    cout << "\n" << "DijkstraHeap algorithm's time is : " << ((double)(end - start)) / CLOCKS_PER_SEC << " s" << "\n" << endl;
}

int main(int argc, char const *argv[]) {
    string fileName(argv[1]);
    replTest("data/" + fileName);

    return 0;
}
