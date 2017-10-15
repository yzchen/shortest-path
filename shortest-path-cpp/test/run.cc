#include <utility>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <dirent.h>

#include "graph.hh"

using namespace std;

void run(string fileName){
    std::ofstream outfile("output/output.csv", std::ios::out | std::ios::app);
    clock_t start, end;

    //Dijkstra
    Graph *G = read_file(fileName);
    start = clock();
    Dijkstra(G, 0);
    end = clock();

    double t1 = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Dijkstra algorithm's time is : " << t1 << " s" << "\n" << endl;

    // Spfa
    G = read_file(fileName);
    start = clock();
    Spfa(G, 0);
    end = clock();

    double t2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Spfa algorithm's time is : " << t2 << " s" << "\n" << endl;

    outfile << fileName << "," << G->nNodes << "," << G->nEdges << "," << t1 << "," << t2 << "\n";

    outfile.close();
}

void get_fileNames(string directory, std::vector<std::string> &v) {
    std::cout << "files in data/ : " << '\n';
    DIR *dir = opendir(directory.c_str());
    struct dirent *iterator;

    if (dir != NULL) {
        while (iterator = readdir(dir)) {
            string fileName(iterator->d_name);
            if (fileName.compare(".") != 0 && fileName.compare("..") != 0) {
                std::cout << "    " << fileName << '\n';
                v.push_back(iterator->d_name);
            }
        }
    }
    std::cout << endl;
}

int main(int argc, char const *argv[]) {
    std::ofstream outfile("output/output.csv", std::ios::out);
    outfile << "fileName,nNodes,nEdges,Dijkstra,Spfa" << "\n";
    outfile.close();

    string folder("data/");

    std::vector<string> v;
    get_fileNames(folder, v);

    for (std::vector<string>::iterator vit = v.begin(); vit != v.end(); vit++){
        run(folder + *vit);
    }

    return 0;
}
