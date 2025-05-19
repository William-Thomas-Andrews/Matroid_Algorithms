#include "VectorSpace.hpp"
#include "Graph.hpp"
#include "Oracle.hpp"
#include "Set.hpp"

template <class SET_TYPE, typename ELEMENT_TYPE>
class Matroid {
    private:
        Set<SET_TYPE, ELEMENT_TYPE> ground_set;
        Set<SET_TYPE, ELEMENT_TYPE> solution_set;
        Oracle oracle;
    public:
        Matroid() : ground_set(Set<SET_TYPE, ELEMENT_TYPE>()), solution_set(Set<SET_TYPE, ELEMENT_TYPE>()) {}
        Matroid(SET_TYPE input_set) : ground_set(Set<SET_TYPE, ELEMENT_TYPE>(input_set)), solution_set(Set<SET_TYPE, ELEMENT_TYPE>()) {}

        // MAKE SURE TO COPY GROUND SET NOT CHANGE ACTUAL
        SET_TYPE optimize_matroid() {
            // ground_set.sort();
            while (ground_set.not_empty()) {
                auto e = ground_set.top();
                if (oracle.independent(solution_set, e)) {
                    solution_set.add(e);
                }
                ground_set.pop();
            }
            return solution_set;
        }
};