

template <typename ELEMENT_TYPE>
class MinCompare {
    public:
        bool operator()(ELEMENT_TYPE a, ELEMENT_TYPE b) {
            if (a.get_weight() > b.get_weight()) {
                return true;
            }
            return false;
        }
};

template <typename ELEMENT_TYPE>
class MaxCompare {
    public:
        bool operator()(ELEMENT_TYPE a, ELEMENT_TYPE b) {
            if (a.get_weight() < b.get_weight()) {
                return true;
            }
            return false;
        }
};