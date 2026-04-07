#include <iostream>
#include <fstream>
#include <locale>
#include <random>
#include <set>
#include <vector>
#include <windows.h>


// using set, wcin, wcout, sqrt, cout;
using namespace std;


struct diap {
private:
    // Кэш
    vector<int> primes;
    // Генератор
    mt19937 rand{1531};
public:
    int k; // от
    int n; // до
    int min_prime;
    int max_prime;
    int m;
    int p;
    set<int> set;

    diap (int a, int b, int * _m=nullptr, int * _p=nullptr)
    : k{a}, n{b} {
        min_prime = a < 2? 2 : a;
        max_prime = b;
        primes.push_back(a);
        while (!is_prime(min_prime)) ++min_prime;
        while (!is_prime(max_prime)) --max_prime;
        while (primes.back() < max_prime) {
            primes.push_back(
                get_prime_to_right(primes.back())
            );
        }
        m = !_m? primes[rand() % primes.size()] : *_m;
        p = !_p? primes[rand() % primes.size()] : *_p;

        for (int i=a; i <= b; ++i) {
            if (i % m == 0 ^ i % p == 0)
                set.insert(i);
        }
    }

    static bool is_prime(const int x) {
        if (x < 2) return false;
        int cur = 2;
        while (x >= cur*cur) {
            if (x % cur == 0) return false;
            ++cur;
        }
        return true;
    }

    int get_prime_to_left(int normal) {
        int i=normal-1;
        while (!is_prime(i)) {
            if (i <= min_prime) return min_prime;
            --i;
        }
        return i;
    }

    int get_prime_to_right(int normal) {
        int i=normal+1;
        while (!is_prime(i)) {
            if (i >= max_prime) return max_prime;
            ++i;
        }
        return i;
    }
};

#include "paths.h"

int main () {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "Russian");

    ifstream tests{p_PROJECT "19 tests.txt"};
    while (!tests.eof()) {
        int k, n, w=0, p=0;
        tests >> k >> n >> w >> p;
        wcout << L"\n Введены: " << k << L" и " << n << L" и " << w << L" и " << p << "\n";

        diap diap(k, n, w?&w:nullptr , p?&p:nullptr);
        for (auto& el : diap.set) {
            wcout << el << " ";
        }
    }
}