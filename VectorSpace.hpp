#include <iostream>
#include <vector>
#include <memory>
// #include "Vector.hpp"
#include "Matrix.hpp"

class VectorSpace {
    private:
        Vector standard_basis;
        int dimension;
        std::vector<std::unique_ptr<Matrix>> matrix_collection;

    public:
        VectorSpace() : dimension(0), standard_basis(Vector(std::vector<double>{0})) {}
        VectorSpace(int input_dimension) : dimension(0), standard_basis(Vector(std::vector<double>(1, input_dimension))) {

        }

        void add_matrix(Matrix A) {
            if (A.get_rows() > dimension) { throw std::invalid_argument("The input matrix cannot have a larger dimension than the vector space"); }
            // std::unique_ptr<Matrix> p(A);
            matrix_collection.push_back(std::unique_ptr<Matrix>(std::make_unique<Matrix>(A)));
        }

        // 'dim' operator
        friend int dim(VectorSpace V);
};

int dim(VectorSpace V) {
    return V.dimension;
}