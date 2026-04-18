#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <windows.h>

using namespace std;

constexpr double DEFAULT_VALUE = 67;

// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppMemberFunctionMayBeConst
// ReSharper disable CppRedundantBaseClassAccessSpecifier
class row : private vector<double> {
public:
    using vector::vector;
    using vector::size;
    using vector::resize;
    using vector::begin;
    using vector::end;
    using vector::operator[];
    // using vector::operator=;

    explicit row(size_t N) {
        *this = row();
        while (N) {
            push_back(DEFAULT_VALUE);
            --N;
        }
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

    void insert_item(double item, size_t ins=-1) {
        if (ins >= size())
            push_back(item);
        else
            insert(begin() + ins, item);

    }

    string str(int precision=0) {
        ostringstream oss;
        const row& vec = *this;

        oss << fixed << setprecision(precision); // Не ясная чёрная магия C++

        oss << "[" << vec[0];
        for (size_t i = 1; i < size(); ++i) {
            oss << ",\t";
            oss << vec[i];
        }
        oss << "]";
        return oss.str();
    }

    void print(int prec=0) {
        cout << str(prec) << "\n";
    }
};

class Matrix : private vector<row> {
public:
    using vector::vector;
    using vector::begin;
    using vector::end;
    using vector::operator[];
    // using vector::operator=;

    explicit Matrix(size_t m=0, size_t n=0) {
        reform(m, n);
    }

    void arrange_from(double start=1, double step=1) {
        if (empty()) throw domain_error {"Matrix is empty, sir!"};
        at(0).arrange_from(start, step);
        for (size_t i=1; i < M(); ++i) {
            at(i).arrange_from(at(i-1)[N()-1], step);
        }
    }

    Matrix sub_Matrix(const vector<size_t>& Rows, const vector<size_t>& Columns) {
        Matrix sub;

        for (size_t i=0; i < M(); ++i) {
            bool to_skip = false;
            for (const size_t& s : Rows) {
                if (i == s) {
                    to_skip = true;
                    break;
                }
            }
            if (!to_skip) {
                row subr = at(i).sub_row(Columns);
                sub.push_back(subr);
            }
        }

        return sub;
    }

    Matrix& reform(size_t M, size_t N) {
        if (M == 0 || N == 0) {
            resize(0);
            return *this;
        }

        resize(M);
        for (row& row : *this) {
            row.resize(N);
        }
        return *this;
    }

    void insert_row(row r, size_t ins=-1) {
        if (!empty()) r.resize(N());
        if (ins >= M())
            push_back(r);
        else
            insert(begin() + ins, r);
    }

    void insert_column(row c, size_t ins=-1) {
        c.resize(M());
        for (size_t i=0; i < M();++i)
            (*this)[i].insert_item(c[i], ins);

    }

    size_t M() {
        return size();
    }

    size_t N() {
        if (empty()) return 0;
        return at(0).size();
    }

    string str(int precision=0){
        ostringstream oss;

        oss << "\n[";
        if (!empty()) {
            Matrix& self = *this;
            oss << self[0].str(precision);
            for (int i=1; i < M(); ++i) {
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

    void print_size() {
        wcout
        << L"Строк: " << M()
        << L"\nСтолбцов: " << N() << "\n";
    }

};



int main() {
    setlocale(0, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    auto A = Matrix(10, 10);
    A.arrange_from(1);
    A.print();
    A.print_size();

    A.reform(5, 5);
    A.print();

    A.insert_row({1123, 5234});
    A.print();
    A.print_size();

    A.insert_column({8, 800, 555 ,35, 35}, 2);
    A.print();
    A.print_size();

    Matrix B = A.sub_Matrix({2, 4}, {1, 3});
    B.print();
    B.print_size();


}