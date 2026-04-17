#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

constexpr double DEFAULT_VALUE = 67;


class row : private vector<double> {
public:
    using vector::vector;
    using vector::resize;
    using vector::begin;
    using vector::end;

    explicit row(size_t N) {
        *this = row();
        while (N) {
            push_back(DEFAULT_VALUE);
            --N;
        }
    }

    double p() {
        pop
    }

    void arrange_from(double start=1, double step=1) {
        for (double& el : *this) {
            el = start;
            start += step;
        }
    }

    row sub_row(const vector<size_t>& skip) {
        row sub;
        for (size_t i=0; i < size(); i++) {
            bool to_skip = false;
            for (size_t s : skip) {
                if (i == s) {
                    to_skip = true;
                    break;
                }
            }
            if (!to_skip)
                sub.push_back(at(i));
        }
        return sub;
    }

    string str(int precision=0) {
        ostringstream oss;
        const row& vec = *this;

        oss << fixed << setprecision(precision); // Не ясная чёрная магия C++

        oss << "[" << vec[0];
        for (size_t i = 1; i < size(); ++i) {
            oss << ", ";
            oss << vec[i];
        }
        oss << "]";
        return oss.str();
    }

    void print(int prec=0) {
        cout << str(prec) << "\n";
    }
};

class Matr : private vector<row> {
    size_t m=0;
    size_t n=0;
public:
    using vector::vector;
    explicit Matr(size_t M=4, size_t N=4, double val=DEFAULT_VALUE) {
        reform(M, N);
        //
        // for (row& row : *this) {
        //     for (double& el : row) {
        //         el = val;
        //     }
        // }

    }

    Matr sub_Matr(vector<size_t>& Rows, vector<size_t>& Columns) {
        Matr sub;

    }

    void reform(size_t M, size_t N) {
        if (M == 0 || N == 0) {
            m = 0; n = 0;
            resize(0);
            return;
        }
        m = M; n = N;

        resize(m);
        for (row& row : *this) {
            row.resize(n);
        }
    }
    
    string str(int precision=0){
        ostringstream oss;

        oss << "\n[";
        if (!empty()) {
            Matr& self = *this;
            oss << self[0].str(precision);
            for (int i=1; i < m; ++i) {
                row& row = self[i];
                oss << ",\n " << row.str(precision);
            }
        } else oss << "[]";
        oss << "]\n";

        return oss.str();
    }

    void print(int prec=0) {
        cout << str(prec);
    }
};


int main() {

}