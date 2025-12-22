#include <cstring>
#include <cstdio>
#include <cctype>

char matchA[] = "<B>";
char matchB[] = "</B>";

const char replaceA[] = "<BOLD>";
const char replaceB[] = "<END BOLD>";
char * replace;

char str[1024];
char res[1024];
int i=0, j=0;

int var = 0;

int main () {
    if (scanf("%s", &str) < 1) {fprintf(stderr, "Conversion error"); return -1;}
    unsigned l = strlen(str);

    for (; i < l; ++i) {
        if (str[i] != '<') res[j++] = str[i];

        else {
            ++i;
            strcpy(replace, replaceA);
            switch (tolower(str[i])) {
                case '/':
                    ++i;
                strcpy(replace, replaceB);
                case 'b':
                    if (str[i + 1] == '>')
                        strcat(res, replace);
                        j += strlen(replace);
                    break;

                    default: break;
            }

        }
    }

    printf("%s", res);
}