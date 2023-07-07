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
 * Para resolver o problema da coloração de grafos com duas cores,
 * pensei em uma abordagem semelhante a uma busca em largura,
 * onde de forma prática eu atribuo uma cor a um primeiro
 * vértice e atribuo a cor oposta aos seus vizinhos,
 * assim sucessivamente até que todos os vértices
 * sejam coloridos.
 * 
 * Utilizei um vetor para mapear cada vértice a uma determinada cor,
 * e comecei escolhendo uma cor para o primeiro vértice. Também
 * utilizei um vetor para mapear quais vértices já foram
 * visitados, para que não haja repetição de vértices.
 * 
 * Também utilizei uma fila para implementar a busca em largura,
 * onde é retirado o primeiro vértice da fila, que é marcado 
 * como visitado, e seus vizinhos são coloridos com a cor
 * oposta a do vértice atual.
 * 
 * 
 * Assim, para cada vértice percorrido, verifico se seus vizinhos
 * já foram coloridos, se não, atribuo a cor oposta a do vértice
 * atual e adiciono o vértice na fila. Caso o vértice já tenha
 * sido colorido, verifico se a cor do vértice atual é igual
 * a do vértice vizinho, se sim, então é fato que não é
 * possível colorir esse grafo com apenas duas cores.
*/

bool Bicoloration(const Graph& graph) {
    int number_of_vertices = graph.get_number_of_vertices();

    vector<char> colors(number_of_vertices, ' ');
    vector<bool> visited_vertices(number_of_vertices, false);

    for(int i = 0; i < number_of_vertices; i++) {
        if(!visited_vertices[i]) {
            queue<int> queue_of_vertices;
            queue_of_vertices.push(i);
            colors[i] = 'R';

            while(!queue_of_vertices.empty()) {
                int current_vertice = queue_of_vertices.front();
                queue_of_vertices.pop();
                visited_vertices[current_vertice] = true;

                for(const auto& edge : graph.neighbors(current_vertice)) {
                    int neighbor = edge.get_destiny();

                    if(colors[neighbor] == ' ') {
                        if(colors[current_vertice] == 'R') colors[neighbor] = 'B';
                        
                        else if(colors[current_vertice] == 'B') colors[neighbor] = 'R';

                        queue_of_vertices.push(neighbor);
                    }
                    
                    else if(colors[neighbor] == colors[current_vertice]) return false;
                }
            }
        }
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

        cout << (Bicoloration(graph) ? "SIM" : "NAO") << endl;
        number_of_graphs--;
    }

    file.close();

    return 0;
}