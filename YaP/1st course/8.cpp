#include <cstdio>

int main () {
    unsigned count = 0;
    int i = 0;
    char str[1025];
    char match[] = "aba";

    printf("str = "); gets(str);

    for (char& curr : str) {
        if (curr == match[i]) ++i;
        else i = curr == match[0];

        if (match[i] == 0) {
            ++count; i=1;
        }}

    printf("\n%d", count);
}