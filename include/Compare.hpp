#include <iomanip>

template <typename ELEMENT_TYPE>
class MinCompare {
    public:
        bool operator()(ELEMENT_TYPE a, ELEMENT_TYPE b) {
            // if (a > b) {
            //     return true;
            // }
            // return false;
            return (a > b);
        }
};

template <typename ELEMENT_TYPE>
class MaxCompare {
    public:
        bool operator()(ELEMENT_TYPE a, ELEMENT_TYPE b) {
            // if (a < b) {
            //     return true;
            // }
            // return false;
            return (a < b);
        }
};