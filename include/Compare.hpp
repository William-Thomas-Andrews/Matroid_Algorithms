#include <iomanip>

template <typename ELEMENT>
class MinCompare {
    public:
        bool operator()(ELEMENT a, ELEMENT b) {
            return (a > b);
        }
};

template <typename ELEMENT>
class MaxCompare {
    public:
        bool operator()(ELEMENT a, ELEMENT b) {
            return (a < b);
        }
};