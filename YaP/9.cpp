#include <cctype>
#include <cstdio>
#include <cstring>
#include <cctype>

// Buffero OverFlowus


unsigned const size = 1024;
char str[size], new_str[size], buffer[size];

unsigned c, offset = 0;
int i = 0;


char matchA[] = "BOLD>";
char matchB[] = "END BOLD>";


int main() {
    puts("str:");
    gets(str);

    for (; i < strlen(str); ++i) {
        new_str[i + offset] = str[i];

        if (str[i] == '<') {
            ++i;
            if (tolower(str[i]) == 'b') {
                if (str[++i] == '>') {
                    strcat(new_str, matchA);
                    offset += strlen(matchA) - 2;
                }
            } else if (str[i] == '/') {
                ++i;
                if (str[i] == 'b' | str[i] == 'B')
                    if (str[++i] == '>') {
                    strcat(new_str, matchB);
                    offset += strlen(matchB) - 2;
                }
            } else if (str[i] == '<') --i; else ----i;
        }
    }
    printf("%s", new_str);

}