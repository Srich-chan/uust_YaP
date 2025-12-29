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

    int t = 0, b = (int)m_side - 1;
    int l = 0, r = (int)m_side - 1;
    int idx = 0;

    while (t <= b && l <= r) {
        for (int i = l; i <= r; ++i)
            res[idx++] = A[i][t];
        t++;

        for (int i = t; i <= b; ++i)
            res[idx++] = A[r][i];
        r--;

        if (t <= b) {
            for (int i = r; i >= l; --i)
                res[idx++] = A[i][b];
            b--;
        }

        if (l <= r) {
            for (int i = b; i >= t; --i)
                res[idx++] = A[l][i];
            l++;
        }
    }
        for (int i = (int)(m_side * m_side) - 1; i >= 0; --i)
            printf("%c", res[i]);
        puts("");

        // СВОБОДА
        for (unsigned i = 0; i < m_side; ++i)
            delete[] A[i];
        delete[] A;
        delete[] res;

        return 0;
    }
