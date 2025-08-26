#pragma once

#include <vector>
#include <iostream>

using Vertex = unsigned long;

class UnionFind {
    private:
        std::vector<int> union_data;
    public:
        UnionFind() {}
        UnionFind(int size);
        
        void union_operation(Vertex v, Vertex u);
        Vertex find_operation(Vertex v);

        void print_data();
        std::string get_string();

        friend std::ostream& operator<<(std::ostream& os, UnionFind union_set);
};

std::ostream& operator<<(std::ostream& os, UnionFind union_set);