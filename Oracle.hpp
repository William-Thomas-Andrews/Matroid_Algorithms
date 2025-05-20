// #include "Matrix.hpp"
// #include "Graph.hpp"


template <class SET_TYPE, typename ELEMENT_TYPE>
class Oracle {
    private:
    public:
        Oracle() {}
        
        bool independent(SET_TYPE S, ELEMENT_TYPE e) {
            if (S.is_independent(e)) {
                return true;
            }
            return false;
        }
};