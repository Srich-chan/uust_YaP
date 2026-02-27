#include <cstdio>
#include <cmath>
#include <clocale>
#include <cstring>


int main() {
    setlocale(LC_ALL, "Russian");
    wprintf(L"Введите строку: ");
    char str[1024];
    scanf("%s", str);

    unsigned str_len = strlen(str);
    unsigned m_side = ceil(sqrt(str_len));
    // Определяется A, str_len, m_side
    char** A = new char*[m_side];

    for (unsigned i = 0, l = 0; i < m_side; ++i) {
        A[i] = new char[m_side + 1];
        for (unsigned j = 0; j < m_side; ++j)
            A[i][j] = l < str_len ? str[l++] : '#';
        A[i][str_len] = '\0';
    }

    printf("n = %u, len = %u\n", m_side, str_len);
    for (unsigned i = 0; i < m_side; ++i) {
        for (unsigned j = 0; j < m_side; ++j)
            printf("  %c", A[i][j]);
        printf("\n");
    }
    // C A[0][0] против часовой по спирали считывается строка, возвращается адрес массива
    char* res = new char[m_side * m_side + 1];

    // Объявление границ спирального обхода
    int top = 0, bottom = (int)m_side - 1;
    int left = 0, right = (int)m_side - 1;
    int idx = 0;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; ++i)
            res[idx++] = A[i][top];
        top++;
        for (int i = top; i <= bottom; ++i)
            res[idx++] = A[right][i];
        right--;
        if (top <= bottom) {
            for (int i = right; i >= left; --i)
                res[idx++] = A[i][bottom];
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; --i)
                res[idx++] = A[left][i];
            left++;
        }
    }

    for (int i = (int)(m_side * m_side) - 1; i >= 0; --i)
        printf("%c", res[i]);
    puts("");

    // Освобождение памяти
    for (unsigned i = 0; i < m_side; ++i)
        delete[] A[i];
    delete[] A;
    delete[] res;

    return 0;
}