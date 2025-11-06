#include <cstdio>
#include <cmath>
#include <string>


int main () {
    int ms; scanf("%d" , &ms);

    int n = 1;
    while ((n * n - n) / 2 + n != ms) ++n;

    int A[n][n];

    int x, y;
    int max = std::numeric_limits<int>::min();

    for (int i=0; i < ms; ++i) {
        x = i / n;
        y = i % n;
        scanf("%d", &A[x][y]);

        if (x != y) A[y][x] = A[x][y];

        if (A[x][y] > max) max = A[x][y];
    }
    // TODO: Output
    char spaces[(int)log10(max) + 1];
    for (char& i : spaces) i = ' ';

    // какой-то buffer
    std::basic_string<unsigned char> buffer;


}
