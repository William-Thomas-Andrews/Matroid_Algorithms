#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>

#include "Vector.hpp"
#include "Compare.hpp"


const double EPS = 1e-10;


// The input set for a Linear Matroid
class Matrix {
    private:
        int rows;
        int columns;
        std::vector<Vector> data; // columns entries of row vectors    
    public:
        Matrix(); // Empty Matrix
        Matrix(int r, int c); // Random data
        Matrix(double item, int r, int c); // Uniform data
        Matrix(std::vector<Vector> input_data, int r, int c);
        Matrix(const std::vector<std::vector<double>> input_data, int r, int c);
        Matrix(const std::vector<std::vector<double>> input_data, int r, int c, bool by_column);
        Matrix(const Matrix& A); // Copy Constructor
        ~Matrix(); // Destructor

        void print();
        void update_zeros();
        void add_element(Vector v);
        void remove_back();
        void swap_vectors(Vector& v1, Vector& v2);

        // Operators
        Vector operator()(int col_index); // Index operator, returns a new vector of the same data (still a matrix)
        double& operator()(int row_index, int col_index); // Index operator, returns an entry in the matrix
        Matrix operator+(Matrix& other);
        Matrix operator-(Matrix& other);
        Matrix operator*(double scalar);
        Matrix operator/(double scalar);
        Matrix& operator=(const Matrix& other);
        bool operator==(const Matrix& other);
        bool operator!=(const Matrix& other);

        // Gettrs
        int get_size() const ;
        std::vector<Vector> get_data();
        std::string get_list_string(); // a copy of the data in a string format (originally arithmetic data)
        std::string to_string_precise(double value, int precision );
        std::string get_matrix_string(); // a copy of the data in a string format (originally arithmetic data)
        std::string get_truncated_matrix_string(); // a copy of the data in a string format (originally arithmetic data)
        double& get_element(int row_index, int col_index);
        int get_rows();
        int get_columns();

        // Transpose Operation
        Matrix Transpose();

        // Standard Matroid Operations
        void min_sort();
        void max_sort();
        void insertion_sort();
        bool not_empty();
        Vector& top();
        void pop();
        bool is_independent(Vector& v);

        // Matrix Operations
        void switch_row(int row1, int row2);
        void multiply_row(int row, double scalar);
        void row_replacement(int root_row, int replacee, double scalar);
        friend void full_double_round(Matrix& A);
        friend void row_reduce(Matrix& A);
        friend int no_reduce_rank(Matrix& A);
        friend int rank(Matrix& A);

        friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
};

// Extra Matrix Operations
double double_round(double val);
void full_double_round(Matrix& A);
void row_reduce(Matrix& A);
int no_reduce_rank(Matrix& A);
int rank(Matrix& A);

std::ostream& operator<<(std::ostream& os, const Matrix& A);