#include "VectorSpace.hpp"
#include "Graph.hpp"
#include "Oracle.hpp"
// #include "Set.hpp"

template <class SET_TYPE, typename ELEMENT_TYPE>
class Matroid {
    private:
        SET_TYPE ground_set;
        SET_TYPE solution_set;
        Oracle<SET_TYPE, ELEMENT_TYPE> oracle;
    public:
        Matroid() : ground_set(SET_TYPE()), solution_set(SET_TYPE()) {}
        Matroid(SET_TYPE input_set) : ground_set(SET_TYPE(input_set)), solution_set(SET_TYPE(9)) {}

        // MAKE SURE TO COPY GROUND SET NOT CHANGE ACTUAL
        SET_TYPE optimize_matroid() {

            // ground_set.min_sort();
            ground_set.max_sort();
            while (ground_set.not_empty()) {
                        std::cout << "::" << std::endl;
                auto e = ground_set.top();
                            std::cout << ground_set << std::endl;
                if (oracle.independent(solution_set, e)) {
                    std::cout << "::" << std::endl;
                    solution_set.add(e);
                }
                ground_set.pop();
            }
            return solution_set;
        }
};