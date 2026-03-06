#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <windows.h>
#include <cwchar>

// Просто путь проекта
#include "path.h"


struct ZOO {
    wchar_t* name;
    wchar_t* nick;
    wchar_t* diet_type;
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
    FILE* sorted = _wfopen(PROJECT_PATH L"\\13. indexes.txt", L"w, ccs=UTF-8");
    FILE* file = _wfopen(PROJECT_PATH L"\\13. ZOO B.txt", L"r, ccs=UTF-8");
    ZOO* pmi_pad = nullptr;
    
    Solution() {
        if (!file) {
            std::wcerr << L"Ошибка: не удалось открыть файл\n";
            return;
        }
        
        pmi_pad = new ZOO[zoo_size]{};
        
        wchar_t buffer[buffer_size];
        wchar_t* line;
        wchar_t* context = nullptr;
        
        int count = 0;
        while (fgetws(buffer, buffer_size, file) && count < zoo_size) {
            size_t len = wcslen(buffer);
            if (len && buffer[len - 1] == L'\n') {
                buffer[len - 1] = L'\0';
            }
            // В случае хотя бы одного пустого поля скипаем всю строку
            // Название животного
            line = wcstok_s(buffer, L", ", &context);
            if (line == nullptr) continue;
            pmi_pad[count].name = new wchar_t[wcslen(line) + 1];
            wcscpy(pmi_pad[count].name, line);

            // Кличка/Имя
            line = wcstok_s(nullptr, L", ", &context);
            if (line == nullptr) continue;
            pmi_pad[count].nick = new wchar_t[wcslen(line) + 1];
            wcscpy(pmi_pad[count].nick, line);

            // Хавка
            line = wcstok_s(nullptr, L", ", &context);
            if (line == nullptr) continue;
            pmi_pad[count].diet_type = new wchar_t[wcslen(line) + 1];
            wcscpy(pmi_pad[count].diet_type, line);

            // Вес хавки
            line = wcstok_s(nullptr, L", ", &context);
            if (line == nullptr) continue;
            pmi_pad[count].diet_weight = wcstof(line, nullptr);

            // Возраст
            line = wcstok_s(nullptr, L", ", &context);
            if (line == nullptr) continue;
            pmi_pad[count].age = _wtoi(line);

            ++count;
        }
        std::wcout << L"\nВсего насчитано сокурсников: " << count << L'\n';
        
        
        int sorted_indexes[zoo_size];
        for (int i=0; i < count; ++i) {
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

        // вывод мясожрунов
        std::wcout << L"Мясожруны:\n";
        for (int i = 0; i < count; i++) {
            int idx = sorted_indexes[i];
            if (wcscmp(pmi_pad[idx].diet_type, L"meat") == 0 ||
                wcscmp(pmi_pad[idx].diet_type, L"мясо") == 0) {
                std::wcout << pmi_pad[idx].name     << L", "
                           << pmi_pad[idx].nick     << L", "
                           << pmi_pad[idx].diet_type<< L", "
                           << pmi_pad[idx].diet_weight<< L", "
                           << pmi_pad[idx].age      << L'\n';
            }
        }
        // ВЫВОД ВСЕХ
        #if 1
        std::wcout << L"\n\nВсе:\n";
        for (int i = 0; i < count; i++) {
            int idx = sorted_indexes[i];
            std::wcout << pmi_pad[idx].name         << L", "
                       << pmi_pad[idx].nick         << L", "
                       << pmi_pad[idx].diet_type    << L", "
                       << pmi_pad[idx].diet_weight  << L", "
                       << pmi_pad[idx].age          << L'\n';
        }
        #endif

        #if 1
        for(int i=0; i < count; ++i) {
            fwprintf(sorted, L"%i\n", sorted_indexes[i] + 1);
        }
        #endif
    }

    ~Solution() {
        if (file) fclose(file);
        if (sorted) fclose(sorted);
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

//todo: Манагер