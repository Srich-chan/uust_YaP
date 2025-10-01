#include <cstdio>
#include <cmath>

double ctg (double x) {
    return 1 / tan(x);
}


int main() {
    float alpha;
    printf("\nalpha = ");
    scanf("%f", &alpha);
    const double PI = 3.14159;  // ...

    double z1 = sin(4 * alpha) / (1 + cos(4 * alpha)) * cos (2 * alpha) / (1 + cos(2 * alpha));
    double z2 = ctg(1.5 * PI - alpha);

    printf("Z1 = %f", z1);
    printf("\nZ2 = %f", z2);

    _sleep(10000);

}