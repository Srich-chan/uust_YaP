#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


class row : public vector<double> {
    using vector::vector;

public:
    string to_str(int presicion=4) {
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



class Matr : public vector<row> {
    using vector::vector;

    size_t m = 4;
    size_t n = 4;


public:
    Matr(double val=DEFAULT_VALUE, size_t M=4, size_t N=4) {
        if (M < 1 || N < 1) throw domain_error{"Unreal condition!"};
        m = M; n = N;

        this->resize(m);
        for (row& row : *this) {
            row.resize(n);
            for (double& el : row) {
                el = val;
            }
        }
    }

    Matr(const vector<row>& ref) {
        *this = ref;
        m = ref.size();
        if (!ref.empty())
            n = ref[0].size();
        else
            n = 0;
    }

    string to_str(bool mult_lines=1, bool postline=1){
        ostringstream oss;
        Matr& self = *this;


        oss << "[";
        for (auto& row : self) {
            oss << row.to_str() << mult_lines? ",\n " : ", ";
        }
        oss << "]";
        if (postline)
            oss << "\n";

        return oss.str();
    }
};


class Matrix {
    int m, n;
protected:
    vector<row> self;
public:
    Matrix(int M, int N, double val=DEFAULT_VALUE) {
        if (M < 1 || N < 1) throw domain_error{"Unreal condition!"};
        m = M; n = N;
        const row base = row(N, val);
        self.resize(M);
        for (row& el : self) {
            el = base;
        }
    }

    explicit Matrix(vector<row>& mtrx) {
        self = mtrx;
        m = static_cast<int>(mtrx.size());
        n = static_cast<int>(mtrx[0].size());
    }



};

int main() {
    cout << Matr{}.to_str() << "\n";

    cout << Matr{1.1}.to_str();
}