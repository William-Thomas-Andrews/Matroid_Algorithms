// #include "Matrix.hpp"
// #include "Graph.hpp"


template <class SET_TYPE, typename ELEMENT_TYPE>
class Oracle {
    private:
    public:
        Oracle() {}
        
        bool independent(SET_TYPE S, ELEMENT_TYPE e) {
            std::cout << "here" << std::endl;
            if (S.is_independent(e)) {
                std::cout << "here" << std::endl;
                return true;
            }
            std::cout << "here" << std::endl;
            return false;
        }

        // bool independent(Graph& G, Edge& e) {
        //     if (G.is_not_cycle(e)) {
        //         return true;
        //     }
        //     return false;
        // }

        // bool independent(Matrix& A, Vector& v) {
        //     if (A.is_linearly_independent(v)) {
        //         return true;
        //     }
        //     return false;
        // }
};