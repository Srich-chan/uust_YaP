#include <cstdio>
#include <cmath>

int s;
int num_of_spaces (int num) {
    return s - (int)log10(num);

}

int main() {
    int n, curr;
    printf("\nn = ");
    scanf("%d", &n);
//    int _matrix[n][n];
    s = (int)log10(n) + 2;
    for (int i=0; i < n; ++i) {

        for (int j = 0; j < n; ++j) {
            curr = j - i + 1;
            if (curr < 0) {curr = 0; for (int sp=0; sp < s; ++sp) printf(" ");}
            else for (int sp=0; sp < num_of_spaces(curr); ++ sp) printf(" ");

            printf("%d", curr);
//            _matrix[i][j] = curr;
        }
        printf("\n");
    }
}