


// A Mathematical Vector (in algebraic context)
class Vector {
    private:
        std::vector<double> data;
        int dimension;

    public:
        Vector() : dimension(0), data({}) {}
        Vector(std::vector<double> input) : dimension(input.size()), data(input) {}
        Vector(int size, double element) : dimension(size), data(std::vector<double>(size, element)) {}
        ~Vector() {}

        // Get Vector Dimension
        int dim() const {
            return dimension;
        }

        // Get Vector Data
        const std::vector<double>& get_data() const {
            return data;
        }
        std::vector<double>& get_data() {
            return data;
        }

        // Get Vector String
        std::string get_string() {
            std::string str = "(";
            for (int i = 0; i < dimension; i++) {
                str.append(std::to_string(data[i]));
                if (i == dimension - 1) continue;
                str.append(", ");
            }
            str.append(")");
            return str;
        }

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
            for (int i = 0; i < this->dimension; i++) {
                this->data[i] = other.data[i];
            }
            for (int j = this->dimension; j < other.dim(); j++) {
                this->data.push_back(other.data[j]);
            }
            this->dimension = other.dimension;
        }

        // Add Element
        void add(double element) {
            data.push_back(element);
            dimension++;
        }

        // Cumulative Vector Addition +=
        Vector operator+=(Vector& v2) {
            if (this->dimension < v2.dimension) { throw std::invalid_argument("Vector 1 size cannot be smaller than Vector 2 size for cumulative addition."); }
            for (int i = 0; i < v2.dimension; i++) {
                this->data[i] += v2.data[i];
            }
            return *this;
        }

        // Cumulative Vector Subtraction -=
        Vector operator-=(Vector& v2) {
            if (this->dimension < v2.dimension) { throw std::invalid_argument("Vector 1 size cannot be smaller than Vector 2 size for cumulative addition."); }
            for (int i = 0; i < v2.dimension; i++) {
                this->data[i] -= v2.data[i];
            }
            return *this;
        }

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
Vector operator+(Vector& v1, Vector& v2) {
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



// Vector Subtraction -
Vector operator-(Vector& v1, Vector& v2) {
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

// Scalar Multiplication
Vector operator*(double& scalar, Vector& v) {
    Vector result = Vector();
    for (auto x : v.data) {
        result.add(x * scalar);
    }
    return result;
}
Vector operator*(Vector& v, double& scalar) {
    Vector result = Vector();
    for (auto x : v.data) {
        result.add(x * scalar);
    }
    return result;
}

// Scalar Inverse Multiplication (Division)
Vector operator/(Vector& v, double& scalar) {
    Vector result = Vector();
    for (auto x : v.data) {
        result.add(x * (1 / scalar));
    }
    return result;
}
Vector operator/(double& scalar, Vector& v) {
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