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
        Matrix() : rows(0), columns(0) {} // Empty Matrix
        Matrix(int r, int c) : rows(r), columns(c) { // Random data
            double min = 0; 
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
            // row_reduce(*this); // Can be enabled for auto row-reduction
        }
        Matrix(double item, int r, int c) : rows(r), columns(c) { // Uniform data
            for (int i = 0; i < c; i++) {
                data.push_back(Vector(r, item));
            }
            // row_reduce(*this); // Can be enabled for auto row-reduction
        }
        Matrix(std::vector<Vector> input_data, int r, int c) : rows(r), columns(c) { 
            if (input_data.size() != c) throw std::invalid_argument("Size of array does not match dimension sizes.");
            for (int i = 0; i < c; i++) {
                data.push_back(Vector());
                for (int j = 0; j < input_data[i].dim(); j++) {
                    data[i].add(input_data[i][j]);
                }
            } 
            // row_reduce(*this); // Can be enabled for auto row-reduction
        }
        Matrix(const std::vector<std::vector<double>> input_data, int r, int c) : rows(r), columns(c) { 
            // Reads each nested vector as a vector
            if (input_data.size() != c) throw std::invalid_argument("Number of columns of array does not match dimension sizes.");
                for (int col = 0; col < c; col++) {
                    if (input_data[col].size() != r) throw std::invalid_argument("Number of rows of array does not match dimension sizes.");
                    data.push_back(Vector());
                    for (int row = 0; row < r; row++) {
                        data[col].add(input_data[col][row]);
                    }
                } 
            // row_reduce(*this); // Can be enabled for auto row-reduction
        }
        Matrix(const std::vector<std::vector<double>> input_data, int r, int c, bool by_column) : rows(r), columns(c) { 
            if (by_column) {
                if (input_data.size() != c) throw std::invalid_argument("Number of columns of array does not match dimension sizes.");
                for (int col = 0; col < c; col++) {
                    if (input_data[col].size() != r) throw std::invalid_argument("Number of rows of array does not match dimension sizes.");
                    data.push_back(Vector());
                    for (int row = 0; row < r; row++) {
                        data[col].add(input_data[col][row]);
                    }
                } 
                return;
            }
            if (input_data.size() != r) throw std::invalid_argument("Number of rows of array does not match dimension sizes.");
            for (int col = 0; col < c; col++) {
                data.push_back(Vector());
                for (int row = 0; row < r; row++) {
                    if (input_data[row].size() != c) throw std::invalid_argument("Number of columns of array does not match dimension sizes.");
                    data[col].add(input_data[row][col]);
                }
            }
            // row_reduce(*this); // Can be enabled for auto row-reduction
        }

        // Copy Constructor
        Matrix(const Matrix& A) : rows(A.rows), columns(A.columns), data(A.data) {
            // row_reduce(*this); // Can be enabled for auto row-reduction
        }
        // Destructor
        ~Matrix() {}

        void print() { std::cout << get_matrix_string(); }

        void update_zeros() {
            for (int col = 0; col < columns; col++) {
                while (data[col].dim() < rows) {
                    data[col].add(0.0);
                }
                while (data[col].dim() > rows) {
                    if (data[col].get_element(data[col].dim()-1) != 0) throw std::invalid_argument("Vector has a longer size than the matrix dimension"); 
                    data[col].remove_back();
                }
            }
        }

        void add_element(Vector v) {
            if (v.is_zero()) return;
            if (rows > v.dim()) {
                while (v.dim() < rows) {
                    v.add(0);
                }
            }
            else if (rows < v.dim()) {
                rows = v.dim();
            }
            data.push_back(v);
            columns++;
            update_zeros();
        }

        void remove_back() {
            if (rows == 0 or columns == 0) throw std::invalid_argument("Cannot remove the last vector from an empty matrix");
            data.pop_back();
            columns--;
            update_zeros();
        }

        void swap_vectors(Vector& v1, Vector& v2) {
            Vector temp = v2;
            for (int i = 0; i < v2.dim(); i++) {
                v1[i] = v2[i];
            }
            for (int j = 0; j < temp.dim(); j++) {
                v2[j] = temp[j];
            }
        }

        // Operators
        Vector operator()(int col_index) { // Index operator, returns a new vector of the same data (still a matrix)
            if (columns <= col_index) {
                throw std::out_of_range("Column index out of range");
            }
            if (0 > col_index) {
                throw std::out_of_range("Column index cannot be negative");
            }
            Vector return_vector = {};
            for (int i = 0; i < rows; i++) {
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
            Matrix result = Matrix(data, this->rows, this->columns);
            for (int i = 0; i < this->get_size(); i++) {
                result.data[i] -= other.data[i];
            }
            return result;
        }
        Matrix operator*(double scalar) {
            Matrix result = Matrix(data, this->rows, this->columns);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    result(i, j) *= scalar;
                }
            }
            return result;
        }
        Matrix operator/(double scalar) {
            Matrix result = Matrix(data, this->rows, this->columns);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    result(i, j) /= scalar;
                }
            }
            return result;
        }
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

        std::vector<Vector> get_data() { // a copy of the data
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
        std::string to_string_precise(double value, int precision = 5) {
            std::ostringstream out;
            out << std::fixed << std::setprecision(precision) << value;
            return out.str();
        }

        std::string get_matrix_string() { // a copy of the data in a string format (originally arithmetic data)
            if (rows == 0 or columns == 0) return "[]";
            std::string str = "";
            for (int i = 0; i < rows; i++) {
                str.append("[ ");
                for (int j = 0; j < columns; j++) {
                    if (this->get_element(i, j) == 0) {
                        str.append(std::to_string(0.0) + " ");
                    }
                    else {
                        str.append(to_string_precise(this->get_element(i, j)) + " ");
                    }
                }
                if (i != rows-1) {
                    str.append("]\n");
                }
                else {
                    str.append("]");
                }
            }
            return str;
        }
        std::string get_truncated_matrix_string() { // a copy of the data in a string format (originally arithmetic data)
            if (rows == 0 or columns == 0) return "[]";
            std::string str = "";
            for (int i = 0; i < rows; i++) {
                str.append("[ ");
                for (int j = 0; j < columns; j++) {
                    str.append(std::to_string(static_cast<int>(this->get_element(i, j))) + " ");
                }
                if (i != rows-1) {
                    str.append("]\n");
                }
                else {
                    str.append("]");
                }
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
                B.add_element(v);
            }
            return B;
        }

        void min_sort() {
            std::sort(data.begin(), data.end(), MinCompare<Vector>());
        }

        void max_sort() {
            std::sort(data.begin(), data.end(), MaxCompare<Vector>());
        }

        void insertion_sort() {
            for (int i = 1; i < data.size(); ++i) {
                Vector key = data[i];
                int j = i - 1;
                while (j >= 0 && data[j] > key) {
                    data[j + 1] = data[j];
                    j = j - 1;
                }
                data[j + 1] = key;
            }
        }

        bool not_empty() {
            if (rows != 0 and columns != 0) return true;
            return false;
        }

        Vector& top() {
            return data[data.size()-1];
        }

        void pop() {
            remove_back();
        }

        bool is_independent(Vector& v) {
            // First to check if it is the zero vector
            if (v.is_zero()) return false; // If yes, then it returns false because adding the zero vector makes the matrix linearly dependent
            Matrix A = *this;
            A.add_element(v);
            row_reduce(A);
            int rank_A = rank(A);
            int rank_this = rank(*this);
            if (rank_A == rank_this) {
                return false;
            } 
            return true;
        }

        void switch_row(int row1, int row2) {
            for (int col = 0; col < columns; col++) {
                double temp = this->get_element(row1, col);
                this->get_element(row1, col) = this->get_element(row2, col);
                this->get_element(row2, col) = temp;
            }
        }

        void multiply_row(int row, double scalar) {
            for (int col = 0; col < columns; col++) {
                this->get_element(row, col) = this->get_element(row, col) * scalar;
            }
        }

        void row_replacement(int root_row, int replacee, double scalar) {
            for (int col = 0; col < columns; col++) {
                this->get_element(replacee, col) = this->get_element(replacee, col) + this->get_element(root_row, col) * scalar;
            }
        }

        friend void full_double_round(Matrix& A);
        friend void row_reduce(Matrix& A);
        friend int no_reduce_rank(Matrix& A);
        friend int rank(Matrix& A);


        // TODO: Implement dot products
        friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
};

double double_round(double val) {
    if (std::abs(val) < EPS) return 0;
    return val;
}

void full_double_round(Matrix& A) {
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.columns; j++) {
            A(i, j) = double_round(A(i, j));
        }
    }
}


void row_reduce(Matrix& A) {
    if (A.data.empty()) return; 
    for (int col = 0, row = 0; col < A.columns; col++, row++) {
        if (row >= A.rows) break; 
        int index = row;
        while (A(index, col) == 0 and index < A.rows-1) { 
            index++; 
        }
        A(row, col) = double_round(A(row, col));
        A.switch_row(row, index);
        A(row, col) = double_round(A(row, col));
        if (A(row, col) == 0) continue;
        full_double_round(A);
        A.multiply_row(row, (1 / A(row, col))); // Multiply the row by the inverse of its selected element
        full_double_round(A);
        for (int i = row+1; i < A.rows; i++) {
            if (A(i, col) != 0) {
                A.row_replacement(row, i, (-A(i, col)));
                full_double_round(A);
            }
        }    
    }
    A.update_zeros();
}

int no_reduce_rank(Matrix& A) {
    Matrix B = Matrix(A);
    int rank = 0;
    int col_start = 0;
    for (int row = 0; row < B.rows; row++) {
        for (int col = col_start; col < B.columns; col++) {
            if ((B(row, col) != 0.0) or (B(row, col) != (-0.0))) {
                rank++;
                col_start++;
                break;
            }
        }
    }
    return rank;
}

int rank(Matrix& A) {
    Matrix B = Matrix(A);
    row_reduce(B);
    int rank = 0;
    int col_start = 0;
    for (int row = 0; row < B.rows; row++) {
        for (int col = col_start; col < B.columns; col++) {
            if ((B(row, col) != 0.0) or (B(row, col) != (-0.0))) {
                rank++;
                col_start++;
                break;
            }
        }
    }
    return rank;
}


std::ostream& operator<<(std::ostream& os, Matrix& A) {
    // std::string str = A.get_truncated_matrix_string();
    std::string str = A.get_matrix_string();
    os << str;
    return os;
}