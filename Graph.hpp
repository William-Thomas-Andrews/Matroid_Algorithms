#include <iostream>
#include <vector>
#include "UnionFind.hpp"

using Vertex = unsigned long;
using Weight = unsigned long;

class Edge {
    private:
        Vertex v;
        Vertex u;
        Weight weight;
    public:
        Edge(Vertex v1, Vertex v2, Weight w) : v(v1 > v2 ? v1 : v2), u(v1 > v2 ? v2 : v1), weight(w) {}

        std::string get_string() {
            std::string str = "(";
            str += std::to_string(v);
            str += " - ";
            str += std::to_string(u);
            str += ")";
            return str;
        }

        Vertex get_left() {
            return v;
        }

        Vertex get_right() {
            return u;
        }

        Weight get_weight() {
            return weight;
        }

        void set_weight(Weight w) {
            weight = w;
        }

        friend std::ostream& operator<<(std::ostream& os, Edge& e);
};

std::ostream& operator<<(std::ostream& os, Edge& e) {
    os << e.get_string();
    return os;
}

class Graph {
    private:
        std::vector<Edge> edges;
    public:
        Graph() {}
        Graph(std::vector<std::tuple<Vertex, Vertex, Weight>> input_data) {
            for (auto x : input_data) {
                Edge e = Edge(std::get<0>(x), std::get<1>(x), std::get<2>(x));
                this->add_edge(e);
            }
         }

         std::vector<Edge>& get_edges() {
            return edges;
         }

        void add_edge(Edge& e) {
            edges.push_back(e);
        }

        // If adding Edge e does not create a cycle then it will return true
        bool is_not_cycle(Edge& e) {
            if (e.get_left)
        }   
};