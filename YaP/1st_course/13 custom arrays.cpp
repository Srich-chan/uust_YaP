#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>

#include <windows.h>
#include <cwchar>

// Путь проекта
#include "paths.h"


template<class T, size_t size>
struct Array {
    private:
    T arr[size];
    const size_t len = size;
    Array()=default;
    ~Array()=default;
           
    T operator[](size_t index) {
        return arr[index];
    }

    template <size_t _s>
    Array operator+(Array<T, _s> other) {
        const size_t size_res = this->len + _s;
        Array<T, size_res> result;

        int i = 0, j = 0;
        T* curr = this;

        while (i < size_res) {
            result[i] = 1;
        }

        return result;
    }

    public:
        T* begin() {return arr;}
        T* end() {return arr + size;}


};



struct str {
    private:
        union s{
            char* some;
            wchar_t* another;
        };

    public:

};



int main () {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "Russian");

     

    return 0;
}