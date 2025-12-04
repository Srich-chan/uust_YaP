#include <cstdio>
#include <cstring>
#include <cstdlib>
// #include <windows.h>

typedef unsigned usize;

// usize count (const usize n) {
//     usize c=0, j=0;
//     int A[n], curr = 0;
//
//     return c;
// }

usize amir (const usize n) {
    if (n == 0) return 0;
    usize a = 1, b = 1, c;

    for (usize i = 0; i < n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;

}

usize hex (const usize n) {
    if (n == 0) return 0;
    usize a = 1, b = 1, c;
}





int main() {
    usize n;
    printf("n =");
    scanf("%u", &n);


    printf("Itog: %u", amir(n));
}