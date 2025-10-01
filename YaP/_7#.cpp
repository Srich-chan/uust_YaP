#include <cstdio>
#include <ctime>
#include <cstdlib>

int main() {
    int n, m;
    printf("n = "); scanf("%d", &n);
    printf("m = "); scanf("%d", &m);
    int A[n][m];

    srand(static_cast<unsigned int>(time(0)));

    for (int i=0; i < n; ++i) {
        for (int j=0; j < m; ++j) {
            A[i][j] = rand() % 100;
        }
    }

    for (int i =0;i < n; ++i) {
        for (int j =0; j < m; ++j) {
            printf(" %d", A[i][j]);
        } printf("\n");
    }

    int min_i, min_j, max_i=0, max_j=0;
    for (int j = 0; j < m; ++j) {
        min_j = A[0][j];
        for (int i = 1; i < n; ++i)
            if (min_j > A[i][j]) min_j = A[i][j];

        if (j == 0) max_j = min_j;
        else if (max_j < min_j) max_j = min_j;
    }

    for (int i = 0; i < n; ++i) {
        min_i = A[i][0];
        for (int j = 1; j < m; ++j) {
            if (min_i > A[i][j]) min_i = A[i][j];
        }
        if (i == 0) max_i = min_i;
        else if (max_i < min_i) max_i = min_i;
    }

    printf("%d, %d", min_i, min_j);
}

