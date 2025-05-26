#include "Graph.hpp"

class TransversalMatroid {
    private:
        std::vector<Graph> ground_set;
        std::vector<Graph> used_graphs;
        Graph mapped_graph;
        UnionFind union_set;
        // std::vector<int> matche_indices;
        int coverage = 0;
    public:
        TransversalMatroid() {}
        TransversalMatroid(std::vector<Graph>& input) : ground_set(input) { 

        }

        TransversalMatroid(Graph& input) : mapped_graph(input) { 

        }

        TransversalMatroid(std::vector<Graph>& input_set, Graph& input_elements) : ground_set(input_set), mapped_graph(input_elements) { 

        }

        // Matroid functions begin --------------------------------------------------------------------------------------------------
        void min_sort() {
            std::sort(mapped_graph.get_data().begin(), mapped_graph.get_data().end(), MinCompare<Edge>{});
        }

        void max_sort() {
            std::sort(mapped_graph.get_data().begin(), mapped_graph.get_data().end(), MaxCompare<Edge>{});
        }

        bool not_empty() {
            return (!mapped_graph.get_data().empty() and !ground_set.empty());
        }

        Edge top() {
            if (mapped_graph.get_data().empty()) { throw std::runtime_error("Cannot get first element of an empty graph"); }
            else {
                return mapped_graph.get_data()[mapped_graph.get_data().size()-1];
            }
        }

        // If adding Edge e does not create a cycle then it will return true
        bool is_independent(Edge& e) {
            std::cout << ground_set.size() << std::endl;
            for (int i = 0; i < ground_set.size(); i++) {
                std::cout << "hey" << ground_set[0].get_string() << std::endl;
                for (auto g : ground_set[i].get_data()) {
                    if (e == g) {
                        coverage++;
                        used_graphs.emplace_back(ground_set[i]); // Save that graph
                        ground_set[i] = Graph(); // Eliminate that graph from being accessed again
                        return true;
                    }
                    std::cout << e << g<< std::endl;
                }
            }
            std::cout << "here" << std::endl;
            return false;
        }   

        void add_element(Edge e) {
            mapped_graph.add_element(e);
            union_set.union_operation(e.get_left(), e.get_right());
        }

        void pop() {
            mapped_graph.pop();
        }
        // Matroid functions end ---------------------------------------------------------------------------------------------------------
        

        void add_graph(Graph& G) {
            ground_set.push_back(G);
        }

        int rank() {
            return coverage;
        }

        std::vector<Graph>& get_data() {
            return ground_set;
        }

        std::vector<Graph>& get_used_data() {
            return used_graphs;
        }

        Graph& get_mapped_graph() {
            return mapped_graph;
        }

        std::string get_string() {
            std::string str = "";
            for (int i = 0; i < ground_set.size(); i++) {
                str += "G" + std::to_string(i + 1) + ": ";
                for (auto& e : ground_set[i].get_data()) 
                    str += e.get_string() + " ";
                str += "\n";
            }
            return str;
        }

        

        friend std::ostream& operator<<(std::ostream& os, TransversalMatroid& T);
};

std::ostream& operator<<(std::ostream& os, TransversalMatroid& T) {
    os << T.get_string();
    return os;
}