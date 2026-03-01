#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <windows.h>
#include <cwchar>

#include "path.h"


struct ZOO {
    wchar_t* name = nullptr;
    wchar_t* nick = nullptr;
    wchar_t* diet_type = nullptr;
    float diet_weight = 0;
    int age = 0;

    ~ZOO() {
        delete[] name;
        delete[] nick;
        delete[] diet_type;
    }
};

constexpr int zoo_size = 256;
constexpr int buffer_size = 512;

struct Solution {
    FILE* file = _wfopen(PROJECT_PATH L"\\13. ZOO B.txt", L"r, ccs=UTF-8");
    ZOO* pmi_pad = nullptr;
    int count = 0;

    Solution() {
        if (!file) {
            std::wcerr << L"Ошибка: не удалось открыть файл\n";
            return;
        }

        pmi_pad = new ZOO[zoo_size]{};

        wchar_t buffer[buffer_size];
        wchar_t* line;
        wchar_t* context = nullptr;

        while (fgetws(buffer, buffer_size, file) && count < zoo_size) {
            // убираем перенос строки
            size_t len = wcslen(buffer);
            if (len && buffer[len - 1] == L'\n') {
                buffer[len - 1] = L'\0';
            }

            line = wcstok_s(buffer, L", ", &context);
            if (line == nullptr) continue;

            pmi_pad[count].name = new wchar_t[wcslen(line) + 1];
            wcscpy(pmi_pad[count].name, line);

            line = wcstok_s(nullptr, L", ", &context);
            if (line == nullptr) continue;
            pmi_pad[count].nick = new wchar_t[wcslen(line) + 1];
            wcscpy(pmi_pad[count].nick, line);

            line = wcstok_s(nullptr, L", ", &context);
            if (line == nullptr) continue;
            pmi_pad[count].diet_type = new wchar_t[wcslen(line) + 1];
            wcscpy(pmi_pad[count].diet_type, line);

            line = wcstok_s(nullptr, L", ", &context);
            if (line == nullptr) continue;
            pmi_pad[count].diet_weight = wcstof(line, nullptr);

            line = wcstok_s(nullptr, L", ", &context);
            if (line == nullptr) continue;
            pmi_pad[count].age = _wtoi(line);

            ++count;
        }
        std::wcout << L"Всего считано сокурсников: " << count << L'\n';

        // сортировка индексов по имени
        int* sorted_indexes = new int[count];
        for (int i = 0; i < count; i++) {
            sorted_indexes[i] = i;
        }
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (wcscmp(pmi_pad[sorted_indexes[j]].name,
                           pmi_pad[sorted_indexes[j + 1]].name) > 0) {
                    int temp = sorted_indexes[j];
                    sorted_indexes[j] = sorted_indexes[j + 1];
                    sorted_indexes[j + 1] = temp;
                }
            }
        }

        // вывод хищников
        for (int i = 0; i < count; i++) {
            int idx = sorted_indexes[i];
            if (wcscmp(pmi_pad[idx].diet_type, L"meat") == 0 ||
                wcscmp(pmi_pad[idx].diet_type, L"мясо") == 0) {
                std::wcout << pmi_pad[idx].name << L", "
                           << pmi_pad[idx].nick << L", "
                           << pmi_pad[idx].diet_type << L", "
                           << pmi_pad[idx].age << L'\n';
            }
        }
        delete[] sorted_indexes;
    }

    ~Solution() {
        if (file) fclose(file);
        if (pmi_pad) delete[] pmi_pad;

    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Solution solution;
    return 0;
}