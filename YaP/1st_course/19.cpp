#include <iostream>
#include <locale>
#include <random>
#include <set>
#include <vector>
#include <windows.h>
// #include <math.h>

using std::set, std::wcin, std::wcout, std::sqrt, std::cout;

bool is_prime(const int x) {
    if (x < 2) return false;
    int cur=2;
    while (cur < int(sqrt(x)) + 1) {
        if (x % cur == 0) return false;
        ++cur;
    }
    return true;
}

int get_prime(int n) {
    static std::vector primes{2, 3, 5, 7, 11};
    if (n < 0) throw std::domain_error{"Tupo"};
    if (n <= primes.size()) return primes[n];
    for (int i=primes.size(); primes[i] <= n; ++i) {
        if (is_prime(i+2)) primes.push_back(i);
    }
    return primes[n];
}


int main () {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "Russian");

    std::mt19937 rand(0);

    int k, n;
    wcout << L"\nВведите границы диапазона от k до n: ";
    wcin >> k >> n;
    wcout << L"\n Введены: " << k << L" и " << n << "\n";
    set<int> res;
    get_prime(n);
    // Любые простые числа до n
    const int m = get_prime(rand() + 1);
    const int p = get_prime(rand() + 1);

    wcout <<  L"\nБыли выбраны:\n\tm = " << m <<
        L"\n\tp = " << p << '\n';

    for (int i=k; i <= n; ++i) {
        if (i % m == 0 ^ i % p == 0) {
            res.insert(i);
        }
    }

    wcout << L"Получено мн-во:\n{";

    size_t c = 1;

    for (auto& el : res) {
        cout << el << (c != res.size() ? ", ":"");
        if (c % 10 == 0) cout << '\n';
        ++c;
    }

    wcout << "}\n";

}