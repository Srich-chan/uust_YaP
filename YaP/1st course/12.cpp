#include <cstdio>
// #include <cstdlib>
#include <clocale>
#include <cstring>

typedef wchar_t str[256];

struct Player {
    unsigned number=1;
    str surname;    // wchar_t i_name, i_otchestvo;
    int bushido=0;
    unsigned exit_time = 0;
    unsigned goals=0;
    unsigned goals_time[32];
    unsigned warns = 0;

    void start_creating() {
        wprintf_s(L"Введите номер игрока: "); wscanf(L"%u", &number);
        wprintf_s(L"Введите фамилию и инициалы:"); wscanf(L"%s", &surname);
        wprintf_s(L"Введите МАРШРУТ: "); wscanf(L"%d", &bushido);
        wprintf_s(L"Кол-во голов: "); wscanf(L"%u", &goals);

        wprintf_s(L"Время голов: ");
        for (int i=0; i < goals; ++i)
            wscanf(L"%u", &goals_time[i]);

        wprintf_s(L"Кол-во предупреждений: "); wscanf(L"%u", &goals);

        // todo: Сортировка goals_time
    }
};

int main(void) {
    setlocale(0, "Russian");
    Player players[128];
    wprintf_s(L"");

    unsigned time=0;
    unsigned p = 0;
}