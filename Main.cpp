// #include "VectorSpace.hpp"
#include "Matroid.hpp"

int main() {
    std::cout << "Matrix Test 1:\n\n"; 
    Matrix A1(0, 0);  // Edge case
    Matrix A2(3, 3);
    Matrix A3(2, 5);
    std::cout << A1 << "\n\n" << A2 << "\n\n" << A3 << std::endl << std::endl;
    A2 = A2 * 5;
    std::cout << A2 << std::endl << std::endl << std::endl;


    std::cout << "Matrix Test 2:\n\n"; 
    Matrix A(3, 4);
    Matrix T = A.Transpose().Transpose();
    // std::cout << "Original:\n\n" << A << "\n\n" << A.Transpose() << "\n\n";
    std::cout << "Double Transposed:\n\n" << T << std::endl << std::endl;
    A.multiply_row(1, 0);
    A.multiply_row(1, 1); // Restore it
    A.switch_row(0, 2);
    std::cout << A << std::endl;
}