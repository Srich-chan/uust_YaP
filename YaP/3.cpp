#include <cstdio>
#include <cmath>


int main() {
    float a, b, c;
    int Xs, Xe, dX;

    printf("\na = ");scanf("%f", &a);
    printf("b = ");scanf("%f", &b);
    printf("c = ");scanf("%f", &c);

    if (c == 0)
        return 1;

    printf("Start (Xs) = ");scanf("%d", &Xs);
    printf("End (Xe) = ");    scanf("%d", &Xe);
    printf("Step (dX) = ");   scanf("%d", &dX);

    const bool A = (((int)a | (int)b) ^ ((int)b & (int)c)) == 0;
    float res;
    int liner = 0;
    for (;Xs <= Xe; Xs += dX) {

        if (Xs < 1 && Xs - b != 0)
            res = a * Xs * Xs + b;
        else if (Xs > 1 && Xs + b == 0)
            res = (Xs - a) / Xs;
        else
            res = Xs / c;

        if (liner++ % 10 == 0)  printf("\n");
        else                    printf("\t");

        if (A)
            printf("%d", (int)res);
        else
            printf("%f", res);

    }
    _sleep(10000);
}