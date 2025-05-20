#include <vector>
#include <iostream>
using Vertex = unsigned long;

class UnionFind {
    private:
        std::vector<int> union_data;
    public:
        UnionFind() {}
        UnionFind(int size) : union_data(size, -1) {}

        // TODO: MAKE MORE DYNAMICALLY SIZED
        
        void union_operation(Vertex v, Vertex u) {
            Vertex v_index = find_operation(v);
            Vertex u_index = find_operation(u);
            if (union_data[v_index] < union_data[u_index]) {
                union_data[v_index] += union_data[u_index];
                union_data[u] = v_index;
            }
            if (union_data[v_index] >= union_data[u_index]) {
                union_data[u_index] += union_data[v_index];
                union_data[v] = u_index;
            }
        }

        Vertex find_operation(Vertex v) {
            if (union_data[v] < 0) {
                return v;
            }
            else {
                return find_operation(union_data[v]);
            }
        }

        void print_data() {
            for (int i = 0; i < union_data.size(); i++) {
                std::cout << "(" << i << ", " << union_data[i] << ") ";
            }
            std::cout << std::endl;
        }

        std::string get_string() {
            std::string str = "";
            std::cout << union_data.size() << std::endl;
            for (int i = 0; i < union_data.size(); i++) {
                str += "(";
                str += std::to_string(i);
                str += ", ";
                str += std::to_string(union_data[i]);
                str += ") ";
            }
            return str;
        }

        friend std::ostream& operator<<(std::ostream& os, UnionFind union_set);
};

std::ostream& operator<<(std::ostream& os, UnionFind union_set) {
    os << union_set.get_string();
    return os;
}