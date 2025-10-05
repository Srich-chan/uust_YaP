#include <iostream>
#include <cmath>

using std::cout, std::cin;

int trash_func(int n) {
    int i=2;
    for (; (i * i - i / 2) < n; ++i);
    return i;
}

int main () {
    int n;
    cin >> n;

    if (n > 100 || n < 1) { cout << "hren\n";}
    int m = trash_func(n);
    int A[m][m];

    for (int i=0; i < n; ++i) {
       //potom
    }




}
