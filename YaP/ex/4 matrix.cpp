#include <vector>
#include <iostream>

using namespace std;
constexpr double DEFAULT_VALUE = 67;

class Matrix {
    vector<vector<double>> self;
    int m, n;

public:
    Matrix(int M, int N, double val=DEFAULT_VALUE) {
        if (M < 1 || N < 1) throw domain_error{"SUKA"};
        vector<double> base = vector<double>(static_cast<size_t>(N), val);
        
    }
    Matrix(vector<vector<double>>&& mtrx) {
        self = mtrx;
    }
};