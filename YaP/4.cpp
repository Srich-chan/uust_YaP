#include <cstdio>
#include <cmath>

const double EPS = 0.000001;
int main() {

    double x;
    printf("x = "); scanf("%lf", &x);

    if (1 >= fabs(x)) return 228;

    double res = 0;
    double curr;
    const double a = x;
    int n = 1;

    do {
        curr = 1 / (n * x);
        x *= a*a;
        ++++n;
        res += curr;
    } while (fabs(curr) >= EPS) ;

    printf("arcth x = %1.16f", res);
}


// 2.6516524540295374 при встройке
// 2.6516524540295374 при моей + 1.5 секунды