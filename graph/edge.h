#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <iostream>
#include <limits>
#include <sstream>

class Edge {
private:
    int source;
    int destiny;
    double weight;

public:
    Edge(int source, int destiny, double weight = 1.0) : source(source), destiny(destiny), weight(weight) {}

    // Construtor para arestas falsas.

    Edge() : source(-1), destiny(-1), weight(std::numeric_limits<double>::infinity()) {}

    // Construtor de cópia.

    Edge(const Edge& other) : source(other.source), destiny(other.destiny), weight(other.weight) {}

    // Sobrecarga do operador de igualdade para arestas.

    bool operator==(const Edge& other) const {
        return source == other.source && destiny == other.destiny;
    }

    int get_destiny() const { return destiny; }

    int get_source() const { return source; }

    double get_weight() const { return weight; }

    std::string to_string() const {
        std::stringstream stream;
        stream << "(" << source << ", " << destiny << ", " << weight << ")";

        return stream.str();
    }

    // Sobrecarga do operador de inserção em stream.

    friend std::ostream& operator<<(std::ostream& ostream, const Edge& edge) {
        ostream << "(" << edge.source << ", " << edge.destiny << ", " << edge.weight << ")";

        return ostream;
}



};

#endif