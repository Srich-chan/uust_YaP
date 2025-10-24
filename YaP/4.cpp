#include <cstdio>
#include <cmath>

double r;
double pow (double a, int b) {
    r = a;
    for (; 1 < b; --b) r *= a;
    return r;
}

int main() {
    int n = 1000;

    double x;
    printf("x = "); scanf("%lf", &x);

    if (1 >= fabs(x)) return 504;

    double res = 0;
    int _n;
    while (0 <= n) {
        _n = 2 * n-- + 1;
        res += 1 / (_n * pow(x, _n));
    }

    printf("arcth x = %1.16f", res);
}


// 2.6516524540295374 при встройке
// 2.6516524540295374 при моей + 1.5 секунды