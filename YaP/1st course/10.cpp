#include <cstdio>
#include <cmath>
#include <clocale>
#include <cstring>

#define LOG 1


wchar_t ** gimme_matrix(const wchar_t * const &str) {
    unsigned len = wcslen(str);
    unsigned n = ceil(sqrt(len));
    wchar_t** A = new wchar_t *[n];

    for (int i=0, l=0; i < n; ++i) {
        A[i] = new wchar_t[n + 1];
        for (int j=0; j < n; ++j)
            A[i][j] = l < len ? str[l++] : L'#';
        A[i][n] = L'\0';
    }
#if LOG
    printf("n = %u, len = %u  \n", n ,len);
    for (int i=0; i < n; ++i) {
        for (int j=0; j < n; ++j) {
            wprintf(L"  %lc", A[i][j]);
        }
        wprintf(L"\n");
    }
#endif
    return A;
}

void free_matrix(const wchar_t ** &matrix, const unsigned n) {
    for (unsigned i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}
wchar_t * spiral(const wchar_t ** const &matrix, unsigned n) {
    wchar_t * res = new wchar_t[n * n + 1];
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    int idx = 0;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; ++i) {
            res[idx++] = matrix[top][i];
        }
        top++;

        for (int i = top; i <= bottom; ++i) {
            res[idx++] = matrix[i][right];
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; --i) {
                res[idx++] = matrix[bottom][i];
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                res[idx++] = matrix[i][left];
            }
            left++;
        }
    }

    res[idx] = L'\0';
    return res;
}


int main () {
    wchar_t str[1024], *res;
    wscanf(L"%s", str);
    auto A = gimme_matrix(str);
    res = spiral(A);

    wprintf(res);

    free_matrix(A);
}
