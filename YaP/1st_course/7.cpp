#define GENERATE 1
#include <cstdio>
#include <cstdlib>
#include <ctime>

unsigned dlen (unsigned x) {
    unsigned spaces = 1;
    while (x >= 10) {
        x /= 10;
        ++spaces;
    }
    return spaces;
}
unsigned dlen (int x) {
    return dlen((unsigned) abs(x)) + (x < 0);
}

int main() {

    #if GENERATE
    srand(static_cast<unsigned int>(time(nullptr)));
    #endif

    unsigned ms;
    printf("array size = ");

    if (scanf("%lld", &ms) < 1) {fprintf(stderr, "Input Conversion Err"); return -2;}
    if (ms == 0) {fprintf(stderr, "Size should be NATURAL"); return -1;}

    int n = 1;
    while ((n * n - n) / 2 + n < ms) ++n;

    printf("Array size: %u \n", ms);
    printf("Matrix nxn side: %d \n", n);

    int _array[ms];
    int iii = 0;

    int **A = new int*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new int[n];
        for (int j=0; j < n; ++j) A[i][j] = 0;

    }

        int max = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n && iii < ms; ++j) {
            int v;
            if (GENERATE)
                v = (rand() % (RAND_MAX / 2)) * (rand() < RAND_MAX / 2 ? -1 : 1);
            else {
                printf("Gimme %d: ", iii);
                scanf("%d", &v);
            }
            int abs_v = abs(v);
            if (max < abs_v) max = abs_v;

            _array[iii++] = v;
            A[i][j] = A[j][i] = v;
        }
    }

    unsigned spaces = dlen (max);
    unsigned ms_len = dlen(ms);

    // Вывод массива
    printf("Array (%%index%%. %%number%%):\n");
    for (int i=0; i < iii; ++i) {
        printf("%*d. %*d \n", ms_len, i, spaces + 1,  _array[i]);
    }
    puts("");

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf("%*d", spaces + 2, A[i][j]);
        puts("");

        delete[] A[i];
    }
    delete[] A;
    return 0;
}
