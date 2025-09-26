#include <cstdio>
#include <cmath>

typedef float num;
typedef num pos[2];
typedef pos rect[2];

enum Cords {
    X, Y
};

enum Rect_point {
    Upper_Left_Point,
    Lower_Right_Point
};

pos C = {-4, -4}; // Круг
num R = 4;

rect rects[3] = {
    {{-6, -3}, {-2, -6}},
    {{-4, 0}, {5, -3}},
    {{-2, 4}, {2, 0}}
};

bool in_circle(pos p) {
    return
    sqrt(pow(C[X] - p[X], 2) +
            pow(C[Y] - p[Y], 2)) <= R;
}


bool in_rects(pos p) {
    for (auto& rect : rects)
        if (
            rect[Upper_Left_Point][X] <= p[X] && rect[Lower_Right_Point][X] >= p[X] &&
            rect[Upper_Left_Point][Y] >= p[Y] && rect[Lower_Right_Point][Y] <= p[Y]
        )
            return true;
    return false;
}
int main() {
    float x, y;
    printf("\nx = ");
    scanf("%f", &x);
    printf("\ny = ");
    scanf("%f", &y);
    pos p = {x, y};

    if (in_circle(p) ^ in_rects(p))
         printf("true");
    else printf("false");

    _sleep(10000);
}