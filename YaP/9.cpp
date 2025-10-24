#include <cstdio>

unsigned const MAX_STR_SIZE = 100;

char str[MAX_STR_SIZE];
char res[MAX_STR_SIZE];
unsigned i=0;
unsigned j;

unsigned size(const char str[]) {
    unsigned c=0;
    for (; str[c] != '\0'; ++c);
    return c;
}


bool is_it(unsigned c) {
    return (str[c] == 'b' || str[c] == 'B') && str[++c] == '>';
}


int main () {
    // only ASCII without spaces
    scanf("%s", &str);
    unsigned s = size(str);
    
    
    while (i < s) {
        j = i;
        res[i] = str[i];
        
    }
}