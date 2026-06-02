#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <windows.h>
#include "paths.h"
#include <string>
#include <io.h>
#include <fcntl.h>


using namespace std;


size_t count_this_pls(wstring str, const wstring& simbs = L"") {
    if (simbs.empty()) return 0ULL;
    size_t cnt = 0;
    for (const wchar_t& c : str) {
        for (const wchar_t& s : simbs) {
            if (c == s) {
                ++cnt;
                break;
            }
        }
    }
    return cnt;
}

void cyr(const wstring& str) {
    for (wchar_t c : str) {
        wcout << c;
    }
}

constexpr size_t buff_size = 10000ULL;

int main () {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(0, "Russian");
    // cout << 'а';
    // cout << 'ё';

    cyr(L"фывафыва");

}

