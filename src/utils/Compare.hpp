#pragma once

template <typename ELEMENT>
class MinCompare {
    public:
        bool operator()(ELEMENT a, ELEMENT b);
};

template <typename ELEMENT>
class MaxCompare {
    public:
        bool operator()(ELEMENT a, ELEMENT b);
};