#include "VectorSpace.hpp"
#include "Graph.hpp"
#include "Oracle.hpp"

template <class SET_TYPE, typename ELEMENT_TYPE>
class Matroid {
    private:
        SET_TYPE ground_set;
        SET_TYPE solution_set;
        Oracle<SET_TYPE, ELEMENT_TYPE> oracle;
    public:
        Matroid() : ground_set(SET_TYPE()), solution_set(SET_TYPE()) {}
        Matroid(SET_TYPE& input_set) : ground_set(SET_TYPE(input_set)), solution_set(SET_TYPE()) {}

        SET_TYPE min_optimize_matroid() {
            ground_set.min_sort();                 // For minimum basis
            while (ground_set.not_empty()) {
                ELEMENT_TYPE e = ground_set.top();
                if (oracle.independent(solution_set, e)) solution_set.add_element(e);
                ground_set.pop();
            }
            return solution_set;
        }

        SET_TYPE max_optimize_matroid() {
            ground_set.max_sort();                 // For maximum basis
            while (ground_set.not_empty()) {
                ELEMENT_TYPE e = ground_set.top();
                if (oracle.independent(solution_set, e)) solution_set.add_element(e);
                ground_set.pop();
            }
            return solution_set;
        }
};