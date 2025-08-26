#include "Oracle.hpp"

template <class SET, typename ELEMENT>
Oracle<SET, ELEMENT>::Oracle() {}

template <class SET, typename ELEMENT>
bool independent(SET S, ELEMENT e) {
    return (S.is_independent(e));
}