#include <cstdio>
#include <cmath>

int main() {
    int n, curr;
    printf("\nn = ");
    scanf("%d", &n);
//    int _matrix[n][n];

    char format[4] = "%3d";
    int s = int (log10(n)) + 2;
    if (s > 9) { puts("n is to big");}
    else if (s > 3) format[1] = char(s + 48);

    for (int i=0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            curr = j - i + 1;
            if (curr <= 0)
                curr = 0;
            printf(format, curr);
//            _matrix[i][j] = curr;
        } puts("");  //newline
    }
    
}