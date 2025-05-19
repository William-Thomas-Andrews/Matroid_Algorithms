#include "VectorSpace.hpp"
#include "Graph.hpp"
#include "Oracle.hpp"

// TODO: overload first, then use templates
class Matroid {
    private:
        Oracle oracle;
        Graph G;
        Matrix A;
        int matroid_type;
    public:
        Matroid(Graph graph) : G(graph), matroid_type(1) {}
        Matroid(Matrix matrix) : A(matrix), matroid_type(2) {}

        auto optimize_matroid() {
            std::sort_heap(edge_set);
            for (int i = 0; i < edge_set.size(); i++) {
                if (oracle.independent(A, e)) {
                    add e to new set
                }
                else {
                    pop e
                }
            }
            return set;
        }
};