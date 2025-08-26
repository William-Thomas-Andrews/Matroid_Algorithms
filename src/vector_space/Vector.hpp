#pragma once

#include <vector>

// A Mathematical Vector (in algebraic context)
// Defined by two operations:
// Vector addition:            v_1 + v_2 \in V
// Scalar multiplication:    \lambda * v_1 \in V

class Vector {
    private:
        std::vector<double> data;
        double weight = 0;

    public:
        Vector();
        Vector(std::vector<double> input);
        Vector(int size, double element);
        ~Vector();

        // Get Vector Dimension
        int dim() const ;

        // Get Vector Data
        const std::vector<double>& get_data() const ;

        std::vector<double>& get_data();

        // Get Vector String
        std::string get_string();

        double get_element(int index);

        void remove_back();

        bool is_zero();

        double get_weight();

        // Element Accessor []
        double& operator[](int index);

        // Equal Operator
        bool operator==(Vector& other);

        // Not Equal Operator
        bool operator!=(const Vector& other);

        // Assignment Operator
        void operator=(const Vector& other);

        // Add Element
        void add(double element);

        // Cumulative Vector Addition +=
        Vector operator+=(Vector& v2);

        // Cumulative Vector Subtraction -=
        Vector operator-=(Vector& v2);

        // Comparison operator <
        bool operator<(Vector& v2);

        // Comparison operator >
        bool operator>(Vector& v2);

        // Vector Addition
        friend Vector operator+(Vector& v1, Vector& v2);
        // Vector Subtraction
        friend Vector operator-(Vector& v1, Vector& v2);
        // Scalar Multiplication
        friend Vector operator*(double& scalar, Vector& v);
        friend Vector operator*(Vector& v, double& scalar);
        // Scalar Inverse Multiplication (Division)
        friend Vector operator/(double& scalar, Vector& v);
        friend Vector operator/(Vector& v, double& scalar);
};

// Vector Addition +
Vector operator+(Vector& v1, Vector& v2);

// Vector Subtraction -
Vector operator-(Vector& v1, Vector& v2);

// Scalar Multiplication
Vector operator*(double& scalar, Vector& v);
Vector operator*(Vector& v, double& scalar);

// Scalar Inverse Multiplication (Division)
Vector operator/(Vector& v, double& scalar);
Vector operator/(double& scalar, Vector& v);

// Output Operator
std::ostream& operator<<(std::ostream& os, Vector& v);