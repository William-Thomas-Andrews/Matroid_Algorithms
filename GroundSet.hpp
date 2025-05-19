#include "Graph.hpp"
#include "Matrix.hpp"

class GroundSet {
    private:
        Graph G;
        Matrix A;
        std::unique_ptr<
    public:
        GroundSet() {}
        GroundSet(Graph graph) : G(graph) {
            
        } 
        GroundSet(Matrix matrix) : A(matrix) {

        }

        auto get_ground_ptr() {
            
        }
};