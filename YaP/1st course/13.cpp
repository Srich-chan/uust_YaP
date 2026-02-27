#include <cstdio>
#include <clocale>
#include <cstring>
// #include <wchar.h>
#define DEBUG 1
#define ERROR_HANDLE 1
#define print if (DEBUG) wprintf
#define fprint if (DEBUG) fwprintf

typedef struct {
    wchar_t name[128];
    unsigned weight;
} diet;

struct ZOO {
    wchar_t name[128];
    wchar_t nick[128];
    diet diets[128];

};

// ZOO init (char _name[128], char _nick[128], diet &_diets, ...) {
ZOO init () {
    ZOO new_animal; // name, nick and diet

    // strcpy(new_animal.name, _name);
    // strcpy(new_animal.nick, _nick);

    wchar_t buff[1024];
    unsigned diet_len;

    name:
    print(L"Название животного: ");
    scanf("%s", &buff);

    if (wcslen(buff) >= 128) {
        fprint(stderr, L"\nСлишком длинное название. Ещё раз\n");
        goto name;
    }
    wcscpy(new_animal.name, buff);

    nickname:
    print(L"Кличка животного: ");
    scanf("%s", &buff);

    if (wcslen(buff) >= 128) {
        fprint(stderr, L"\nСлишком длинная кличка. Ещё раз\n");
        goto nickname;
    }
    wcscpy(new_animal.nick, buff);

    diet:
    print(L"Размерность рациона: ");
    scanf("%u", &diet_len);
#if ERROR_HANDLE
    if (diet_len > 128) {
        fprint(stderr, L"\nПоумерьте аппетиты животного\n");
        goto diet;
    } if (diet_len == 0) {
        fprint(stderr, L"\nХоть чем-то кормите.\n");
        goto diet;
    }
#endif

    while (diet_len > 0) {
        print(L"Что жрёт: ");
        print(L"%i. ", 129 - diet_len);

    }

    return new_animal;
}



int main () {
    setlocale(0, "Russian");

    ZOO Oleg = ZOO {
        L"Oleg",
        L"Gega",
        {
            {L"meat", 1}
        }
    };
    ZOO *he = &Oleg;

    wprintf(he->diets->name);

    if (he->diets->name == L"meat")
        wprintf(L"\n%ls кушац %ls", Oleg.name, Oleg.diets->name);



    else printf("\nidk");
}