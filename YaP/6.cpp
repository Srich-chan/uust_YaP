#include <cstdio>
#include <cmath>

int s;
int num_of_spaces (int num) {
    static int step;
    static int sub;

    if (num == 1) {
        step = 10;
        sub = 0;
    }
    if (num == step) {
        step *= 10;
        ++sub;
        return sub;
    }
    return 0;
}

int main() {
    int n, curr;
    printf("\nn = ");
    scanf("%d", &n);
//    int _matrix[n][n];
    s = int (floor(log10(n))) + 1;
    int d;
    char max_spaces[s];
    for (char& i : max_spaces) i = ' ';

    char curr_spaces[s];
    for (char& i : curr_spaces) i = ' ';


    for (int i=0; i < n; ++i) {

        for (char& c : curr_spaces) c = ' ';

        for (int j = 0; j < n; ++j) {
            curr = j - i + 1;
            if (curr <= 0) {
                curr = 0;
                printf("%s", max_spaces);
            } else {
                d = num_of_spaces(curr);
                if (d > 0)
                    curr_spaces[s - d] = NULL;
                printf(curr_spaces);

            }

            printf("%d", curr);
//            _matrix[i][j] = curr;
        }
        printf("\n");
    }
}