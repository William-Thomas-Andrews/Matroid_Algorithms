#include "VectorSpace.hpp"
#include "Graph.hpp"
#include "Oracle.hpp"

template <class SET, typename ELEMENT>
class Matroid {
    private:
        SET ground_set;
        SET solution_set;
        Oracle<SET, ELEMENT> oracle;
    public:
        Matroid() : ground_set(SET()), solution_set(SET()) {}
        Matroid(SET& input_set) : ground_set(SET(input_set)), solution_set(SET()) {}

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