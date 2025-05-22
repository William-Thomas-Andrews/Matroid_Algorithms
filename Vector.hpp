


// A Mathematical Vector (in algebraic context)
class Vector {
    private:
        std::vector<double> data;
        // static int dimension;
        double weight = 0;

    public:
        Vector() : data({}) {}
        Vector(std::vector<double> input) : data(input) {
            for (auto x : input) {
                weight += x;
            }
        }
        Vector(int size, double element) :  data(std::vector<double>(size, element)) {
            weight += size * element;
        }
        ~Vector() {}

        // Get Vector Dimension
        int dim() const {
            // dimension = data.size();
            return data.size();
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
            for (int i = 0; i < data.size(); i++) {
                str.append(std::to_string(data[i]));
                if (i == data.size() - 1) continue;
                str.append(", ");
            }
            str.append(")");
            return str;
        }

        double get_element(int index) {
            return data[index];
        }

        void remove_back() {
            data.pop_back();
        }

        bool is_zero() {
            std::cout << data.size() << std::endl;
            std::cout << this->get_string() << std::endl;
            for (int i = 0; i < data.size(); i++) {
                std::cout << data.size() << std::endl;
                if (data[i] != 0 or data[i] != (-0)) {
                    return false;
                }
            }
            return true;
        }

        double get_weight() {
            // return weight;
            double sum = 0;
            for (int row = 0; row < data.size(); row++) {
                sum += this->get_element(row);
            }
            return sum;
        }

        void set_weight(double& val) {
            weight = val;
        }

        // Element Accessor []
        double& operator[](int index) {
            return data[index];
        }

        // // Element Accessor []
        // const double& operator[](int index) const {
        //     return data[index];
        // }

        // Equal Operator
        bool operator==(const Vector& other) {
            if (this->data.size() != other.data.size()) {
                return false;
            }
            // for (int i = 0; i < other.dim(); i++) {
            //     if (this->data[i] != other.data[i]) {
            //         return false;
            //     }
            // }
            if (weight == other.weight) {
                return true;
            }
            return false;
            // return true;
        }

        // Not Equal Operator
        bool operator!=(const Vector& other) {
            if (this->data.size() != other.data.size()) {
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
            for (int i = 0; i < this->data.size(); i++) {
                this->data[i] = other.data[i];
            }
            for (int j = this->data.size(); j < other.dim(); j++) {
                this->data.push_back(other.data[j]);
            }
            // this->data.size() = other.data.size();
        }

        // Add Element
        void add(double element) {
            data.push_back(element);
            weight += element;
            // data.size()++;
        }

        // Cumulative Vector Addition +=
        Vector operator+=(Vector& v2) {
            if (this->data.size() < v2.data.size()) { throw std::invalid_argument("Vector 1 size cannot be smaller than Vector 2 size for cumulative addition."); }
            for (int i = 0; i < v2.data.size(); i++) {
                this->data[i] += v2.data[i];
            }
            return *this;
        }

        // Cumulative Vector Subtraction -=
        Vector operator-=(Vector& v2) {
            if (this->data.size() < v2.data.size()) { throw std::invalid_argument("Vector 1 size cannot be smaller than Vector 2 size for cumulative addition."); }
            for (int i = 0; i < v2.data.size(); i++) {
                this->data[i] -= v2.data[i];
            }
            return *this;
        }

        // Comparison operator <
        bool operator<(Vector& v2) {
            if (this->get_weight() < v2.get_weight()) {
                return true;
            }
            return false;
        }

        // Comparison operator >
        bool operator>(Vector& v2) {
            if (this->get_weight() > v2.get_weight()) {
                return true;
            }
            return false;
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
    if (v1.data.size() == v2.data.size()) {
        Vector result = Vector(std::vector<double>(v1.data.size(), 0));
        for (int i = 0; i < v1.data.size(); i++) {
            result[i] += v1[i] + v2[i];
        }
    }
    else {
        int size = std::max(v1.data.size(), v2.data.size());
        Vector result = Vector(std::vector<double>(size, 0));
        // TODO optimize
        for (int i = 0; i < v1.data.size(); i++) {
            result[i] += v1[i];
        }
        for (int j = 0; j < v2.data.size(); j++) {
            result[j] += v2[j];
        }
    }
    return result;
}



// Vector Subtraction -
Vector operator-(Vector& v1, Vector& v2) {
    std::vector<double> result;
    if (v1.data.size() == v2.data.size()) {
        Vector result = Vector(std::vector<double>(v1.data.size(), 0));
        for (int i = 0; i < v1.data.size(); i++) {
            result[i] += v1[i] - v2[i];
        }
    }
    else {
        int size = std::max(v1.data.size(), v2.data.size());
        Vector result = Vector(std::vector<double>(size, 0));
        // TODO optimize
        for (int i = 0; i < v1.data.size(); i++) {
            result[i] += v1[i];
        }
        for (int j = 0; j < v2.data.size(); j++) {
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