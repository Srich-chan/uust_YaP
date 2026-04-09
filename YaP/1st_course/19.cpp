#include <iostream>
#include <fstream>
#include <locale>
#include <random>
#include <vector>
#include <windows.h>



//TODO: Переделать нахуй
using namespace std;

vector<int> primes;

struct diap {
private:
    // Генератор
    // mt19937 rand{1531};
public:
    int k; // от
    int n; // до
    int min_prime;
    int max_prime;
    int m;
    int p;
    vector<int> result;

    diap (int a, int b, int mn, int pn)
    : k{a}, n{b} {
        min_prime = abs(a) < 2? 2 : a;
        max_prime = abs(b);
        primes[0];
        while (!is_prime(min_prime)) ++min_prime;
        while (!is_prime(max_prime)) --max_prime;
        while (primes.back() < max_prime) {
            primes.push_back(
                get_prime_to_right(primes.back())
            );
        }


        for (int i=a; i <= b; ++i) {
            if (i % m == 0 ^ i % p == 0)
                result.push_back(i);
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
        char buff[256];
        tests.getline(buff, 256);
        if (buff[0] == '#') continue; // # - пустая строка

        int k = strtol(buff, nullptr, 10);
        int n = strtol(buff, nullptr, 10);
        int w = strtol(buff, nullptr, 10);
        int p = strtol(buff, nullptr, 10);

        wcout << L"\n Введены: " << k << L" и " << n
        << L" и " << w << L" и " << p << "\n";

        diap diap(k, n, w?&w:nullptr , p?&p:nullptr);
        for (auto& el : diap.result) {
            wcout << el << " ";
        }
    }
}