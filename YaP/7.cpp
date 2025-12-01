#include <cstdio>
#include <cmath>
#include <ctime>


const int generate = 0;


const int MAX = 400;
const int max_spaces = (int)log10(MAX) + 3;

int main () {
    printf("array size = ");
    int ms; scanf("%d" , &ms);
    int n = 1;
    while ((n * n - n) / 2 + n < ms) ++n;

    int A[n][n];

    int max = std::numeric_limits<int>::min();
    if (generate) srand(static_cast<unsigned int>(time(0)));

    for (int i=0; i < n; ++i) {
        for (int j=i; j < n; ++j) {
            int& curr = A[i][j];
            int& opos = A[j][i];
            if (ms == 0) {
                curr = 0;
                opos = 0;
            } else {

                if (generate)
                    curr = (rand() % MAX) * (rand() % 2 ? -1 : 1);
                else
                    scanf("%d", &curr);

                opos = curr;
                if (fabs(max) < fabs(curr)) max = curr;
                --ms;
            }
        }
    }
    char format[] = "%3d";
    if (max_spaces > 3 && max_spaces < 10) format[1] = char(48 + max_spaces);

    for (auto& i : A) {
        for (int& j : i) {
            printf(format, j);
        }
        puts("");
    }
}
