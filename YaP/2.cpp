#include <cstdio>
#include <cmath>


typedef float num;
//typedef num pos[2];
typedef struct {
    num x;
    num y;
} pos;
//typedef pos rect[2];
typedef struct {
    pos a;
    pos d;
} rect;
typedef struct {
    pos C;
    num R;
} circ;
// Круг
//pos C {-4, -4};
//num R = 4;
circ a {{-4, -4}, 4};
// Прямоугольники
rect rects[3] {
    {{-6, -3}, {-2, -6}},
    {{-4, 0}, {5, -3}},
    {{-2, 4}, {2, 0}}
};

bool in_circle(pos p) {
    return sqrt(
            pow(a.C.x - p.x, 2) +
            pow(a.C.y - p.y, 2)) <= a.R;
}

bool in_rects(pos p) {
    for (auto& rect : rects)
        if (
            rect.a.x <= p.x && rect.d.x >= p.x &&
            rect.a.y >= p.y && rect.d.y <= p.y
        )
            return true;
    return false;
}
int main() {
    float x, y;
    printf("\nx = ");
    scanf("%f", &x);
    printf("y = ");
    scanf("%f", &y);
    pos p {x, y};

    if (in_circle(p) ^ in_rects(p))
         printf("true");
    else printf("false");

}