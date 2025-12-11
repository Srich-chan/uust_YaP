#include <cstdio>
#include <cmath>

int main() {
    int n, curr;
    printf("\nn = ");
    scanf("%d", &n);
//    int _matrix[n][n];
    // Format
    char format[32];
    int s = int (log10(n)) + 2;
    sprintf(format, "%%%d ", s);

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