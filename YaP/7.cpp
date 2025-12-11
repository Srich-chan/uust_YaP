#define MAX_RAND 9000
#define GENERATE 1
// #define CHARS 1



#include <cstdio>
#if GENERATE
#include <cstdlib>
#include <ctime>
#endif


int main() {

    #if GENERATE
    srand(time(0));
    #endif

    int ms;
    int handle;

    printf("array size = ");
    handle = scanf("%d", &ms);

    if (ms <= 0) {fprintf(stderr, "Size should be NATURAL"); return -1;}
    if (handle < 1) {fprintf(stderr, "Input Conversion Err"); return -2;}


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

            #if GENERATE
                int v = rand() % MAX_RAND * (rand() % 2 ? -1 : 1);
            #else
                int v;
                printf("\nGimme el: ");
                scanf("%d", &v);
            #endif


            A[i][j] = A[j][i] = v;
            int len = 1, t = v < 0 ? -v : v;
            while (t >= 10) { t /= 10; ++len; }
            if (v < 0) ++len;
            if (len > max_w) max_w = len;
        }
    }

    char format[32];
    sprintf(format, "%%%dd ", max_w + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf(format, A[i][j]);
        printf("\n");
        delete[] A[i];
    }
    delete[] A;
    return 0;
}