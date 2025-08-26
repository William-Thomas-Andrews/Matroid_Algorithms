#pragma once

#include <iostream>
// #include <algorithm>
#include "UnionFind.hpp"


using Vertex = unsigned long;
using Weight = unsigned long;

// Corresponds to the Edge type for Graphic Matroids
class Edge {
    private:
        Vertex v;
        Vertex u;
        Weight weight;
    public:
        Edge();
        Edge(Vertex v1, Vertex v2, Weight w);

        std::string get_string();

        const std::string get_string() const ;

        Vertex get_left();
        Vertex get_right();
        Weight get_weight();

        void set_weight(Weight w);

        // Comparison operator <
        bool operator<(Edge& e2);

        // Comparison operator >
        bool operator>(Edge& e2);

        // Comparison operator ==
        bool operator==(Edge& e2);

        // Comparison operator !=
        bool operator!=(Edge& e2);

        friend std::ostream& operator<<(std::ostream& os, Edge& e);
        friend std::ostream& operator<<(std::ostream& os, const Edge& e);
};

std::ostream& operator<<(std::ostream& os, Edge& e);
std::ostream& operator<<(std::ostream& os, const Edge& e);


// The input set for a Graphic Matroid
class Graph {
    private:
        std::vector<Edge> edges;
        UnionFind union_set;
    public:
        Graph();
        Graph(int size);
        Graph(std::vector<std::tuple<Vertex, Vertex, Weight>> input_data);
        Graph(std::vector<Edge> input_data);

        // Matroid functions begin --------------------------------------------------------------------------------------------------
        void min_sort();
        void max_sort();
        bool not_empty();
        Edge top();
        bool is_independent(Edge& e);
        void add_element(Edge e);
        void pop();
        // Matroid functions end ---------------------------------------------------------------------------------------------------------

        std::vector<Edge>& get_data();
        std::string get_string();

        friend std::ostream& operator<<(std::ostream& os, Graph& G);
};

std::ostream& operator<<(std::ostream& os, Graph& G);