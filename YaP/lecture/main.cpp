#include <iostream>
#include <locale>
using namespace std;

struct point {
    wchar_t * name;
    int age;
    point* next;
};

point* make_point(){
    point* p = new point;
    setlocale(0, "Russian");
    wchar_t buff[64];
    wcout << L"\nВведи имя: ";
    wcin >> buff;
    p->name = buff;
    wcout << L"\nВведи возраст: ";
    wcin >> p->age;
    p->next=nullptr;
    return p;
}

point* make_list(unsigned size) {
    point* beg=make_point();
    point* temp;

    for (unsigned i=0; i < size; i++) {
        temp = make_point();
        temp->next = beg;

        beg = temp;
    }
    return beg;
}

void print_point(point* p) {
    setlocale(0, "Russian");
    wcout << p->name << '\n';
    wcout << p->age << '\n';
    wcout << "- --- - --- - --- -\n";
}

unsigned print_list(point* const beg) {
    point *p = beg;
    unsigned count = 0;
    while (p) {
        print_point(p);
        p = p->next;
        ++count;
    }
    return count;
};

int main() {
     setlocale(0, "Russian");
    unsigned kalvo; cin >> kalvo;

    point* list = make_list(kalvo);
    print_list(list);
}