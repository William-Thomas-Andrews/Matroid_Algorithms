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

        SET_TYPE optimize_matroid() {
            // ground_set.min_sort();                 // For minimum basis
            std::cout << ground_set << solution_set << std::endl;
            ground_set.max_sort();                    // For maximum basis
            for (auto v : ground_set.get_data()) {
                std::cout << "weight: " << v.get_weight() << std::endl;
            }
            std::cout << "hiiii" << std::endl;
            while (ground_set.not_empty()) {
                std::cout << ground_set << std::endl;
                std::cout << std::endl;
                ELEMENT_TYPE e = ground_set.top();
                std::cout << e.get_weight() << std::endl;
                if (oracle.independent(solution_set, e)) {
                    solution_set.add_element(e);
                }
                ground_set.pop();
                // std::cout << solution_set << std::endl;
                // std::cout << std::endl << std::endl;
            }
            return solution_set;
        }
};