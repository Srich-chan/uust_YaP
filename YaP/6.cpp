#include <cstdio>
#include <cmath>

int main() {
    int n, curr;
    printf("\nn = ");
    scanf("%d", &n);
    const int ss = n;
    int _matrix[ss][ss];
    int s = int (log10(n)) + 2;

    for (int i=0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            curr = j - i + 1;
            if (curr <= 0)
                curr = 0;
            printf("%*d", s, curr);
            _matrix[i][j] = curr;
        } puts("");  //newline
    }
    
}