#include "VectorSpace.hpp"

int main() {
    // Vector v = Vector({1, 2, 3});
    // std::cout << v.get_string() << std::endl;
    // std::cout << v << std::endl;
    VectorSpace V = VectorSpace(10);
    std::cout << dim(V) << std::endl;
    Matrix A = Matrix(6, 10);
    
    // std::cout << A.get_columns() << std::endl;
    // std::cout << A.get_rows() << std::endl;
    // std::cout << A << std::endl;
    V.add_matrix(A);
    V.print_standard_basis();
    std::cout << V.get_matrix(0) << std::endl;
    Matrix rando = Matrix(2, 4);
    std::cout << rando << std::endl;
    Matrix B = V.get_matrix(0);
    std::cout << B << std::endl;
    B = B*3;
    std::cout << B << std::endl;
    B.Transpose();
    Matrix B3 = B.Transpose();
    std::cout << B3 << std::endl;
    std::cout << B << std::endl;
}