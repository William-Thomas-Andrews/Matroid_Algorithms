// #include "VectorSpace.hpp"
#include "Matroid.hpp"

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

    Graph G = Graph(9);
    Edge e1 = Edge(1, 2, 1); Edge e2 = Edge(2, 3, 1); Edge e3 = Edge(1, 3, 2); Edge e4 = Edge(3, 4, 1);Edge e5 = Edge(1, 4, 3); Edge e6 = Edge(5, 4, 5); Edge e7 = Edge(5, 3, 2); Edge e8 = Edge(2, 6, 3); Edge e9 = Edge(5, 6, 6);
    std::cout << e1 << std::endl;
    G.add_element(e1); G.add_element(e2); G.add_element(e3); G.add_element(e4); G.add_element(e5); G.add_element(e6); G.add_element(e7); G.add_element(e8); G.add_element(e9); 
    std::cout << e1 << std::endl;
    std::cout << G << std::endl;
    Matroid M = Matroid<Graph, Edge>(G);
    Graph H = M.optimize_matroid();
    std::cout << H << std::endl;

    std::cout << B3 << std::endl;
    row_reduce(B3);

    // Vector v = Vector(std::vector<double>({}));
    // B3.add_element(v);
    std::cout << B3 << std::endl;
    std::cout << rank(B3) << std::endl;
    Vector v = Vector(std::vector<double>({0,0, 0, 0, 0, 1}));
    std::cout << B3.is_independent(v) << std::endl;
    std::cout << "B3:" << B3.get_matrix_string() << std::endl;
    B3.add_element(v);
    std::cout << B3 << std::endl;
    // B3.switch_row(0, 8);
    // B3.multiply_row(0, 100.001);
    // std::cout << B3 << std::endl;
    // B3.multiply_row(0, (1/B3(0,0)));
    // std::cout << B3 << std::endl;
    // B3.row_replacement(0, 1, (-B3(1,0)));
    // std::cout << B3 << std::endl;
    // Matrix B4 = B.Transpose();
    // std::cout << B4 << std::endl;
}