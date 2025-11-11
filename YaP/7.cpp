#include <cstdio>
#include <cmath>
#include <ctime>

const bool generate = 1;


int s;
int main () {
    int ms; scanf("%d" , &ms);
    int n = 1;
    while ((n * n - n) / 2 + n < ms) ++n;

    int A[n][n];

    int max = std::numeric_limits<int>::min();

    if (generate) srand(static_cast<signed int>(time(0)));

    for (int i=0; i < n; ++i) {
        for (int j=i; j < n; ++j) {
            int& curr = A[i][j];
            int& opos = A[j][i];
            if (ms == 0) {
                curr = 0;
                opos = 0;
            } else {
                if (generate) {
                    curr = rand();
                } else {
                    scanf("%d", &curr);
                }

                opos = curr;
                if (max < curr) max = curr;
                --ms;
            }
        }
    }

    // DO: GOVNO
    if (max != 0) s = (int)log10(max) + 1;
    else s = 1;

    auto m = [](int a) -> int {
        if (a == 0) return ::s;
        return ::s - int(log10(a));
    };

    for (auto& i : A) {
        for (int& j : i) {
            for (int c=0; c < m(j); ++c) printf(" ");
            printf(" %d", j);
        }
        printf("\n");
    }


}
