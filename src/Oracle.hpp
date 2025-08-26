#pragma once

template <class SET, typename ELEMENT>
class Oracle {
    public:
        Oracle();
        bool independent(SET S, ELEMENT e);
};