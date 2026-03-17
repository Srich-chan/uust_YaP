#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <windows.h>
#include <cwchar>

// Просто путь проекта
#include "paths.h" // => p_PROJECT  

constexpr wchar_t* p_input_A = p_PROJECT L"13. ZOO A.txt";
constexpr wchar_t* p_input_B = p_PROJECT L"13. ZOO B.txt";
constexpr wchar_t* p_sorted = p_PROJECT L"13. indexes.txt";

constexpr size_t zoo_size = 256;
constexpr size_t buffer_size = 512;

constexpr wchar_t* SEP = L"\n ";
constexpr wchar_t* SUB_SEP = L", ";


struct ZOO {
    wchar_t* name = L"NULL";
    wchar_t* nick = L"NULL";
    wchar_t* diet_type = L"NULL";
    float diet_weight = 0;
    int age = 0;


    void printself() const {
    std::wcout 
        << name        << SUB_SEP
        << nick        << SUB_SEP
        << diet_weight << SUB_SEP
        << diet_type   << SUB_SEP
        << age         << SEP;
    }
    
    ~ZOO() {
        delete[] name;
        delete[] nick;
        delete[] diet_type;
    }
};





struct Arrs {
        
    public:
    ZOO* data = nullptr;
    ZOO** sorted = nullptr;
    size_t len = 0;


    void sort(){
        // <| Код говно |>
        if (len == 0) throw std::domain_error{"Arrs::sort -> Не тот порядок функций при первичной инициализации! (Arrs.len = 0)"};

        sorted = new ZOO*[len];
        ZOO* ptr_a = data;
        ZOO** sptr_b = sorted;

        while (sptr_b != sorted + len)
            *(sptr_b++) = ptr_a++;
        

        for (int i = 0; i < len - 1; ++i) {
            for (int j = 0; j < len - i - 1; ++j) {
                if (wcscmp(sorted[j]->name, sorted[j + 1]->name) > 0) {
                    ZOO* t = sorted[j];
                    sorted[j] = sorted[j+1];
                    sorted[j] = t;
                }
            }
        }
    }


    ZOO* read_zoo(FILE* file) {
        data = new ZOO[zoo_size];
        wchar_t buffer[buffer_size];

        while (fgetws(buffer, buffer_size, file) && len < zoo_size) {
            size_t blen = wcslen(buffer)-1;
            if (buffer[blen] == '\n') buffer[blen]; 
            
            wchar_t* token = wcstok(buffer, SUB_SEP);
            if (!token) continue;

            data[len].name = _wcsdup(token); // _wcsdup() <=> new wchar_t*()

            token = wcstok(nullptr, SUB_SEP);
            if (!token) continue;
            data[len].nick = _wcsdup(token);

            token = wcstok(nullptr, SUB_SEP);
            if (!token) continue;
            data[len].diet_type = _wcsdup(token);

            token = wcstok(nullptr, SUB_SEP);
            if (!token) continue;
            data[len].diet_weight = wcstof(token, nullptr);

            token = wcstok(nullptr, SUB_SEP);
            if (!token) continue;
            data[len].age = wcstol(token, nullptr, 10);
            
            ++len;
        }

        std::wcout
        << L"Всего считано " <<len<< L" строк.\n";    
        
        if (!len) std::wcerr << L"                                                                                                                                              \n";


        return data;
    }


    void print_list(ZOO* list, size_t len, bool diet_condition=0) {
        for (int i=0; i < len; ++i)
            if(!diet_condition  || wcscmp(list[i].diet_type, L"мясо") == 0
                                || wcscmp(list[i].diet_type, L"meat") == 0)
                list[i].printself();
    }
    


    void print(bool diet_condition=0) {
        print_list(data, len, diet_condition);
    }
 

    Arrs() {
        
    }

    ~Arrs() {
        if (sorted) delete[] sorted;
        if (data) delete[] data;
    }

};



struct FILE_C // Файло закрыватор
{
    FILE* content;
    FILE_C(wchar_t* file_name){
    content = _wfopen(file_name, L"r, ccs=UTF-8");

        if (!content) {
            std::wcerr << L"Ошибка: не удалось открыть файл\n";
            throw std::domain_error{"Закрываемся"};
        }
    }

    ~FILE_C(){
        if (content)
            fclose(content);
    }
};


void tests() {
    FILE_C input{p_input_B};
    // FILE_c output{p_sorted};
    
    Arrs arrs{};
    arrs.read_zoo(input.content);
    arrs.print();
    // arrs.sort();



}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    tests();
    return 0;
}