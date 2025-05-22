#include <iomanip>

template <typename ELEMENT_TYPE>
class MinCompare {
    public:
        bool operator()(ELEMENT_TYPE a, ELEMENT_TYPE b) {
            if (a > b) {
                return true;
            }
            return false;
        }
};

template <typename ELEMENT_TYPE>
class MaxCompare {
    public:
        bool operator()(ELEMENT_TYPE a, ELEMENT_TYPE b) {
            // std::cout << "weight 1: " << std::setprecision(17) << a.get_weight() << std::endl;
            // std::cout << "weight 2: " << std::setprecision(17) << b.get_weight() << std::endl;
            if (a < b) {
                return true;
            }
            return false;
        }
};