#include <cstdio>

int main() {
    int n; printf("\nn = "); scanf("%d", &n);
    int S = 0;
    int t;
    for (int i=1; i <= n; ++i) {
        t = 1;
        for (int j=i; j <= 2 * i; ++j) t *= j;
        S += t;
    }
    printf("result = %d", S);
}