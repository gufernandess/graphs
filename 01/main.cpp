#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <queue>

#include "../graph/Graph.h"

using namespace std;

/**
 * Criei uma função auxiliar para contar quantos grafos existem no arquivo,
 * essa informação é necessária, visto que preciso saber quantas vezes o
 * programa têm de ser executado dentro do arquivo e quantos grafos 
 * existem no mesmo.
 * 
 * Basicamente percorro o arquivo linha por linha e verifico se a linha
 * segue o padrão de criação de um grafo, sendo respectivamente o
 * número de vértices, um espaço e o número de arestas. Se a
 * linha possuir essas características, é um indicativo de
 * que há a criação de um novo grafo, assim eu incremento
 * o contador.
*/

int graph_counting(const std::string& file_name) {
    ifstream file(file_name);
    string line;
    int couting = 0;

    while(getline(file, line)) {
        istringstream stream(line);

        int vertices, edges;

        if(stream >> vertices >> edges && stream.eof()) couting++;
    }

    file.close();

    return couting;
}

/**
 * A ideia é que o grafo seja bipartido, ou seja, que seja possível
 * dividir os vértices em dois conjuntos disjuntos, de forma que
 * todos os vértices de um conjunto não tenham arestas com
 * vértices do mesmo conjunto.
 * 
 * Na função is_bipartite, eu crio um vetor de cores, onde cada
 * vértice recebe uma cor, e a partir disso eu atribuo cores
 * aos vértices e pinto seus vizinhos com a cor oposta,
 * realizando uma busca em largura para percorrer
 * todos os vértices do grafo. Se em algum momento
 * eu encontrar um vértice que possui um vizinho
 * com a mesma cor, o grafo não é bipartido.
*/

bool is_bipartite(Graph& graph, int initial_vertice) {
    int number_of_vertices = graph.get_number_of_vertices();

    vector<char> colors(number_of_vertices, ' ');
    colors[initial_vertice] = 'R';

    queue<int> queue_of_vertices;
    queue_of_vertices.push(initial_vertice);

    while(!queue_of_vertices.empty()) {
        int current_vertice = queue_of_vertices.front();

        queue_of_vertices.pop();

        for(auto neighbor : graph.neighbors(current_vertice)) {
            if(colors[neighbor.get_destiny()] == ' ') {
                colors[neighbor.get_destiny()] = (colors[current_vertice] == 'R') ? 'B' : 'R';
                queue_of_vertices.push(neighbor.get_destiny());
            }
            
            else if(colors[neighbor.get_destiny()] == colors[current_vertice]) return false;
        }
    }

    return true;
}

/**
 * A função is_bipartite_graph percorre todos os vértices do grafo
 * e verifica se cada um deles é bipartido, se algum deles não for
 * bipartido, o grafo não é bipartido.
 * 
 * Basicamente ele realiza a operação do is_bipartite para cada
 * vértice do grafo.
*/

bool is_bipartite_graph(Graph& graph) {
    int number_of_vertices = graph.get_number_of_vertices();

    for(int i = 0; i < number_of_vertices; ++i) {
        if(!is_bipartite(graph, i)) return false;
    }
    
    return true;
}


int main() {
    fstream file;
    file.open("grafos.txt");

    int number_of_graphs = graph_counting("grafos.txt");
    
    while(number_of_graphs > 0) {
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

        cout << (is_bipartite_graph(graph) ? "SIM" : "NAO") << endl;
        number_of_graphs--;
    }

    file.close();

    return 0;
}