#include <cstdio>
#include <cmath>
#include <locale.h>

double ctg (double x) {
    return 1 / tan(x);
}

int main() {
    setlocale(LC_ALL, "Russian");
    double alpha;
    double c1, c2;
    do {
    wprintf(L"\nalpha(в градусах) = ");
    scanf("%lf", &alpha);

        alpha *= 1.0 / 180 * M_PI;
        c1 = cos(alpha * 4), c2 = cos(alpha * 2);
        printf("alpha = %lf\nc1 = %lf\nc2 = %lf\n",
            alpha, c1, c2);
        if (c1 == -1 |
            c2 == -1 |
            alpha == 1.5 * M_PI)
            wprintf(L"Error: Zero Division\nTry again\n");
        else
            break;

    } while (1);


    double z1 = sin(4 * alpha) /
            (1 + c1) * c2 / (1 + c2);
    double z2 = ctg(1.5 * M_PI - alpha) * (8.0 / 9);

    printf("Z1 = %lf", z1);
    printf("\nZ2 = %lf", z2);
}