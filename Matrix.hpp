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
    
public:
    Matrix(int r, int c) : rows(r), columns(c) {
        for (int i = 0; i < data.size(); i++) {
            // data.push_back(std::vector<double>(r, 0));
            data.push_back(Vector(r, 0));
            std::cout << data[i].get_string() << std::endl;
        }
    }
    Matrix(double item, int r, int c) : rows(r), columns(c) {
        for (int i = 0; i < data.size(); i++) {
            // data.push_back(std::vector<double>(r, item));
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
    ~Matrix() {}
    void print() { std::cout << get_string(); }

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
        // return data[(row_index * columns) + col_index];
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
    Matrix operator+(const Matrix& other) {
        if (this->rows != other.rows) {
            throw std::invalid_argument("Row sizes must match to perform matrix element-wise addition.");
        }
        if (this->columns != other.columns) {
            throw std::invalid_argument("Column sizes must match to perform matrix element-wise addition.");
        }
        Matrix return_matrix = Matrix(data, rows, columns);
        // Matrix return_matrix = Matrix(this.data, this.size, this.rows, this.columns);
        for (int i = 0; i < this->get_size(); i++) {
            return_matrix.data[i] += other.data[i];
        }
        return return_matrix;
    }
    Matrix operator-(const Matrix& other) {
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
    void operator=(const Matrix& other) {
        if (this == &other) return;
        for (int i = 0; i < other.get_size(); i++) {
            this->data[i] = other.data[i];
        }
        // this->size = other.size;
        this->rows = other.rows;
        this->columns = other.columns;
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
    std::string get_string() { // a copy of the data in a string format (originally arithmetic data)
        // std::string str = "";
        // for (int i = 0; i < get_size(); i++) {
        //     str += data[i].get_string();
        //     str += " ";
        //     if ((((i+1) % columns) == 0) && (i != get_size()-1)) {
        //         str += '\n';
        //     }
        // }
        // return str;
        std::string str = "(";

        for (int i = 0; i < columns; i++) {
            
            str.append(data[i].get_string());
            std::cout << "hey" << std::endl;
            if (i == columns - 1) continue;
            str.append(", ");
        }
        return str;
    }
    int get(int row_index, int col_index) {
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
        // return data[(row_index * columns) + col_index];
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
    os << A.get_string();
    return os;
}