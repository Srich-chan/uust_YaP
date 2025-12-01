#include <cstdio>


int main() {
typedef unsigned long long num;
    num S = 0;

    // S = (1 * 2) + () + (i * (i + 1) ... ( 2 * i))
    num prev;
    num t;
    num n;

    do {
        printf("\nn = ");
        scanf("%llu", &n);
        if (n == 0) printf("N is Natural!\n");
        else break;
    } while (1);

    for (num i=1; i <= n; ++i) {
        // t = 1;
        // for (num j=i; j <= 2 * i; ++j)
        //     t *= j;



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