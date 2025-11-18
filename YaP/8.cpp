// A
#include <cstdio>
// B
#include <iostream>

int main () {
    unsigned c = 0;
    const unsigned MAX_STR_SIZE = 100;
    char str[MAX_STR_SIZE]; // A, B1
    // std::basic_string<char> str; // B2
    // // A
    // scanf("%s", &str);
    // for (unsigned i=0; str[i] != NULL; ++i)
    //     if (str[i] == 'a') if (str[++i] == 'b') if (str[++i] == 'a') ++c;

    // B1
    char match[] = "aba";
    // std::getline(std::cin, str);
    // scanf("%s", &str);

    unsigned i = 0, j = 0;
    puts; gets(str);
    while (str[i] != '\0') {
        if (str[i] == match[j]) ++j;
        else if (j > 0 | str[i] == match[j - 1]) --j;
        else j = 0;

        if (j == 2) {
            j = 1;
            ++c;
        }
        ++i;
    }

    printf("\n%d", c);
}