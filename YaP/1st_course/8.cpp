#include <cstdio>

int main () {
    char str[1025];
    char match[] = "aba";

    unsigned count = 0;
    unsigned i = 0;
    printf("str = "); gets(str);

    for (char& curr : str) {
        if (curr == match[i]) ++i;
        else i = curr == match[0];

        if (match[i] == '\0') {
            ++count; i = 1;
        }
    }
    // ababa => 2
    printf("RESULT = %d", count);
}