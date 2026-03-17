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


typedef long long  ll;
ll how_many(ll num) {
    ll t = 10, c = 1;
    while (num >= t) {
        t *= 10; ++c;
    }
    return c;
}

ll dig_sum(ll num, ll c) {
    ll t = 1, m = 10, s = 0;
    for (ll i=0; i < c; ++i) {
        s += (num % m) / t;
        t = m; m *= 10;
    }
    return s;
}

int main() {
    setlocale(0, "Russian");
    ll n;
    wprintf(L"Натуральное число: ");
    if (scanf("%lld", &n) < 1) {
        fwprintf(stderr, L"Ошибка конвертации или что то вроде");
        return -2;
    }
    if (n <= 0) {
        fwprintf(stderr, L"Число не натуральное, абортинг...");
        return -1;
    }

    ll c =  how_many(n);
    wprintf(L"Результат:\n\tКол-во цифр:\t%lld\n\tСумма цифр:\t%lld", c, dig_sum(n, c));

}