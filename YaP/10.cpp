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
    }

    for (auto& l : A)
        printf("%s \n", l);
    puts("");

    i=0; // for res
    int x=0, y=0, k=0, turn = 1;
    // | / - - \
    // | | / \ |
    // | | X | |
    // | \ - / |
    // \ - - - /
    int max_ = ceil(sqrt(n));
    while (k < max_){
        for (; turn == 1 ? y <= n : y >= k ; y += turn) {
            res[i--] = A[y][x];
        } y -= turn;
        x += turn;
        for (; turn == 1 ? y <= n : y >= k ; y += turn) {
            res[i--] = A[y][x];
        } x -= turn;
        turn = -turn;
        x += turn;

        ++k;
    }
    res[0] = A[x][y];

    puts(res);
}

int main () {
    f();
}