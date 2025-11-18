#include <cstdio>
#include <cmath>
#include <ctime>

// todo: Переделать

const bool generate = 1;
const int MAX = 100;

int s;
int main () {
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
                if (generate) {
                    curr = rand() % MAX;
                } else {
                    scanf("%d", &curr);
                }

                opos = curr;
                if (fabs(max) < fabs(curr)) max = curr;
                --ms;
            }
        }
    }

    // DO: GOVNO
    if (!generate)
    if (max != 0) s = (int)log10(max) + 1 + (max < 0);
    else s = 1;
    else s = (int)log10(MAX) + 1 ? :

    auto m = [](int a) -> int {
        if (a == 0) return ::s;

        return ::s - int(log10(fabs(a))) + (a < 0);
    };

    for (auto& i : A) {
        for (int& j : i) {
            for (int c=0; c < m(j); ++c) printf(" ");
            printf(" %d", j);
        }
        printf("\n");
    }


}
