#include <cstdio>
#include <cmath>


int main() {
    float a, b, c, Xs, Xe, dX;

    printf("\na = ");scanf("%f", &a);
    printf("b = ");scanf("%f", &b);
    printf("c = ");scanf("%f", &c);

    const bool A = (((int)a | (int)b) ^ ((int)b & (int)c)) == 0;
    printf("(((int)a | (int)b) ^ ((int)b & (int)c)) = ");
    if (A) printf("True"); else printf("False");

    if (c == 0)
        return 1;

    printf("\n\nStart (Xs) = ");scanf("%f", &Xs);
    printf("End (Xe) = ");    scanf("%f", &Xe);
    printf("Step (dX) = ");   scanf("%f", &dX);

    int var;
    float res;
    while (Xs <= Xe) {

        if (Xs < 1 && Xs - b != 0) {
            var = 1;
            res = a * Xs * Xs + b;
        }
        else if (Xs > 1 && Xs + b == 0) {
            var = 2;
            res = (Xs - a) / Xs;
        }
        else {
            var = 3;
            res = Xs / c;
        }

        if (A)
            printf("\nx=%.2f   \tF=%d   \t%d", Xs, (int)res, var);
        else
            printf("\nx=%.2f   \tF=%.3f   \t%d", Xs, res, var);

        Xs += dX;
    }
}