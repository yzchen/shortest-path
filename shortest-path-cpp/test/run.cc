#include <utility>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <dirent.h>

#include "graph.hh"

using namespace std;

void run(string fileName) {
    std::ofstream outfile("output/output.csv", std::ios::out | std::ios::app);
    clock_t start, end;

    //Dijkstra with Unordered Array
    Graph *G = readFile(fileName);
    if (!G) {
        return;
    }

    start = clock();
    DijkstraArray(G, 0);
    end = clock();

    double t1 = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "DijkstraArray algorithm's time is : " << t1 << " s" << "\n" << endl;

    //Dijkstra
    G = readFile(fileName);
    if (!G) {
        return;
    }

    start = clock();
    Dijkstra(G, 0);
    end = clock();

    double t2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "DijkstraHeap algorithm's time is : " << t2 << " s" << "\n" << endl;

    // Spfa
    G = readFile(fileName);
    if (!G) {
        return;
    }

    start = clock();
    Spfa(G, 0);
    end = clock();

    double t3 = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Spfa algorithm's time is : " << t3 << " s" << "\n" << endl;

    outfile << fileName << "," << G->nNodes << "," << G->nEdges << "," << t1 << "," << t2 << "," << t3 << "\n";

    outfile.close();
}

void getFileNames(string directory, std::vector<std::string> &v) {
    std::cout << "files in data/ : " << '\n';
    DIR *dir = opendir(directory.c_str());
    struct dirent *iterator;

    if (dir != NULL) {
        while (iterator = readdir(dir)) {
            string fileName(iterator->d_name);
            if (fileName.compare(".") != 0 && fileName.compare("..") != 0 && fileName.compare(".gitkeep") != 0) {
                std::cout << "    " << fileName << '\n';
                v.push_back(iterator->d_name);
            }
        }
    }
    std::cout << endl;
}

int main(int argc, char const *argv[]) {
    std::ofstream outfile("output/output.csv", std::ios::out);
    outfile << "fileName,nNodes,nEdges,DijkstraArray(s),DijkstraHeap(s),Spfa(s)" << "\n";
    outfile.close();

    string folder("data/");

    std::vector<string> v;
    getFileNames(folder, v);

    for (std::vector<string>::iterator vit = v.begin(); vit != v.end(); vit++){
        run(folder + *vit);
    }

    return 0;
}
