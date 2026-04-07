#include <iostream>
#include <cstdio>
#include <windows.h>
#include <cwchar>
#include "paths.h" // --> p_PROJECT  

constexpr const wchar_t* p_const = p_PROJECT L"13 ZOO B.txt";
constexpr const wchar_t* p_dynamic = p_PROJECT L"13. indexes.txt";
constexpr size_t zoo_size = 256;
constexpr size_t buffer_size = 512;

// Функции для удобства
void trim_left (wchar_t* str) {
    int n = 0;
    while (str[n] == L' ' || str[n] == L'\t') ++n;
    if (!n) return;

    int i=0;
    for (; str[i+n] != L'\0'; ++i) {
        str[i] = str[i+n];
    }
    str[i] = L'\0';
}

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
    bool operator<(const ZOO& another) const {
        return another > *this;
    }

    void printself(FILE* dest = stdout) const {
        fwprintf(dest, L"%ls; %ls; %ls; %.2f; %i\n",
            name, nick,  diet_type, diet_weight, age);
    }

    void free_str() {
        delete[] name;
        delete[] nick;
        delete[] diet_type;
    }

    ~ZOO() {
        free_str();
    }
};

// Файло закрыватор и прочее
struct FILE_c
{
    const wchar_t* name = nullptr;
    FILE* content = nullptr;

    explicit FILE_c(const wchar_t* file_name=p_const, const wchar_t* Mode = L"r") {
        name = wcsdup(file_name);
        wchar_t mode_buffer[buffer_size];
        _snwprintf(mode_buffer, buffer_size, L"%ls, ccs=UTF-8", Mode);
        content = _wfopen(file_name, mode_buffer);
    }

    ~FILE_c() {
        if (content) fclose(content);
        delete[] name;
    }

    void clear() {
        _wfreopen(name, L"w+", content);
    }

    bool is_empty() {
        long start = ftell(content);
        fseek(content, start, SEEK_END);
        long size = ftell(content);
        fseek(content, start, SEEK_SET);
        return size == 0;
    }
};

// Список
struct RUNTIME_DATA {
private:
    wchar_t buffer[buffer_size];
    ZOO* data=nullptr;
    ZOO** free_list = nullptr;
    size_t fri=0;

    int get_int () {
        fgetws(buffer, buffer_size, stdin);
        return wcstol(buffer, nullptr, 10);
    }

    wchar_t* get_ws () {
        fgetws(buffer, buffer_size, stdin);
        size_t blen = wcslen(buffer);
        if (buffer[blen-1] == L'\n') {
            buffer[blen-1] = L'\0';
        }
        wchar_t* str = _wcsdup(buffer);
        trim_left(str);
        return str;
    }
public:
    ZOO** list = nullptr;
    size_t len = 0;
    RUNTIME_DATA(bool _new = true) {
        data = new ZOO[zoo_size];
        list = new ZOO*[zoo_size];
        free_list = new ZOO*[zoo_size];
        len = 0;
        fri = 0;

        bool is_sorted = !_new && !FILE_c{p_dynamic}.is_empty();
        FILE_c file{is_sorted?
            p_dynamic : p_const
        };

        while (len < zoo_size && fgetws(buffer, buffer_size, file.content)) {
            // Пропускаем уж слишком короткие строки и что-то типо комментов
            if (wcslen(buffer) < 5 || buffer[0] == L'#') continue;
            wchar_t* context = nullptr;
            wchar_t* token = wcstok_s(buffer, L";", &context);
            trim_left(token);
            data[len].name = _wcsdup(token);

            token = wcstok_s(nullptr, L";", &context);
            trim_left(token);
            data[len].nick = _wcsdup(token);

            token = wcstok_s(nullptr, L";", &context);
            trim_left(token);
            data[len].diet_type = _wcsdup(token);

            token = wcstok_s(nullptr, L";", &context);
            data[len].diet_weight = wcstof(token, nullptr);

            token = wcstok_s(nullptr, L";", &context);
            data[len].age = wcstol(token, nullptr, 10);

            list[len] = &data[len];
            ++len;

            if (!is_sorted) this->sort();
        }

        std::wcout << L"Всего считано " <<len<< L" строк.\n";
        if (!len)
            throw std::domain_error {"WARNING: ЧТЕНИЕ ФАЙЛОВ СЛОМАНО"};
    }

    ~RUNTIME_DATA() {
        delete[] data;
        delete[] list;
        delete[] free_list;
    }

    void reset() {
        this->~RUNTIME_DATA();
        new (this) RUNTIME_DATA{true};
    }

    void sort() {
        if (len == 0) throw std::domain_error{"RUNTIME_DATA::sort --> Array is empty, sir!"};
        for (size_t i = 0; i < len - 1; ++i) {
            for (size_t j = 0; j < len - i - 1; ++j) {
                if (*list[j] > *list[j+1]) {
                    ZOO* temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                }
            }
        }
    }

    void print_item() {
        std::wcout << L"\nВведите номер животины: ";
        int n = get_int();
        if (n < 1 || n > len)
            std::wcerr << L"Животины под таким номером нет!\n";
        else {
            std::wcout << L"Животина под номером " <<n<< L":\n\t";
            list[n-1]->printself();
        }
    }

    void print(bool diet_condition = false, FILE* dest=stdout, bool nums=true) const {
        for (size_t i = 0; i < len; ++i) {
            if (!diet_condition ||
                wcscmp(list[i]->diet_type, L"мясо") == 0 ||
                wcscmp(list[i]->diet_type, L"meat") == 0) {
                if (nums) std::wcout << i+1 << ". ";
                list[i]->printself(dest);
            }
        }
    }

    void new_item() {
        if (len == zoo_size - 1) {
            std::wcerr << L"Список переполнен\n";
        }

        ZOO* item;
        if (fri) {
            item = free_list[--fri];
            item->free_str();
        } else
            item = &data[len];


        std::wcout << L"Введите название животины: ";
        item->name = get_ws();

        std::wcout << L"Введите кличку/имя животины: ";
        item->nick = get_ws();

        std::wcout << L"Введите что жрёт: ";
        item->diet_type = get_ws();

        std::wcout << L"Введите сколько жрёт кг в день: ";
        fgetws(buffer, 128, stdin);
        item->diet_weight = wcstof(buffer, nullptr);

        std::wcout << L"Введите возраст: ";
        item->age = get_int();

        int n=0;
        while (n < len && *item > *list[n]) {
            ++n;
        }
        // n - итоговый индекс для item

        for (int i=(int)len; i > n; --i) {
            list[i] = list[i-1];
        }
        std::wcout << n+1 << L". " << item->nick << L" успешно добавлен!\n";

        list[n] = item;
        ++len;
    }

    void delete_item() {
        std::wcout << L"\nВведите номер провинившейся животины: ";
        const int n = get_int() - 1;
        ZOO* deleted = list[n];
        for (int i=n; i < len; ++i) {
            list[i] = list[i+1];
        }
        std::wcout << n+1 << L". " << deleted->nick << L" успешно удалён!\n";
        free_list[fri++] = deleted;
        --len;
    }
};

void show_options()  {
    std::wcout <<
    L"\n\n---   МЕНЮ   ---\n"
    " -1. Использовать стоковые данные\n"
    "  0 или Enter. Выход\n"
    "---   Манипуляции   ---\n"
    "  1. Добавить животное\n"
    "  2. Удалить животное по номеру\n"
    "---   Вывод   ---\n"
    "  3. Вывести животное по номеру\n"
    "  4. Вывести всех\n"
    "  5. Вывести мясожрунов\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    RUNTIME_DATA data{false};
    wchar_t buffer[buffer_size];
    while (1) {
        show_options();
        fgetws(buffer, buffer_size, stdin);
        int choice = wcstol(buffer, nullptr, 10);
        if (choice != 0)
            switch (choice) {
            case -1:
                    data.~RUNTIME_DATA();
                    new (&data) RUNTIME_DATA{true};
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
                    data.print(true);
                    break;
            default:
                    std::wcerr << L"Ахтунг: Такого выбора нет!\n";
            }
        else break;
    }
    std::wcerr << L"Выход...\n";
    FILE_c save{p_dynamic, L"w"};
    data.print(false, save.content, false);
    return 0;
}