#include "../include/Matroid.hpp"

int main() {
    std::cout << "Matrix Test 1:\n\n"; 
    Matrix A11(0, 0);  // Edge case
    Matrix A22(3, 3);
    Matrix A33(2, 5);
    std::cout << A11 << "\n\n" << A22 << "\n\n" << A33 << std::endl << std::endl;
    A22 = A22 * 5;
    std::cout << A22 << std::endl << std::endl << std::endl;


    std::cout << "Matrix Test 2:\n\n"; 
    Matrix A(3, 4);
    Matrix T = A.Transpose().Transpose();
    std::cout << "Original:\n" << A << "\n\n Transposed:\n" << A.Transpose().get_matrix_string() << "\n\n";
    std::cout << "Double Transposed:\n" << T << "\n\n Double Transposed * scalar 4:\n" << (T*4).get_matrix_string() << "\n\n";
    A.multiply_row(1, 2.0);
    A.multiply_row(1, 10.0); 
    A.switch_row(0, 2);
    std::cout << A << "\n\n";
    A.multiply_row(2, 0.9);
    std::cout << A << "\n\n\n";

    std::cout << "Matroid Test 1:\n\n";
    row_reduce(A);
    std::cout << A << "\n\n";
    Matroid M = Matroid<Matrix, Vector>(A);
    Matrix M1 = M.min_optimize_matroid();
    // std::cout << rank(M1) << "\n\n";
    std::cout << M1 << "\n\n";
    row_reduce(M1);
    std::cout << M1 << "\n\n";



    std::cout << "=== Row Reduction & Rank Test Suite ===\n\n";

    // Test 1: Zero Matrix
    std::cout << "Test 1: Zero Matrix\n";
    Matrix A1(std::vector<std::vector<double>>({{0, 0}, {0, 0}}), 2, 2);
    std::cout << "Original:\n" << A1 << "\n";
    row_reduce(A1);
    std::cout << "Reduced:\n" << A1 << "\n";
    std::cout << "Rank: " << rank(A1) << "\n\n";

    // Test 2: Identity Matrix
    std::cout << "Test 2: Identity Matrix\n";
    Matrix A2(std::vector<std::vector<double>>({{1, 0}, {0, 1}}), 2, 2);
    std::cout << "Original:\n" << A2 << "\n";
    row_reduce(A2);
    std::cout << "Reduced:\n" << A2 << "\n";
    std::cout << "Rank: " << rank(A2) << "\n\n";

    // Test 3: Row Swaps Required
    std::cout << "Test 3: Row Swaps\n";
    Matrix A3(std::vector<std::vector<double>>({
        {0, 2, 1},
        {1, 0, 0},
        {0, 1, 0}
    }), 3, 3);
    std::cout << "Original:\n" << A3 << "\n";
    row_reduce(A3);
    std::cout << "Reduced:\n" << A3 << "\n";
    std::cout << "Rank: " << rank(A3) << "\n\n";

    // Test 4: Linearly Dependent Rows
    std::cout << "Test 4: Duplicate Rows\n";
    Matrix A4(std::vector<std::vector<double>>({
        {1, 2, 3},
        {1, 2, 3},
        {2, 4, 6}
    }), 3, 3);
    std::cout << "Original:\n" << A4 << "\n";
    row_reduce(A4);
    std::cout << "Reduced:\n" << A4 << "\n";
    std::cout << "Rank: " << rank(A4) << "\n\n";

    // Test 5: Rectangular Tall Matrix
    std::cout << "Test 5: More Rows than Columns\n";
    Matrix A5(std::vector<std::vector<double>>({
        {1, 2, 3},
        {4, 5, 6}
    }), 3, 2);
    std::cout << "Original:\n" << A5 << "\n";
    row_reduce(A5);
    std::cout << "Reduced:\n" << A5 << "\n";
    std::cout << "Rank: " << rank(A5) << "\n\n";

    // Test 6: Rectangular Wide Matrix
    std::cout << "Test 6: More Columns than Rows\n";
    Matrix A51(std::vector<std::vector<double>>({
        {1, 2, 3},
        {4, 5, 6}
    }), 2, 3, false);
    std::cout << "Original:\n" << A51 << "\n";
    row_reduce(A51);
    std::cout << "Reduced:\n" << A51 << "\n";
    std::cout << "Rank: " << rank(A51) << "\n\n";

    // Test 7: Sparse Matrix
    std::cout << "Test 7: Sparse Matrix\n";
    Matrix A6(std::vector<std::vector<double>>({
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0}
    }), 3, 4, false);
    std::cout << "Original:\n" << A6 << "\n";
    row_reduce(A6);
    std::cout << "Reduced:\n" << A6 << "\n";
    std::cout << "Rank: " << rank(A6) << "\n\n";

    // Test 8: Single Row
    std::cout << "Test 8: Single Row\n";
    Matrix A7(std::vector<std::vector<double>>({
        {3, 4, 5}
    }), 1, 3, false);
    std::cout << "Original:\n" << A7 << "\n";
    row_reduce(A7);
    std::cout << "Reduced:\n" << A7 << "\n";
    std::cout << "Rank: " << rank(A7) << "\n\n";

    // Test 9: Single Column
    std::cout << "Test 9: Single Column\n";
    Matrix A8(std::vector<std::vector<double>>({
        {1},
        {0},
        {5}
    }), 3, 1, false);
    std::cout << "Original:\n" << A8 << "\n";
    row_reduce(A8);
    std::cout << "Reduced:\n" << A8 << "\n";
    std::cout << "Rank: " << rank(A8) << "\n\n";

    // Test 10: Real Matrix with Elimination
    std::cout << "Test 10: Real Coefficients\n";
    Matrix A9(std::vector<std::vector<double>>({
        {1.0, 1.00001},
        {1.0, 1.0}
    }), 2, 2, false);
    std::cout << "Original:\n" << A9 << "\n";
    row_reduce(A9);
    std::cout << "Reduced:\n" << A9 << "\n";
    std::cout << "Rank: " << rank(A9) << "\n\n";

    // Test 11: Complex Elimination
    std::cout << "Test 11: Mixed Elimination\n";
    Matrix A10(std::vector<std::vector<double>>({
        {2, 4, 6, 8},
        {1, 3, 5, 7},
        {3, 7, 11, 15},
        {4, 10, 16, 22}
    }), 4, 4);
    std::cout << "Original:\n" << A10 << "\n";
    row_reduce(A10);
    std::cout << "Reduced:\n" << A10 << "\n";
    std::cout << "Rank: " << rank(A10) << "\n\n";

    // Test 12: Floating point stability
    std::cout << "Test 12: Floating Point Stability Test:\n";
    Matrix A_fp({
        {1e-10, 1},
        {1, 1e-10}
    }, 2, 2, false);
    std::cout << "Original:\n" << A_fp << "\n";
    row_reduce(A_fp);
    std::cout << "Reduced:\n" << A_fp << "\n";
    std::cout << "Rank: " << rank(A_fp) << "\n\n";

    // Test 13: Arbitrary Test
    std::cout << "Test 13: Arbitrary Test Matrix:\n";
    Matrix A_hr({
        {1, 0, 0, 1},
        {0, 1, 0, 1},
        {0, 0, 1, 1}
    }, 3, 4, false);
    std::cout << "Original:\n" << A_hr << "\n";
    row_reduce(A_hr);
    std::cout << "Reduced:\n" << A_hr << "\n";
    std::cout << "Rank: " << rank(A_hr) << "\n\n";

    // Test 14: Random 5x5 Dense Matrix
    std::cout << "Test 14: Random Dense 5x5 Matrix:\n";
    Matrix A_dense({
        {2, 4, 6, 8, 10},
        {1, 3, 5, 7, 9},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1}
    }, 5, 5, false);
    std::cout << "Original:\n" << A_dense << "\n";
    row_reduce(A_dense);
    std::cout << "Reduced:\n" << A_dense << "\n";
    std::cout << "Rank: " << rank(A_dense) << "\n\n";

    std::cout << "Matroid Test: Maximize Independent Rows\n";
    Matrix A_m({
        {1, 2, 3},
        {2, 4, 6},   
        {3, 6, 9},   
        {1, 1, 0}   
    }, 4, 3, false);
    Matroid M_m = Matroid<Matrix, Vector>(A_m);
    Matrix basis = M_m.max_optimize_matroid();
    std::cout << "Optimized Matroid:\n" << basis << "\n";
    row_reduce(basis);
    std::cout << "Reduced:\n" << basis << "\n";
    std::cout << "Rank: " << rank(basis) << "\n\n";

    std::cout << "Matroid Test: Minimize Independent Rows\n";
    Matrix A_m2({
        {1, 2, 3},
        {2, 4, 6},   
        {3, 6, 9},   
        {1, 1, 0}    
    }, 4, 3, false);
    Matroid M_m2 = Matroid<Matrix, Vector>(A_m2);
    Matrix basis2 = M_m2.min_optimize_matroid();
    std::cout << "Optimized Matroid:\n" << basis2 << "\n";
    row_reduce(basis2);
    std::cout << "Reduced:\n" << basis2 << "\n";
    std::cout << "Rank: " << rank(basis2) << "\n\n";


    std::cout << "Matroid Test: Maximize Independent Rows, now reading by vector\n";
    Matrix A_m3({
        {1, 2, 3},
        {2, 4, 6},   // Dependent
        {3, 6, 9},   // Dependent
        {1, 1, 0}    // Independent
    }, 3, 4, true);
    Matroid M_m3 = Matroid<Matrix, Vector>(A_m3);
    Matrix basis3 = M_m3.max_optimize_matroid();
    std::cout << "Optimized Matroid:\n" << basis3 << "\n";
    row_reduce(basis3);
    std::cout << "Reduced:\n" << basis3 << "\n";
    std::cout << "Rank: " << rank(basis3) << "\n\n";

    std::cout << "Matroid Test: Minimize Independent Rows, now reading by vector\n";
    Matrix A_m4({
        {1, 2, 3},
        {2, 4, 6},   // Dependent
        {3, 6, 9},   // Dependent
        {1, 1, 0}    // Independent
    }, 3, 4, true);
    Matroid M_m4 = Matroid<Matrix, Vector>(A_m4);
    Matrix basis4 = M_m4.min_optimize_matroid();
    std::cout << "Optimized Matroid:\n" << basis4 << "\n";
    row_reduce(basis4);
    std::cout << "Reduced:\n" << basis4 << "\n";
    std::cout << "Rank: " << rank(basis4) << "\n\n";

}