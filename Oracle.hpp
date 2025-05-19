#include "Matrix.hpp"
#include "Graph.hpp"


class Oracle {
    private:
    public:
        Oracle() {}
        // Oracle(Graph G) {

        // }

        // Oracle(Matrix A) {

        // }

        bool independent(Graph& G, Edge& e) {
            if (G.is_not_cycle(e)) {
                return true;
            }
            return false;
        }

        bool independent(Matrix& A, Vector& v) {
            if (A.is_linearly_independent(v)) {
                return true;
            }
            return false;
        }
};