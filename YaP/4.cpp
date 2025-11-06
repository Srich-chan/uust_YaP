#include <cstdio>
#include <cmath>

const double EPS = 0.0000001;
double x;

int main() {


    printf("x = "); scanf("%lf", &x);

    if (1 >= fabs(x)) {
        printf("Value error: |x| <= 1");
        return 1;
    }

    double l = x;
    double curr;
    double res = 0;
    int n = 0;

    do {
        curr = 1.0 / ((2*n + 1) * l);
        l *= x * x;
        res += curr;
        ++n;
    } while (fabs(curr) > EPS);


    printf("arcth x = %1.16f", res);
}

// 2.6516524540295374 при встройке
// 2.6516524540295374 при моей + 1.5 секунды