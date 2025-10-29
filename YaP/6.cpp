#include <cstdio>
#include <cmath>

void spaces(int n) {
    for (int i=0; i < n; ++i) printf(" ");
}


int main() {
    int n, curr;
    printf("\nn = ");
    scanf("%d", &n);
//    int _matrix[n][n];
    int ms = floor(log10(n)) + 1;

    // char

    for (int i=0; i < n; ++i) {

        for (int j = 0; j < n; ++j) {
            curr = j - i + 1;
            if (curr <= 0) {curr = 0; spaces(ms);}

            else spaces(ms - floor(log10(curr)));

            printf("%d", curr);
//            _matrix[i][j] = curr;
        }
        printf("\n");
    }
}