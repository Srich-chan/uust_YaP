#include <cstdio>
#include <cmath>

double ctg (double x) {
    return 1 / tan(x);
}

int main() {
    double alpha;
    printf("\nalpha = ");
    scanf("%lf", &alpha);
    const double eps = 0.5;

    alpha *= M_PI / 180;

    double c1 = cos(alpha * 4), c2 = cos(alpha * 2);
    if (c1 < eps - 1 |
        c2 < eps - 1 |
        alpha == 1.5 * M_PI) {
        printf("!!!: Uncorrect!\n");
        return -1;
    }


    double z1 = sin(4 * alpha) /
            (1 + cos(4 * alpha)) * cos(2 * alpha) /
                                    (1 + cos(2 * alpha));
    double z2 = ctg(1.5 * M_PI - alpha) * (8.0 / 9);

    printf("Z1 = %f", z1);
    printf("\nZ2 = %f", z2);


}