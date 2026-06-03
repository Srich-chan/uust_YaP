// #include <algorithm>
#include <iostream>
#include <fstream>
#include <locale>
#include <windows.h>
#include "paths.h"
#include <string>

#include <set>

using namespace std;

constexpr size_t buff_size = 10000;
#define m_FILE p_PROJECT "24.txt"
constexpr char* p_File = m_FILE;
constexpr wchar_t* wp_File = L"" m_FILE;

typedef pair<size_t, size_t> ind_pair;

class FILE_c
{
public:
    const wchar_t* name = nullptr;
    FILE* content = nullptr;

    explicit FILE_c(const wchar_t* file_name=wp_File, const wchar_t* Mode = L"r") {
        name = wcsdup(file_name);
        wchar_t mode_buffer[buff_size];
        _snwprintf(mode_buffer, buff_size, L"%ls, ccs=UTF-8", Mode);
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

size_t find_begin(const wstring& str, size_t right_pos) {
    if (str.size() <= right_pos)
        right_pos = str.size();
    if (right_pos == 0) return 0;

    size_t curr = right_pos - 1;
    while (curr != 0) {
        if (str[curr] == L' ')
            return curr + 1;
        --curr;
    }
    return 0;
}

size_t count_simbols(const wstring& str, const wstring& simbs, const ind_pair scope = {0, -1}) {
    if (simbs.empty() || str.empty()) return 0ULL;
    size_t end = min(str.size(), scope.second);
    size_t cnt = 0;
    for (size_t i = scope.first; i < end; ++i) {
        wchar_t c = towlower(str[i]);
        for (const wchar_t& s : simbs) {
            if (c == s) {
                ++cnt;
                break;
            }
        }
    }
    return cnt;
}

pair<wstring, size_t> find_and_count(const wstring& str, const wstring& simbs) {
    size_t comma = str.find(L",", 0);
    if (comma == -1)
        return {};

    ind_pair max_word = {find_begin(str, comma), comma};
    size_t max_count = count_simbols(str, simbs, max_word);

    while (true) {
        comma = str.find(L",", comma + 1);
        if (comma == str.npos)
            break;
        ind_pair curr_word = {find_begin(str, comma), comma};
        size_t count = count_simbols(str, simbs, curr_word);

        if (count > max_count) {
            max_count = count;
            max_word = curr_word;
        }
    }
    pair result = {str.substr(max_word.first, max_word.second - max_word.first), max_count};
    wcout << L"max_count = " <<max_count<< " | " << result.first << '\n';

    return result;
}


void wpl(const wstring& str) {
    wcout << str << '\n';
}


void to_lower(wstring& str) {
    for (wchar_t& c : str) {
        c = towlower(c);
    }
}

wstring simbolize(const wstring& orig) {
    size_t i=0, j=orig.size()-1;
    while (orig[i] == L' ' || orig[i] == L'\n') ++i;
    while (orig[j] == L' ' || orig[j] == L'\n') --j;

    wstring str = orig.substr(i, j-i + 1);
    to_lower(str);
    set<wchar_t> check;
    wstring final;

    for (wchar_t c : str)
        check.insert(c);

    for (wchar_t c : check) {
        final.push_back(c);
    }

    return final;
}

int main () {

    wchar_t buff[buff_size];
    FILE_c file = FILE_c{wp_File};
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "Russian");


    wcout << L"Введите символы: ";
    fgetws(buff, 32, stdin);
    wstring simbs = simbolize(buff);

    pair<wstring, size_t> max = {L"", 0};
    while (fgetws(buff, buff_size, file.content)){
        pair<wstring, size_t> curr = find_and_count(buff, simbs);
        if (max.second < curr.second) {
            max = curr;
        }
    }
    wcout << L"Результат для \"" <<simbs<< L"\" со счётом "<< max.second <<":\n\t"
            << max.first;
}

