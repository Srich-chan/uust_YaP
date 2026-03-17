#include <cstdio>
#include <cstring>
#include <cctype>

#define SIZE 1024
char str[SIZE], new_str[2 * SIZE];
constexpr char matchA[] = "<BOLD>";
constexpr char matchB[] = "<END BOLD>";

unsigned offset = 0;
unsigned i = 0;

int main() {
    puts("str:");
    gets(str);

    for (;str[i] != 0; ++i) {
        int is_end = str[i + 1] == '/';
        if (str[i] == '<' && toupper(str[i + 1 + is_end]) == 'B' && str[i + 2 + is_end] == '>') {
            strcat(
                new_str,
                !is_end ? matchA : matchB
            );
            i += 2 + is_end;
            offset += strlen(!is_end ? matchA : matchB) - (3 + is_end);
        }
        else new_str[i + offset] = str[i];
    }
    puts(new_str);
}