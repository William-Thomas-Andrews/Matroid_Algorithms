#include <iostream>
// #include <vector>
// #include <memory>
// #include "Vector.hpp"
#include "Matrix.hpp"

class VectorSpace {
    private:
        Matrix standard_basis;
        int dimension;
        std::vector<std::unique_ptr<Matrix>> matrix_collection;

    public:
        VectorSpace() : dimension(0) {
            standard_basis = Matrix(0, 1, 1);
        }
        VectorSpace(int input_dimension) : dimension(input_dimension) {
            standard_basis = Matrix(0, input_dimension, input_dimension);
            for (int i = 0, j = 0; i < dimension; i++, j++) {
                standard_basis(i, j) = 1;
            }
        }

        void add_matrix(Matrix& A) {
            if (A.get_rows() > dimension) { throw std::invalid_argument("The input matrix cannot have a larger dimension than the vector space"); }
            std::unique_ptr<Matrix> ptr = std::make_unique<Matrix>(A);
            matrix_collection.push_back(std::move(ptr));
        }

        void print_standard_basis() {
            std::cout << standard_basis << std::endl;
        }

        Matrix& get_matrix(int index) {
            if (index >= dimension or index < 0) { throw std::invalid_argument("Index out of bounds"); }
            return *matrix_collection[index];
        }

        bool check_linear_independence(Matrix& A, Vector& v) {
            if (A.is_linearly_independent(v)) {
                return true;
            }
            return false;
        }

        // 'dim' operator
        friend int dim(const VectorSpace& V);
};

int dim(const VectorSpace& V) {
    return V.dimension;
}