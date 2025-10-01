#include <cstdio>
#include <cmath>

int main() {
    int n = 16000;
//    printf("n = "); scanf("%d", &n);

    double x;
    printf("x = "); scanf("%lf", &x);

    if (1 >= fabs(x)) return 0xf8;

    double res = 0;
    while (0 <= n) {
        int _n = 2 * n-- + 1;
//        res += pow(x, _n) / (_n);
        res += 1 / (_n * pow(x, _n));
    }

    printf("arcth x = %1.16f", res);
}
