#include <iostream>
#include <locale>
#include <cwchar>
using namespace std;

struct point {
    wchar_t* name;
    int age;
    point* next;
};

point* make_point() {
    point* p = new point;

    wchar_t buff[64];
    wcout << L"\nВведи имя: ";
    wcin >> buff;

    p->name = new wchar_t[wcslen(buff) + 1];
    wcscpy(p->name, buff);

    wcout << L"\nВведи возраст: ";
    wcin >> p->age;
    p->next = nullptr;

    return p;
}

point* make_list(unsigned size) {
    if (size == 0) return nullptr;

    point* beg = make_point();
    point* temp;

    for (unsigned i = 1; i < size; i++) {
        temp = make_point();
        temp->next = beg;
        beg = temp;
    }
    return beg;
}

void print_point(point* p) {
    wcout << L"Имя: " << p->name << L'\n';
    wcout << L"Возраст: " << p->age << L'\n';
    wcout << L"- --- - --- - --- -\n";
}

unsigned print_list(point* const beg) {
    point* p = beg;
    unsigned count = 0;
    while (p) {
        print_point(p);
        p = p->next;
        ++count;
    }
    return count;
}

void del_list(point* beg) {
    point* temp;
    while (beg) {
        temp = beg;
        beg = beg->next;
        delete[] temp->name;
        delete temp;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    unsigned kalvo;
    wcout << L"Введите количество элементов: ";
    wcin >> kalvo;

    if (kalvo == 0) {
        wcout << L"Список пуст\n";
        return 0;
    }

    point* list = make_list(kalvo);
    wcout << L"\nСписок элементов:\n";
    print_list(list);

    del_list(list);

    return 0;
}