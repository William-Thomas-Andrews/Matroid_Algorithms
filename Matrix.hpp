#pragma once


#include <array>
#include <iostream>
#include <string>
#include <stdexcept> 
#include <vector>
#include <initializer_list>
#include <cmath>
#include <cstdlib>
#include <ranges>
#include <concepts> 
#include <iomanip>
#include <thread>
#include <future>
#include <type_traits>
#include <variant>
#include <any>
#include <execution>
#include <algorithm>
// #include <omp.h>
#include <chrono> 
#include <random>
#include "Vector.hpp"
#include <string>





class Matrix {
private:
    int rows;
    int columns;
    std::vector<Vector> data; // columns entries of row vectors
    // bool linearly_independent;
    
public:
    Matrix() : rows(0), columns(0) { // Empty Matrix
        // data.push_back(Vector());
    }
    Matrix(int r, int c) : rows(r), columns(c) { // Random data
        double min = 0; // Positive for now
        double max = 10;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(min, max);
        for (int col = 0; col < columns; col++) {
            data.push_back(Vector());
            for (int row = 0; row < rows; row++) {
                data[col].add(dis(gen));
            }
        }
    }
    Matrix(double item, int r, int c) : rows(r), columns(c) { // Uniform data
        for (int i = 0; i < c; i++) {
            data.push_back(Vector(r, item));
        }
    }
    Matrix(const std::vector<Vector> input_data, int r, int c) : rows(r), columns(c) { 
        if (input_data.size() != c) { throw std::invalid_argument("Size of array does not match dimension sizes."); }
        for (int i = 0; i < c; i++) {
            data.push_back(Vector());
            for (int j = 0; j < input_data[i].dim(); j++) {
                data[i].add(input_data[i][j]);
            }
        } 
    }
    Matrix(const std::vector<std::vector<double>> input_data, int r, int c) : rows(r), columns(c) { 
        if (input_data.size() != c) { throw std::invalid_argument("Size of array does not match dimension sizes."); }
        for (int i = 0; i < c; i++) {
            data.push_back(Vector());
            for (int j = 0; j < input_data[i].size(); j++) {
                data[i].add(input_data[i][j]);
            }
        } 
    }
    // TODO Fix C-style array input
    // Matrix(const double* input_data, int input_data_size, int r, int c) : rows(r), columns(c), data(input_data, input_data + input_data_size) { 
    //     if (input_data_size != r*c) { throw std::invalid_argument("Size of array does not match dimension sizes."); } 
    //     for (int i = 0; i < c; i++) {
    //         data.push_back({});
    //         for (int j = 0; j < input_data[i].size(); j++) {
    //             data[i].push_back(input_data[i][j]);
    //         }
    //     } 
    // }
    // TODO std::array input
    // Copy Constructor
    Matrix(const Matrix& A) : rows(A.rows), columns(A.columns), data(A.data) {}
    // Destructor
    ~Matrix() {}

    void print() { std::cout << get_matrix_string(); }

    void add_vector(Vector v) {
        data.push_back(v);
        columns++;
        if (rows < v.dim()) {
            rows = v.dim();
        }
    }

    // void extend_vector(int col_index, double val) {
    //     if 
    //     // data[col_index].add(val);
    //     // rows++;
    //     // for (int i = 0; i < columns; i++) {
    //     //     if (i == col_index) continue;
    //     // }
    // }

    // Operators
    Vector operator()(int col_index) { // Index operator, returns a new vector of the same data (still a matrix)
        if (columns <= col_index) {
            throw std::out_of_range("Column index out of range");
        }
        if (0 > col_index) {
            throw std::out_of_range("Column index cannot be negative");
        }
        Vector return_vector = {};
        for (int i = 0; i < columns; i++) {
            return_vector.add(data[col_index][i]);
        }
        return return_vector;
    }
    double& operator()(int row_index, int col_index) { // Index operator, returns an entry in the matrix
        if (rows <= row_index) {
            throw std::out_of_range("Row index out of range");
        }
        if (0 > row_index) {
            throw std::out_of_range("Row index cannot be negative");
        }
        if (columns <= col_index) {
            throw std::out_of_range("Column index out of range");
        }
        if (0 > col_index) {
            throw std::out_of_range("Column index cannot be negative");
        }
        return data[col_index][row_index];
    }
    const double& operator()(int row_index, int col_index) const { // Index operator, returns an entry in the matrix
        if (rows <= row_index) {
            throw std::out_of_range("Row index out of range");
            exit(1);
        }
        if (0 > row_index) {
            throw std::out_of_range("Row index cannot be negative");
            exit(1);
        }
        if (columns <= col_index) {
            throw std::out_of_range("Column index out of range");
            exit(1);
        }
        if (0 > col_index) {
            throw std::out_of_range("Column index cannot be negative");
            exit(1);
        }
        // return data[(row_index * columns) + col_index];
        return data[col_index][row_index];
    }
    // TODO: Fix below
    Matrix operator+(Matrix& other) {
        if (this->rows != other.rows) {
            throw std::invalid_argument("Row sizes must match to perform matrix element-wise addition.");
        }
        if (this->columns != other.columns) {
            throw std::invalid_argument("Column sizes must match to perform matrix element-wise addition.");
        }
        Matrix return_matrix = Matrix(data, rows, columns);
        for (int i = 0; i < this->get_size(); i++) {
            return_matrix.data[i] += other.data[i];
        }
        return return_matrix;
    }
    Matrix operator-(Matrix& other) {
        if (this->rows != other.rows) {
            throw std::invalid_argument("Row sizes must match to perform matrix element-wise subtraction.");
        }
        if (this->columns != other.columns) {
            throw std::invalid_argument("Column sizes must match to perform matrix element-wise subtraction.");
        }
        Matrix return_matrix = Matrix(data, this->rows, this->columns);
        for (int i = 0; i < this->get_size(); i++) {
            return_matrix.data[i] -= other.data[i];
        }
        return return_matrix;
    }
    Matrix operator*(double scalar) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                this->get_element(i, j) *= scalar;
            }
        }
        return *this;
    }
    Matrix operator/(double scalar) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                this->get_element(i, j) /= scalar;
            }
        }
        return *this;
    }

    // Matrix operator*(const Matrix& other) {
    //     if (this->rows != other.rows) {
    //         throw std::invalid_argument("Row sizes must match to perform matrix element-wise multiplication.");
    //     }
    //     if (this->columns != other.columns) {
    //         throw std::invalid_argument("Column sizes must match to perform matrix element-wise multiplication.");
    //     }
    //     Matrix return_matrix = Matrix(data, rows, columns);
    //     for (int i = 0; i < columns; i++) {
    //         return_matrix.data[i] *= other.data[i];
    //     }
    //     return return_matrix;
    // }
    // Matrix operator/(const Matrix& other) {
    //     if (this->rows != other.rows) {
    //         throw std::invalid_argument("Row sizes must match to perform matrix element-wise division.");
    //     }
    //     if (this->columns != other.columns) {
    //         throw std::invalid_argument("Column sizes must match to perform matrix element-wise division.");
    //     }
    //     Matrix return_matrix = Matrix(data, rows, columns);
    //     for (int i = 0; i < this->get_size(); i++) {
    //         return_matrix.data[i] /= other.data[i];
    //     }
    //     return return_matrix;
    // }
    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;
        data = other.data;
        rows = other.rows;
        columns = other.columns;
        return *this;
    }
    bool operator==(const Matrix& other) {
        if ((this->rows != other.rows) || (this->columns != other.columns)) {
            return false;
        }
        if (this->get_size() != other.get_size()) {
            return false;
        }
        for (int i = 0; i < other.get_size(); i++) {
            if (this->data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Matrix& other) {
        if ((this->rows != other.rows) || (this->columns != other.columns)) {
            return true;
        }
        if (this->get_size() != other.get_size()) {
            return true;
        }
        for (int i = 0; i < other.get_size(); i++) {
            if (this->data[i] != other.data[i]) {
                return true;
            }
        }
        return false;
    }

    // Gettrs
    int get_size() const { return data.size(); }

    std::vector<Vector> get_data() const { // a copy of the data
        std::vector<Vector> vec({});
        for (int i = 0; i < get_size(); i++) {
            vec.push_back(data[i]);
        }
        return vec;
    }

    std::string get_list_string() { // a copy of the data in a string format (originally arithmetic data)
        std::string str = "(";
        for (int i = 0; i < columns; i++) {            
            str.append(data[i].get_string());
            if (i == columns - 1) continue;
            str.append(", ");
        }
        str.append(")");
        return str;
    }
    std::string get_matrix_string() { // a copy of the data in a string format (originally arithmetic data)
        std::string str = "";
        for (int i = 0; i < rows; i++) {
            str.append("[ ");
            for (int j = 0; j < columns; j++) {
                str.append(std::to_string(this->get_element(i, j)) + " ");
            }
            str.append("]\n");
        }
        return str;
    }
    std::string get_trucated_matrix_string() { // a copy of the data in a string format (originally arithmetic data)
        std::string str = "";
        for (int i = 0; i < rows; i++) {
            str.append("[ ");
            for (int j = 0; j < columns; j++) {
                str.append(std::to_string(static_cast<int>(this->get_element(i, j))) + " ");
            }
            str.append("]\n");
        }
        return str;
    }

    double& get_element(int row_index, int col_index) {
        if (rows <= row_index) {
            throw std::out_of_range("Row index out of range");
        }
        if (0 > row_index) {
            throw std::out_of_range("Row index cannot be negative");
        }
        if (columns <= col_index) {
            throw std::out_of_range("Column index out of range");
        }
        if (0 > col_index) {
            throw std::out_of_range("Column index cannot be negative");
        }
        return data[col_index][row_index];
    }

    int get_rows() { return rows; }
    int get_columns() { return columns; }

    // Transpose Operation
    Matrix Transpose() {
        Matrix B = Matrix();
        for (int i = 0; i < rows; i++) {
            Vector v = Vector();
            for (int j = 0; j < columns; j++) {
                v.add(this->get_element(i, j));
            }
            B.add_vector(v);
        }
        return B;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
    friend Matrix dot_serial(const Matrix& A, const Matrix& B);
    friend Matrix dot_static_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_dynamic_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_for_each(const Matrix& A, const Matrix& B);
    friend Matrix dot_coarse_grained(const Matrix& A, const Matrix& B);
    friend Matrix dot_fine_grained(const Matrix& A, const Matrix& B);
};

std::ostream& operator<<(std::ostream& os, Matrix& A) {
    os << A.get_trucated_matrix_string();
    return os;
}