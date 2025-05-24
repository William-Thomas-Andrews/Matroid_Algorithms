#include "Graph.hpp"
#include <vector>

using Partition = int;

class BipartiteEdge : Edge {
    private:
        Vertex v;
        Vertex u;
        Weight weight;
        Partition partition = -1; // Paritition 1 or 2 are the options
    public:
        BipartiteEdge(Vertex v1, Vertex v2, Weight w, Partition p) : v(v1 > v2 ? v1 : v2), u(v1 > v2 ? v2 : v1), weight(w), partition(p != 1 or p != 2 ? -200 : p) {}
        Partition get_partition() { return partition; }
        void set_partition(Partition p) {
            if (p != 1 or p != 2) { throw std::invalid_argument("The partition specified is not 1 or 2. Bipartite graphs only have 2 partitions."); }
            partition = p;
        }
}; //TODO figure out the inheritance stuff

// The input set for a Transversal Matroid
class BipartiteGraph : Graph {
    private:
        std::vector<Edge> edges;
        std::vector<Vertex> partition_1;
        std::vector<Vertex> partition_2;
        UnionFind union_set;
    public:
        BipartiteGraph(std::vector<std::tuple<Vertex, Vertex, Weight, Partition>> input_data) : union_set(UnionFind(input_data.size())) {
            for (auto x : input_data) {
                BipartiteEdge e = BipartiteEdge(std::get<0>(x), std::get<1>(x), std::get<2>(x), std::get<3>(x));
                this->add_element(e);
                union_set.union_operation(e.get_left(), e.get_right());
            }
        }
        BipartiteGraph(std::vector<Edge> input_data) : union_set(UnionFind(input_data.size())) {
            for (Edge e : input_data) {
                this->add_element(e);
                union_set.union_operation(e.get_left(), e.get_right());
            }
        }
        void add_element(BipartiteEdge& e) {
            
        }
};