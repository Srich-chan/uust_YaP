#include <cstdio>

unsigned const MAX_STR_SIZE = 100;

char str[MAX_STR_SIZE];
unsigned i=0;


bool is_it() {
    return (str[i] == 'b' || str[i] == 'B') && str[++i] == '>');
}


int main () {
    scanf("%s", &str);

    unsigned size=0;
    while (str[size] != NULL)

    while (str[i] != NULL) {
        if (str[i] == '<') {
            if (str[++i] == '/') {
                ++i;
                if (is_it())
            }
            else if (is_it()) {

            }
        } else ++i;
    }
}