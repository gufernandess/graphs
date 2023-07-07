#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../graph/Graph.h"

using namespace std;

int main() {

    fstream file;
    file.open("grafos.txt");

    int number_of_vertices, number_of_edges;

    file >> number_of_vertices >> number_of_edges;

    Graph graph(number_of_vertices, false);

    int count { number_of_edges };

        while(count > 0) {
            int source, destiny;

            file >> source >> destiny;

            graph.insert(Edge(source, destiny));

            count--;
        }

    file.close();

    return 0;
}