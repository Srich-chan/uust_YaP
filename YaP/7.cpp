#include <cstdio>
#include <cmath>


int main () {
    int ms; scanf("%d" , &ms);

    int n = 1;
    while ((n * n - n) / 2 + n != ms) ++n;

    int A[n][n];
    int col;

    int x, y;
    for (int i=0; i < ms; ++i) {
        x = i / n;
        y = i % n;
        scanf("%d", &A[x][y]);
        if (x != y) A[y][x] = A[x][y];
    }

    // TODO: Output

}
