#include <cstdio>
#include <cstring>
#include <cmath>

const unsigned size = 1024;
char str[size];


void f () {
    puts("str:"); gets(str);
    unsigned s = strlen(str);
    const int n = int (ceil(sqrt(s)));

    char A[n][n+1];
    char res[n * n + 1];
    int i=0;
    for (; i < s; ++i) {
        A[i / n][i % n] = str[i];
        printf("%c\n", str[i]);
    }
    for (;i < n * n; ++i) {
        A[i / n][i % n] = '#';
        puts("#");
    }

    printf("len = %d, n = %d, i = %d : %s \n", s, n, i, str);
    for (auto& l : A)
        printf("len = %llu : %s \n", strlen(l), l);
        ;
    puts("");

    // puts(res);
}

int main () {
    f();
}