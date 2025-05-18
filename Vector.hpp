#include <array>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>

class Vector {
    private:
        std::vector<double> data;
        int dimension;

    public:
        Vector() : dimension(0), data({}) {}
        Vector(std::vector<double> input) {
            for (int i = 0; i < input.size(); i++) {
                data.push_back(input[i]);
            }
        }

        int dimension() {
            return dimension;
        }

        // std::vector<double>& get_data() {
        //     return data;
        // }

        // Element Accessor []
        double& operator[](int index) {
            return data[index];
        }

        // Scalar Multiplication
        Vector operator*(double scalar) {
            for (auto x : data) {
                x *= scalar;
            }
        }

        // Vector Addition
        friend Vector operator+(Vector v1, Vector v2);
};

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