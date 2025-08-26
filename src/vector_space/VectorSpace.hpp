#pragma once

#include <iostream>
#include "Matrix.hpp"


class VectorSpace {
    private:
        Matrix standard_basis;
        int dimension;
        std::vector<std::unique_ptr<Matrix>> matrix_collection;

    public:
        VectorSpace();
        VectorSpace(int input_dimension);

        void add_matrix(Matrix& A);

        void print_standard_basis();

        Matrix& get_matrix(int index);

        bool check_linear_independence(Matrix& A, Vector& v);

        friend int dim(const VectorSpace& V);
};

int dim(const VectorSpace& V);