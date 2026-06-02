#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

int main() {
    // CRITICAL: Set console mode for UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // CRITICAL: Set stdout to wide character mode
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Set locales
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    // Read file
    const int buff_size = 1024;
    wchar_t buff[buff_size] = {0};


    // Now wcout should work

    std::wstring a = L"НУ ПАЗЯЗЯ";
    std::wcout << a << std::endl;

    return 0;
}