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


typedef unsigned long long u64;
u64 how_many(u64 num) {
    u64 t = 10, c = 1;
    while (num >= t) {
        t *= 10; ++c;
    }
    return c;
}

u64 dig_sum(u64 num, u64 c) {
    u64 t = 1, m = 10, s = 0;
    for (u64 i=0; i < c; ++i) {
        s += (num % m) / t;
        t = m; m *= 10;
    }
    return s;
}

int main() {
    setlocale(0, "Russian");
    u64 n;
    wprintf(L"Натуральное число: ");
    scanf("%llu", &n);
    if (n == 0) {
        wprintf(L"Число не натуральное, абортинг...");
        return -1;
    }
    u64 c =  how_many(n);
    wprintf(L"Результат:\n\tКол-во цифр:%llu\n\tСумма цифр:%llu", c, dig_sum(n, c));

}