#include <cstdio>
#include <cmath>

int main() {
    int n;
    printf("\nn = ");
    scanf("%d", &n);
    int x;

    for (int i=0; i < n; ++i) {
        printf("%d.", i + 1);
        for (int j = 0; j < n; ++j) {
            x = j - i + 1;
            if (x < 0) x = 0;
            printf("\t%d", x);
        }
        printf("\n");
    }
}