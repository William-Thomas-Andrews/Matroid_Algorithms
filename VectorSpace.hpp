#include <iostream>
#include <vector>
#include "Vector.hpp"

class VectorSpace {
    private:
        Vector standard_basis;
        int dimension;

    public:
        VectorSpace() : dimension(0), standard_basis(Vector(std::vector<double>{0})) {}
        VectorSpace(int input_dimension) : dimension(0), standard_basis(Vector(std::vector<double>(1, input_dimension))) {

        }

        // 'dim' operator
        friend int dim(VectorSpace V);
};

int dim(VectorSpace V) {
    return V.dimension;
}