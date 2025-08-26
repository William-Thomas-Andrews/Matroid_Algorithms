#include <iomanip>
#include "Compare.hpp"

template <typename ELEMENT>
bool MinCompare<ELEMENT>::operator()(ELEMENT a, ELEMENT b) {
    return (a > b);
}

template <typename ELEMENT>
bool MaxCompare<ELEMENT>::operator()(ELEMENT a, ELEMENT b) {
    return (a < b);
}