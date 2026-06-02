#include <iostream>
#include <fstream>
#include <locale>
#include <random>
#include <set>
#include <windows.h>
#include "paths.h"
#include <algorithm>


using namespace std;

class Shit : public logic_error {
public:
    using logic_error::logic_error;
};

int main () {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "Russian");
    ifstream in(p_PROJECT "19 tests.txt");

    if (!in.is_open())
        throw Shit{"file isn't opened!"};

    set<int> M;
    set<int> P;
    set<int> Result;
    int c = 0;
    char buff[129];

    while (!in.eof()) {
        if (in.peek() == ' ')
            in.getline(buff, 123123);
        in.getline(buff, 128, ' ');
        int k = stoi(buff);
        in.getline(buff, 128);
        int n = stoi(buff);
        
        in.getline(buff, 128, ' ');
        int m = stoi(buff);
        in.getline(buff, 128);
        int p = stoi(buff);

        wcout << L"Случай " << ++c << ":\n"
        << "\tk = " << k << ", n = " << n << ",\n"
        << "\tm = " << m << ", p = " << p << "\n"
        << L"\nРезультат:\n";

        for (int i = k; i <= n; ++i) {
            if (i % m == 0)
                M.insert(i);
            if (i % p == 0)
                P.insert(i);
        }

        set_symmetric_difference(
            M.begin(), M.end(),
            P.begin(), P.end(),
            inserter(Result, Result.begin())
        );

        cout << "{";
        if (!Result.empty()) {
            set<int>::iterator beg = Result.begin();
            cout << *beg++;
            while (beg != Result.end()) {
                cout << ", " << *beg++;
            }
        }
        cout << "}\n\n";

        M.clear();
        P.clear();
        Result.clear();
    }
    in.close();
}