#include <cstdio>
#include <cstring>
#include <cmath>

const unsigned size = 1024;
char str[size];

void f () {
    puts("str:"); gets(str);
    unsigned s = strlen(str);
    const int n = int (ceil(sqrt(s)));

    char A[n][n+1];
    char res[n * n * 2];
    int i=0;

    for (; i < s; ++i) {
        A[i / n][i % n] = str[i];
    }
    for (;i < n * n; ++i) {
        A[i / n][i % n] = '#';
    } --i;

    for (auto& l : A)
        printf("%s \n", l);
    puts("");

    // for res
    int x=0, y=0, k=0, turn = 1;
    // | / - - \
    // | | / \ |
    // | | X | |
    // | \ - / |
    // \ - - - /
    int max_ = ceil(sqrt(n));
    while (k < max_){
        for (; turn == 1 ? y <= n - k : y >= k ; y += turn) {
            res[i--] = A[y][x];
            printf("Y: %d %d %c\n", y, x, turn == -1 ? '+' : '-');
        } y -= turn;
        x += turn;
        for (; turn == 1 ? y <= n - k : y >= k ; y += turn) {
            res[i--] = A[y][x];
            printf("X: %d %d %c\n", y, x, turn == -1 ? '+' : '-');

        } x -= turn;
        turn = -turn;
        x += turn;
        if (turn == 1) ++k;
    }
    res[0] = A[x][y];

    puts(res);
}

int main () {
    f();
}