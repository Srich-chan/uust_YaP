#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <windows.h>


using namespace std;

// template <class T>
// class list {
//     class Node {
//         T value;
//         Node* prev=nullptr;
//         Node* next=nullptr;
//
//         void push() {
//
//         }
//
//         void delete_with_next() {
//             next->delete_with_next();
//             delete this;
//         }
//     };
//
//     Node* begin=nullptr;
//     Node* back=nullptr;
//     Node* end=nullptr;
// public:
// };

// class Footballer {
// public:
//     int number=0;
//     string name; // С инициалами
//     int way=0;
//     double time=0;
//     size_t goals_size=0;
//     vector<double> goals;
//     size_t danger_count=0;
// };

typedef tuple<int, wstring, int, double,
    size_t, vector<double>, size_t>
    Footballer;

wstring trim(wstring orig) {
    size_t i=0, j=orig.size()-1;
    while (orig[i] == L' ' || orig[i] == L'\t') ++i;
    while (orig[j] == L' ' || orig[j] == L'\t') --j;
    return orig.substr(i, j-i + 1);
}

class Team : vector<Footballer> {
public:
    using vector::vector;
    using vector::size;
    using vector::begin;
    using vector::end;

    Team (const string& file_name) {
        wifstream flist{file_name};
        if (!flist.is_open())
            throw domain_error{"Ti eblan?"};
        size_t count=0;

        while (!flist.eof()) {
            wchar_t buff[1024];

            flist.getline(buff, 1023, L';');
            int n = stoi(buff);

            flist.getline(buff, 1023, L';');
            wstring name = trim(buff);

            flist.getline(buff, 1023, L';');
            int way = stoi(buff);

            flist.getline(buff, 1023, L';');
            double time = stod(buff);

            flist.getline(buff, 1023, L';');
            size_t goals_size = stoull(buff);
            vector<double> goals;
            goals.reserve(goals_size);
            for (int i=0; i < goals_size; ++i) {
                flist.getline(buff, 1023, L';');
                goals[i] = stod(buff);
            }

            flist.getline(buff, 1023, L';');
            size_t warns = stoull(buff);
            emplace_back(n, name, way, time, goals_size, goals, warns);
        }

        wcout << "Введено "<<count<< " Футболлеров\n";

    }

    vector<Footballer> bench;
};



int main() {
    setlocale(0, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // wifstream file("12 Футболлеры.txt");
    Team s("12 Футболлеры.txt");
}