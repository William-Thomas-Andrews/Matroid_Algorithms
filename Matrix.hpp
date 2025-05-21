#include <random>
#include "Vector.hpp"


class Matrix {
private:
    int rows;
    int columns;
    std::vector<Vector> data; // columns entries of row vectors
    bool is_row_reduced = false;
    // bool linearly_independent = false;
    
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
        row_reduce(*this);
    }
    Matrix(double item, int r, int c) : rows(r), columns(c) { // Uniform data
        for (int i = 0; i < c; i++) {
            data.push_back(Vector(r, item));
        }
        row_reduce(*this);
    }
    Matrix(const std::vector<Vector> input_data, int r, int c) : rows(r), columns(c) { 
        if (input_data.size() != c) { throw std::invalid_argument("Size of array does not match dimension sizes."); }
        for (int i = 0; i < c; i++) {
            data.push_back(Vector());
            for (int j = 0; j < input_data[i].dim(); j++) {
                data[i].add(input_data[i][j]);
            }
        } 
        row_reduce(*this);
    }
    Matrix(const std::vector<std::vector<double>> input_data, int r, int c) : rows(r), columns(c) { 
        if (input_data.size() != c) { throw std::invalid_argument("Size of array does not match dimension sizes."); }
        for (int i = 0; i < c; i++) {
            data.push_back(Vector());
            for (int j = 0; j < input_data[i].size(); j++) {
                data[i].add(input_data[i][j]);
            }
        } 
        row_reduce(*this);
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
    Matrix(const Matrix& A) : rows(A.rows), columns(A.columns), data(A.data) {
        row_reduce(*this);
    }
    // Destructor
    ~Matrix() {}

    void print() { std::cout << get_matrix_string(); }

    void add_element(Vector v) {
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
                if (this->get_element(i, j) == 0) {
                    str.append(std::to_string(0.0) + " ");
                }
                else {
                    str.append(std::to_string(this->get_element(i, j)) + " ");
                }
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
            B.add_element(v);
        }
        return B;
    }

    bool is_independent(Vector& v) {
        // First to check if it is the zero vector
        int count = 0;
        for (auto x : v.get_data()) {
            if (x == 0) count++;
        }
        if (count == v.dim()) return false; // If yes, then it returns false because adding the zero vector makes the matrix linearly dependent
        Matrix A = *this;
        A.add_element(v);
        row_reduce(A);
        std::cout << rank(A) << " " << rank(*this) << std::endl;
        if (rank(A) == rank(*this)) {
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

    friend void row_reduce(Matrix& A);
    friend int rank(Matrix& A);


    // TODO: Implement dot products
    friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
    friend Matrix dot_serial(const Matrix& A, const Matrix& B);
    friend Matrix dot_static_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_dynamic_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_for_each(const Matrix& A, const Matrix& B);
    friend Matrix dot_coarse_grained(const Matrix& A, const Matrix& B);
    friend Matrix dot_fine_grained(const Matrix& A, const Matrix& B);
};


void row_reduce(Matrix& A) {
    if (A.data.empty()) { return; }
    for (int col = 0, row = 0; col < A.columns; col++, row++) {
        if (row >= A.rows) { break; }
        int index = row;
        while (A(index, col) == 0 and index < A.rows-1) { 
            index++; 
        }
        A.switch_row(row, index);
        if (A(row, col) == 0) { continue; }
        A.multiply_row(row, (1 / A(row, col))); // Multiply the row by the inverse of its selected element
        for (int i = row+1; i < A.rows; i++) {
            if (A(i, col) != 0) {
                A.row_replacement(row, i, (-A(i, col)));
            }
        }
    }
    A.is_row_reduced = true;
}

int rank(Matrix& A) {
    // if (A.is_row_reduced == false) {
    //     row_reduce(A);
    //     st
    // }
    int rank = 0;
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.columns; col++) {
            if (A(row, col) != 0) {
                rank++;
                break;
            }
        }
    }
    return rank;
}


std::ostream& operator<<(std::ostream& os, Matrix& A) {
    os << A.get_trucated_matrix_string();
    // os << A.get_matrix_string();
    return os;
}