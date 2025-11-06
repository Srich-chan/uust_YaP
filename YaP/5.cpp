#include <cstdio>

typedef unsigned long long num;

int main() {
    num n; printf("\nn = "); scanf("%llu", &n);
    num S = 0;
    num prev;
    num t;

    if (n == 0) return -123;

    for (num i=1; i <= n; ++i) {
        t = 1;
        for (num j=i; j <= 2 * i; ++j)
            t *= j;

        prev = S;
        S += t;
        if (prev > S) {
            printf("\nS overflow");
            S = -1;
            break;
        }
    }

    printf("\nresult = %llu", S);
}