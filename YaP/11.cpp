// #include <cstdio>
// #include <cstdlib>
// void* ptrs[100];
// unsigned ptrs_i = 0;
//
// template <class T>
// T* _new(T* p) {
//     void* res = malloc(sizeof(T));
//     // printf("Declared array %p %p of size %llu on index %u \n", res, (T*)res, sizeof(T), ptrs_i);
//     ptrs[ptrs_i++] = res;
//     return (T*)res;
// }
// template <class T>
// T* _new_array(T* p, unsigned n) {
//     void* res = malloc(sizeof(T) * n);
//     // printf("Declared var %p of size %llu on index %u \n", res, n * sizeof(T), ptrs_i);
//     ptrs[ptrs_i++] = res;
//     return (T*)res;
// }
//


#include <cstdio>
#include <cmath>
#include <clocale>
#include <cstring>


typedef unsigned long u32;
u32 how_many(u32 num) {
    u32 t = 10, c = 1;
    while (num >= t) {
        t *= 10; ++c;
    }
    return c;
}

u32 dig_sum(u32 num, u32 c) {
    u32 t = 1, m = 10, s = 0;
    for (u32 i=0; i < c; ++i) {
        s += (num % m) / t;
        t = m; m *= 10;
    }
    return s;
}

int main() {
    setlocale(0, "Russian");
    u32 n;
    char buffer[1025];
    wprintf(L"Натуральное число: ");
    if (!scanf("%llu", &n)) return -2;
    // gets(buffer);

    sscanf_s(buffer, "%llu", &n);
    if (n == 0) {
        wprintf(L"Число не натуральное, абортинг...");
        return -1;
    }
    u32 c =  how_many(n);
    wprintf(L"Результат:\n\tКол-во цифр:%lu\n\tСумма цифр:%lu", c, dig_sum(n, c));

}