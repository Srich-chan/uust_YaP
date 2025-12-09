// #include <cstdio>
// #include <cstring>
// #include <cmath>
//
// const unsigned size = 1024;
// char str[size];
//
// void f () {
//     puts("str:"); gets(str);
//     unsigned s = strlen(str);
//     const int n = int (ceil(sqrt(s)));
//
//     char A[n][n+1];
//     char res[n * n + 1];
//     int i=0;
//
//     for (; i < s; ++i) {
//         A[i / n][i % n] = str[i];
//     }
//     for (;i < n * n; ++i) {
//         A[i / n][i % n] = '#';
//     } --i;
//
//     for (auto& l : A)
//         printf("%s \n", l);
//     puts("");
//
//     // for res
//     int x=0, y=0, k=0, turn = 1;
//     // | / - - \
//     // | | / \ |
//     // | | X | |
//     // | \ - / |
//     // \ - - - /
//     int max_ = ceil(sqrt(n));
//     while (k < max_){
//         for (; turn == 1 ? y <= n - k : y >= k ; y += turn) {
//             res[i--] = A[y][x];
//             printf("Y: %d %d %c\n", y, x, turn == -1 ? '+' : '-');
//         } y -= turn;
//         x += turn;
//         for (; turn == 1 ? y <= n - k : y >= k ; y += turn) {
//             res[i--] = A[y][x];
//             printf("X: %d %d %c\n", y, x, turn == -1 ? '+' : '-');
//
//         } x -= turn;
//         turn = -turn;
//         x += turn;
//         if (turn == 1) ++k;
//     }
//     res[0] = A[x][y];
//
//     puts(res);
// }
//
//
//
//     // f();


// #include <cstdlib>
#include <cstdio>
#include <cmath>
#include <clocale>
#include <cstring>

unsigned wstrlen(const wchar_t * str) {
    unsigned i=0;
    while (str[i] != 0) ++i;
    return i;
}

wchar_t ** gimme_matrix(const wchar_t * str) {
    // void* pstr = &str;
    unsigned len = wstrlen(str);
    unsigned i = 0;
    unsigned n = ceil(sqrt(len));
    auto** A = new wchar_t *[n];
    for (int l=0; l < n; ++l) {
        A[l] = new wchar_t[n];
        for (int j=0; j < n; ++j)
            A[l][j] = i < len ? str[i++] : L'#';
    }
    return A;
}


// #include <memory>


int main () {
    wchar_t str[1024];
    scanf("%s", str);

}
