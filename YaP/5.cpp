#include <cstdio>

int main() {
    unsigned n; printf("\nn = "); scanf("%u", &n);
    unsigned long int S = 0;
    unsigned long int t;
    unsigned j;
    for (int i=1; i <= n; ++i) {
        t = 1;
        for (j=i; j <= 2 * i; ++j)
            t *= j;
        S += t;
    }
    printf("result = %lu", S);
}