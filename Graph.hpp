#include <iostream>
#include <vector>
#include <algorithm>
#include "UnionFind.hpp"
#include "Compare.hpp"

using Vertex = unsigned long;
using Weight = unsigned long;

// template <typename ELEMENT_TYPE>
// class Compare {
//     public:
//         bool operator()(ELEMENT_TYPE a, ELEMENT_TYPE b) {
//             if (a.get_weight() > b.get_weight()) {
//                 return true;
//             }
//             return false;
//         }
// };

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
            str += "(";
            str += std::to_string(weight);
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
        UnionFind union_set;
    public:
        Graph() {}
        Graph(int size) : union_set(UnionFind(size)) {}
        Graph(std::vector<std::tuple<Vertex, Vertex, Weight>> input_data) : union_set(UnionFind(input_data.size())) {
            for (auto x : input_data) {
                Edge e = Edge(std::get<0>(x), std::get<1>(x), std::get<2>(x));
                this->add(e);
                union_set.union_operation(e.get_left(), e.get_right());
            }
        }

        // Matroid functions --------------------------------------------------------------------------------------------------
        void min_sort() {
            std::sort(edges.begin(), edges.end(), MinCompare<Edge>{});
        }

        void max_sort() {
            std::sort(edges.begin(), edges.end(), MaxCompare<Edge>{});
        }

        bool not_empty() {
            if (edges.empty()) {
                return false;
            }
            return true;
        }

        Edge top() {
            if (edges.empty()) { throw std::runtime_error("Cannot get first element of an empty graph"); }
            else {
                return edges[edges.size()-1];
            }
        }

        // If adding Edge e does not create a cycle then it will return true
        bool is_independent(Edge& e) {
            std::cout << "here2" << std::endl;
            std::cout << e << std::endl;
            std::cout << union_set.find_operation(e.get_left()) << std::endl;
            std::cout << union_set.find_operation(e.get_right()) << std::endl;
            // If both sides of the edge are in the same partition, 
            if (union_set.find_operation(e.get_left()) == union_set.find_operation(e.get_right())) {
                return false; // then it creates a cycle and we return false because adding 'e' is not valid if we want to keep the graph acyclic
            }
            std::cout << "here1" << std::endl;
            return true; // otherwise, return true because both parititions are disjoint
        }   

        void add(Edge e) {
            edges.push_back(e);
            // std::cout << e.get_right() << std::endl;
            // std::cout << union_set << std::endl;
            // std::cout << union_set.find_operation(e.get_left()) << std::endl;
            union_set.union_operation(e.get_left(), e.get_right());
        }

        void pop() {
            edges.pop_back();
        }
        // ------------------------------------------------------------------------------------------------------------------

        const std::vector<Edge>& get_elements() {
            return edges;
        }

        std::string get_string() {
            std::string str = "";
            for (auto edge : edges) {
                str += edge.get_string();
                str += " ";
            }
            str += "\n";
            return str;
        }

        friend std::ostream& operator<<(std::ostream& os, Graph& G);
};

std::ostream& operator<<(std::ostream& os, Graph& G) {
    os << G.get_string();
    return os;
}