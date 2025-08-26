#pragma once

#include "Graph.hpp"
#include "Compare.hpp"
// #include <vector>
// #include <iostream>
// #include <algorithm>

using Partition = int;

// Corresponds to the Edge type for Transversal Matroids
class BipartiteEdge {
    private:
        Vertex v;
        Vertex u;
        Weight weight;
        Partition v_partition; // Paritition 1 or 2 are the options for v and u
        Partition u_partition; 
    public:
        BipartiteEdge();
        BipartiteEdge(Vertex v1, Vertex v2, Weight w, Partition p1, Partition p2);

        Partition get_left_partition();
        Partition get_right_partition();
        Weight get_weight();
        void set_left_partition(Partition p1);
        void set_right_partition(Partition p2);
        Vertex get_left();
        Vertex get_right();
        std::string get_string();
        Vertex other(Vertex t);

        bool operator<(BipartiteEdge e2);
        bool operator>(BipartiteEdge& e2);
        bool operator==(BipartiteEdge& e2);
        bool operator!=(BipartiteEdge& e2);
}; 


// The input set for a Transversal Matroid
class BipartiteGraph {
    private:
        std::vector<std::vector<BipartiteEdge>> edges;
        std::vector<int> partition_map;
        std::vector<Vertex> vertices;
        UnionFind union_set;
    public:
        BipartiteGraph();
        BipartiteGraph(int size_1, int size_2);
        BipartiteGraph(std::vector<std::tuple<Vertex, Vertex, Weight, Partition, Partition>> input_data);
        BipartiteGraph(std::vector<BipartiteEdge> input_data);
        
        std::string get_string();
        int left_size();
        int right_size();
        std::vector<Vertex>& get_vertices();

        // Matroid functions begin --------------------------------------------------------------------------------------------------
        void min_sort();
        void max_sort();
        bool not_empty();
        Vertex top();
        bool is_independent(Vertex& v);
        void add_element(Vertex v);
        void remove_element();
        void pop();
        // Matroid functions end ---------------------------------------------------------------------------------------------------------
        
        bool in(Vertex v);

        std::string get_vertices_string();

        friend std::ostream& operator<<(std::ostream& os, BipartiteGraph& G);
};

std::ostream& operator<<(std::ostream& os, BipartiteGraph& G);
