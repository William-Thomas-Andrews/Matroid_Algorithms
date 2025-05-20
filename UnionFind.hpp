#include <vector>
using Vertex = unsigned long;

class UnionFind {
    private:
        std::vector<Vertex> union_data;
    public:
        UnionFind() {}
        UnionFind(int size) : union_data(size, -1) {}
        
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
};