#include "../include/Matroid.hpp"
#include <cassert>

int main() {

    std::cout << "=== Small Matrix Test Suite ===\n\n";

    std::cout << "Matrix Test:\n\n"; 
    Matrix A11(0, 0);  // Edge case
    Matrix A22(3, 3);
    Matrix A33(2, 5);
    std::cout << A11 << "\n\n" << A22 << "\n\n" << A33 << std::endl << std::endl;
    A22 = A22 * 5;
    std::cout << A22 << std::endl << std::endl << std::endl;


    std::cout << "Matrix Test:\n\n"; 
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

    std::cout << "Matroid Test:\n\n";
    row_reduce(A);
    std::cout << A << "\n\n";
    Matroid M = Matroid<Matrix, Vector>(A);
    Matrix M1 = M.min_optimize_matroid();
    // std::cout << rank(M1) << "\n\n";
    std::cout << M1 << "\n\n";
    row_reduce(M1);
    std::cout << M1 << "\n\n";



    std::cout << "=== Row Reduction & Rank Test Suite ===\n\n";

    // Test: Zero Matrix
    std::cout << "Test: Zero Matrix\n";
    Matrix A1(std::vector<std::vector<double>>({{0, 0}, {0, 0}}), 2, 2);
    std::cout << "Original:\n" << A1 << "\n";
    row_reduce(A1);
    std::cout << "Reduced:\n" << A1 << "\n";
    std::cout << "Rank: " << rank(A1) << "\n\n";

    // Test: Identity Matrix
    std::cout << "Test: Identity Matrix\n";
    Matrix A2(std::vector<std::vector<double>>({{1, 0}, {0, 1}}), 2, 2);
    std::cout << "Original:\n" << A2 << "\n";
    row_reduce(A2);
    std::cout << "Reduced:\n" << A2 << "\n";
    std::cout << "Rank: " << rank(A2) << "\n\n";

    // Test: Row Swaps Required
    std::cout << "Test: Row Swaps\n";
    Matrix A3(std::vector<std::vector<double>>({
        {0, 2, 1},
        {1, 0, 0},
        {0, 1, 0}
    }), 3, 3);
    std::cout << "Original:\n" << A3 << "\n";
    row_reduce(A3);
    std::cout << "Reduced:\n" << A3 << "\n";
    std::cout << "Rank: " << rank(A3) << "\n\n";

    // Test: Linearly Dependent Rows
    std::cout << "Test: Duplicate Rows\n";
    Matrix A4(std::vector<std::vector<double>>({
        {1, 2, 3},
        {1, 2, 3},
        {2, 4, 6}
    }), 3, 3);
    std::cout << "Original:\n" << A4 << "\n";
    row_reduce(A4);
    std::cout << "Reduced:\n" << A4 << "\n";
    std::cout << "Rank: " << rank(A4) << "\n\n";

    // Test: Rectangular Tall Matrix
    std::cout << "Test: More Rows than Columns\n";
    Matrix A5(std::vector<std::vector<double>>({
        {1, 2, 3},
        {4, 5, 6}
    }), 3, 2);
    std::cout << "Original:\n" << A5 << "\n";
    row_reduce(A5);
    std::cout << "Reduced:\n" << A5 << "\n";
    std::cout << "Rank: " << rank(A5) << "\n\n";

    // Test: Rectangular Wide Matrix
    std::cout << "Test: More Columns than Rows\n";
    Matrix A51(std::vector<std::vector<double>>({
        {1, 2, 3},
        {4, 5, 6}
    }), 2, 3, false);
    std::cout << "Original:\n" << A51 << "\n";
    row_reduce(A51);
    std::cout << "Reduced:\n" << A51 << "\n";
    std::cout << "Rank: " << rank(A51) << "\n\n";

    // Test: Sparse Matrix
    std::cout << "Test: Sparse Matrix\n";
    Matrix A6(std::vector<std::vector<double>>({
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0}
    }), 3, 4, false);
    std::cout << "Original:\n" << A6 << "\n";
    row_reduce(A6);
    std::cout << "Reduced:\n" << A6 << "\n";
    std::cout << "Rank: " << rank(A6) << "\n\n";

    // Test: Single Row
    std::cout << "Test: Single Row\n";
    Matrix A7(std::vector<std::vector<double>>({
        {3, 4, 5}
    }), 1, 3, false);
    std::cout << "Original:\n" << A7 << "\n";
    row_reduce(A7);
    std::cout << "Reduced:\n" << A7 << "\n";
    std::cout << "Rank: " << rank(A7) << "\n\n";

    // Test: Single Column
    std::cout << "Test: Single Column\n";
    Matrix A8(std::vector<std::vector<double>>({
        {1},
        {0},
        {5}
    }), 3, 1, false);
    std::cout << "Original:\n" << A8 << "\n";
    row_reduce(A8);
    std::cout << "Reduced:\n" << A8 << "\n";
    std::cout << "Rank: " << rank(A8) << "\n\n";

    // Test: Real Matrix with Elimination
    std::cout << "Test: Real Coefficients\n";
    Matrix A9(std::vector<std::vector<double>>({
        {1.0, 1.00001},
        {1.0, 1.0}
    }), 2, 2, false);
    std::cout << "Original:\n" << A9 << "\n";
    row_reduce(A9);
    std::cout << "Reduced:\n" << A9 << "\n";
    std::cout << "Rank: " << rank(A9) << "\n\n";

    // Test: Complex Elimination
    std::cout << "Test: Mixed Elimination\n";
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

    // Test: Floating point stability
    std::cout << "Test: Floating Point Stability Test:\n";
    Matrix A_fp({
        {1e-10, 1},
        {1, 1e-10}
    }, 2, 2, false);
    std::cout << "Original:\n" << A_fp << "\n";
    row_reduce(A_fp);
    std::cout << "Reduced:\n" << A_fp << "\n";
    std::cout << "Rank: " << rank(A_fp) << "\n\n";

    // Test: Arbitrary Test
    std::cout << "Test: Arbitrary Test Matrix:\n";
    Matrix A_hr({
        {1, 0, 0, 1},
        {0, 1, 0, 1},
        {0, 0, 1, 1}
    }, 3, 4, false);
    std::cout << "Original:\n" << A_hr << "\n";
    row_reduce(A_hr);
    std::cout << "Reduced:\n" << A_hr << "\n";
    std::cout << "Rank: " << rank(A_hr) << "\n\n";

    // Test: Random 5x5 Dense Matrix
    std::cout << "Test: Random Dense 5x5 Matrix:\n";
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



    std::cout << "=== Matroid Test Suite ===\n\n";

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
    std::cout << A_m2 << std::endl;
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
    std::cout << A_m3 << "\n";
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
    std::cout << A_m4 << "\n";
    Matroid M_m4 = Matroid<Matrix, Vector>(A_m4);
    Matrix basis4 = M_m4.min_optimize_matroid();
    std::cout << "Optimized Matroid:\n" << basis4 << "\n";
    row_reduce(basis4);
    std::cout << "Reduced:\n" << basis4 << "\n";
    std::cout << "Rank: " << rank(basis4) << "\n\n";



    std::cout << "=== Partition Matroid Test Suite ===\n\n";

    std::cout << "[TEST] Min Sort Test\n";
    std::vector<PartitionPair> elements = {
        make_pair(5, 0),
        make_pair(2, 1),
        make_pair(8, 2),
        make_pair(1, 3)
    };

    PartitionMatroid matroid(elements);
    matroid.min_sort();


    std::cout << "Expected order (reverse, to be expected): 8, 5, 2, 1\n";
    std::cout << "Actual order:   " << matroid << "\n";


    std::cout << "\n[TEST] Max Sort and Top Element Test\n";
    std::vector<PartitionPair> elements_p0 = {
        make_pair(3, 0),
        make_pair(6, 1),
        make_pair(2, 2)
    };

    PartitionMatroid matroid_p0(elements_p0);
    matroid_p0.max_sort();

    std::cout << "Expected top element: 6\n";
    PartitionPair top = matroid_p0.top();
    std::cout << "Actual top element:   " << top.get_element() << "\n";

    assert(top.get_element() == 6);


    std::cout << "\n[TEST] Independence Test\n";
    std::vector<PartitionPair> elements_p1 = {
        make_pair(1, 0),
        make_pair(2, 1),
    };

    PartitionMatroid matroid_p1(elements_p1);

    PartitionPair new_independent = make_pair(3, 2);
    PartitionPair new_dependent   = make_pair(4, 1);

    assert(matroid_p1.is_independent(new_independent) == true);
    assert(matroid_p1.is_independent(new_dependent) == false);

    std::cout << "Independent check passed.\n";


    std::cout << "\n[TEST] Add and Pop Test\n";
    PartitionMatroid matroid_p2;

    assert(!matroid_p2.not_empty());
    matroid_p2.add_element(make_pair(9, 4));
    assert(matroid_p2.not_empty());
    std::cout << "After add: " << matroid_p2 << "\n";

    matroid_p2.pop();
    assert(!matroid_p2.not_empty());
    std::cout << "After pop: (should be empty)\n";


    std::cout << "\n[TEST] Matroid Optimization Tests (Min & Max)\n";

    std::vector<PartitionPair> elems = {
        make_pair(5, 0),  // weight 5, partition 0
        make_pair(2, 0),  // weight 2, partition 0 (same partition)
        make_pair(3, 1),  // weight 3, partition 1
        make_pair(4, 2),  // weight 4, partition 2
        make_pair(1, 2)   // weight 1, partition 2 (same partition)
    };

    std::cout << "Input elements:\n";
    for (auto& e : elems)
        std::cout << "(" << e.get_element() << ", P" << e.get_partition() << ") ";
    std::cout << "\n";

    // Minimize weight (greedy picks lowest per partition)
    PartitionMatroid min_matroid(elems);
    Matroid<PartitionMatroid, PartitionPair> min_m(min_matroid);
    PartitionMatroid min_basis = min_m.min_optimize_matroid();

    std::cout << "\nMinimize Optimization Result:\n";
    for (auto& e : min_basis.get_data())
        std::cout << "(" << e.get_element() << ", P" << e.get_partition() << ") ";
    std::cout << "\nExpected: (2, P0), (3, P1), (1, P2)\n";

    // Maximize weight (greedy picks highest per partition)
    PartitionMatroid max_matroid(elems);
    Matroid<PartitionMatroid, PartitionPair> max_m(max_matroid);
    PartitionMatroid max_basis = max_m.max_optimize_matroid();

    std::cout << "\nMaximize Optimization Result:\n";
    for (auto& e : max_basis.get_data())
        std::cout << "(" << e.get_element() << ", P" << e.get_partition() << ") ";
    std::cout << "\nExpected: (5, P0), (3, P1), (4, P2)\n";

    std::cout << "\n[TEST] Optimization Test Passed if above output matches expectation\n";
}