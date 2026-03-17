#include <iostream>
#include <fstream>
#include <cstdio>

#include <windows.h>
#include <cwchar>

#include "paths.h" // --> p_PROJECT  


constexpr const wchar_t* p_input_A = p_PROJECT L"13. ZOO A.txt";
constexpr const wchar_t* p_input_B = p_PROJECT L"13. ZOO B.txt";
constexpr const wchar_t* p_sorted = p_PROJECT L"13. indexes.txt";

constexpr const size_t zoo_size = 256;
constexpr const size_t buffer_size = 512;

struct ZOO {
    wchar_t* name = nullptr;
    wchar_t* nick = nullptr;
    wchar_t* diet_type = nullptr;
    float diet_weight = 0;
    int age = 0;

    bool operator>(const ZOO& another) const {
        if (wcscmp(name, another.name) == 0)
            return wcscmp(nick, another.nick) > 0;
        return wcscmp(name, another.name) > 0;
    }

    void printself(FILE* dest = stdin) const {
        fwprintf(dest, L"%ls, %ls, %ls, %f, %i\n",
            name, nick, diet_weight, diet_type, age);
    }

    ~ZOO() {
        delete[] name;
        delete[] nick;
        delete[] diet_type;
    }
};



struct FILE_c // Файло закрыватор 
{   
    FILE* content;
    bool writable;
    FILE_c(const wchar_t* file_name=L"Noname", const wchar_t* mode = L"r") {
        if (!mode || wcscmp(mode, L"") == 0) 
            throw std::domain_error{"FILE_c::FILE_c -> mode can't be empty"};
        writable = wcscmp(mode, L"r") != 0;

        wchar_t mode_buffer[256];
        _snwprintf(mode_buffer, sizeof(mode_buffer), L"%ls, ccs=UTF-8", mode);

        content = _wfopen(file_name, mode_buffer);

        if (!content) {
            std::wcerr << L"Ошибка: не удалось открыть файл " << file_name << '\n';
            throw std::runtime_error("Incorrect file path");
        }
    }
    
    ~FILE_c() {
        if (content) fclose(content);
    }
};



struct RUNTIME_DATA {
    private:
    wchar_t buffer[buffer_size];
    ZOO* data = nullptr;
    ZOO** free_list = nullptr; // Список освобождённых адресов
    size_t fri=0;

    // int get_int() {
    //     fgetws(buffer, buffer_size, stdin);
    //     return wcstol(buffer, nullptr, 10);
    // }
    int get_int () {
        int n;
        while (scanf("%li", &n) < 1) {
            std::wcerr << L"Ошибка. Ещё раз\n";
        };
        return n;
    }
    wchar_t* get_ws () {
        fgetws(buffer, 128, stdin);
        int blen = wcslen(buffer);
        if (buffer[blen-1] == L'\n') {
            buffer[blen-1] == L'\0';
        }
        return _wcsdup(buffer);
    }

    public:
    ZOO** list = nullptr;
    size_t len = 0;

    RUNTIME_DATA(FILE_c file=FILE_c{p_input_B}) {
        data = new ZOO[zoo_size];
        list = new ZOO*[zoo_size];
        free_list = new ZOO*[zoo_size];
        len = 0;

        while (len < zoo_size && fgetws(buffer, buffer_size, file.content)) {        
            // Пропускаем уж слишком короткие строки и что-то типо комментов
            if (wcslen(buffer) < 5 || buffer[0] == L'#') continue; 
            
            wchar_t* context = nullptr;
            wchar_t* token = wcstok_s(buffer, L", ", &context);
            data[len].name = _wcsdup(token);
                
            token = wcstok_s(nullptr, L", ", &context);
            data[len].nick = _wcsdup(token);
            
            token = wcstok_s(nullptr, L", ", &context);
            data[len].diet_type = _wcsdup(token);
            
            token = wcstok_s(nullptr, L", ", &context);
            data[len].diet_weight = wcstof(token, nullptr);
            
            token = wcstok_s(nullptr, L", ", &context);
            data[len].age = wcstol(token, nullptr, 10);
        
            list[len] = &data[len];
            ++len;
             
            if (token)  delete[] token;
            if (context)delete[] context;
            
        }

        std::wcout << L"Всего считано " <<len<< L" строк.\n";    
        if (!len) 
            throw std::domain_error {"WARNING: A KAK?"}; 
    }

    
    ZOO** sort()
    {
        if (len == 0) throw std::domain_error{"RUNTIME_DATA::sort -> Array is empty, sir!"};
        for (size_t i = 0; i < len - 1; ++i) {
            for (size_t j = 0; j < len - i - 1; ++j) {
                if (list[j] > list[j+1]) {
                    ZOO* temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                }
            }
        }
        return list;
    }

    void print_item() {
        std::wcout << L"\nВведите номер животины: ";
        int n = get_int();
        if (n < 1 || n >= len)
            std::wcerr << L"Животины под таким номером нет!\n";
        else {
            std::wcout << L"Животина под номером " <<n<< L":\n\t";
            list[n-1]->printself();
        }
    }

    void print(bool diet_condition = false) const {
        if (!list) {
           throw std::domain_error{"void RUNTIME_DATA::print --> list is undefinded"};
        }
        for (size_t i = 0; i < len; ++i) {
            if (!diet_condition || 
                wcscmp(list[i]->diet_type, L"мясо") == 0 ||
                wcscmp(list[i]->diet_type, L"meat") == 0) {
                std::wcout << i+1 << ". ";
                list[i]->printself();
            }
        }
    }

    void print_meat() const {
        print(true);
    }


    void new_item() {
        if (len == zoo_size - 1) {
            std::wcerr << L"Список переполнен\n";
        }

        ZOO* item;
        if (fri)
             item = free_list[--fri];
        else item = &data[len];

        std::wcout << L"\nВведите название животины: ";
        item->name = get_ws();

        std::wcout << L"\nВведите кличку/имя животины: ";
        item->nick = get_ws();

        std::wcout << L"\nВведите что жрёт: ";
        item->diet_type = get_ws();

        std::wcout << L"\nВведите сколько жрёт кг в день: ";
        fgetws(buffer, 128, stdin);
        item->diet_weight = wcstof(buffer, nullptr);

        std::wcout << L"\nВведите возраст: ";
        item->age = get_int();
        
        int n;
        for (n=0; n < len && *item > *list[n]; ++n) {
            
        }
        // n - итоговый индекс для item

        for (int i=len; i >= n; --i) {
            list[i-1] = list[i];
        }

        list[len] = &data[len];
        ++len;

    }

    void delete_item() {
        std::wcout << L"\nВведите номер провинившейся животины: ";
        int n = get_int();
        
    }

    
    ~RUNTIME_DATA() {
        delete[] list;
        delete[] free_list;
        delete[] data;
    }
};



struct MANAGER {
    private:
    FILE_c fsorted{p_sorted};
    FILE_c input{p_input_B, L"a+"};
    RUNTIME_DATA data;
    
    public:
    inline void show_options() const {
        
        
        std::wcout << 
        L"\n\n---   МЕНЮ   ---\n"
        "  -1. Стереть все данные и начать с начала\n"
        "  0. Выход\n"
        "\n---   Манипуляции   ---\n"
        "  1. Добавить животное\n"
        "  2. Удалить животное по номеру\n"
        "\n---   Вывод   ---\n"
        "  3. Вывести животное по номеру\n"
        "  4. Вывести всех\n"
        "  5. Вывести мясожрунов\n";
    }
    
    void main_cycle() {
        wchar_t buffer[buffer_size];
        while (1) {
            fgetws(buffer, buffer_size, stdin);
            int choice = wcstol(buffer, nullptr, 10);
            if (choice)
            switch(choice) {
                case -1:
                    data.~RUNTIME_DATA();
                    break;
                case 1:
                    data.new_item();
                    break;
                case 2:
                    data.delete_item();
                    break;
                case 3:
                    data.print_item();
                    break;
                case 4:
                    data.print();
                    break;
                case 5:
                    data.print_meat();
                    break;
                default:
                    std::wcout << L"";
            }
            else break;
        }
        close();
    }
    
    void close() {}
};

void tests() {
    
    FILE_c input{p_input_B};
    RUNTIME_DATA arrs{input};
    
    std::wcout << L"\n--- Исходные данные ---\n";
    arrs.print();
    
    arrs.sort();
    std::wcout << L"\n--- Отсортированные данные ---\n";
    arrs.print();
    
    std::wcout << L"\n--- Только мясожруны ---\n";
    arrs.print(true);
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    
    tests();
    return 0;
}