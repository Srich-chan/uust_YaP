#include <iostream>
#include <string>

using std::cin, std::cout, std::string;

typedef unsigned short num;

num M[10][4];
num types[8][2];
num count[8];
bool yeah;
bool proval;

bool check(num x, num y) {
    num type = M[x][y];
    if (x + types[type][0] > 10 || y + types[type][1] > 4)
        return false;
    for (num i = 0; i < types[type][0]; ++i)
        for (num j = 0; j < types[type][1]; ++j)
            if (M[x + i][y + j] != type)
                return false;
    return true;
}

string buffer;

int main() {
    num k;
    cin >> k;

    num curr = 0;
    for (num j = 3; j <= 4; ++j)
        for (num i = 1; i < 4; ++i) {
            types[curr][0] = j;
            types[curr][1] = i;
            ++curr;
        }

    types[7][0] = 3;
    types[7][1] = 3;

    for (num _i = 0; _i < k; ++_i) {
        for (num i = 0; i < 8; ++i) count[i] = 0;
        yeah = true;

        for (num x = 0; x < 10; ++x) {
            cin >> buffer;
            for (num y = 0; y < 4; ++y)
                M[x][y] = buffer[y] - '0';
        }

        for (num x = 0; x < 10; ++x)
            for (num y = 0; y < 4; ++y) {
                proval = check(x, y);
                count[M[x][y]] += proval;
                yeah &= proval;
            }

        cout << (yeah ? "YES\n" : "NO\n");
        for (num i = 0; i < 8; ++i) cout << count[i] << " ";
        cout << "\n";
    }
}
