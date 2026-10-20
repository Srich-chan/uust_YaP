// #define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include "Classes.h"

int main () {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Monarchy Britain{"Британия"};
    {
        Republic France{"Франция"};
        State::printAll();
    }
    Kingdom Rus{"Россия"};
    State::printAll();
}