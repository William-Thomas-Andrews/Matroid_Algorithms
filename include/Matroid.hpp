#include "VectorSpace.hpp"
// #include "Graph.hpp"
#include "BipartiteGraph.hpp"
// #include "TransversalMatroid.hpp"
#include "PartitionMatroid.hpp"
#include "Oracle.hpp"


// -------------------------------------------------------------------------------------------------- //
// "Matroids take “It’s useful to have multiple perspectives on this thing” to a ridiculous extent."  //
// -------------------------------------------------------------------------------------------------- //


// SET being the type of input set, like Graph, or a Matrix
// ELEMENT being the corresponding element for each set, like Edge for graphs, and Vector for matrices
template <class SET, typename ELEMENT>
class Matroid {
    private:
        SET ground_set;
        SET solution_set;
        Oracle<SET, ELEMENT> oracle;
    public:
        Matroid() : ground_set(SET()), solution_set(SET()) {}
        Matroid(SET& input_set) : ground_set(SET(input_set)), solution_set(SET()) {}
        Matroid(SET& input_set, SET& other_set) : ground_set(SET(input_set)), solution_set(SET(other_set)) {
            while (!(solution_set.get_vertices().empty())) {
                solution_set.remove_element();
            }
        }

        // Note: for sorting, the lists of elements within the sets are sorted in reverse order to account for the necessary reverse order
        // of pushing and popping from the vector

        SET min_optimize_matroid() {
            ground_set.min_sort();                 // For minimum basis
            while (ground_set.not_empty()) {
                ELEMENT e = ground_set.top();
                if (oracle.independent(solution_set, e)) solution_set.add_element(e);
                ground_set.pop();
            }
            return solution_set;
        }

        SET max_optimize_matroid() {
            ground_set.max_sort();                 // For maximum basis
            while (ground_set.not_empty()) {
                ELEMENT e = ground_set.top();
                if (oracle.independent(solution_set, e)) solution_set.add_element(e);
                ground_set.pop();
            }
            return solution_set;
        }

        // TODO Read More on Exchange Property
        ELEMENT matroid_exchange_property(Matroid& M){

        }

        friend SET matroid_intersection(Matroid& M1, Matroid& M2);
        friend SET matroid_union(Matroid& M1, Matroid& M2);
};

// TODO: Implement Matroid Intersection
template <class SET, typename ELEMENT>
SET matroid_intersection(Matroid<SET, ELEMENT>& M1, Matroid<SET, ELEMENT>& M2) {

}

// TODO: Implement Matroid Union
template <class SET, typename ELEMENT>
SET matroid_union(Matroid<SET, ELEMENT>& M1, Matroid<SET, ELEMENT>& M2) {

}