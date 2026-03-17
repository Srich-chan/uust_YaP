#include <cmath>
#include <cstdio>

typedef const float num;
typedef struct {
    num x;
    num y;
} Vec2D;


num dist (Vec2D a, Vec2D b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void t(bool a) {
    if (a) printf("true");
    else ;
}


int main() {
    float x,y;
    scanf("%f", &x); scanf("%f", &y);

    if (x > 0 && y > 0) {
        printf("%f");
    }
    // dist({1, 2}, {1, 2});
}