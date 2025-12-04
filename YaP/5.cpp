#include <cstdio>


int main() {
typedef unsigned long long num;
    num S = 0, prev, n, t=2;

    do {
        printf("\nn = ");
        scanf("%llu", &n);
        if (n == 0) printf("N is Natural!\n");
        else break;
    } while (1);

    for (num i = 2; i <= n; ++i) {
        t *= 2 * i * (2 * i - 1);
        prev = S;
        S += t;
        if (prev > S) {
            printf("\nS overflow");
            S = -1;
            break;
        }
        t /= i;
    }

    printf("\nresult = %llu", S);
}