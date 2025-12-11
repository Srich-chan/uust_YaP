#include <cstdio>
#include <bitset>

int main () {
    unsigned long long m = 1;

    printf("%llu \n", m);
    m += ULLONG_MAX;
    printf("%llu \n", m);


}