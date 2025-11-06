#include <cstdio>

const unsigned MAX_STR_SIZE = 100;

char str[MAX_STR_SIZE];

int main () {
    scanf("%s", &str);
    unsigned c = 0;

    // A
    for (unsigned i=0; str[i] != NULL; ++i)
        if (str[i] == 'a') if (str[++i] == 'b') if (str[++i] == 'a') ++c;

    // // B :: not working properly hz
    // for (unsigned i=0; str[i] != NULL; ++i)
    //     if (str[i] == 'a') while (str[++i] == 'b' && str[++i] == 'a') ++c;


    printf("\n%d", c);
}