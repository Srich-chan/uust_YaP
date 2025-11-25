#include <cstdio>
#include <cmath>

double x;

int main() {
    const double EPS = 1e-36;

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
        curr = 1.0 / ((2 * ++n + 1) * l);
        l *= x * x;
        res += curr;
    } while (fabs(curr) > EPS);

    printf("arcth x = %.15f", res);
}

