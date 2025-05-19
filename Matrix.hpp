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
    Matrix() : rows(0), columns(0) {
        data.push_back(Vector());
    }
    Matrix(int r, int c) : rows(r), columns(c) {
        for (int i = 0; i < c; i++) {
            data.push_back(Vector(r, 0));
        }
    }
    Matrix(double item, int r, int c) : rows(r), columns(c) {
        for (int i = 0; i < c; i++) {
            // data.push_back(std::vector<double>(r, item));
            data.push_back(Vector(r, item));
            std::cout << data[i] << std::endl;
            std::cout << data.size() << std::endl;
        }
        std::cout << item << std::endl;
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
    ~Matrix() {}
    void print() { std::cout << get_matrix_string(); }

    void add_vector(Vector v) {
        data.push_back(v);
    }

    // Operators
    Vector operator()(int col_index) { // Index operator, returns a new vector of the same data (still a matrix)
        if (columns <= col_index) {
            throw std::out_of_range("Column index out of range");
            exit(1);
        }
        if (0 > col_index) {
            throw std::out_of_range("Column index cannot be negative");
            exit(1);
        }
        Vector return_vector = {};
        for (int i = 0; i < columns; i++) {
            // return_data.add(data[i + col_index*rows]);
            return_vector.add(data[col_index][i]);
        }
        return return_vector;
    }
    double& operator()(int row_index, int col_index) { // Index operator, returns an entry in the matrix
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
    // Matrix operator+(const Matrix& other) {
    //     if (this->rows != other.rows) {
    //         throw std::invalid_argument("Row sizes must match to perform matrix element-wise addition.");
    //     }
    //     if (this->columns != other.columns) {
    //         throw std::invalid_argument("Column sizes must match to perform matrix element-wise addition.");
    //     }
    //     Matrix return_matrix = Matrix(data, rows, columns);
    //     // Matrix return_matrix = Matrix(this.data, this.size, this.rows, this.columns);
    //     for (int i = 0; i < this->get_size(); i++) {
    //         return_matrix.data[i] += other.data[i];
    //     }
    //     return return_matrix;
    // }
    // Matrix operator-(const Matrix& other) {
    //     if (this->rows != other.rows) {
    //         throw std::invalid_argument("Row sizes must match to perform matrix element-wise subtraction.");
    //     }
    //     if (this->columns != other.columns) {
    //         throw std::invalid_argument("Column sizes must match to perform matrix element-wise subtraction.");
    //     }
    //     Matrix return_matrix = Matrix(data, this->rows, this->columns);
    //     for (int i = 0; i < this->get_size(); i++) {
    //         return_matrix.data[i] -= other.data[i];
    //     }
    //     return return_matrix;
    // }

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

    int get_element(int row_index, int col_index) {
        if (rows <= row_index) {
            throw std::out_of_range("Row index out of range");
            return INT_MIN;
        }
        if (0 > row_index) {
            throw std::out_of_range("Row index cannot be negative");
            return INT_MIN;
        }
        if (columns <= col_index) {
            throw std::out_of_range("Column index out of range");
            return INT_MIN;
        }
        if (0 > col_index) {
            throw std::out_of_range("Column index cannot be negative");
            return INT_MIN;
        }
        return data[col_index][row_index];
    }

    int get_rows() { return rows; }
    int get_columns() { return columns; }

    // The transpose operation
    // Matrix Transpose() {
    //     Matrix B = Matrix(columns, rows);
    //     int B_index = 0;
    //     for (int i = 0; i < columns; i++) {
    //         for (int j = i; j < i+(columns*rows); j+=columns) {
    //             B.data[B_index] = data[j];
    //             B_index++;
    //         }
    //     }
    //     return B;
    // }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
    friend Matrix dot_serial(const Matrix& A, const Matrix& B);
    friend Matrix dot_static_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_dynamic_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_for_each(const Matrix& A, const Matrix& B);
    friend Matrix dot_coarse_grained(const Matrix& A, const Matrix& B);
    friend Matrix dot_fine_grained(const Matrix& A, const Matrix& B);
};

std::ostream& operator<<(std::ostream& os, Matrix& A) {
    os << A.get_matrix_string();
    return os;
}