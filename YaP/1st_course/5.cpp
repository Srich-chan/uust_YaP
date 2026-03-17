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
        printf_s("%llu. S  = %llu,\t t = %llu, \t S < t = %d\n", i, S, t, S < t);

        S += t;

        /*
        Можно рассмотреть как в условных значениях
        S + t
        если переполнение, то

            S = S + t - ULLONG_MAX


        */


        // if (prev > S) {
        //     printf("\nS overflow");
        //     S = -1;
        //     break;
        // }
        t /= i;
    }

    printf("\nresult = %llu", S);
}