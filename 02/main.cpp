#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <queue>

#include <algorithm>
#include <iterator>

#include "../graph/Graph.h"

using namespace std;

/**
 * Implementei uma função auxiliar que me retorna o número de atores
 * envolvidos (sem as repetições), ou seja, o número de vértices do
 * grafo.
 * 
 * Necessito dessa informação para a criação do grafo já com os
 * vértices.
*/

int read_vertices_number(const string& file_name) {
    ifstream file(file_name);
    string line;

    vector<string> actors;
    
    while(getline(file, line)) {
        istringstream new_line(line);
        string element;

        int counter = 0;
        
        while(getline(new_line, element, ';')) {
            if(counter == 0 || counter == 2) {
                if(find(actors.begin(), actors.end(), element) == actors.end()) {
                    actors.push_back(element);
                }
            }
            
            counter++;
        }
    }
    
    file.close();

    return actors.size();
}

/**
 * Devido a incapacidade de representar vértices e arestas como qualquer tipo de dado
 * que não seja inteiro, foi necessário criar dois vetores de strings, uma para os
 * atores e outra para os filmes. A ideia é mapear os índices desses vetores com
 * os índices dos vértices e arestas do grafo, assim podemos localizar atores e
 * filmes a partir de seus índices.
 * 
 * No caso dos atores, insiro o nome do ator no vetor de atores caso ele ainda não
 * esteja presente, caso o mesmo já esteja presente, não é necessária a inserção.
 * 
 * No caso dos filmes, insiro o nome do filme no vetor de filmes normalmente, pois
 * não há repetições de filmes.
 * 
 * Após a inserção dos atores e filmes nos vetores, é criada uma aresta que liga
 * ambos, sendo o peso da aresta o filme que conecta-os, e essa
 * aresta é inserida no grafo.
 * 
 * Vale ressaltar que a cada iteração, mantenho uma track do indice do ator e do
 * filme atual, para que eu possa criar a aresta que liga os atores.
*/

void create_graph(const string& file_name, Graph& graph, vector<string>& actors, vector<string>& movies) {
    ifstream file(file_name);
    string line;
    
    while(getline(file, line)) {
        istringstream new_line(line);
        string element;

        int counter, current_actor, current_movie;

        counter = current_actor = current_movie = 0;
        
        while(getline(new_line, element, ';')) {
            if(counter == 0) {
                if(find(actors.begin(), actors.end(), element) == actors.end()) {
                    actors.push_back(element);
                }
                    
                current_actor = distance(actors.begin(), find(actors.begin(), actors.end(), element));

            }

            if(counter == 2) {
                if(find(actors.begin(), actors.end(), element) == actors.end()) actors.push_back(element);

                Edge edge(current_actor, distance(actors.begin(), find(actors.begin(), actors.end(), element)), current_movie);

                graph.insert(edge);
            }
            
            else if(counter == 1) {
                
                    movies.push_back(element);
                    current_movie = distance(movies.begin(), find(movies.begin(), movies.end(), element));
                
            }
            
            counter++;
        }
    }
    
    file.close();
}

/**
 * A função que calcula o número de Bacon de um ator é uma BFS que
 * percorre o grafo a partir do ator passado como parâmetro, e
 * retorna o número de atores que estão no caminho entre
 * o ator passado como parâmetro e o ator Kevin Bacon.
 * 
 * Para isso, utilizo uma fila de atores, e um vetor de visitados.
 * 
 * A cada iteração, retiro o ator da fila, e verifico se o mesmo é
 * o ator Kevin Bacon, caso seja, retorno o número de atores que
 * estão no caminho entre o ator passado como parâmetro e o ator
 * Kevin Bacon.
 * 
 * Caso o ator não seja o ator Kevin Bacon, incremento o número de
 * atores que estão no caminho entre o ator passado como parâmetro
 * e o ator Kevin Bacon, e adiciono os atores adjacentes ao ator
 * atual na fila, caso os mesmos ainda não tenham sido visitados.
 * 
 * O índice do Kevin nesse caso é 0, pois o mesmo é o primeiro ator
 * a ser inserido no grafo, e o índice do ator passado como parâmetro
 * é obtido através da função distance, que retorna a distância entre
 * o início do vetor e o elemento passado como parâmetro.
 * 
*/

int bacon_number(const Graph& graph, const vector<string>& actors, const vector<string>& movies, const string& actor) {
    int actor_index = distance(actors.begin(), find(actors.begin(), actors.end(), actor));
    int number;

    if(actor_index != actors.size()) {
        number = 0;

        queue<int> actors_queue;
        vector<bool> visited(graph.get_number_of_vertices(), false);

        actors_queue.push(actor_index);
        visited[actor_index] = true;

        while(!actors_queue.empty()) {
            int current_actor = actors_queue.front();
            actors_queue.pop();

            if(current_actor != actor_index) number++;

            for(const Edge& edge : graph.neighbors(current_actor)) {
                int neighbor = edge.get_destiny();

                if(!visited[neighbor]) {
                    visited[neighbor] = true;

                    actors_queue.push(neighbor);
                }
            }
        }
    }

    return number;
}

/**
 * Tratei de ordenar os atores em ordem alfabética junto de seus
 * números de Bacon e filmes, como pedido na questão.
*/

int main() {
    int number_of_vertices = read_vertices_number("grafos.txt");

    Graph graph(number_of_vertices, false);

    vector<string> actors;
    vector<string> movies;

    create_graph("grafos.txt", graph, actors, movies);

    vector<pair<string, int>> actor_data;

    for(int i = 0; i < number_of_vertices; i++) {
        int number = bacon_number(graph, actors, movies, actors[i]);
        actor_data.push_back(make_pair(actors[i], number));
    }

    sort(actor_data.begin(), actor_data.end());

    for(const auto& pair : actor_data) {
        auto actor_index = distance(actors.begin(), find(actors.begin(), actors.end(), pair.first));

        cout << "O numero de Bacon de " << pair.first << " é " << pair.second << " pelo filme "
        << (pair.first == "Kevin Bacon" ? "" : movies[graph.neighbors(actor_index).front().get_weight()]) << '\n';
    }

    return 0;
}