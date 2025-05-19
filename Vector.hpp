#include <array>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
#include <sstream>

class Vector {
    private:
        std::vector<double> data;
        int dimension;

    public:
        Vector() : dimension(0), data({}) {}
        Vector(std::vector<double> input) : dimension(input.size()), data(input) {
            // for (int i = 0; i < input.size(); i++) {
            //     data.push_back(input[i]);
            // }
        }
        Vector(int size, double element) : dimension(size), data(std::vector<double>(size, element)) {}

        int dim() const {
            return dimension;
        }

        const std::vector<double>& get_data() {
            return data;
        }

        std::string get_string() {
            std::string str = "(";
            std::cout << data[1] << std::endl; // Problem, these variables somehow don't exist
            std::cout << dimension << std::endl;
            for (int i = 0; i < dimension; i++) {
                
                str.append(std::to_string(data[i]));
                if (i == dimension - 1) continue;
                str.append(", ");
            }
            str.append(")");
            return str;
        }


        // std::vector<double>& get_data() {
        //     return data;
        // }

        // Element Accessor []
        double& operator[](int index) {
            return data[index];
        }

        // Element Accessor []
        const double& operator[](int index) const {
            return data[index];
        }

        // Equal Operator
        bool operator==(const Vector& other) {
            if (this->dimension != other.dimension) {
                return false;
            }
            for (int i = 0; i < other.dim(); i++) {
                if (this->data[i] != other.data[i]) {
                    return false;
                }
            }
            return true;
        }

        // Not Equal Operator
        bool operator!=(const Vector& other) {
            if (this->dimension != other.dimension) {
                return false;
            }
            int count = 0;
            for (int i = 0; i < other.dim(); i++) {
                if (this->data[i] == other.data[i]) {
                    count++;
                }
            }
            return (count == other.dim()) ? true : false;
        }

        // Assignment Operator
        void operator=(const Vector& other) {
            if (this == &other) return;
            for (int i = 0; i < other.dim(); i++) {
                this->data[i] = other.data[i];
            }
            this->dimension = other.dimension;
        }

        void add(double element) {
            data.push_back(element);
            dimension++;
        }

        // Vector Addition
        friend Vector operator+(Vector v1, Vector v2);
        friend void operator+=(Vector v1, Vector v2);
        // Vector Subtraction
        friend Vector operator-(Vector v1, Vector v2);
        friend void operator-=(Vector v1, Vector v2);
        // Scalar Multiplication
        friend Vector operator*(double scalar, Vector v);
        friend Vector operator*(Vector v, double scalar);
        // Scalar Inverse Multiplication (Division)
        friend Vector operator/(double scalar, Vector v);
        friend Vector operator/(Vector v, double scalar);
};

// Vector Addition +
Vector operator+(Vector v1, Vector v2) {
    std::vector<double> result;
    if (v1.dimension == v2.dimension) {
        Vector result = Vector(std::vector<double>(v1.dimension, 0));
        for (int i = 0; i < v1.dimension; i++) {
            result[i] += v1[i] + v2[i];
        }
    }
    else {
        int size = std::max(v1.dimension, v2.dimension);
        Vector result = Vector(std::vector<double>(size, 0));
        // TODO optimize
        for (int i = 0; i < v1.dimension; i++) {
            result[i] += v1[i];
        }
        for (int j = 0; j < v2.dimension; j++) {
            result[j] += v2[j];
        }
    }
    return result;
}

// Vector Addition +=
void operator+=(Vector v1, Vector v2) {
    if (v1.dim() < v2.dim()) { throw std::invalid_argument("Vector 1 size cannot be smaller than Vector 2 size for cumulative addition."); }
    for (int i = 0; i < v2.dim(); i++) {
        v1.data[i] += v2.data[i];
    }
}

// Vector Subtraction -
Vector operator-(Vector v1, Vector v2) {
    std::vector<double> result;
    if (v1.dimension == v2.dimension) {
        Vector result = Vector(std::vector<double>(v1.dimension, 0));
        for (int i = 0; i < v1.dimension; i++) {
            result[i] += v1[i] - v2[i];
        }
    }
    else {
        int size = std::max(v1.dimension, v2.dimension);
        Vector result = Vector(std::vector<double>(size, 0));
        // TODO optimize
        for (int i = 0; i < v1.dimension; i++) {
            result[i] += v1[i];
        }
        for (int j = 0; j < v2.dimension; j++) {
            result[j] -= v2[j];
        }
    }
    return result;
}

// Vector Subtraction -=
void operator-=(Vector v1, Vector v2) {
    if (v1.dim() < v2.dim()) { throw std::invalid_argument("Vector 1 size cannot be smaller than Vector 2 size for cumulative subtraction."); }
    for (int i = 0; i < v2.dim(); i++) {
        v1.data[i] -= v2.data[i];
    }
}

// Scalar Multiplication
Vector operator*(double scalar, Vector v) {
    Vector result = Vector();
    for (auto x : v.data) {
        result.add(x * scalar);
    }
    return result;
}
Vector operator*(Vector v, double scalar) {
    Vector result = Vector();
    for (auto x : v.data) {
        result.add(x * scalar);
    }
    return result;
}

// Scalar Inverse Multiplication (Division)
Vector operator/(Vector v, double scalar) {
    Vector result = Vector();
    for (auto x : v.data) {
        result.add(x * (1 / scalar));
    }
    return result;
}
Vector operator/(double scalar, Vector v) {
    Vector result = Vector();
    for (auto x : v.data) {
        result.add(x * (1 / scalar));
    }
    return result;
}

// Output Operator
std::ostream& operator<<(std::ostream& os, Vector& v) {
    os << v.get_string();
    return os;
}