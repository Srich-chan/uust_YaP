#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


class row : public vector<double> {
    using vector::vector;

public:
    string str(int presicion=2) {
        ostringstream oss;
        auto& vec = *this;
        oss << fixed << setprecision(presicion); // Не ясная чёрная магия C++

        oss << "[" << vec[0];
        for (size_t i = 1; i < size(); ++i) {
            oss << ", ";
            oss << vec[i];
        }
        oss << "]";
        return oss.str();
    }
};

constexpr double DEFAULT_VALUE = 67;

class Matr : vector<row> {
    using vector::vector;
    size_t m = 4;
    size_t n = 4;

public:
    Matr(double val=DEFAULT_VALUE, size_t M=4, size_t N=4) {
        if (M < 1 || N < 1) throw domain_error{"Unreal condition!"};
        m = M; n = N;

        resize(m);
        for (row& row : *this) {
            row.resize(n);
            for (double& el : row) {
                el = val;
            }
        }
    }

    void reform(size_t M, size_t N) {
        if (M < 1 || N < 1) throw domain_error{"Unreal condition!"};
        m = M; n = N;

        resize(m);
        for (row& row : *this) {
            row.resize(n);
        }
    }
    
    string str(bool mult_lines=1, bool postline=1){
        ostringstream oss;
        Matr& self = *this;

        // for (auto& row : self) {
            // oss << row.to_str() << (mult_lines? ",\n " : ", ");
        // }

        oss << "[" << self[0].str();
        for (int i=1; i < m; ++i) {
            row& row = self[i];
            oss << (mult_lines? ",\n " : ", ") << row.str();
        }
        oss << "]";

        if (postline)
            oss << "\n";

        return oss.str();
    }
};


int main() {
    cout << Matr{}.str() << "\n";
    cout << Matr{1.1}.str();

    cout << Matr{67, 5, 10}.str();
}