#include <cstdio>
#include <cmath>

int main() {
    int n, curr;
    printf("\nn = ");
    scanf("%d", &n);
//    int _matrix[n][n];
    const int s = (int)log10(n) + 1;
    int spaces;
    for (int i=0; i < n; ++i) {

        for (int j = 0; j < n; ++j) {
            curr = j - i + 1;
            if (curr < 0) {curr = 0;}
            else
            for (spaces = s - (int)log10(curr) + 1; spaces > 0; --spaces) printf(" ");

            printf("%d", curr);
//            _matrix[i][j] = curr;
        }
        printf("\n");
    }
}