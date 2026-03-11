#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <windows.h>
#include <cwchar>

// Просто путь проекта
#include "paths.h"



//TODO: Манагер
/*
# Возможности:
    1. [x] Считывать файл "13. ZOO A" и "13. ZOO B"
    2. [x] Стуктура ZOO
    3. [ ] Сортировать массив указателей ZOO
*/

constexpr int zoo_size = 256;
constexpr int buffer_size = 512;

constexpr wchar_t* _sep = L"; ";
constexpr wchar_t* _sub_sep = L", ";
constexpr wchar_t* p_input_A = p_PROJECT L"13. ZOO A_.txt";
constexpr wchar_t* p_input_B = p_PROJECT L"13. ZOO B .txt";
constexpr wchar_t* p_sorted = p_PROJECT L"13. indexes.txt";

constexpr bool dev = 1;


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



struct FILE_c // FILE closer
{
    // Не заморачивайся над ошибками 
    FILE* content;
    FILE_c(wchar_t* file_name=p_input_B){
        content = _wfopen(file_name, L"r, ccs=UTF-8");
        
        if (!content) {
            std::wcerr << L"Ошибка: не удалось открыть файл\n";
            throw std::runtime_error{"Закрываемся..."};
        }
    }

    ~FILE_c(){
        if (content)
        fclose(content);
    }
};


struct zoo_manager
{
    ZOO* pmi_pad=nullptr;
    int count=0;
    FILE_c input{};
    FILE_c sorted{p_sorted};
    wchar_t buffer[buffer_size];
    
    void sort(ZOO* pmi=nullptr, int count=0){
        if (!pmi) pmi = pmi_pad;
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (wcscmp(pmi[j].name, pmi[j + 1].name) > 0) {
                    ZOO t = pmi[j];
                    pmi[j] = pmi[j + 1];
                    pmi[j + 1] = t;
                }
            }
        }
    }
    

    void print_list(ZOO* list, int count, wchar_t* diet_condition=nullptr,
        wchar_t* sep=_sep, wchar_t* sub_sep=_sub_sep) {
        int i = 0;
        if (wcscmp(diet_condition, L"мясо!") == 0)
            std::wcout << L"Вывожу мясожрунов\n";
        else
            std::wcout << L"Вывожу животных\n";
        while (i < count){
            auto& curr = list[i++];
    
            if(!diet_condition || wcscmp(curr.diet_type, diet_condition) == 0)
                std::wcout 
                << curr.name        << sub_sep
                << curr.nick        << sub_sep
                << curr.diet_weight << sub_sep
                << curr.diet_type   << sub_sep
                << curr.age         << sep;
        }
    }
    

    ZOO* read_zoo(FILE* file, int& count, wchar_t* sep=_sub_sep) {

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


    zoo_manager() {
        pmi_pad = read_zoo(input.content, count);

        print_list(pmi_pad, count, nullptr, L"\n");
        sort(pmi_pad, count);
        print_list(pmi_pad, count, nullptr, L"\n");

    }

    ~zoo_manager() {
        delete[] pmi_pad;
    }
};



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    zoo_manager solution;
    // delete &solution;
    return 0;
}
