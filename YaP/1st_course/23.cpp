#include <iostream>
#include <fstream>
#include <random>
#include "paths.h"
#include <map>

using namespace std;
mt19937 random(123);

int rand(int diap=50) {
    return int(random() % (2 * diap + 1)) - diap;
}

int main () {
    fstream file_A{p_PROJECT "23 A.txt"};
    fstream file_B{p_PROJECT "23 B.txt"};

    // Нужно гарантировать случай повтора числа, т.е. разброс меньше количества
    const int kolvo = 1000;
    for (int i = 0; i < kolvo; ++i) {
        file_A << rand(kolvo / 3) << " ";
    }
    file_A.seekg(0);

    map<int, int> count;
    vector<int> nums;
    while (!file_A.eof()) {
        int num;
        file_A >> num;
        map<int, int>::iterator fit = count.find(num);
        if (fit == count.end()) {
            count[num] = 1;
            nums.push_back(num);
        } else {
            ++count[num];
        }
    }

    for (int num : nums) {
        file_B << num;
        if (count[num] > 1)
            file_B << "*";
        file_B << " ";
    }

}