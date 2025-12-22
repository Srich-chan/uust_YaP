#include <cstdio>
#include <cstring>
#include <cctype>

#define size 1024
char str[size], new_str[2 * size];
constexpr char matchA[] = "<BOLD>";
constexpr char matchB[] = "<END BOLD>";

unsigned offset = 0;
unsigned i = 0;


int main() {
    puts("str:");
    gets(str);

    for (;str[i] != 0; ++i) {
        int kek = str[i + 1] == '/';
        if (str[i] == '<' && toupper(str[i + 1 + kek]) == 'B' && str[i + 2 + kek] == '>') {
            strcat(
                new_str,
                !kek ? matchA : matchB
            );
            i += 3 + kek;
            offset += strlen(!kek ? matchA : matchB) - (3 + kek);
        }
        new_str[i + offset] = str[i];
    }
    puts(new_str);
}