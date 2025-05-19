#include "VectorSpace.hpp"

int main() {
    VectorSpace V = VectorSpace(10);
    Matrix A = Matrix(6, 10);
    // std::cout << dim(V) << std::endl;
    std::cout << A.get_columns() << std::endl;
    std::cout << A.get_rows() << std::endl;
    std::cout << A << std::endl;
    // V.add_matrix(A);
    Vector v = Vector({1, 2, 3});
    std::cout << v.get_string() << std::endl;
    std::cout << v << std::endl;
}