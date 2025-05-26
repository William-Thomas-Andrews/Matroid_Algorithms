// #include "Graph.hpp"
// // #include "Compare.hpp"
// #include <vector>
// #include <iostream>
// #include <algorithm>

// using Partition = int;

// class BipartiteEdge : public Edge {
//     private:
//         Vertex v;
//         Vertex u;
//         Weight weight;
//         Partition v_partition; // Paritition 1 or 2 are the options for v and u
//         Partition u_partition; 
//     public:
//         BipartiteEdge() {}
//         BipartiteEdge(Vertex v1, Vertex v2, Weight w, Partition p1, Partition p2) : v(v1 > v2 ? v1 : v2), u(v1 > v2 ? v2 : v1), weight(w) {
//             if (p1 != 1 and p1 != 2 and p2 != 1 and p2 != 2) throw std::invalid_argument("The first and second partitions specified are not 1 or 2. Bipartite graphs only have 2 partitions.");
//             if (p1 != 1 and p1 != 2) throw std::invalid_argument("The first partition specified is not 1 or 2. Bipartite graphs only have 2 partitions.");
//             if (p2 != 1 and p2 != 2) throw std::invalid_argument("The second partition specified is not 1 or 2. Bipartite graphs only have 2 partitions.");
//             v_partition = p1;
//             u_partition = p2;
//         }
//         Partition get_left_partition() { return v_partition; }
//         Partition get_right_partition() { return u_partition; }
//         void set_left_partition(Partition p1) {
//             if (p1 != 1 or p1 != 2) { throw std::invalid_argument("The partition specified is not 1 or 2. Bipartite graphs only have 2 partitions."); }
//             v_partition = p1;
//         }
//         void set_right_partition(Partition p2) {
//             if (p2 != 1 or p2 != 2) { throw std::invalid_argument("The partition specified is not 1 or 2. Bipartite graphs only have 2 partitions."); }
//             u_partition = p2;
//         }
//         Vertex get_left() { return u; }
//         Vertex get_right() { return v; }
//         std::string get_string() {
//             std::string str = "(" + std::to_string(v) + ":p" + std::to_string(v_partition) + " - " + std::to_string(u) + ":p" + std::to_string(u_partition) + ")" + "(" + std::to_string(weight) + ")";
//             return str;
//         }

//         // Comparison operator <
//         bool operator<(BipartiteEdge e2) {
//             return (weight < e2.get_weight());
//         }

//         // Comparison operator >
//         bool operator>(BipartiteEdge& e2) {
//             return (weight > e2.get_weight());
//         }

//         // Comparison operator ==
//         bool operator==(BipartiteEdge& e2) {
//             return (weight == e2.get_weight());
//         }

//         // Comparison operator !=
//         bool operator!=(BipartiteEdge& e2) {
//             return (weight != e2.get_weight());
//         }
// }; 
// //TODO figure out the inheritance stuff

// // The input set for a Transversal Matroid
// class BipartiteGraph : public Graph {
//     private:
//         // std::vector<BipartiteEdge> edges;
//         std::vector<int> partition_map;
//         // std::vector<Vertex> partition_1;
//         // std::vector<Vertex> partition_2;
//         UnionFind union_set;
//     public:
//         BipartiteGraph() {}
//         BipartiteGraph(int size_1, int size_2) : union_set(UnionFind(size_1 + size_2)) {}
//         BipartiteGraph(std::vector<std::tuple<Vertex, Vertex, Weight, Partition, Partition>> input_data) : union_set(UnionFind(input_data.size())), partition_map(std::vector<int>({-1})) {
//             for (auto x : input_data) {
//                 BipartiteEdge e = BipartiteEdge(std::get<0>(x), std::get<1>(x), std::get<2>(x), std::get<3>(x), std::get<4>(x));
//                 Vertex left = e.get_left();
//                 Vertex right = e.get_right();
//                 // If in the same partition, then the bijection of the transversal between the two partitions is violated
//                 if (partition_map[left] == partition_map[right]) { 
//                     std::cout << "Edge could not be added because Vertex_1 and Vertex_2 are both in the same partition, violating transversal bijection." << std::endl;;
//                     continue;
//                 }
//                 if (left >= partition_map.size()) {
//                     while (partition_map.size() <= left) {
//                         partition_map.push_back(-1);
//                     }
//                 }
//                 if (right >= partition_map.size()) {
//                     while (partition_map.size() <= right) {
//                         partition_map.push_back(-1);
//                     }
//                 }
//                 partition_map[left] = e.get_left_partition();
//                 partition_map[right] = e.get_right_partition();
//                 this->add_element(e);
//                 union_set.union_operation(left, right);
//             }
//         }
//         BipartiteGraph(std::vector<BipartiteEdge> input_data) : union_set(UnionFind(input_data.size())) {
//             for (BipartiteEdge e : input_data) {
//                 Vertex left = e.get_left();
//                 Vertex right = e.get_right();
//                 // If in the same partition, then the bijection of the transversal between the two partitions is violated
//                 if (partition_map[left] == partition_map[right]) { 
//                     std::cout << "Edge could not be added because Vertex_1 and Vertex_2 are both in the same partition, violating transversal bijection." << std::endl;;
//                     continue;
//                 }
//                 if (left >= partition_map.size()) {
//                     while (partition_map.size() <= left) {
//                         partition_map.push_back(-1);
//                     }
//                 }
//                 if (right >= partition_map.size()) {
//                     while (partition_map.size() <= right) {
//                         partition_map.push_back(-1);
//                     }
//                 }
//                 partition_map[left] = e.get_left_partition();
//                 partition_map[right] = e.get_right_partition();
//                 this->add_element(e);
//                 union_set.union_operation(left, right);
//             }
//         }
//         std::string get_string() {
//             std::string str = "";
//             for (auto edge : edges) {
//                 str += edge.get_string() + " ";
//             }
//             str += "\n";
//             return str;
//         }
//         int left_size() {
//             int count = 0;
//             for (int i = 0; i < partition_map.size(); i++) {
//                 if (partition_map[i] == 1) {
//                     count++;
//                 }
//             }
//             return count;
//         }
//         int right_size() {
//             int count = 0;
//             for (int i = 0; i < partition_map.size(); i++) {
//                 if (partition_map[i] == 2) {
//                     count++;
//                 }
//             }
//             return count;
//         }

//         // const std::vector<BipartiteEdge>& get_data() {
//         //     return edges;
//         // }

//         // Matroid functions begin --------------------------------------------------------------------------------------------------
//         void min_sort() {
//             std::sort(edges.begin(), edges.end(), MinCompare<BipartiteEdge>{});
//         }

//         void max_sort() {
//             std::sort(edges.begin(), edges.end(), MaxCompare<BipartiteEdge>{});
//         }

//         bool not_empty() {
//             return (!edges.empty());
//         }

//         BipartiteEdge top() {
//             if (edges.empty()) { throw std::runtime_error("Cannot get first element of an empty graph"); }
//             else {
//                 return edges[edges.size()-1];
//             }
//         }

//         // If adding Edge e does not create a cycle then it will return true
//         bool is_independent(BipartiteEdge& e) {
//             // If both sides of the edge are in the same partition, 
//             // then it creates a cycle and we return false because adding 'e' is not valid if we want to keep the graph acyclic.
//             // Otherwise return true because both parititions are disjoint
//             return (!(union_set.find_operation(e.get_left()) == union_set.find_operation(e.get_right())));
//         }   

//         void add_element(BipartiteEdge e) {
//             edges.push_back(e);
//             union_set.union_operation(e.get_left(), e.get_right());
//         }

//         void pop() {
//             edges.pop_back();
//         }
//         // Matroid functions end ---------------------------------------------------------------------------------------------------------


//         friend std::ostream& operator<<(std::ostream& os, BipartiteGraph& G);
// };

// std::ostream& operator<<(std::ostream& os, BipartiteGraph& G) {
//     os << G.get_string();
//     return os;
// }
