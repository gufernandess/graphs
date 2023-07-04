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
 * e comecei escolhendo uma cor para o primeiro vértice.
 * 
 * Também utilizei uma fila para armazenar os vértices que já foram
 * coloridos.
 * 
 * Assim, para cada vértice percorrido, verifico se seus vizinhos
 * já foram coloridos, se não, atribuo a cor oposta a do vértice
 * atual e adiciono o vértice na fila. Caso o vértice já tenha
 * sido colorido, verifico se a cor do vértice atual é igual
 * a do vértice vizinho, se sim, então não é possível
 * colorir esse grafo com apenas duas cores.
*/

bool valid_coloring(Graph& graph) {
    vector<char> colors(graph.get_number_of_vertices(), ' ');
    colors[0] = 'R';

    queue<int> queue;
    queue.push(0);

    while(!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for(auto edge : graph.neighbors(current)) {
            if(colors[edge.get_destiny()] == ' ') {
                if(colors[current] == 'R') colors[edge.get_destiny()] = 'B';

                else colors[edge.get_destiny()] = 'R';

                queue.push(edge.get_destiny());
            }
            
            else if(colors[edge.get_destiny()] == colors[current]) {
                return false;
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

        cout << (valid_coloring(graph) ? "SIM" : "NAO") << endl;
        number_of_graphs--;
    }

    file.close();

    return 0;
}