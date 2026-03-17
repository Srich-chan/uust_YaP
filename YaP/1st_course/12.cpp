#include <cstdio>
#include <cstdlib>
#include <locale>
#include <cwchar>
#include "windows.h"
// Путь проекта
#include "paths.h"

struct Player {
    int number; // номер футболиста
    wchar_t *surname; // Фамилия и инициалы
    int path_num; // номер маршрута
    int time; // Время выхода
    int goal_count;
    int *goals; // Динамически
    int warns;

    ~Player() {
        delete[] surname;
        delete[] goals;
    }
};

constexpr int buffer_size = 512;
constexpr int whole_size = 256;

struct Solution {
    FILE* file;
    Player *whole;
    int *whole_ind;
    Player *runtime;
    
    
    Solution() {
        file = _wfopen(p_PROJECT L".\\12. some some.txt", L"r, css='UTF-8'");

        if (!file) {
            fwprintf(stderr, L"Варнинг: всё сломалось");
            return;
        }

        int count=0;
        whole = new Player[whole_size];
        wchar_t buffer[buffer_size];
        wchar_t *line;
        wchar_t *context = nullptr;

        while (fgetws(buffer, buffer_size, file) && count < whole_size) {
            size_t len = wcslen(buffer);
            if (len && buffer[len - 1] == L'\n') {
                buffer[len - 1] = L'\0';
            }

            auto& curr = whole[count];
            
            // int number; // номер футболиста
            line = wcstok_s(buffer, L"; ", &context);
            if (!line) continue;
            curr.number = _wtoi(line);
            
            // wchar_t *surname; // Фамилия и инициалы
            line = wcstok_s(nullptr, L"; ", &context);
            if (!line) continue;
            wcscpy(curr.surname, line);
            
            // int path_num; // номер маршрута
            line = wcstok_s(nullptr, L"; ", &context);
            if (!line) continue;
            curr.path_num = _wtoi(line);
            
            // int time; // Время выхода
            line = wcstok_s(nullptr, L"; ", &context);
            if (!line) continue;
            curr.time = _wtoi(line);
            
            // int goal_count;
            line = wcstok_s(nullptr, L"; ", &context);
            if (!line) continue;
            curr.goal_count = _wtoi(line);
            
            // int *goals; // Время голов
            line = wcstok_s(nullptr, L"; ", &context);
            if (!line) continue;
            if(curr.goal_count > 0) {
                curr.goals = new int[curr.goal_count];
                wchar_t *sub_context;
                int sub_count = 0;
                while (sub_count < curr.goal_count) {
                    auto sub_line = wcstok_s(line, L", ", &sub_context);
                    // без проверок
                    curr.goals[++sub_count] = _wtoi(sub_line);
                }
            }

            // int warns;
            line = wcstok_s(nullptr, L"; ", &context);
            if (!line) continue;
            curr.warns = _wtoi(line);            
        }
        //--------------------------------------------------------------------------------------------------------------//
        // Сортировка
        
    }

    ~Solution() {
        if (file) fclose(file);  
        if (whole) delete[] whole;
        if (runtime) delete[] runtime;
    }
};




int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "Russian");

    Solution puk;
    return 0;
}