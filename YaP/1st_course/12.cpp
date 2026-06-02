#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <windows.h>
#include <string>
#include <memory>

using namespace std;

class Shit : public logic_error {
public:
    using std::logic_error::logic_error;
};


string trim(const string& orig) {
    size_t i=0, j=orig.size()-1;
    while (orig[i] == ' ' || orig[i] == '\t') ++i;
    while (orig[j] == ' ' || orig[j] == '\t') --j;
    return orig.substr(i, j-i + 1);
}

class Footballer {
public:
    int number=0;
    string name; // С инициалами
    int way=0;
    double time=0;
    size_t goals_size=0;
    vector<double> goals;
    size_t danger_count=0;

    Footballer (int a1, string&& a2, int a3, double a4, size_t a5, vector<double>&& a6, size_t a7)
    : number(a1), name(a2), way(a3), time(a4), goals_size(a5), goals{a6}, danger_count(a7) {}

    string str() const {
        return to_string(number) + " " + name;
    }
};

// Есть варик использовать map вместо vector
class Team : public vector<Footballer> {
public:
    using vector::operator=;
    using vector::vector;
    using vector::size;
    using vector::begin;
    using vector::end;

    Team (const string& file_name) {
        ifstream flist;
        flist.open(file_name);
        if (!flist.is_open())
            throw domain_error{"Check filepath"};
        char buff[1024];
        while (!flist.eof()) {
            if (flist.peek() == '#') {
                flist.getline(buff, 1023);
                continue;
            }

            flist.getline(buff, 1023, ';');
            if (trim(buff).empty()) break;
            int n = stoi(buff);

            flist.getline(buff, 1023, ';');
            string name = trim(buff);

            flist.getline(buff, 1023, ';');
            int way = stoi(buff);

            flist.getline(buff, 1023, ';');
            double time = stod(buff);

            flist.getline(buff, 1023, ';');
            size_t goals_size = stoull(buff);
            vector<double> goals;
            if (goals_size) goals.resize(goals_size);

            for (size_t i = 0; i < goals_size; ++i) {
                flist.getline(buff, 1023, ';');
                goals[i] = stod(buff);
            }

            flist.getline(buff, 1023);
            size_t warns = stoull(buff);

            emplace_back(n, std::move(name), way, time, goals_size, std::move(goals), warns);
        }

        sort_by_time();
        cout << "Введено "<<size()<< " Футболлеров\n";
    }

    Footballer& find_by_number(int number) {
        iterator it = begin();
        while (it != end()) {
            if (it->number == number)
                return *it;
            ++it;
        }
        throw Shit("find_by_number | There is no such player");
    }

    void play() const {
        size_t ots = 0;
        size_t curr = 0;

        array<int, 11> field;
        for (;curr < 11; ++curr) {
            field[curr] = at(curr).number;
        }

        // Начальный состав
        cout << "Первыми вышли на поле:\n";
        print_from(0, curr);
        cout << "\nНа скамейке сидят:\n";
        print_from(curr);

        // Этап меню
        int choice;
        char buff[128];
        bool stop = false;
        do {
            get_menu();
            cin.getline(buff, 128);
            choice = atoi(buff);

            switch (choice) {
                case -1:
                    stop = true;
                    break;
                case 0:
                    do {
                        for (int i = 0; i < 10; ++i) {
                            field[i + 1] = field[i];
                        }
                        field[0] = at(curr).number;
                        cout << "На " << at(curr).time << " минуте матча "
                                << at(curr).str() << " заменяет " << at(ots).str() + "\n";

                        ++curr;
                        ++ots;
                        if (curr == size()) {
                            break;
                        }
                    } while (at(curr).time == at(curr - 1).time);
                    break;
                case 1:
                    cout << "Игроки на поле:\n";
                    print_from(ots, curr);
                    break;
                case 2:
                    cout << "Игроки на скамейке:\n";
                    print_from(curr);
                    break;
                case 3:
                    if (!ots) {
                        cout << "Отстойник пуст!\n";
                    }
                    else {
                        cout << "Игроки в отстойнике:\n";
                        print_from(0, ots);
                    }
                    break;
                default:
                    cout << "Некорректный выбор\n";
                    cout << "Ещё раз!\n";

            }
        } while (!stop && curr < size());


        cout << "\nИгра закончена!\n";
    }



    void print_from(size_t strt, size_t end=-1, bool all=0) const {
        end = min(end, size());
        if (end - strt > 10 && !all) {
            for (size_t i = strt; i < strt + 3; ++i) {
                cout << "\t" + at(i).str() + "\n";
            }

            cout << "\t... " << end - strt - 6 << " футболлеров ...\n";

            for (size_t i = end - 3; i < end; ++i) {
                cout << "\t" + at(i).str() + "\n";
            }
        } else {
            for (size_t i = strt; i < end; ++i) {
                cout << "\t" + at(i).str() + "\n";
            }
        }
    }

private:
    void get_menu() const {
        cout <<
        "\n\n---    ИГРА    ---\n"
        "-1. Закончить игру\n"
        "0. Продолжить игру\n"
        "---    ВЫВОД    ---\n"
        "1. Игроки на поле\n"
        "2. Игроки на скамейке\n"
        "3. Игроки в отстойнике\n"
        "\nВыбор: ";
    }


    void sort_by_time() {
        for (int i = 0; i < size() - 1; ++i) {
            for (int j = 0; j < size() - i - 1; ++j) {
                if (at(j).time > at(j+1).time) {
                    std::swap(at(j), at(j+1));
                }
            }
        }
    }
};



int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Team team{ "C:/repos/user/CXX_projects/main_cmake/YaP/1st_course/12 Footballers.txt"};
    for (auto& [n, name, some, time, some2, vec, some3] : team) {
        // auto [n, name, some, some1, some2, vec, some3] = member;
        cout << n << " " << name << " " << time << '\n';
    }

    team.play();
}
