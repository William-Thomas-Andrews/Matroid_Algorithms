#include <iostream>
#include "VectorSpace.hpp"


VectorSpace::VectorSpace() : dimension(0) {
    standard_basis = Matrix(0, 1, 1);
}
VectorSpace::VectorSpace(int input_dimension) : dimension(input_dimension) {
    standard_basis = Matrix(0, input_dimension, input_dimension);
    for (int i = 0, j = 0; i < dimension; i++, j++) {
        standard_basis(i, j) = 1;
    }
}

void VectorSpace::add_matrix(Matrix& A) {
    if (A.get_rows() > dimension) { throw std::invalid_argument("The input matrix cannot have a larger dimension than the vector space"); }
    std::unique_ptr<Matrix> ptr = std::make_unique<Matrix>(A);
    matrix_collection.push_back(std::move(ptr));
}

void VectorSpace::print_standard_basis() {
    std::cout << standard_basis << std::endl;
}

Matrix& VectorSpace::get_matrix(int index) {
    if (index >= dimension or index < 0) { throw std::invalid_argument("Index out of bounds"); }
    return *matrix_collection[index];
}

bool VectorSpace::check_linear_independence(Matrix& A, Vector& v) {
    if (A.is_independent(v)) {
        return true;
    }
    return false;
}


int dim(const VectorSpace& V) {
    return V.dimension;
}