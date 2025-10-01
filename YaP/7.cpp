#include <cstdio>

int main() {
//    int n, curr;
//    printf("\nn = ");
//    scanf("%d", &n);

    for ()

    int _matrix[n][n];

    for (int i=0; i < n; ++i) {
        printf("%d.\t", i + 1);
        for (int j = 0; j < n; ++j) {
            curr = j - i + 1;
            if (curr < 0) curr = 0;

            printf(" %x", curr);
//            _matrix[i][j] = curr;
        }
        printf("\n");
    }
}