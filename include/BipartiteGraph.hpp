// #include "Graph.hpp"
// #include <vector>

// // The input set for a Transversal Matroid
// class BipartiteGraph : Graph {
//     private:
//         std::vector<Edge> edges;
//         UnionFind union_set;
//     public:
//         BipartiteGraph() {}
//         BipartiteGraph(int size) : union_set(UnionFind(size)) {}
//         BipartiteGraph(std::vector<std::tuple<Vertex, Vertex, Weight>> input_data) : union_set(UnionFind(input_data.size())) {
//             for (auto x : input_data) {
//                 Edge e = Edge(std::get<0>(x), std::get<1>(x), std::get<2>(x));
//                 this->add_element(e);
//                 union_set.union_operation(e.get_left(), e.get_right());
//             }
//         }


// };