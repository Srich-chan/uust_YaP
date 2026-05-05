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
//
class Footballer {
public:
    int number=0;
    string name; // С инициалами
    int way=0;
    double time=0;
    size_t goals_size=0;
    vector<double> goals;
    size_t danger_count=0;
    Footballer (int a1, string a2, int a3, double a4, size_t a5, vector<double> a6, size_t a7)
    : number(a1), name(a2), way(a3), time(a4), goals_size(a5), goals{a6}, danger_count(a7) {}
};



string trim(string orig) {
    size_t i=0, j=orig.size()-1;
    while (orig[i] == ' ' || orig[i] == '\t') ++i;
    while (orig[j] == ' ' || orig[j] == '\t') --j;
    return orig.substr(i, j-i + 1);
}

class Team : vector<Footballer> {
public:
    using vector::vector;
    using vector::size;
    using vector::begin;
    using vector::end;

    Team (const string& file_name) {
        ifstream flist;
        flist.open(file_name);
        if (!flist.is_open())
            throw domain_error{"Check filepath"};
        size_t count=0;
        char buff[1024];
        while (!flist.eof()) {
            if (flist.peek() == '#') {
                flist.getline(buff, 1023);
                continue;
            }

            flist.getline(buff, 1023, ';');
            cout << buff << '\n';
            if (trim(buff).empty()) throw runtime_error{"Check the file"};
            int n = stoi(buff);

            flist.getline(buff, 1023, ';');
            cout << buff << '\n';
            string name = trim(buff);

            flist.getline(buff, 1023, ';');
            cout << buff << '\n';
            int way = stoi(buff);

            flist.getline(buff, 1023, ';');
            cout << buff << '\n';
            double time = stod(buff);

            flist.getline(buff, 1023, ';');
            cout << buff << ' ';
            size_t goals_size = stoull(buff);
            cout << goals_size << '\n';
            vector<double> goals;
            if (goals_size) goals.resize(goals_size);

            for (size_t i = 0; i < goals_size; ++i) {
                flist.getline(buff, 1023, ';');
                cout << buff << "+++" << "\n";
                goals[i] = stod(buff);
            }

            flist.getline(buff, 1023, ';');
            cout << buff << '\n';
            size_t warns = stoull(buff);
            cout << "\n----------------\n";
            emplace_back(n, name, way, time, goals_size, goals, warns);
            ++count;
        }

        wcout << "Введено "<<count<< " Футболлеров\n";

    }

};


#include "paths.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

#include <iostream>
#include <windows.h>
#include <sstream>
#include <memory>

int main() {
    // Установка кодовой страницы консоли Windows на UTF-8
    SetConsoleOutputCP(65001); // CP_UTF8
    SetConsoleCP(65001);

    Team team{ "C:/repos/user/CXX_projects/main_cmake/YaP/1st_course/12 Footballers.txt"};
    for (auto& member : team) {
        // auto [n, name, some, some1, some2, vec,some3] = member;
        // cout << n << name << '\n';
    }
    cout << team.size();

    return 0;
}
