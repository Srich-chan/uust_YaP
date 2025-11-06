#include <cstdio>
#include <cmath>
#include <cstring>

int s;
int num_of_spaces (int num) {
    static int count = 0;
    return s - (int)log10(num);

}

int main() {
    int n, curr;
    printf("\nn = ");
    scanf("%d", &n);
//    int _matrix[n][n];
    s = (int)log10(n) + 1;

    char max_spaces[s];
    for (char& i : max_spaces) i = ' ';
    char curr_spaces[s];

    for (int i=0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            curr = j - i + 1;
            if (curr <= 0) {
                curr = 0;
                printf("%s", max_spaces);
            }
            else {
                for (char& k : curr_spaces) k = NULL;
                for (int k=0; k < num_of_spaces(curr); ++k);
                printf("%s", curr_spaces);
            }

            printf("%d", curr);
//            _matrix[i][j] = curr;
        }
        printf("\n");
    }
}