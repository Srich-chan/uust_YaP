#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));
    printf("array size = ");
    int ms; scanf("%d", &ms);
    int n = 1;
    while ((n * n - n) / 2 + n < ms) ++n;


    printf("Array size: %d \n", ms);
    printf("Matrix nxn side: %d \n", n);


    int **A = new int*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new int[n];
        for (int j = 0; j < n; ++j) A[i][j] = 0;
    }

    int max_w = 1;
    for (int i = 0; i < n && ms > 0; ++i) {
        for (int j = i; j < n && ms > 0; ++j, --ms) {
            int v = rand() % 1230 * (rand() % 2 ? -1 : 1);
            A[i][j] = A[j][i] = v;

            // Определяем максимальную ширину
            int len = 1, t = v < 0 ? -v : v;
            while (t >= 10) { t /= 10; ++len; }
            if (v < 0) ++len; // знак минус
            if (len > max_w) max_w = len;
        }
    }

    char fmt[10];
    sprintf(fmt, "%%%dd ", max_w + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf(fmt, A[i][j]);
        printf("\n");
        delete[] A[i];
    }
    delete[] A;

    return 0;
}