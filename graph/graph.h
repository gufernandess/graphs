#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <limits>

#include "Edge.h"

using std::list;
using std::vector;
using std::numeric_limits;

class Graph {
private:
    int number_of_vertices;
    int number_of_edges;
    bool is_directed;
    vector<list<Edge>> adjacency_list;

public:
    Graph(int number_of_vertices, bool is_directed) : number_of_vertices(number_of_vertices),
    number_of_edges(0), is_directed(is_directed), adjacency_list(
        vector<list<Edge>>(number_of_vertices, list<Edge>())
    ) {}

    ~Graph() = default;

    int get_number_of_vertices() const { return number_of_vertices; }

    int get_number_of_edges() const { return number_of_edges; }

    bool get_is_directed() const { return is_directed; }

    vector<list<Edge>> get_adjacency_list() const { return adjacency_list; }

    /**
     * Caso a origem ou destino da aresta não existam no grafo,
     * uma exceção é lançada.
     * 
     * Se uma aresta semelhante a mesma já existir no grafo,
     * a nova aresta não é inserida.
     * 
     * Passando por essas condições, a aresta é inserida dentro
     * da lista de adjacências do vértice de origem.
    */

    void insert(const Edge& edge) {
        if(edge.get_source() >= number_of_vertices || edge.get_destiny() >= number_of_vertices) {
            throw std::out_of_range("Aresta inválida.");
        }

        if(!is_edge(edge.get_source(), edge.get_destiny())) {
            adjacency_list[edge.get_source()].push_back(edge);
            
            number_of_edges++;
        }
    }

    /**
     * É feita uma verificação na lista de adjecências que possui
     * a origem em procura do vértice de destino.
     * 
     * Caso a aresta com ambos origem e destino seja encontrada,
     * significa que a tal aresta existe no grafo. 
    */

    bool is_edge(int source, int destiny) const {
        if(source >= number_of_vertices || destiny >= number_of_vertices) {
            throw std::out_of_range("Aresta inválida.");
        }

        for(auto& edge : adjacency_list[source]) {
            if(edge.get_destiny() == destiny) {
                return true;
            }
        }

        return false;
    }

    /**
     * Caso a aresta exista no grafo, ela é retornada.
     * 
     * Caso contrário, uma aresta com peso infinito é retornada.
    */

    Edge get_edge(int source, int destiny) const {
        if(source >= number_of_vertices || destiny >= number_of_vertices) {
            throw std::out_of_range("Aresta inválida.");
        }

        for(auto& edge : adjacency_list[source]) {
            if(edge.get_destiny() == destiny) {
                return edge;
            }
        }

        return Edge(source, destiny, numeric_limits<double>::infinity());
    }

    /**
     * Retorna uma referência para a lista de adjacências de um vértice.
    */

    list<Edge>& neighbors(int source) {
        if(source >= number_of_vertices) {
            throw std::out_of_range("Vértice inválido.");
        }

        return adjacency_list[source];
    }
    
    const list<Edge>& neighbors(int source) const {
        if(source >= number_of_vertices) {
            throw std::out_of_range("Vértice inválido.");
        }

        return adjacency_list[source];
    }

    /** 
     * Retorna um iterator para a primeira aresta adjacente ao vértice especificado.
    */

    list<Edge>::iterator begin(int source) {
        if(source >= number_of_vertices) {
            throw std::out_of_range("Vértice inválido.");
        }

        return adjacency_list[source].begin();
    }

    list<Edge>::const_iterator begin(int source) const {
        if(source >= number_of_vertices) {
            throw std::out_of_range("Vértice inválido.");
        }

        return adjacency_list[source].begin();
    }

    /** Retorna um iterador uma posicão após a última aresta 
     * adjacente ao vértice especificado.
     */

    list<Edge>::iterator end(int source) {
        if(source >= number_of_vertices) {
            throw std::out_of_range("Vértice inválido.");
        }

        return adjacency_list[source].end();
    }

    list<Edge>::const_iterator end(int source) const {
        if(source >= number_of_vertices) {
            throw std::out_of_range("Vértice inválido.");
        }

        return adjacency_list[source].end();
    }

    Graph(const Graph&) = delete;

    Graph& operator=(const Graph&) = delete;

};


#endif