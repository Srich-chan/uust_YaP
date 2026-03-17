#include <iostream>
#include <fstream>
#include <cstdio>
// #include <cstdlib>


#include <windows.h>
#include <cwchar>

#include "paths.h" // --> p_PROJECT  

constexpr const wchar_t* p_input_A = p_PROJECT L"13. ZOO A.txt";
constexpr const wchar_t* p_input_B = p_PROJECT L"13. ZOO B.txt";
constexpr const wchar_t* p_sorted = p_PROJECT L"13. indexes.txt";

constexpr const wchar_t* SEP = L"\n ";
constexpr const wchar_t* SUB_SEP = L", ";

constexpr size_t zoo_size = 256;
constexpr size_t buffer_size = 512;

struct ZOO {
    wchar_t* name = nullptr;
    wchar_t* nick = nullptr;
    wchar_t* diet_type = nullptr;
    float diet_weight = 0;
    int age = 0;

    bool operator>(const ZOO& another) const {
        return wcscmp(name, another.name) > 0;
    }
    bool operator<(const ZOO& another) const {
        return wcscmp(name, another.name) < 0;
    }



    void printself() const {
        std::wcout 
            << name         << SUB_SEP
            << nick         << SUB_SEP
            << diet_weight  << SUB_SEP
            << diet_type    << SUB_SEP
            << age          << SEP;
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
    ZOO** unsorted = nullptr;
    ZOO** sorted = nullptr;
    size_t len = 0;

    

    void sort() // задаёт sorted и unsorted как бы странно бы то не звучало
    {
        if (len == 0) throw std::domain_error{"Arrs::sort -> Массив пуст, милорд!"};
        // if (sorted) {
        //     delete[] sorted;
        //     sorted = nullptr;
        // } // Необязательно, т.к. на последнем поле стоит число, а `wcstol` срезает не-цифры.
        
        unsorted = new ZOO*[len];
        sorted = new ZOO*[len];
        for (size_t i = 0; i < len; ++i) {
            sorted[i] = &data[i];
            unsorted[i] = &data[i];
        }
        
        for (size_t i = 0; i < len - 1; ++i) {
            for (size_t j = 0; j < len - i - 1; ++j) {
                if (sorted[j] > sorted[j+1]) {
                    ZOO* temp = sorted[j];
                    sorted[j] = sorted[j + 1];
                    sorted[j + 1] = temp;
                }
            }
        }
    }


    void read_zoo(FILE* file) {
        if (data) {
            delete[] data;
            data = nullptr;
            len = 0;
        }
        
        data = new ZOO[zoo_size];
        wchar_t buffer[buffer_size];
        len = 0;

        while (len < zoo_size && fgetws(buffer, buffer_size, file)) {

            size_t blen = wcslen(buffer);
            if (blen > 0 && buffer[blen-1] == L'\n') 
                buffer[blen-1] = L'\0';
            
            if (blen < 5 || buffer[0] == L'#') continue; 
            // Пропускаем уж слишком короткие строки и что-то типо комментов
            
            wchar_t* context = nullptr;
            wchar_t* token = wcstok_s(buffer, SUB_SEP, &context);
            
            if (token) {
                data[len].name = _wcsdup(token);
                
                token = wcstok_s(nullptr, SUB_SEP, &context);
                if (token) data[len].nick = _wcsdup(token);
                else continue;
                token = wcstok_s(nullptr, SUB_SEP, &context);
                if (token) data[len].diet_type = _wcsdup(token);
                else continue;
                token = wcstok_s(nullptr, SUB_SEP, &context);
                if (token) data[len].diet_weight = wcstof(token, nullptr);
                else continue;
                token = wcstok_s(nullptr, SUB_SEP, &context);
                if (token) data[len].age = wcstol(token, nullptr, 10);
                else continue;
                ++len;
            }
        }

        std::wcout << L"Всего считано " <<len<< L" строк.\n";    
        if (!len) std::wcerr << L"Предупреждение: Ну ты попал конечно\n";
    }
    
    void print_sorted(bool diet_condition = false) const {
        if (!sorted) {
            std::wcerr << L"sorted не определён\n";
            return;
        }
        print_list(sorted, diet_condition);
    }

    void print(bool diet_condition = false) const {
        if (!unsorted) {
           throw std::domain_error{"void Arrs::print --> unsorted is undefinded"};
        }
        print_list(unsorted, diet_condition);
    }
    
    ~Arrs() {
        delete[] unsorted;
        delete[] sorted;
        delete[] data;
    }
    private:
        void print_list(ZOO** list, bool diet_condition = false) const {
            for (size_t i = 0; i < len; ++i) {
                if (!diet_condition || 
                    wcscmp(list[i]->diet_type, L"мясо") == 0 ||
                    wcscmp(list[i]->diet_type, L"meat") == 0) {
                    std::wcout << i+1 << ". ";
                    list[i]->printself();
                }
            }
        }
};


struct FILE_c // Файло закрыватор 
{ 

    FILE* content;
    wchar_t Mode[256];
    explicit FILE_c(const wchar_t* file_name=L"Noname", const wchar_t* mode = L"r") {
        wcscpy(Mode, mode);
        wchar_t mode_buffer[256];
        _snwprintf(mode_buffer, sizeof(mode_buffer), L"%ls, ccs=UTF-8", mode);

        content = _wfopen(file_name, mode_buffer);

        if (!content) {
            std::wcerr << L"Ошибка: не удалось открыть файл " << file_name << std::endl;
            throw std::runtime_error("INCORRECT PATH TO FILES");
        }
    }
    
    void operator<<(const wchar_t* out) const {
        fwprintf(this->content, L"%ls", out);
    }
    

    ~FILE_c() {
        if (content) {
            fclose(content);
        }
    }
};



void tests() {
    
    FILE_c input{p_input_B};
    Arrs arrs;
    arrs.read_zoo(input.content);
    arrs.sort();
    
    std::wcout << L"\n--- Исходные данные ---\n";
    arrs.print();
    
    std::wcout << L"\n--- Отсортированные данные ---\n";
    arrs.print_sorted();
    
    std::wcout << L"\n--- Только мясожруны ---\n";
    arrs.print_sorted(true);
}



struct MANAGER {
    private:
    FILE_c sorted{p_sorted};
    FILE_c input{p_input_B, L"a"};

    public:
    inline void show_options() const {
        /*
        1.     
        
        */
        std::wcout << 
        
        
    
        L"Дарова\n"
        L"Дарова\n"
        L"Дарова\n"
        L"Дарова\n"
        L"Дарова\n"
        ;
    }


};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    tests();
    return 0;
}