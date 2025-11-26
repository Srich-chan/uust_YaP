#include <cstdio>
#include <cmath>


int main() {
    float a, b, c, Xs, Xe, dX;

    printf("\na = ");scanf("%f", &a);
    printf("b = ");scanf("%f", &b);

    while (1) {
        printf("c(not zero) = ");scanf("%f", &c);
        if (c == 0) printf("NOT ZERO\n");
        else break;
    }


    const bool A = (((int)a | (int)b) ^ ((int)b & (int)c)) == 0;
    printf("(((int)a | (int)b) ^ ((int)b & (int)c)) = %s",
        A ? "True" : "False");

    printf("\n\nStart (Xs) = ");scanf("%f", &Xs);
    printf("End (Xe) = ");    scanf("%f", &Xe);
    printf("Step (dX) = ");   scanf("%f", &dX);

    int var;
    float res;
    printf("\n   X\t|\t    F   \t");////////////
    for (; Xs <= Xe; Xs += dX) {

        if (Xs < 1 && Xs - b != 0) {
            res = a * Xs * Xs + b;
        } else if (Xs > 1 && Xs + b == 0) {
            res = (Xs - a) / Xs;
        } else {
            res = Xs / c;
        }

        if (A) printf("\n%.2f\t|\t %d", Xs, (int)res);
        else   printf("\n%.2f\t|\t %.3f", Xs, res);
    }
}