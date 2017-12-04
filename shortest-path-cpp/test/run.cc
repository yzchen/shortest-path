#include <utility>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <dirent.h>

#include "graph.hh"

using namespace std;

vector<string> splitString(string data, char splitCh) {
    vector<string> v;

    string tmp("");
    for (string::iterator it = data.begin(); it != data.end(); ++it) {
        if (*it == splitCh) {
            v.push_back(tmp);
            tmp = "";
        } else {
            tmp.push_back(*it);
        }
    }
    v.push_back(tmp);

    return v;
}

void run(string fileName, int dataset) {
    std::ofstream outfile("output/output_" + to_string(dataset) + ".csv", std::ios::out | std::ios::app);
    clock_t start, end;

    //Dijkstra
    Graph *G = readFile(fileName);
    if (!G) {
        return;
    }

    start = clock();
    DijkstraHeap(G, 0);
    end = clock();

    double t1 = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Dijkstra Normal Heap algorithm's time is : " << t1 << " s" << "\n" << endl;

    //Dijkstra
    G = readFile(fileName);
    if (!G) {
        return;
    }

    start = clock();
    Dijkstra(G, 0);
    end = clock();

    double t2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Dijkstra Pairing Heap algorithm's time is : " << t2 << " s" << "\n" << endl;

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

    vector<string> filePaths = splitString(fileName, '/');
    string pureFileName = filePaths[filePaths.size() - 1];
    outfile << pureFileName << "," << G->nNodes << "," << G->nEdges << "," << t1 << "," << t2 << "," << t3 << "\n";

    outfile.close();
}

void getSubfolders(string directory, vector<string> &v) {
    std::cout << "files in data/ : " << '\n';
    DIR *dir = opendir(directory.c_str());
    struct dirent *iterator;

    if (dir != NULL) {
        while (iterator = readdir(dir)) {
            string subFolder(iterator->d_name);
            if (subFolder.compare(".") != 0 && subFolder.compare("..") != 0 && subFolder.compare(".gitkeep") != 0 && subFolder.compare(".DS_Store") != 0) {
                std::cout << "    " << subFolder << '\n';
                v.push_back(subFolder + "/");
            }
        }
    }
    std::cout << endl;
}

void getFileNames(string directory, vector<string> &v) {
    std::cout << "files in " + directory + "/ : " << '\n';
    DIR *dir = opendir(directory.c_str());
    struct dirent *iterator;

    if (dir != NULL) {
        while (iterator = readdir(dir)) {
            string fileName(iterator->d_name);
            if (fileName.compare(".") != 0 && fileName.compare("..") != 0 && fileName.compare(".gitkeep") != 0 && fileName.compare(".DS_Store") != 0) {
                std::cout << "    " << fileName << '\n';
                v.push_back(fileName);
            }
        }
    }
    std::cout << endl;
}

int main(int argc, char const *argv[]) {
    string folder("data/");

    std::vector<string> folders, v;
    getSubfolders(folder, folders);
    for (int i = 0; i < folders.size(); i++) {
        std::ofstream outfile("output/output_" + to_string(i+1) + ".csv", std::ios::out);
        outfile << "fileName,nNodes,nEdges,DijkstraHeap,DijkstraPairing,Spfa" << "\n";
        outfile.close();
        getFileNames(folder + folders[i], v);

        for (vector<string>::iterator vit = v.begin(); vit != v.end(); vit++){
            run(folder + folders[i] + *vit, i + 1);
        }
    }

    return 0;
}
