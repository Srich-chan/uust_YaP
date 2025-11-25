#include <cstdio>
#include <cstring>
#include <cmath>

const unsigned size = 1024;
char str[size];

enum state {
    decrease = -1,
    increase = 1
};

char* spiral(char A[][], int n, int k, int x=n-1, int y=n-1, int turn = decrease) {
    char res[n * n + 1];


    if (n == 1) return res;
    strcat(res, spiral(A, n-1, k, x - turn, y, -turn));
    return res;
}

void f () {
    puts("str:"); gets(str);
    unsigned s = strlen(str);
    const int n = int (ceil(sqrt(s)));

    char A[n][n+1];
    char res[n * n + 1];
    int i=0;

    for (; i < s; ++i) {
        A[i / n][i % n] = str[i];
    }
    for (;i < n * n; ++i) {
        A[i / n][i % n] = '#';
    }

    // Diag
    printf("len = %d, n = %d, i = %d : %s \n", s, n, i, str);
    for (auto& l : A)
        // printf("len = %llu : %s \n", strlen(l), l);
        printf("%s \n", l);
    puts("");
    i=0;
    int x=n-1, y=n-1, k=0, turn = -1;

    while (1) {
        for (; turn == 1 ? x <= n - k : x >= k; x += turn) {
            res[i++] = A[y][x];
            printf("x %d %d %s\n", x, y, turn == 1 ? "+":"-");
        } x -= turn;
        y += turn;
        printf("!%d %d\n", x, y);
        if (k == n-1) break;
        for (; turn == 1 ? y <= n - k : y >= k; y += turn) {
            res[i++] = A[y][x];
            printf("y %d %d %s\n", x, y, turn == 1 ? "+":"-");
        } y -= turn;
        turn = -turn;
        x += turn;
        printf("!!%d %d\n", x, y);
        ++k;
    }

    puts(res);
}

int main () {
    f();
}