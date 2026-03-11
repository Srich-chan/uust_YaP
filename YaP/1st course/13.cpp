#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <windows.h>
#include <cwchar>

// Просто путь проекта
#include "paths.h"


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


//TODO: Манагер
/*
# Возможности:
    1. [x] Считывать файл "13. ZOO A" и "13. ZOO B"
    2. [x] Стуктура ZOO
    3. [ ] Сортировать массив указателей ZOO
*/





constexpr int zoo_size = 256;
constexpr int buffer_size = 512;

constexpr wchar_t* sep = L"; ";
constexpr wchar_t* sub_sep = L", ";
constexpr wchar_t* p_input_A = p_PROJECT L"13. ZOO A_.txt";
constexpr wchar_t* p_input_B = p_PROJECT L"13. ZOO B.txt";
constexpr wchar_t* p_sorted = p_PROJECT L"13. indexes.txt";

constexpr bool dev = 1;

ZOO* read_zoo(FILE* file, int& count) {
    ZOO* pmi_pad = new ZOO[zoo_size];
    wchar_t buffer[buffer_size];
    count = 0;

    while (fgetws(buffer, buffer_size, file) && count < zoo_size) {
        wchar_t* token = wcstok(buffer, sep);
        if (!token) continue;

        pmi_pad[count].name = _wcsdup(token); // _wcsdup() <=> new wchar_t*()

        token = wcstok(nullptr, sep);
        if (!token) continue;
        pmi_pad[count].nick = _wcsdup(token);

        token = wcstok(nullptr, sep);
        if (!token) continue;
        pmi_pad[count].diet_type = _wcsdup(token);

        token = wcstok(nullptr, sep);
        if (!token) continue;
        pmi_pad[count].diet_weight = wcstof(token, nullptr);

        token = wcstok(nullptr, sep);
        if (!token) continue;
        pmi_pad[count].age = wcstol(token, nullptr, 10);
        
        ++count;
    }
    if (dev) 
        std::wcout
        << L"Всего считано " <<count<< L" : строк.\n";    

    return pmi_pad;
}


void sort(ZOO* pmi, int count){
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (wcscmp(pmi[j].name, pmi[j + 1].name) > 0) {
                auto t = pmi[j];
                pmi[j] = pmi[j + 1];
                pmi[j + 1] = t;
            }
        }
    }
}



void print_list(ZOO* list, int count, wchar_t* diet_condition=nullptr) {
    int i = 0;
    while (i < count){
        auto& curr = list[i++];

        if(!diet_condition || wcscmp(curr.diet_type, diet_condition) == 0)
            std::wcout 
            << curr.name        << sub_sep
            << curr.nick        << sub_sep
            << curr.diet_weight << sub_sep
            << curr.diet_type   << sub_sep
            << curr.age         << sub_sep;
    }
}

struct FILE_c // FILE closer
{
    // Не заморачивайся над ошибками 
    FILE* file;
    FILE_c(wchar_t* file_name=p_input_B){
    file = _wfopen(file_name, L"r, ccs=UTF-8");

        if (!file) {
            std::wcerr << L"Ошибка: не удалось открыть файл\n";
            throw std::runtime_error("Закрываемся");
        }
    }

    ~FILE_c(){
        if (file)
            fclose(file);
    }
};


struct Solution {
    FILE_c input{};
    FILE_c sorted{p_sorted};
    wchar_t buffer[buffer_size];

    Solution() {
        while (fgetws(buffer, buffer_size, input.file)) {
            std::wcout << buffer;
        }
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Solution solution;
    return 0;
}
